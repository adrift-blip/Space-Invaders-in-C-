//
// Created by hamda on 11/16/2025.
//
#include<raylib.h>
#include "Spaceship.h"
#include<conio.h>
#include"Bullets.h"
#include"Aliens.h"
#include<iostream>
#include"Boss.h"
#include"GameData.h"
using namespace std;
void InitSpaceship(Spaceship &ship) { //Initializes the spaceship
    ship.image_s = LoadTexture("Graphics/spaceship.png");
    ship.sposx = (GetScreenWidth() - ship.image_s.width) / 2;
    ship.sposy = GetScreenHeight() - ship.image_s.height - 100; //Coordinates are at the bottom and centred
}
void DrawSpaceship(const Spaceship &ship) { //Draws the spaceship
    DrawTexture(ship.image_s, ship.sposx, ship.sposy, WHITE);
}
void CleanupSpaceship(Spaceship &ship) { //Unloads texture of spaceship from VRAM
    UnloadTexture(ship.image_s);
}
void UpdateSpaceship(Spaceship &ship) {
    if (IsKeyDown(KEY_LEFT)) { //Raylib functions are used instead of conio as raylib disables consol input output
        ship.sposx -= 7;
        if(ship.sposx < 25) {
            ship.sposx = 25;
        }
    }
    else if (IsKeyDown(KEY_RIGHT)) {
        ship.sposx += 7;
        if(ship.sposx > GetScreenWidth() - ship.image_s.width - 25) { //Prevents spaceship from moving out of bounds
            ship.sposx = GetScreenWidth() - ship.image_s.width - 25;
        }
    }
}
void CheckSpaceship(Spaceship &ship) { //Checks for collisions with player between bullets by aliens or boss
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (AlienBull[i].status == true) {
            Rectangle shipRect = SpaceshipBox(ship);
            Rectangle AlienBullRec = GetBulletRect(AlienBull[i]);
            if (CheckCollisionRecs(shipRect, AlienBullRec)) {
                if (lives == 0) {
                    exit;
                }
                lives--;
                AlienBull[i].status = false;
            }
        }
        if (BossTracker[i].status == true) {
            Rectangle shipRect = SpaceshipBox(ship);
            Rectangle BossBullRec = GetBulletRect(BossTracker[i]);
            if (CheckCollisionRecs(shipRect, BossBullRec)) {
                if (lives == 0) {
                    exit;
                }
                lives -= 2; //Boss deletes 2 lives
                BossTracker[i].status = false;
            }
        }
    }
}
Rectangle SpaceshipBox(Spaceship &ship) { //Creates an invisible rectangle to check for collisions
    Rectangle rect = { (float)ship.sposx, (float)ship.sposy, (float)ship.image_s.width, (float)ship.image_s.height };
    return rect;
}
void ResetSpaceship(Spaceship &ship) { //Resets the spaceship to original position
    ship.sposx = (GetScreenWidth() - ship.image_s.width) / 2;
    ship.sposy = GetScreenHeight() - ship.image_s.height - 100;
}
