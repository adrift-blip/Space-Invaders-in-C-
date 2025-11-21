// Started By Ayaan on the 12th
#include "Aliens.h"
#include "Bullets.h"
#include "Spaceship.h"
#include <cstdlib>
#include <time.h>
#include "raylib.h"
#include<iostream>
#include"GameData.h"
using namespace std;
const int row = 7, column = 8;
Alien alien[row][column]; //A 2D array of aliens
Bullet AlienBull[MAX_BULLETS]; //Array to store alien bullets
int AlienBulletIndex = 0;
Alien MysteryAlien;
Texture2D Alien1, Alien2, Alien3; //Different images for different aliens
Texture2D MysteryTexture;
void InitAlien()
{
    //Allows the array of aliens to be random each time
    srand(time(0));
    int startX = 50;
    int startY = 100;
    int spaceX = 50;
    int spaceY = 40;
    Alien1 = LoadTexture("Graphics/alien_1.png");
    Alien2 = LoadTexture("Graphics/alien_2.png");
    Alien3 = LoadTexture("Graphics/alien_3.png");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            alien[i][j].aposx = startX + j * spaceX; //Increment starting positions each time
            alien[i][j].aposy = startY + i * spaceY;
            alien[i][j].active = true;
            alien[i][j].type = (rand() % 3) + 1;
            switch (alien[i][j].type) {
                case 1: alien[i][j].image = Alien1;
                    break; //Loads the appropiate image
                case 2: alien[i][j].image = Alien2;
                    break;
                case 3: alien[i][j].image = Alien3;
                    break;
            }
        }
    }
}

void DrawAlien() { //Draws the aliens depending upon the type in the 2D array
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (alien[i][j].active)
                DrawTexture(alien[i][j].image, alien[i][j].aposx, alien[i][j].aposy, WHITE);
        }
    }
}

void MoveAlien() { //Moves the aliens
    int maxwidth = GetScreenWidth() - 1;
    int minwidth = 1;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (alien[i][j].active) {
                if (alien[i][j].aposx < maxwidth) {
                    alien[i][j].aposx += 0.75;
                }
                else {
                    alien[i][j].aposx = minwidth; //When aliens reach the end of the window make them appear from the other end
                }
            }
        }
    }
}

void AlienPewPew()
{
    //Function for aliens firing bullets
    srand(time(0));
    int activecounter = 0;
    for (int i = 0; i < row; i++) { //Checks which aliens are active
        for (int j = 0; j < column; j++) {
            if (alien[i][j].active == true) {
                activecounter++;
            }
        }
    }
    if (activecounter == 0) {//If none are active terminates
        return;
    }
    //Now finds a random alien among them
    int target = rand() % activecounter;
    int count = 0;
    int activeI = -1, activeJ = -1;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            //Checks which aliens are inactive and if it reaches the target
            if (!alien[i][j].active) //Also incase the selected alien becomes inactive
                continue;
            if (count == target){
                activeI = i;
                activeJ = j;
                break;
            }
            count++;
        }
        if (activeI != -1)
            break;
    }
    for (int i = 0; i < MAX_BULLETS; i++) {
        //Similar logic explained in the Bullets.cpp file to the spaceship bullets
        //The selected alien fires a new bullet
        Bullet &newAlienBullet = AlienBull[AlienBulletIndex];
        if (!newAlienBullet.status) {
            newAlienBullet.bposx = alien[activeI][activeJ].aposx + alien[activeI][activeJ].image.width / 2 - 2;
            newAlienBullet.bposy = alien[activeI][activeJ].aposy + alien[activeI][activeJ].image.height;
            newAlienBullet.status = true;
            AlienBulletIndex = (AlienBulletIndex + 1) % MAX_BULLETS;
            break;
        }
        else
            AlienBulletIndex = (AlienBulletIndex + 1) % MAX_BULLETS; //In case none of the next slots are active, loop back to start
    }
}

void MoveAlienBullet() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        Bullet &ab = AlienBull[i];
        if (ab.status) {
            ab.bposy += 4;
            DrawRectangle(ab.bposx, ab.bposy, 4, 10, {117, 122, 176, 255});
            if (ab.bposy > 770) //Eliminates the bullet if it reaches the yellow line
                ab.status = false;
        }
    }
}
//The two functions below are used to create invisible rectangles around the aliens and mystery alien to check for collisons
Rectangle GetAlienRect(const Alien &ali) {
    return Rectangle{ ali.aposx, ali.aposy, (float)ali.image.width, (float)ali.image.height };
}

Rectangle GetMysteryAlienRect(const Alien &myst) {
    return Rectangle{ myst.aposx, myst.aposy, (float)myst.image.width, (float)myst.image.height };
}

void CheckCollisionsWithBullets(Spaceship &ship) { //Checks collisions for aliens with player bullets
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (alien[i][j].active == true) {
                Rectangle AlienRect = GetAlienRect(alien[i][j]);
                for (int b = 0; b < MAX_BULLETS; b++) {
                    if (Tracker[b].status == true) {
                        Rectangle BulletRect = GetBulletRect(Tracker[b]);
                        if (CheckCollisionRecs(AlienRect, BulletRect)) {
                            Tracker[b].status = false;
                            alien[i][j].active = false;
                            //Different scores depending on alien type
                            if (alien[i][j].type == 1)
                                score += 50;
                            else if (alien[i][j].type == 2)
                                score += 80;
                            else
                                score += 125;
                        }
                    }
                }
            }
        }
    }
//Checks for mystery alien collsiion
    if (MysteryAlien.active == true) {
        Rectangle MysteryRect = GetMysteryAlienRect(MysteryAlien);
        for (int b = 0; b < MAX_BULLETS; b++) {
            if (Tracker[b].status == true) { //As mystery alien does not shoot anything we use spaceships bullets
                Rectangle BulletRect = GetBulletRect(Tracker[b]);
                if (CheckCollisionRecs(MysteryRect, BulletRect)) {
                    Tracker[b].status = false;
                    MysteryAlien.active = false;
                    lives++; //Killing the mystery alien gives a life
                }
            }
        }
    }
}
void InitMysteryAlienTexture() {
    MysteryTexture = LoadTexture("Graphics/mystery.png");
}

void MysteryAlienInit() {
    MysteryAlien.image = MysteryTexture;
    MysteryAlien.aposx = (rand() % 750) + 50;
    MysteryAlien.aposy = 30;
    MysteryAlien.active = true;
}

void DrawMysteryAlien() {
    if (MysteryAlien.active) {
        DrawTexture(MysteryAlien.image, MysteryAlien.aposx, MysteryAlien.aposy, WHITE);
    }
}

void MoveMysteryAlien() {
    if (!MysteryAlien.active) return;
    static float dx;
    static bool dirSet = false;
    if (!dirSet) {
        if (MysteryAlien.aposx < GetScreenWidth() / 2) {
            dx = 1.5;
        }
        else {
            dx = -1.5;
        }
        dirSet = true;
    }
    float dy = 0.7;
    MysteryAlien.aposx += dx;
    MysteryAlien.aposy += dy;
    if (MysteryAlien.aposx >= GetScreenWidth() - MysteryAlien.image.width ||
        MysteryAlien.aposx <= 0) {
        MysteryAlien.active = false;
        dirSet = false;
    }
}

void DestroyMysteryAlien() {
    UnloadTexture(MysteryTexture);
}

void DestroyAlien(){
    UnloadTexture(Alien1);
    UnloadTexture(Alien2);
    UnloadTexture(Alien3);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            alien[i][j].active = false;
        }
    }
}
bool BossSpawner() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (alien[i][j].active == true) {
                return false;
            }
        }
    }
    return true;
}
void ResetAlien() {
    srand(time(0));
    int startX = 50;
    int startY = 100;
    int spaceX = 50;
    int spaceY = 40;
    Alien1 = LoadTexture("Graphics/alien_1.png");
    Alien2 = LoadTexture("Graphics/alien_2.png");
    Alien3 = LoadTexture("Graphics/alien_3.png");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            alien[i][j].aposx = startX + j * spaceX;
            alien[i][j].aposy = startY + i * spaceY;
            alien[i][j].active = true;
            alien[i][j].type = (rand() % 3) + 1;
            switch (alien[i][j].type) {
                case 1: alien[i][j].image = Alien1; break;
                case 2: alien[i][j].image = Alien2; break;
                case 3: alien[i][j].image = Alien3; break;
            }
        }
    }
    for (int i = 0; i < MAX_BULLETS; i++) {
        AlienBull[i].status = false;
    }
}