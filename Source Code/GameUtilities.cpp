//
// Created by hamda on 11/21/2025.
//

#include "GameUtilities.h"
#include"GameData.h"
#include"Spaceship.h"
#include"Boss.h"
#include"Aliens.h"
#include"Obstacles.h"
#include"Bullets.h"
Font GFont = LoadFont("Font/monogram.ttf");
//The three functions following this comment could have been implemented in main but instead they are abstracted further to make main cleaner
void UpdateGameElements(Spaceship &ship, Boss &boss) { //Updates all of the game elements
    UpdateSpaceship(ship);
    UpdateBossPosition(boss);
    MoveAlien();
    MoveMysteryAlien();
    MoveAlienBullet();
    MoveBossBullet();
    MoveBullet();
}
void CollisionChecker(Spaceship &ship, Boss &boss, Obstacles &obstacles) { //Checks collision for all of the game elemens+ts
    CheckCollisionWithObstacles(obstacles);
    CheckSpaceship(ship);
    CheckCollisionsWithBullets(ship);
    CheckCollisionForBoss(boss);;
}
void DrawGameElements(Spaceship &ship, Boss &boss, Obstacles &obstacles) { //Draws all of the game elements
    DrawSpaceship(ship);
    DrawAlien();
    DrawMysteryAlien();
    DrawObstacles(obstacles);
}

void InttoStringWithZeroes(int n, char array[]) { //Converts the score to a string as raylib can only draw scores
    for (int i = 0; i < 4; i++) {
        array[i] = '0';
    }
    array[4] = '\0';
    int index = 3;
    while (n > 0 && index >= 0) {
        array[index] = '0' + (n % 10);
        n /= 10;
        index--;
    }
}
void Reset(Boss &boss, Spaceship &ship, Obstacles &obstacles) { //Resets everything to original state
    ResetData();
    ResetAlien();
    ResetBoss(boss);
    ObstacleReset(obstacles);
    ResetSpaceship(ship);
    ResetBullets();
}
//Unloads all textures and things from VRAM AND RAM
void CleanUpGame(Music &music, Music &music2, Music &music3, Music &music4,Music &music5, Font &Font1, Font &Font2) {
    UnloadFont(Font1);
    UnloadFont(Font2);
    StopMusicStream(music);
    UnloadMusicStream(music);
    StopMusicStream(music2);
    UnloadMusicStream(music2);
    StopMusicStream(music3);
    UnloadMusicStream(music3);
    StopMusicStream(music4);
    UnloadMusicStream(music4);
    StopMusicStream(music5);
    UnloadMusicStream(music5);
}
void CleanUpUserElements(Texture2D &texture, Spaceship &ship, Obstacles &obstacle, Boss &boss) {
    DestroyMysteryAlien();
    CleanupBoss(boss);
    CleanupSpaceship(ship);
    DestroyAlien();
    UnloadTexture(texture);
}
void DrawUI(Color color, Font font, Texture2D texture) {
    DrawLineEx({20, 780}, {780, 780}, 4.0f, color);
    DrawTextEx(font, "SCORE", {50, 15}, 34, 2, color);
    DrawTextEx(font, "HIGHSCORE", {570, 15}, 34, 2, color);
}
void DrawLives(Texture2D textureb) {
    int x = 50;
    for(int i = 0; i < lives; i++) {
        DrawTexture(textureb, float(x), 800, WHITE);
        x += 50;
    }
}
void DisplayLevel(int n, Color color) { //Displays the level according to the score
    if (score < 1000)
        DrawTextEx(GFont, "LEVEL 01", {570, 800}, 34, 2, color);
    else if (score < 2000)
        DrawTextEx(GFont, "LEVEL 02", {570, 800}, 34, 2, color);
    else if (score < 3000)
        DrawTextEx(GFont, "LEVEL 03", {570, 800}, 34, 2, color);
    else if (score < 4000)
        DrawTextEx(GFont, "LEVEL 04", {570, 800}, 34, 2, color);
    else
        DrawTextEx(GFont, "LEVEL 05", {570, 800}, 34, 2, color);
}
void DrawMenu(Color c1, Color c2, Color c3, Font F1){ //Displays the entire menu code and instructions
    DrawTextEx(F1,"SPACE",{325,80},36,1, c1);
    DrawTextEx(F1,"INVADERS",{300,130},36,1, c1);
    DrawTextEx(F1,"BY 2 OMANIS 1 PAKISTANI",{136,180},36,1, c2);
    DrawTextEx(F1,"MOVE USING THE LEFT AND RIGHT ARROW <-- --> KEYS",{40,300},22,1, c3);
    DrawTextEx(F1,"USE SPACEBAR TO FIRE BULLETS",{40,340},22,1,c3);
    DrawTextEx(F1,"YOUR GOAL IS TO DESTROY ALL THE ALIENS",{40,380},22,1,c3);
    DrawTextEx(F1,"AND TO DEFEAT THE BOSS",{40,420},22,1,c3);
    DrawTextEx(F1,"YOU HAVE 3 LIVES TO ACCOMPLISH THIS GOAL",{40,460},22,1,c3);
    DrawTextEx(F1,"GET HIT YOU LOSE A LIFE",{40,500},22,1, c3);
    DrawTextEx(F1,"LOOKOUT FOR THE MYSTERY SHIP!",{40,540},22,1,c3);
    DrawTextEx(F1, "AS LEVELS INCREASE SO DOES DIFFICULTY", {40, 580}, 22, 1, WHITE);
    DrawTextEx(F1, "YOU CAN PRESS P TO PAUSE THE GAME", {40,620}, 22, 1, WHITE);
    DrawTextEx(F1, "OR YOU CAN PRESS R TO RETURN TO THIS MENU", {40,660}, 22, 1, WHITE);
    DrawTextEx(F1,"PRESS ENTER TO START THE GAME WINDOW...",{30,740},28,1,RED);
}
