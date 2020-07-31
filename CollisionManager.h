#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H
#include "Player.h"

void CorrectGroundCollisionOverlapping(struct Player *player, Rectangle *groundRect);
void CorrectPipeCollision(struct Player *player, Rectangle *pipeRect);

/*
* Tile Based Colliosion System Utility Functions
* AABB - Axis Aligned Bounded Box
* we assume that the rectangle won't rotate and all the rectangles are Axis Alligned
*/
bool RayVsRect2D(const Vector2 ray_origin, const Vector2 ray_dir, const Rectangle targetRect, Vector2 *contact_point,Vector2 *contact_normal, float *near_contact_time, Vector2 probableContactPoints[]);
bool DynamicRectVsRect(const Rectangle sourceRect, const Vector2 sourceRectVelocity, const Rectangle targetRect, Vector2 *contact_point, Vector2 *contact_normal, float *near_contact_time, Vector2 probableContactPoints[]);

// helper functions
void SwapFloatValue(float *a, float *b);
void SwapIntValues(int *a, int *b);
float maxF(float num1, float num2);
float minF(float num1, float num2);
int maxI(int num1, int num2);
int minI(int num1, int num2);
float absF(float num);
int absI(int num);


#endif
