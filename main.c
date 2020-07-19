//
//  main.c
//  Super Mario Clone
//
//  Created by phani srikar on 04/06/20.
//  Copyright © 2020 phani srikar. All rights reserved.
//

// Header files hierarchy
/*
Player.h<--raylib.h && stdio.h
CollisionManager.h<--player.h
StateMachine.h<--player.h
*/
// Includes and libraries
#include "StateMachine.h"
#include "CollisionManager.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

// MARK:- Macros
#define G -6  // WORLD GRAVITY
#define QS_FRAME_RATE 40

// MARK:- Global Constants
const int screenWidth = 800;
const int screenHeight = 600;

// Function Declarations
//Core Mechanic Funcitons
void DrawGround(Texture2D groundTex, Rectangle *groundRect);

// Main Function
int main() {
    InitWindow(screenWidth, screenHeight, "Mario clone");
    SetTargetFPS(60);

    GuiSetStyle(DEFAULT, TEXT_SIZE, 14);
    GuiSetStyle(DEFAULT, BORDER_WIDTH, 2);
    GuiSetStyle(LABEL,TEXT_COLOR_PRESSED, 0x000000ff);
    GuiSetStyle(DEFAULT, BORDER_COLOR_PRESSED, 0x000000ff);
    GuiSetStyle(DEFAULT, TEXT_PADDING, 5);


    printf("The colour hex code is : %xN\n", ColorToInt(BLACK));


    // Load Textures
    // BG Elements
    Texture2D bushSingleTexture = (Texture2D)LoadTexture("Resources/Environment/BushSingle.png");
    Texture2D bushDoubleTexture = (Texture2D)LoadTexture("Resources/Environment/BushDouble.png");
    Texture2D bushTripleTexture = (Texture2D)LoadTexture("Resources/Environment/BushTriple.png");

    Texture2D cloudSingleTexture = (Texture2D)LoadTexture("Resources/Environment/CloudSingle.png");
    Texture2D clouDoubleTexture = (Texture2D)LoadTexture("Resources/Environment/CloudDouble.png");
    Texture2D cloudTripleTexture = (Texture2D)LoadTexture("Resources/Environment/CloudTriple.png");

    Texture2D groundTex = (Texture2D)LoadTexture("Resources/Environment/Ground Tile.png");

    Texture2D hillSmallTexture = (Texture2D)LoadTexture("Resources/Environment/HillSmall.png");
    Texture2D hillLargeTexture = (Texture2D)LoadTexture("Resources/Environment/HillLarge.png");
    // Interactables and props
    Texture2D questionBlockTexture = (Texture2D)LoadTexture("Resources/Props/QuestionBlock.png");
    Texture2D brickTex = (Texture2D)LoadTexture("Resources/Props/Bricks.png");
    Texture2D pipeSmallTex = (Texture2D)LoadTexture("Resources/Props/Pipe-1.png");
    Texture2D pipeMediumTex = (Texture2D)LoadTexture("Resources/Props/medium_pipe.png");
    Texture2D pipeLargeTex = (Texture2D)LoadTexture("Resources/Props/large_pipe.png");
    //Characters and Enemies
    Texture2D playerIdleTex = (Texture2D)LoadTexture("Resources/Characters/Mario Idle.png");
    Texture2D playerWalkingTex = (Texture2D)LoadTexture("Resources/Characters/Mario Walking.png");
    Texture2D playerJumpingTex = (Texture2D)LoadTexture("Resources/Characters/Mario Jump.png");

//MARK:- Environment Variables
    // Custom Colors
    Color marioSkyBlue = (Color){107,139,247};

    //MARK:- Player Variables
    struct Player player = {};
    player.Position.x = 1270; // Arbitrary start position
    player.Position.y = 600; // Arbitrary start position
    player.state = Idle; // Initial player state
    // Player Animaiton state spritesheets
    Texture2D playerSheets[] = {playerIdleTex, playerWalkingTex, playerJumpingTex};
    float timeOfAscent = 0.294f;
    float timeOfDescent = 0.623f;

    // Camera Settings
    Camera2D camera = { 0 };
    camera.offset = (Vector2){ screenWidth/2, screenHeight/2 + 200};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

// Environment Object and props Rects
    // BG Rects
    Rectangle groundRect = (Rectangle){0,0, groundTex.width, groundTex.height};
    // Props Rects
    Rectangle a_questionBlockRec_1;
    Rectangle a_questionBlockRec_2;
    Rectangle a_questionBlockRec_3;
    Rectangle a_questionBlockRec_4;

    Rectangle brickRec_1 = (Rectangle){0,0, brickTex.width, brickTex.height};
    Rectangle brickRec_2 = (Rectangle){0,0, brickTex.width, brickTex.height};
    Rectangle brickRec_3 = (Rectangle){0,0, brickTex.width, brickTex.height};

    Rectangle smallPipeRec_1 = (Rectangle){1000, 540, pipeSmallTex.width, pipeSmallTex.height};
    Rectangle mediumPipeRec_1 = (Rectangle){0, 0, pipeMediumTex.width, pipeMediumTex.height};
    Rectangle largePipeRec_1 = (Rectangle){0, 0, pipeLargeTex.width, pipeLargeTex.height};

    // Characters Rects

    //Debug Variables


    // Game Loop
    while (!WindowShouldClose())
    {
        //Update

        // Camera Update
        camera.target = (Vector2){ player.Position.x + 20, player.Position.y + 20 };

        // Player Input
        // move left right only if player is in Idle/Walking state
        if(player.state == Idle || player.state == Walking){
            if(IsKeyDown(KEY_LEFT)){
                player.Velocity.x = -2;
                player.state = Walking;
            }
            else if(IsKeyDown(KEY_RIGHT)){
                player.Velocity.x = 2;
                player.state = Walking;
            }
        }
        // Jump Input
        if(IsKeyPressed(KEY_SPACE)){
            printf("%s\n", "Started Jumping...");
            // Start Jumping
            player.state = Jumping;
        }
        // Base state (Idle) transition
        if(IsKeyUp(KEY_LEFT) && IsKeyUp(KEY_RIGHT) && player.state != Jumping){
            player.Velocity.x = 0;
            player.state = Idle;
        }



        // Player Update
        // update the player collision rect
        player.CollisionRect = (Rectangle){player.Position.x, player.Position.y, player.playerWidth, player.playerHeight};
        // Move Player based on Velocity Vector
        // multiple the veloctiy by the total time elapsed from the last frame and add it to the current position.
        player.Position.x += player.Velocity.x * GetFrameTime() * 100;
        player.Position.y += player.Velocity.y * GetFrameTime() * 100;
        // Manage Jump mechanics of the player here
        Jump(&player, &timeOfAscent, &timeOfDescent);

        //Correct the player's collisions overlapping with Environment
        CorrectGroundCollisionOverlapping(&player, &groundRect);
        CorrectPipeCollision(&player, &smallPipeRec_1);

        // Sprite Animations
        // props animations
        AnimateSpriteSheetRec(questionBlockTexture, &a_questionBlockRec_1, QS_FRAME_RATE, 3);// Question Block 1
        AnimateSpriteSheetRec(questionBlockTexture, &a_questionBlockRec_2, QS_FRAME_RATE, 3);// Question Block 2
        AnimateSpriteSheetRec(questionBlockTexture, &a_questionBlockRec_3, QS_FRAME_RATE, 3);// Question Block 3
        AnimateSpriteSheetRec(questionBlockTexture, &a_questionBlockRec_4, QS_FRAME_RATE, 3);// Question Block 4
        // Player animations
        AnimatePlayer(playerSheets, &player, 15, 3);


        //Drawing
        BeginDrawing();

            ClearBackground(marioSkyBlue);
            BeginMode2D(camera);

            // Background elements
            DrawTexture(hillLargeTexture, 100, 530, RAYWHITE);
            DrawTexture(cloudSingleTexture, 360, 230, RAYWHITE);
            DrawTexture(bushTripleTexture, 500, 570, RAYWHITE);
            DrawTexture(hillSmallTexture, 630, 570, RAYWHITE);
            DrawTexture(cloudSingleTexture, 700, 200, RAYWHITE);
            DrawTexture(bushSingleTexture, 800, 570, RAYWHITE);
            DrawTexture(cloudTripleTexture, 1000, 200, RAYWHITE);
            DrawTexture(hillLargeTexture, 1870, 530, RAYWHITE);
            DrawTexture(clouDoubleTexture, 1400, 200, RAYWHITE);
            DrawTexture(bushDoubleTexture, 1600, 570, RAYWHITE);
            DrawTexture(cloudSingleTexture, 1800, 210, RAYWHITE);

            DrawGround(groundTex, &groundRect); // Ground

            // Interactables and props
            DrawTextureRec(questionBlockTexture, a_questionBlockRec_1, (Vector2){600, 400}, WHITE);
            DrawTextureRec(brickTex, brickRec_1, (Vector2){700, 400}, WHITE);
            DrawTextureRec(questionBlockTexture, a_questionBlockRec_2, (Vector2){700 + brickTex.width, 400}, WHITE);
            DrawTextureRec(brickTex, brickRec_2, (Vector2){700 + brickTex.width + questionBlockTexture.width/3, 400}, WHITE);
            DrawTextureRec(questionBlockTexture, a_questionBlockRec_3, (Vector2){700 + (brickTex.width * 2) + questionBlockTexture.width/3, 400}, WHITE);
            DrawTextureRec(brickTex, brickRec_3, (Vector2){700 + (brickTex.width * 2) + (questionBlockTexture.width/3 * 2), 400}, WHITE);
            DrawTextureRec(questionBlockTexture, a_questionBlockRec_4, (Vector2){700 + (brickTex.width * 1) + (questionBlockTexture.width/3 * 1), 300}, WHITE);

            DrawTextureV(pipeSmallTex, (Vector2){smallPipeRec_1.x, smallPipeRec_1.y}, RAYWHITE);
            DrawTextureRec(pipeMediumTex, mediumPipeRec_1, (Vector2){1400, 510}, RAYWHITE);
            DrawTextureRec(pipeLargeTex, largePipeRec_1, (Vector2){1800, 470}, RAYWHITE);

            //Characters
            // Player
            DrawTextureRec(player.playerTexture, player.AnimatableRect, (Vector2){player.Position.x,player.Position.y}, RAYWHITE);

            // Enemies

            //Debug Stuff
            DrawRectangleLinesEx(groundRect, 4, RAYWHITE);
            DrawRectangleLinesEx(smallPipeRec_1, 2, YELLOW);
            // Player Collision Debug Rectangle
            DrawRectangleLinesEx(player.CollisionRect, 2, GREEN);
            DrawRectangleRec(GetCollisionRec(player.CollisionRect, groundRect), RED);
            DrawRectangleRec(GetCollisionRec(player.CollisionRect, smallPipeRec_1), RED);
            // PrintPlayerState(&player);

            EndMode2D();

            // On Screen Debug Stats
            DrawRectangleRounded((Rectangle){500,20,260,200}, 0.1f, 5, Fade(RED, 0.8));
            DrawText("Debug Stats", 520, 30, 18, BLACK);
            DrawText(FormatText("Current FPS is : %d", GetFPS()) , 520, 60, 14, BLACK);
            DrawText(FormatText("Player State is : %s", GetPlayerStateString(&player)) , 520, 90, 14, BLACK);
            timeOfAscent = GuiSliderBar((Rectangle){610,110,60,20}, "Time of Ascent", FormatText("TOA : %.3f", timeOfAscent), timeOfAscent, 0.001f, 0.5f);
            timeOfDescent = GuiSliderBar((Rectangle){610,140,60,20}, "Time of Descent", FormatText("TOD : %.3f", timeOfDescent), timeOfDescent, 0.001f, 1.0f);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

//Core Mechanic Funcitons
void DrawGround(Texture2D groundTex, Rectangle *groundRect){
    int groundXIterations = (int)3000/(float)groundTex.width;
    int groundYIterations = 2;//(int)60/(float)groundTex.height; /* Use this logic you need tesselated sprites along the Y-Axis.*/

    Vector2 position = (Vector2){0,0};
    //Ground for player
    for(int i = 0; i < groundYIterations ; i++){
        position = (Vector2){groundTex.width * 0,((screenHeight) + (groundTex.height * i))};
        DrawTexture(groundTex, position.x, position.y, RAYWHITE);
        for(int j = 1; j < groundXIterations ; j ++)
        {
            position = (Vector2){groundTex.width * j,((screenHeight) + (groundTex.height * i))};
            DrawTexture(groundTex, position.x, position.y, RAYWHITE);
        }
    }
    groundRect->x = 0;
    groundRect->y = position.y - groundTex.height;
    groundRect->width = position.x + groundTex.width;
    groundRect->height = 2 * groundTex.height;
}
