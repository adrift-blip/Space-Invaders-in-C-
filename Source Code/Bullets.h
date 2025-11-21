
//
// Created by hamda on 11/16/2025.
//
#include "raylib.h"
#ifndef PF_FINAL_PROJECT_BULLETS_H
#define PF_FINAL_PROJECT_BULLETS_H
struct Spaceship;
const int MAX_BULLETS = 100;
struct Bullet {
    float bposx = 0;
    float bposy = 0;
    bool status = false;
};
//The extern keyword while not in our syllabus is necessary here to prevent linker errors
//The extern keyword tells the compiler that the arrays are defined somewhere else when main tries to run the functions
extern Bullet Tracker[MAX_BULLETS];
extern Bullet AlienBull[MAX_BULLETS];
extern Bullet BossTracker[MAX_BULLETS];
extern int AlienBulletIndex;
void FireBullet(Spaceship &ship);
void MoveBullet();
void ResetBullets();
Rectangle GetBulletRect(const Bullet &blt);

#endif //PF_FINAL_PROJECT_BULLETS_H