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

int main() {
    InitWindow(screenWidth, screenHeight, "Mario clone");
    SetTargetFPS(60);

// Load Textures (Environment and player)
   Texture2D playerTex = (Texture2D)LoadTexture("Resources/Character/Mario Idle.png");
   Texture2D groundTex = (Texture2D)LoadTexture("Resources/Environment/Ground Tile.png");
   Texture2D brickTex = (Texture2D)LoadTexture("Resources/Environment/Bricks.png");
   Texture2D hillLargeTexture_1 = (Texture2D)LoadTexture("Resources/Environment/HillLarge.png");
   Texture2D cloudSingleTexture_1 = (Texture2D)LoadTexture("Resources/Environment/CloudSingle.png");
   Texture2D bushTripleTexture_1 = (Texture2D)LoadTexture("Resources/Environment/BushTriple.png");
   Texture2D hillSmallTexture_1 = (Texture2D)LoadTexture("Resources/Environment/HillSmall.png");
   Texture2D questionBlockTexture_1 = (Texture2D)LoadTexture("Resources/Props/QuestionBlock.png");

//MARK:- Environment Variables
    Color marioSkyBlue = (Color){107,139,247};
    const int groundHeight = 0;

//MARK:- Player Variables
    struct Player player = {};
    player.playerWidth = playerTex.width;
    player.playerHeight = playerTex.height;
    player.Position.x = 370;

// Camera Settings
   Camera2D camera = { 0 };
   camera.offset = (Vector2){ screenWidth/2, screenHeight/2 };
   camera.rotation = 0.0f;
   camera.zoom = 1.0f;

// Environment
  Rectangle a_questionBlockRec;









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

        // Question Block 1
        AnimateSpriteSheetRec(questionBlockTexture_1, &a_questionBlockRec, 10, 3);


        //Drawing
        BeginDrawing();

          ClearBackground(marioSkyBlue);
          BeginMode2D(camera);

          DrawFPS(0, 0);


          // Background elements
          DrawTexture(hillLargeTexture_1, 100, 530, RAYWHITE);
          DrawTexture(cloudSingleTexture_1, 360, 230, RAYWHITE);
          DrawTexture(bushTripleTexture_1, 500, 570, RAYWHITE);
          DrawTexture(hillSmallTexture_1, 630, 570, RAYWHITE);
          DrawTexture(cloudSingleTexture_1, 700, 200, RAYWHITE);


          // Ground
          DrawGround(groundTex, groundHeight);


          // Interactables and props
          DrawTextureRec(questionBlockTexture_1, a_questionBlockRec, (Vector2){600, 400}, WHITE);  // Draw part of the texture


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
    int groundYIterations = 2;//(int)60/(float)groundTex.height;
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
