//
// Created by hamda on 11/16/2025.
//

#ifndef PF_FINAL_PROJECT_SPACESHIP_H
#define PF_FINAL_PROJECT_SPACESHIP_H
typedef struct Spaceship {
    Texture2D image_s;
    int sposx;
    int sposy;
} Spaceship;
void InitSpaceship(Spaceship &ship);
void DrawSpaceship(const Spaceship &ship);
void CleanupSpaceship(Spaceship &ship);
void FireBullet();
void UpdateSpaceship(Spaceship &ship);
void CheckSpaceship(Spaceship &ship);
Rectangle SpaceshipBox(Spaceship &ship);
void ResetSpaceship(Spaceship &ship);
#endif //PF_FINAL_PROJECT_SPACESHIP_H