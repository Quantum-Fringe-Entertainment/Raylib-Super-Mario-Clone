#include "CollisionManager.h"

#define FALSE 0
#define TRUE 1

void CorrectGroundCollisionOverlapping(struct Player *player, Rectangle *groundRect){
    // Correct ovelapping collision with the ground or other enviromental props
    if(CheckCollisionRecs(player->CollisionRect, *groundRect)){
        printf("%s\n", "Collison overlapping with the ground");
        // correct the overlap offset
        Rectangle overlapRect = GetCollisionRec(player->CollisionRect, *groundRect);
        player->Position.y -= overlapRect.height;
        printf("%s\n", "Corrected collision overlapping");
        player->isGrounded = true;
        player->Velocity.y = 0;
        player->state = Idle;
    }
    else{
        player->isGrounded = false;
    }
}

void CorrectPipeCollision(struct Player *player, Rectangle *pipeRect){
    // Check if the colllision is occuring to right of left of player
    // Use that the collison rect's widht to correct the overlap
    static bool didCorrect = FALSE;
    if(CheckCollisionRecs(player->CollisionRect, *pipeRect)){
        didCorrect = FALSE;
        printf("%s\n", "Collison overlapping with the pipe");
        // Stop the player from moving further first
        player->Velocity.x = 0;
        // correct the overlap offset
        Rectangle overlapRect = GetCollisionRec(player->CollisionRect, *pipeRect);
        /*
        - Get the current player position and compare the current position of the
          overlapRect to see of it is less than (currentPlayePos + playerWidth/2) to
          decide if its either left/right of the player

        - Do this only if the player is not above the pipe (player y cord > pipe y cord),
          if he is above the pipe make him land on top of the pipe

         */
        if(player->Position.y < pipeRect->y){
            // didCorrect = TRUE;
            CorrectGroundCollisionOverlapping(player, pipeRect);
        }

        if(!didCorrect && player->Position.y > pipeRect->y){
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
        }
    }
    else didCorrect = TRUE;
}
