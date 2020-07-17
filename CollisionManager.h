#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H
#include "Player.h"

void CorrectGroundCollisionOverlapping(struct Player *player, Rectangle *groundRect);
void CorrectPipeCollision(struct Player *player, Rectangle *pipeRect);

#endif
