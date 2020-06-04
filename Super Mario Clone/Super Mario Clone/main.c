//
//  main.c
//  Super Mario Clone
//
//  Created by phani srikar on 04/06/20.
//  Copyright © 2020 phani srikar. All rights reserved.
//

#include <stdio.h>
#include <raylib.h>



int main(int argc, const char * argv[]) {
   
    const int screenWidth = 800;
    const int screenHeight = 600;
    const int playerWidth = 50;
    const int playerHeight = 100;
    
    InitWindow(screenWidth, screenHeight, "Mario clone");
    SetTargetFPS(900);
    
    
    Color marioSkyBlue = (Color){107,139,247};
    Color testGround = (Color){231,91,52,255};
    Color playerColor = (Color){254,240,79,255};
    
    Texture2D groundBrick = LoadTexture("./Resources/Bricks.gif");

    while (!WindowShouldClose())
    {
        // Events and Input handling
        
        // Physics
        
        //Drawing

        BeginDrawing();
        ClearBackground(marioSkyBlue);
        DrawFPS(0, 0);
       
        //Ground for player
        DrawRectangle(0, 400, screenWidth, 100,testGround);
        DrawTexture(groundBrick, 0, 0, RAYWHITE);

        //Collisions
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
