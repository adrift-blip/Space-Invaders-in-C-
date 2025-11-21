//
// Created by ahmed on 17/11/2025.
//
#include "Boss.h"
#include <raylib.h>
#include <conio.h>
#include "Bullets.h"
#include <math.h>
#include"GameData.h"
Bullet BossTracker[MAX_BULLETS];
int CurrentBossBullet = 0;
void InitBoss(Boss &boss) //Initializes the boss
{
    boss.picture = LoadTexture("Graphics/Boss.png");
    boss.Boposx = (GetScreenWidth() - boss.picture.width)/2;
    boss.Boposy = 50;
}
void DrawBoss(const Boss &boss) { //Draws the boss only if its active
    if (boss.status)
    DrawTexture(boss.picture, boss.Boposx, boss.Boposy, WHITE);
}
void CleanupBoss(Boss &boss) { //Cleansup the loaded image from VRAM
    UnloadTexture(boss.picture);
}
void UpdateBossPosition(Boss &boss) { //Moves the boss from left to right
    int newBoposx = boss.Boposx;
    const int movementRange = GetScreenWidth() - boss.picture.width; //Boss's movement range
    //The static keyword makes sure the variables retain their values during multiple function calls
    static bool right = true;
    static bool left = false;
    if (right) {
            newBoposx += 2;
        if (newBoposx>=movementRange){ //If boss reaches the right end move it left
            right = false;
            left = true;
            newBoposx = movementRange;
        }
    }
    else if (left) { //Vice versa
        newBoposx -= 2;
        if (newBoposx<=0) {
            right = true;
            left = false;
            newBoposx = 0;
        }
    }
    boss.Boposx = newBoposx;
}
void BossFire(Boss &boss) {
    //The boss fires a bullet, see comments in the bullet file for better understanding
    Bullet &newBossbullet = BossTracker[CurrentBossBullet];
    if (!newBossbullet.status) {
        newBossbullet.bposx = boss.Boposx + boss.picture.width / 2 - 2;
        newBossbullet.bposy = boss.Boposy + boss.picture.height;
        newBossbullet.status = true;
        CurrentBossBullet = (CurrentBossBullet + 1) % MAX_BULLETS;
    }
}
void MoveBossBullet() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        Bullet &BossBullet = BossTracker[i];
        if (BossBullet.status) {
            BossBullet.bposy += 2.5;
            DrawRectangle(BossBullet.bposx, BossBullet.bposy, 5, 20, RED);
            if (BossBullet.bposy > 760) { //If boss bullets reach the line in the UI delete them
                BossBullet.status = false;
            }
        }
    }
}
void CheckCollisionForBoss(Boss &boss) { //Checks collisions for the boss with player bullets
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (boss.status == true) {
            if (Tracker[i].status == true) {
                //We get rectangles for both boss and player bullets to measure collisions
                Rectangle BossRect = { (float)boss.Boposx, (float)boss.Boposy, (float)boss.picture.width, (float)boss.picture.height };
                Rectangle BulletRect = GetBulletRect(Tracker[i]);
                if (CheckCollisionRecs(BossRect, BulletRect)) {
                    Tracker[i].status = false;
                    if (boss.Bhealth < 0) {
                        boss.status = false;
                        score += 500; //Boss is worth 100 points
                        boss.death = true;
                    }
                    else
                        boss.Bhealth -= 5; //Each damage takes away 5 health from the boss
                }
            }
        }
    }
}
void ResetBoss(Boss &boss) {
    boss.Bhealth = 100;
    boss.death = false;
    boss.status = false;
    for (int i = 0; i < MAX_BULLETS; i++) {
        BossTracker[i].status = false;
    }
}
