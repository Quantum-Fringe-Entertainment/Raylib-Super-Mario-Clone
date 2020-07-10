#include "StateMachine.h"

void AnimatePlayer(Texture2D spriteSheet, struct Player *player, int frameSpeed, int frames){
    static float framesCounterP = 0;
    static int currentFrameP = 3;

    switch (player->state) {
        case Idle: {
            break;
        }
        case Walking: {
            player->AnimatableRect = (Rectangle){ 0.0f, 0.0f, (float)spriteSheet.width/frames, (float)spriteSheet.height };

            framesCounterP +=  GetFrameTime();

            if (framesCounterP >= (float)frameSpeed/100){
            framesCounterP = 0;
            currentFrameP--;

            if (currentFrameP < 1) currentFrameP = 3;
            }
            player->AnimatableRect.x = (float)currentFrameP*(float)spriteSheet.width/frames + 1.4;
            break;
        }
        case Jumping: {
            break;
        }
        case Ducking: {
            break;
        }
        case Skiding: {
            break;
        }
        case Climbing: {
            break;
        }
        case Swimming: {
            break;
        }
    }
}
