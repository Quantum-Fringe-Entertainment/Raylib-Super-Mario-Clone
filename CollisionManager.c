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


// helper functions
void SwapFloatValue(float *a, float *b){
    float t = *a;
    *a = *b;
    *b = t;
}
void SwapIntValues(int *a, int *b){
    register int t = *a;
    *a = *b;
    *b = t;
}
int maxI(int num1, int num2)
{
    return (num1 > num2 ) ? num1 : num2;
}
int minI(int num1, int num2)
{
    return (num1 > num2 ) ? num2 : num1;
}
float maxF(float num1, float num2)
{
    return (num1 > num2 ) ? num1 : num2;
}
float minF(float num1, float num2)
{
    return (num1 > num2 ) ? num2 : num1;
}
int absI(int num){
    return num < 0 ? -num : num;
}
float absF(float num){
    return num < 0 ? -num : num;
}

/*
    DESCRIPTION : A function to detect Collisions between a Ray and a Rectangle.
    - Also provides additonal data such as the contact point and contact normal and the probale collison points

    - PARAMETER ray_origin : A Vector2 defining the origin/start point of the Ray
    - PARAMETER rayA_dir : A Vector2 defining the direction of the Ray
    - PARAMETER targetRect : The target rectangle against which we are checking the collision
    - PARAMETER contact_point(Pointer) : A Vector2 that stores the contact point if the collision occurs with the rectangle
    - PARAMETER contact_normal(Pointer) : A Vector2 that stores the contact normal of the rectangle surface if the collision occurs with the rectangle
    - PARAMETER probableContactPoints : An array of Vector2's that stores the probale near and far contact points with the ray and rectanlge if the there is a chance of collision

    RETURNS : A bool indicating wether the collision has occured or not.
    - Also updates the contact_point, contact_normal and the probableContactPoints pointers

*/
bool RayVsRect2D(const Vector2 ray_origin, const Vector2 ray_dir, const Rectangle targetRect, Vector2 *contact_point,Vector2 *contact_normal, float *near_contact_time, Vector2 probableContactPoints[]){

    /*
    * The t in the P(t) = P + D.t
    * Where t is the parametric variable to plot the near collison point using the parametric line equation (P(t) = P + D.t)
    * Where P is the Position Vector of the Ray and D is the Direciton Vector of the Ray
    */
    float t_hit_near;

    /*
    * Calculate intersection points with rectangle bounding axes
    * Parametric 't' for Near (X,Y) and Far (X,Y)
    */
    float delta_t1_X = targetRect.x - ray_origin.x;
    float t_hit_near_X = (delta_t1_X / ray_dir.x);

    float delta_t1_Y = targetRect.y - ray_origin.y;
    float t_hit_near_Y = (delta_t1_Y / ray_dir.y);

    float delta_t2_X = targetRect.x + targetRect.width - ray_origin.x;
    float t_hit_far_X = (delta_t2_X / ray_dir.x);

    float delta_t2_Y = targetRect.y + targetRect.height - ray_origin.y;
    float t_hit_far_Y = (delta_t2_Y / ray_dir.y);

    /*
    * Sort the distances to maintain Affine uniformity
    * i.e. sort the near and far axes of the rectangle in the appropritate order from the POV of ray_origin
    */
    if (t_hit_near_X > t_hit_far_X) SwapFloatValue(&t_hit_near_X, &t_hit_far_X);
    if (t_hit_near_Y > t_hit_far_Y) SwapFloatValue(&t_hit_near_Y, &t_hit_far_Y);

    // As there is no chance of collision i.e the paramteric line cannot pass throguh the rectangle the probable points are empty
    probableContactPoints[0] = (Vector2){0, 0};
    probableContactPoints[1] = (Vector2){0, 0};

    /*
    * Check the order of the near and far points
    * if they satisfy the below condition the line will pass through the rectanle (It didn't yet)
    * if not return out of the function as it will not pass through
    */
    if(!(t_hit_near_X < t_hit_far_Y && t_hit_near_Y < t_hit_far_X)) return false;

    /*
    * If the parametric line passes through the rectangle calculate the parametric 't'
    * the 't' should be such that it must lie on both the Line/Ray and the Rectangle
    * Use the condition below to calculate the 'tnear' and 'tfar' that gives the near and far collison parametric t
    */
    *near_contact_time = maxF(t_hit_near_X, t_hit_near_Y);
    float t_hit_far = minF(t_hit_far_X, t_hit_far_Y);

    // Use the parametric t values calculated above and subsitute them in the parametric equation to get the near and far contact points
    float Hit_Near_X_Position = ray_origin.x + (ray_dir.x * (*near_contact_time));
    float Hit_Near_Y_Position = ray_origin.y + (ray_dir.y * (*near_contact_time));

    float Hit_Far_X_Position = ray_origin.x + (ray_dir.x * t_hit_far);
    float Hit_Far_Y_Position = ray_origin.y + (ray_dir.y * t_hit_far);

    // Debugging the calculations
    if(0){
    printf("The delta_t1_X is : %f | t_hit_near_X is : %f | ray_dir.x is : %f | rayOrigin.x is : %f | Hit_Near_X_Position is : %f \n", delta_t1_X, t_hit_near_X, ray_dir.x, ray_origin.x, Hit_Near_X_Position);
    printf("The delta_t1_Y is : %f | t_hit_near_Y is : %f | ray_dir.y is : %f | rayOrigin.y is : %f | Hit_Near_Y_Position is : %f \n", delta_t1_Y, t_hit_near_Y, ray_dir.y, ray_origin.y, Hit_Near_Y_Position);
    printf("t_hit_near is : %f \n", *near_contact_time);
    printf("The delta_t2_X is : %f | t_hit_far_X is : %f | ray_dir.x is : %f | rayOrigin.x is : %f | Hit_Far_X_Position is : %f \n", delta_t2_X, t_hit_far_X, ray_dir.x, ray_origin.x, Hit_Far_X_Position);
    printf("The delta_t2_Y is : %f | t_hit_far_Y is : %f | ray_dir.y is : %f | rayOrigin.y is : %f | Hit_Far_Y_Position is : %f \n", delta_t2_Y, t_hit_far_Y, ray_dir.y, ray_origin.y, Hit_Far_Y_Position);
    printf("t_hit_far is : %f \n", t_hit_far);
}

    // Generate Vectors using the near and far collision points
    Vector2 Near_Hit_Vector = (Vector2){Hit_Near_X_Position, Hit_Near_Y_Position};
    Vector2 Far_Hit_Vector = (Vector2){Hit_Far_X_Position, Hit_Far_Y_Position};
    // Since we are sure that the line will pass through the rectanle upadte the probable near and far points
    probableContactPoints[0] = Near_Hit_Vector;
    probableContactPoints[1] = Far_Hit_Vector;

    /*
    * Check wether the parametric 't' values are withing certain bounds to guarantee that the probable collision has actually occured
    * i.e. If the below conditions are true only then the Ray has passed through the Rectangle
    * if not it still can pass but it did not yet
    */
    if(t_hit_far < 0 || t_hit_near > 1) return false;

    // Now Update the actual contact point
    *contact_point = (Vector2){Hit_Near_X_Position, Hit_Near_Y_Position};

    // Update the contact normal of the Ray with the Rectangle surface
    if(t_hit_near_X > t_hit_near_Y){
        if(ray_dir.x < 0) *contact_normal = (Vector2){1, 0};
        else *contact_normal = (Vector2){-1, 0};
    }
    else if(t_hit_near_X < t_hit_near_Y){
        if(ray_dir.y < 0) *contact_normal = (Vector2){0, 1};
        else  *contact_normal = (Vector2){0, -1};
    }
    // Since the contact has definitely occured return true
    return true;
}
/*
    DESCRIPTION : A function to detect Collisions between a Dynamic Rectangle and a static Rectangle.
*/
bool DynamicRectVsRect(const Rectangle sourceRect, const Vector2 sourceRectVelocity, const Rectangle targetRect, Vector2 *contact_point, Vector2 *contact_normal, float *near_contact_time, Vector2 probableContactPoints[]){

    // if(sourceRectVelocity.x == 0 && sourceRectVelocity.y == 0){ return false; }
    // check te collisions agains the expanded target rectanle, useful to correct collisions based on contact time
    Rectangle expanded_target;
    expanded_target.x = targetRect.x - (sourceRect.width/2);
    expanded_target.y = targetRect.y - (sourceRect.height/2);
    expanded_target.width = targetRect.width + sourceRect.width;
    expanded_target.height = targetRect.height + sourceRect.height;

    Vector2 ray_or = (Vector2){sourceRect.x + (sourceRect.width/2), sourceRect.y + (sourceRect.height/2)};
    Vector2 ray_di = (Vector2){sourceRectVelocity.x, sourceRectVelocity.y};
    if(RayVsRect2D(ray_or, ray_di, expanded_target, contact_point, contact_normal, near_contact_time, probableContactPoints)){
        return true;
    }

    return false;
}
