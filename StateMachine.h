#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include<raylib.h>
#include "Player.h"

void AnimatePlayer(Texture2D spriteSheet, struct Player *player, int framespeed, int frames);

#endif
