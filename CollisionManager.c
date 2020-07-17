#include "CollisionManager.h"

void CorrectGroundCollisionOverlapping(struct Player *player, Rectangle *groundRect){
    // Correct ovelapping collision with the ground or other enviromental props
    // checking with the ground
    if(CheckCollisionRecs(player->CollisionRect, *groundRect)){
        printf("%s\n", "Collison overlapping with the ground");
        // correct the overlap offset
        Rectangle overlapRect = GetCollisionRec(player->CollisionRect, *groundRect);
        player->Position.y -= overlapRect.height;
        printf("%s\n", "Corrected collision overlapping");
    }
}

void CorrectPipeCollision(struct Player *player, Rectangle *pipeRect){
    // Check if the colllision is occuring to right of left of player
    // Use that the collison rect's widht to correct the overlap
    if(CheckCollisionRecs(player->CollisionRect, *pipeRect)){
        printf("%s\n", "Collison overlapping with the pipe");
        // correct the overlap offset
        Rectangle overlapRect = GetCollisionRec(player->CollisionRect, *pipeRect);
        /* get the current player position and compare the current position of the
        overlapRect to see of it is less than (currentPlayePos + playerWidth/2) to
        decide if its either left/right of the player*/

        if(overlapRect.x < player->Position.x + (player->playerWidth/2)){
            //the collision rect is left to the player
            //now correct the collison
            player->Position.x += overlapRect.width;
        }
        else if(overlapRect.x > player->Position.x + (player->playerWidth/2)){
            //the collision rect is right to the player
            //now correct the collison
            player->Position.x -= overlapRect.width;
        }
        printf("%s\n", "Corrected collision overlapping");
    }
}
