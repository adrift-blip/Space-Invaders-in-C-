// Started By Ayaan on 12th

#ifndef PF_FINAL_PROJECT_ALIEN_H
#define PF_FINAL_PROJECT_ALIEN_H
#include <raylib.h>

#include "Spaceship.h"
typedef struct Alien {
    Texture2D image;
    float aposx;
    float aposy;
    bool active;
    int type;
}Aliens;

void InitAlien();
void DrawAlien();
void DestroyAlien();
void MoveAlien();
void MoveDownAlien();
void AlienPewPew();
void MoveAlienBullet();
void MysteryAlienInit();
void DrawMysteryAlien();
void DestroyMysteryAlien();
void MoveMysteryAlien();
void CheckCollisionsWithBullets(Spaceship &ship);
void InitMysteryAlienTexture();
Rectangle GetAlienRect(const Alien &ali);
Rectangle GetMysteryAlienRect(const Alien &myst);
bool BossSpawner();
void ResetAlien();
#endif //PF_FINAL_PROJECT_ALIEN_H