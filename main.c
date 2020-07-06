//
//  main.c
//  Super Mario Clone
//
//  Created by phani srikar on 04/06/20.
//  Copyright © 2020 phani srikar. All rights reserved.
//

#include <stdio.h>
#include <raylib.h>

// MARK:- Macros
#define G -20  // WORLD GRAVITYra

// MARK:- Constants
const int screenWidth = 800;
const int screenHeight = 600;


// MARK:- Function Declarations
void DrawGround(Texture2D groundTex, int groundHeight);
void AnimateSpriteSheetRec(Texture2D spriteSheet, Rectangle *frameRec, int framesSpeed, int frames);

// MARK:- Structs
struct Player {
    int playerWidth;
    int playerHeight;
    Vector2 Velocity;
    Vector2 Position;
    Rectangle Rect;
};
// MARK:- Enums


int main() {
    InitWindow(screenWidth, screenHeight, "Mario clone");
    SetTargetFPS(60);

// Load Textures (Environment and player)
   Texture2D playerTex = (Texture2D)LoadTexture("Resources/Character/Mario Idle.png");
   Texture2D groundTex = (Texture2D)LoadTexture("Resources/Environment/Ground Tile.png");
   Texture2D brickTex = (Texture2D)LoadTexture("Resources/Environment/Bricks.png");
   Texture2D hillLargeTexture = (Texture2D)LoadTexture("Resources/Environment/HillLarge.png");
   Texture2D cloudSingleTexture = (Texture2D)LoadTexture("Resources/Environment/CloudSingle.png");
   Texture2D bushTripleTexture = (Texture2D)LoadTexture("Resources/Environment/BushTriple.png");
   Texture2D hillSmallTexture = (Texture2D)LoadTexture("Resources/Environment/HillSmall.png");
   Texture2D questionBlockTexture = (Texture2D)LoadTexture("Resources/Props/QuestionBlock.png");

//MARK:- Environment Variables
    Color marioSkyBlue = (Color){107,139,247};
    const int groundHeight = 0;

//MARK:- Player Variables
    struct Player player = {};
    player.playerWidth = playerTex.width;
    player.playerHeight = playerTex.height;
    player.Position.x = 370; // Arbitrary start position

// Camera Settings
   Camera2D camera = { 0 };
   camera.offset = (Vector2){ screenWidth/2, screenHeight/2 };
   camera.rotation = 0.0f;
   camera.zoom = 1.0f;

// Environment Object and props Rects
  Rectangle a_questionBlockRec_1;
  Rectangle brick_1 = (Rectangle){0,0, brickTex.width, brickTex.height};
  Rectangle a_questionBlockRec_2;








    while (!WindowShouldClose())
    {
        //Update

        // Camera Update
        camera.target = (Vector2){ player.Position.x + 20, player.Position.y + 20 };

        // Player Input
        if (IsKeyDown(KEY_RIGHT)) player.Position.x += 2 * 100 * GetFrameTime();
        else if (IsKeyDown(KEY_LEFT)) player.Position.x -= 2 * 100 * GetFrameTime();

        // Player Update
        player.Rect = (Rectangle){player.Position.x, player.Position.y, player.playerWidth, player.playerHeight};
        player.Position.y = 370;

        // Sprite Animations

        AnimateSpriteSheetRec(questionBlockTexture, &a_questionBlockRec_1, 20, 3);// Question Block 1
        AnimateSpriteSheetRec(questionBlockTexture, &a_questionBlockRec_2, 20, 3);// Question Block 2



        //Drawing
        BeginDrawing();

          ClearBackground(marioSkyBlue);
          BeginMode2D(camera);

          DrawFPS(0, 0);


          // Background elements
          DrawTexture(hillLargeTexture, 100, 530, RAYWHITE);
          DrawTexture(cloudSingleTexture, 360, 230, RAYWHITE);
          DrawTexture(bushTripleTexture, 500, 570, RAYWHITE);
          DrawTexture(hillSmallTexture, 630, 570, RAYWHITE);
          DrawTexture(cloudSingleTexture, 700, 200, RAYWHITE);


          // Ground
          DrawGround(groundTex, groundHeight);


          // Interactables and props
          DrawTextureRec(questionBlockTexture, a_questionBlockRec_1, (Vector2){600, 400}, WHITE);  // Draw part of the texture
          DrawTextureRec(brickTex, brick_1, (Vector2){700, 400}, WHITE);
          DrawTextureRec(questionBlockTexture, a_questionBlockRec_2, (Vector2){700 + brick_1.width, 400}, WHITE);


          // Player
          DrawTexture(playerTex, player.Position.x,player.Position.y, RAYWHITE);
          DrawRectangleLines(player.Position.x, player.Position.y, player.playerWidth, player.playerHeight, BLACK);

          // Enemies


          EndMode2D();

        EndDrawing();

    }

    CloseWindow();
    return 0;
}

void DrawGround(Texture2D groundTex, int groundHeight){
    int groundXIterations = (int)6000/(float)groundTex.width;
    int groundYIterations = 2;//(int)60/(float)groundTex.height; /* Use this logic you need tesselated sprites along the Y-Axis.*/

    //Ground for player
    for(int i = 0; i < groundYIterations ; i++)
    {
        DrawTexture(groundTex, groundTex.width * 0,((screenHeight - groundHeight) + (groundTex.height * i)), RAYWHITE);
        for(int j = 1; j < groundXIterations ; j ++)
        {
            DrawTexture(groundTex, groundTex.width * j,((screenHeight - groundHeight) + (groundTex.height * i)), RAYWHITE);
        }
    }
}

void AnimateSpriteSheetRec(Texture2D spriteSheet, Rectangle *frameRec, int framesSpeed, int frames){
  static float framesCounter = 0;
  static int currentFrame = 0;

  *frameRec = (Rectangle){ 0.0f, 0.0f, (float)spriteSheet.width/frames, (float)spriteSheet.height };

  framesCounter +=  GetFrameTime();

   if (framesCounter >= (float)framesSpeed/100)
   {
       framesCounter = 0;
       currentFrame++;

       if (currentFrame > frames - 1) currentFrame = 0;
   }
   frameRec->x = (float)currentFrame*(float)spriteSheet.width/frames;
}
