//
// Created by hamda on 11/16/2025.
//

#include "Obstacles.h"
#include<iostream>
#include<raylib.h>
#include"Bullets.h"
#include"Aliens.h"
using namespace std;
const int BlockSize = 3; //Standard size for each individual block
const int OG_Obstacle[13][23] = {{0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
{0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1} }; //Original array to make reset easier
void DrawObstacles(Obstacles obstacles) {
    for (int obscount = 0; obscount < 4; obscount++) { //Draws 4 obstacles spaced apart with the grid array 1s being drawn as small blocks
        int startpoint = 145 + (obscount * 150);
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 23; j++) {
                if (obstacles.grid[i][j] == 1) {
                    int Xcord = startpoint + (j * BlockSize);
                    int Ycord = 600 + (i * BlockSize);
                    DrawRectangle(Xcord, Ycord, BlockSize, BlockSize, WHITE);
                }
            }
        }
    }
}
void CheckCollisionWithObstacles(Obstacles &obstacles) { //Checks for collisions of obstacles with bullets from player, alien or boss
    for (int obscount = 0; obscount < 4; obscount++) {
        float CurrentBaseX = 145.0f + (obscount * 150.0f);
        float CurrentBaseY = 600.0f;
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 23; j++) {
                if (obstacles.grid[i][j] == 1) {
                    Rectangle Block = {CurrentBaseX + j * BlockSize, CurrentBaseY + i * BlockSize, (float)BlockSize, (float)BlockSize };
                    for (int k = 0; k < MAX_BULLETS; k++) {
                        if (Tracker[k].status == true) {
                            Rectangle BullRec = GetBulletRect(Tracker[k]);
                            if (CheckCollisionRecs(Block, BullRec)) {
                                Tracker[k].status = false;
                                obstacles.grid[i][j] = 0;
                            }
                        }
                        if (AlienBull[k].status == true) {
                            Rectangle AlienBullRec = GetBulletRect(AlienBull[k]);
                            if (CheckCollisionRecs(Block, AlienBullRec)) {
                                AlienBull[k].status = false;
                                obstacles.grid[i][j] = 0;
                            }
                        }
                        if (BossTracker[k].status == true) {
                            Rectangle BossBullRec = GetBulletRect(BossTracker[k]);
                            if (CheckCollisionRecs(Block, BossBullRec)) {
                                BossTracker[k].status = false;
                                for (int j = 0; j < 23; j++) {
                                    obstacles.grid[i][j] = 0; //Boss bullets delete an entire row of obstacles
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
void ObstacleReset(Obstacles &obstacles) { //Resets the obstacles to the original form
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 23; j++) {
            obstacles.grid[i][j] = OG_Obstacle[i][j];
        }
    }
}