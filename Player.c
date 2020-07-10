#include "Player.h"

// Game Mechanic Functions
void Jump(struct Player *player){
    const float timeOfAscent = 0.2;
    const float timeOfDescent = 0.6;

    static float ta = 0;

    if(player->state == Jumping){
        // Take a few frames to jump and do not do it instantaneously
        // make the jump occur to the heighest point over a few frames
        if(ta < timeOfAscent){
            printf("ta value is  : %f\n", ta);
            player->Velocity.y += GetFrameTime() * 100 * -0.2;
            ta += GetFrameTime();
        }
        else if(ta > timeOfAscent && ta < timeOfDescent){
            player->Velocity.y += GetFrameTime() * 100 * 0.2;
            ta += GetFrameTime();
        }
    }else{
        player->Velocity.y = 0;
        ta = 0;
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
