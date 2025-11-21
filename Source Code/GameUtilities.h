//
// Created by hamda on 11/21/2025.
//

#ifndef PF_FINAL_PROJECT_GAMEUTILITIES_H
#define PF_FINAL_PROJECT_GAMEUTILITIES_H
#include<raylib.h>
#include"Spaceship.h"
#include"Obstacles.h"
#include"Boss.h"
#include"GameData.h"
#include"Aliens.h"
void DrawUI(Color color, Font font, Texture2D texture);
void DrawLives(Texture2D textureb);
void DisplayLevel(int n, Color color);
void UpdateGameElements(Spaceship &ship, Boss &boss);
void CollisionChecker(Spaceship &ship, Boss &boss, Obstacles &obstacles);
void DrawGameElements(Spaceship &ship, Boss &boss, Obstacles &obstacles);
void DrawMenu(Color c1, Color c2, Color C3, Font F1);
void InttoStringWithZeroes(int n, char array[]);
void Reset(Boss &boss, Spaceship &ship, Obstacles &obstacle);
void CleanUpGame(Music &music, Music &music2, Music &music3, Music &music4, Music &music5, Font &Font1, Font &Font2);
void CleanUpUserElements(Texture2D &texture, Spaceship &ship, Obstacles &obstacle, Boss &boss);
#endif //PF_FINAL_PROJECT_GAMEUTILITIES_H