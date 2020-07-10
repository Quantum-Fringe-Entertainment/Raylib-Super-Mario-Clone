#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H
#include "Player.h"

void AnimatePlayer(Texture2D spriteSheet, struct Player *player, int framespeed, int frames);
void AnimateSpriteSheetRec(Texture2D spriteSheet, Rectangle *frameRec, int framesSpeed, int frames);
// Debug Functions
const char* GetPlayerStateString(struct Player *player);

#endif
