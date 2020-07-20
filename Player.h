#ifndef PLAYER_H
#define PLAYER_H
#include <stdio.h>
#include<raylib.h>

enum Direction{
    LEFT = -1,
    RIGHT =
};

enum PlayerStates{
// Animatable States
    Idle = 0,
    Walking,
    Jumping,
    Ducking,
    Skiding,
    Climbing,
    Swimming,
// Non-Animatable States
};
struct Player {
    int playerWidth;
    int playerHeight;
    bool isJumping;

    Vector2 Position;
    Vector2 Velocity;

    Rectangle AnimatableRect;
    Rectangle CollisionRect;

    Texture2D playerTexture;

    enum PlayerStates state;
    enum Direction dir;
};

// Game Mechanic Functions
void Jump(struct Player *player, float *timeOfAscent, float *timeOfDescent);
void Gravity(struct Player *player, float *timeOfDescent);
//Debug Functions
void PrintPlayerState(struct Player *player);
#endif
