#include "Player.h"
// float timeOfAscent = 0.18f;
// Game Mechanic Functions
void Jump(struct Player *player, float *timeOfAscent, float *timeOfDescent){
    static float ta = 0;

    if(player->state == Jumping){
        // Take a few frames to jump and do not do it instantaneously
        // make the jump occur to the heighest point over a few frames
        if(ta < *timeOfAscent){
            player->Velocity.y += GetFrameTime() * 100 * -0.3f;
            ta += GetFrameTime();
        }
        else if(ta > *timeOfAscent && ta < *timeOfDescent){
            player->Velocity.y += GetFrameTime() * 100 * 0.5f;
            ta += GetFrameTime();
        }
        // Enable movement while jumping
        if(IsKeyDown(KEY_LEFT)){
            player->Velocity.x = -2;
            player->dir = LEFT;
        }
        else if(IsKeyDown(KEY_RIGHT)){
            player->Velocity.x = 2;
            player->dir = RIGHT;
        }
    }
    else{
        player->Velocity.y = 2;
        ta = 0;
    }
}

void Gravity(struct Player *player, float *timeOfDescent){
    static float td = 0;

    if(td< *timeOfDescent){
        player->Velocity.y += GetFrameTime() * 100 * 0.5f;
        td += GetFrameTime();
    }
    else{
        player->Velocity.y = 0;
        td = 0;
    }
}


//Debug Functions
void PrintPlayerState(struct Player *player){
    switch (player->state) {
        case Idle: {
            printf("The Player State is : Idle\n");
            break;
        }
        case Walking: {
            printf("The Player State is : Walking\n");
            break;
        }
        case Jumping: {
            printf("The Player State is : Jumping\n");
            break;
        }
        case Ducking: {
            printf("The Player State is : Ducking\n");
            break;
        }
        case Skiding: {
            printf("The Player State is : Skiding\n");
            break;
        }
        case Climbing: {
            printf("The Player State is : Climbing\n");
            break;
        }
        case Swimming: {
            printf("The Player State is : Swimming\n");
            break;
        }
    }
}
