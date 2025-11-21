//
// Created by hamda on 11/20/2025.
//

#ifndef PF_FINAL_PROJECT_GAMEDATA_H
#define PF_FINAL_PROJECT_GAMEDATA_H
#include<raylib.h>
extern int score;
extern int lives;
int LoadHighScore();
void SaveHighScore(int n);
void DisplayLevel(int n, Color color);
int Level(int n);
void ResetData();
double DifficultyAlienFire(int n);
double DifficultyPlayerFire(int n);
#endif //PF_FINAL_PROJECT_GAMEDATA_H