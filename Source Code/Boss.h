//
// Created by ahmed on 17/11/2025.
//

#ifndef PF_FINAL_PROJECT_BOSS_H
#define PF_FINAL_PROJECT_BOSS_H
#include<raylib.h>
#include"Bullets.h"
typedef struct Boss {
    Texture2D picture;
    int Boposx;
    int Boposy;
    int Bhealth = 100; //20 bullets required to kill
    bool status;
    bool death;
} Boss;
void InitBoss(Boss &boss);
void DrawBoss(const Boss &boss);
void CleanupBoss(Boss &boss);
void UpdateHealth(Boss &boss);
void BossShoot(Boss &boss);
void UpdateBossPosition(Boss &boss);
void BossFire(Boss &boss);
void MoveBossBullet();
void CheckCollisionForBoss(Boss &boss);
void ResetBoss(Boss &boss);
#endif //PF_FINAL_PROJECT_BOSS_H