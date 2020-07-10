#include "CollisionManager.h"

void CorrectCollisionOverlapping(struct Player *player, Rectangle *groundRect){
    // Correct ovelapping collision with the ground or other enviromental props
    // checking wihth the ground
    if(CheckCollisionRecs(player->CollisionRect, *groundRect)){
        printf("%s\n", "Collison overlapping with the ground");
        // correct the overlap offset
        Rectangle overlapRect = GetCollisionRec(player->CollisionRect, *groundRect);
        player->Position.y -= overlapRect.height;
        printf("%s\n", "Corrected collision overlapping");
    }
}
