#ifndef PLAYER_H
#define PLAYER_H
#include <stdio.h>
#include<raylib.h>

enum PlayerStates{
    Idle = 0,
    Walking,
    Jumping,
    Ducking,
    Skiding,
    Climbing,
    Swimming
};
struct Player {
    int playerWidth;
    int playerHeight;
    Vector2 Position;
    Vector2 Velocity;
    Rectangle AnimatableRect;
    Rectangle CollisionRect;
    enum PlayerStates state;
};

// Game Mechanic Functions
void Jump(struct Player *player);

//Debug Functions
void PrintPlayerState(struct Player *player);
#endif
