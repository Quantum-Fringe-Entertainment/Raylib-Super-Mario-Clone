//
//  main.c
//  Super Mario Clone
//
//  Created by phani srikar on 04/06/20.
//  Copyright © 2020 phani srikar. All rights reserved.
//

#include <stdio.h>
#include <raylib.h>

const int screenWidth = 800;
const int screenHeight = 600;

void DrawGround(Texture2D groundTex, int groundHeight);

int main(int argc, const char * argv[]) {
   

    const int playerWidth = 50;
    const int playerHeight = 100;
    const int ballSpeed = 4;
    const int groundHeight = 100;
    
    InitWindow(screenWidth, screenHeight, "Mario clone");
      SetTargetFPS(900);
    
    Color marioSkyBlue = (Color){107,139,247};
    Color testGround = (Color){231,91,52,255};
    Color playerColor = (Color){254,240,79,255};
    
    
    Vector2 playerPos = {0,0};
    Vector2 camOffset = {0,0};
    Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };
    //Define the 2D camera here
    Camera2D mainCam2D = (Camera2D){camOffset,ballPosition,0,1};

    Texture2D groundBrick = LoadTexture("/Users/phanisrikar/Desktop/Brick.png");

    while (!WindowShouldClose())
    {
        // Events and Input handling
        if(IsKeyDown(KEY_RIGHT))
            ballPosition.x += ballSpeed * 100.0f * GetFrameTime();
        if(IsKeyDown(KEY_LEFT))
        ballPosition.x -= ballSpeed * 100.0f * GetFrameTime();
        // Physics
        
        //Drawing
        BeginMode2D(mainCam2D);

        BeginDrawing();
        ClearBackground(marioSkyBlue);
        DrawFPS(0, 0);
        
        DrawGround(groundBrick,groundHeight);
        DrawCircleV(ballPosition, 50, MAROON);

        //Collisions
        
        
        EndDrawing();
        EndMode2D();
    }

    CloseWindow();
    return 0;
}

void DrawGround(Texture2D groundTex, int groundHeight){
    int groundXIterations = (int)screenWidth/(float)groundTex.width;
    int groundYIterations = (int)screenHeight/(float)groundTex.height;
    //Ground for player
    for(int i = 0; i < groundYIterations ; i++)
    {
        for(int j = 0; j < groundXIterations ; j ++)
        {
            DrawTexture(groundTex, groundTex.width * j,((screenHeight - groundHeight) + (groundTex.height * i)), RAYWHITE);
        }
    }
}
