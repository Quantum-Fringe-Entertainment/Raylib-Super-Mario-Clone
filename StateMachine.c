#include "StateMachine.h"

void AnimatePlayer(Texture2D spriteSheets[], struct Player *player, int frameSpeed, int frames){
    static float framesCounterP = 0;
    static int currentFrameP = 3;

    Texture2D spriteSheet = spriteSheets[player->state];

    switch (player->state) {
        case Idle: {
            player->AnimatableRect = (Rectangle){ 0.0f, 0.0f, (float)spriteSheet.width, (float)spriteSheet.height };
            player->playerTexture = spriteSheets[player->state];
            player->playerWidth = (float)spriteSheet.width;
            player->playerHeight = (float)spriteSheet.height;
            break;
        }
        case Walking: {
            player->AnimatableRect = (Rectangle){ 0.0f, 0.0f, (float)spriteSheet.width/frames, (float)spriteSheet.height };
            player->playerTexture = spriteSheets[player->state];
            player->playerWidth = (float)spriteSheet.width / 3;
            player->playerHeight = (float)spriteSheet.height;

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
            player->AnimatableRect = (Rectangle){ 0.0f, 0.0f, (float)spriteSheet.width, (float)spriteSheet.height };
            player->playerTexture = spriteSheets[player->state];
            player->playerWidth = (float)spriteSheet.width;
            player->playerHeight = (float)spriteSheet.height;
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

void AnimateSpriteSheetRec(Texture2D spriteSheet, Rectangle *frameRec, int framesSpeed, int frames){
    static float framesCounter = 0;
    static int currentFrame = 0;

    *frameRec = (Rectangle){ 0.0f, 0.0f, (float)spriteSheet.width/frames, (float)spriteSheet.height };

    framesCounter +=  GetFrameTime();

    if (framesCounter >= (float)framesSpeed/100){
        framesCounter = 0;
        currentFrame++;

        if (currentFrame > frames - 1) currentFrame = 0;
    }
    frameRec->x = (float)currentFrame*(float)spriteSheet.width/frames;
}

// Debug Functions
const char* GetPlayerStateString(struct Player *player){
    switch (player->state) {
        case Idle: {
            return "Idle";
        }
        case Walking: {
            return "Walking";
        }
        case Jumping: {
            return "Jumping";
        }
        case Ducking: {
            return "Ducking";
        }
        case Skiding: {
            return "Skiding";
        }
        case Climbing: {
            return "Climbing";
        }
        case Swimming: {
            return "Swimming";
        }
    }
}
