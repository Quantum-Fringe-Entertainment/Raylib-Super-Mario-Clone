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
#define G -20
#define MAX_BUILDINGS   100

// MARK:- Constants
const int screenWidth = 800;
const int screenHeight = 600;


// MARK:- Function Declarations
void DrawGround(Texture2D groundTex, int groundHeight);

// MARK:- Structs
struct Player {
    const int playerWidth;
    const int playerHeight;
    Vector2 Velocity;
    Vector2 Position;
    Rectangle Rect;
};
typedef struct Player Player;

int main() {
   

    
    const int ballSpeed = 4;
    const int groundHeight = 50;
    InitWindow(screenWidth, screenHeight, "Mario clone");
    SetTargetFPS(62);
    
    
//MARK:- Environment Variables
    Color marioSkyBlue = (Color){107,139,247};
       
//MARK:- Player Variables
    
     Player player = {};
    
    
   Camera2D camera = { 0 };
   camera.target = (Vector2){ player.Position.x + 20, player.Position.y + 20 };
   camera.offset = (Vector2){ screenWidth/2, screenHeight/2 };
   camera.rotation = 0.0f;
   camera.zoom = 1.0f;

    Texture2D groundTex = (Texture2D)LoadTexture("/Users/phanisrikar/Documents/Raylib Stuff/Raylib-Super-Mario-Clone/Super Mario Clone/Assets/Brick.png");
    
//    Texture2D groundTex = (Texture2D)LoadTexture("Assets/Brick.png");
    
    
    while (!WindowShouldClose())
    {
        //Update
        camera.target = (Vector2){ player.Position.x + 20, player.Position.y + 20 };
        if (IsKeyDown(KEY_RIGHT)) player.Position.x += 4 * 100 * GetFrameTime();
        else if (IsKeyDown(KEY_LEFT)) player.Position.x -= 4 * 100 * GetFrameTime();

        //Drawing
        BeginMode2D(camera);
        BeginDrawing();
        ClearBackground(marioSkyBlue);
        DrawFPS(0, 0);
        
        
        DrawGround(groundTex, groundHeight);
        DrawRectangleRec(player.Rect, RED);
        DrawCircleV((Vector2){0,0}, 50, MAROON);
        
        EndMode2D();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void DrawGround(Texture2D groundTex, int groundHeight){
    int groundXIterations = (int)6000/(float)groundTex.width;
    int groundYIterations = (int)6000/(float)groundTex.height;
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
