#include<iostream>
#include<raylib.h>
#include"Spaceship.h"
#include"Obstacles.h"
#include"Bullets.h"
#include "Aliens.h"
#include"Boss.h"
#include"GameData.h"
#include "GameUtilities.h"
using namespace std;
int main() {
    int highscore = LoadHighScore(); //Loads the highscore
    //Intiialize all variables required
    double LastFireTime = 0, LastAlienFireTime = 0, LastBossFireTime = 0, LastMATime = 0; //Fire rates for each element
    double RateofAlienFire, RateofPlayerFire;
    //Bool variables for defining state of a game
    bool run = true, GameStarted = false, MysteryAlienCheck = true, paused = false;
    char scoreString[4]; //String for storing score
    int windowheight = 850, windowwidth = 800;
    InitWindow(windowwidth, windowheight, "PF-Final-Projects"); //Create a window for the game
    InitAudioDevice(); //Creates an Audio device to play music
    SetTargetFPS(60); //Sets target fps
    //Loads the music files, sets their volumes and intially plays menu music
    Music MenuMusic = LoadMusicStream("Music/Menu Soundtrack.mp3"), BGM = LoadMusicStream("Music/Game Soundtrack.mp3"), WinMusic = LoadMusicStream("Music/WinSound.mp3"),
    LossMusic = LoadMusicStream("Music/LossSound.mp3"), PauseMusic = LoadMusicStream("Music/PauseMusic.mp3");
    MenuMusic.looping = true;
    BGM.looping = true; //Loops the music continuously
    WinMusic.looping = true;
    LossMusic.looping = true;
    PauseMusic.looping = true;
    bool isLossMusicPlaying = false, isWinMusicPlaying = false, isPauseMusicPlaying = false;
    PlayMusicStream(MenuMusic);
    SetMusicVolume(MenuMusic, 0.5f);
    SetMusicVolume(BGM, 0.5f);
    //Load custom colors
    Color grey = {29, 29, 27, 255}, yellow = {243, 216, 63, 255}, lime = { 0, 255, 64, 255 };
    //Loads certain font and textures unrelated to game objects
    Font TitleFont = LoadFont("Font/Karmatic.ttf"), GameFont = LoadFont("Font/monogram.ttf");
    Texture2D lifeindicator = LoadTexture("Graphics/spaceship.png"); //Indicates player lives
    Obstacles obstacles; //Intializes/Create all the game elements
    Spaceship player;
    Boss boss;
    InitSpaceship(player);
    InitBoss(boss);
    InitAlien();
    while (!WindowShouldClose()) {
        //Updates music depending on game state
        if (!GameStarted) {
            UpdateMusicStream(MenuMusic);
        }
        else if (paused) {
            UpdateMusicStream(PauseMusic);
        }
        else if (lives == 0) {
            UpdateMusicStream(LossMusic);
        }
        else if (run) {
            UpdateMusicStream(BGM);
        }
        else if (boss.death) {
            UpdateMusicStream(WinMusic);
        }
        int level = Level(score); //Sets level and difficulty according to current score
        RateofAlienFire = DifficultyAlienFire(level);
        RateofPlayerFire = DifficultyPlayerFire(level);
        if (IsKeyPressed(KEY_P)) {
            if (GameStarted && run)
                paused = true;
        }
        if (IsKeyPressed(KEY_R) && GameStarted) { //Resets the game and returns to the main menu
            GameStarted = false;
            isLossMusicPlaying = false;
            isWinMusicPlaying = false;
            isPauseMusicPlaying = false;
            StopMusicStream(PauseMusic);
            StopMusicStream(BGM);
            StopMusicStream(WinMusic);
            StopMusicStream(LossMusic);
            PlayMusicStream(MenuMusic);
            Reset(boss, player, obstacles);
        }
        if (paused){
            run = false;
            if (!isPauseMusicPlaying) { //Play pause menu music
                StopMusicStream(BGM);
                SetMusicVolume(PauseMusic, 0.5f);
                PlayMusicStream(PauseMusic);
                UpdateMusicStream(PauseMusic);
                isPauseMusicPlaying = true;
            }
            DrawTextEx(GameFont, "PAUSED! Press U to restart", {300, 800}, 34, 2, yellow);
            if (IsKeyPressed(KEY_U)) {
                isPauseMusicPlaying = false;
                StopMusicStream(PauseMusic);
                PlayMusicStream(BGM);
                paused = false;
                run = true;
            }
        }
        if (!GameStarted) { //If player is on menu then play menu music
            if (IsKeyPressed(KEY_ENTER)) { //Check if user started game
                GameStarted = true;
                StopMusicStream(MenuMusic); //Change music played
                PlayMusicStream(BGM);
            }
        }
        BeginDrawing();
        ClearBackground(grey); //Creates the background
        if (!GameStarted) { //If player is on menu draw the text
           DrawMenu(YELLOW, RED, lime, TitleFont);
        }
        else { //Otherwise draw the game such as UI and levels etc
            DrawUI(yellow, GameFont, lifeindicator);
            if (run) {
                DrawLives(lifeindicator);
                DisplayLevel(score, yellow);
            }
            //Converts score to string and draws it
            InttoStringWithZeroes(score, scoreString);
            DrawTextEx(GameFont, scoreString, {50, 40}, 34, 2, yellow);
            InttoStringWithZeroes(highscore, scoreString);
            DrawTextEx(GameFont, scoreString, {655, 40}, 34, 2, yellow);
            DrawGameElements(player, boss, obstacles);
            if (BossSpawner()) { //Checks if all aliens are dead and spawns the boss
                if (boss.Bhealth > 0)
                    boss.status = true;
                DrawBoss(boss);
                if (run) { //If game si running then the boss fires
                    if (rand() % 10 == 0) { //Out of the 60 frames per second boss fires at a random frame every 30 seconds
                        if (GetTime()-LastBossFireTime > 0.75) { //Prevents spamming of bullets by the boss
                            BossFire(boss);
                            LastBossFireTime = GetTime();
                        }
                    }
                }
            }
            if (run) {
                if (GetTime() - LastMATime >= 30) { //Spawns mystery alien every 30 seconds
                    InitMysteryAlienTexture();
                    MysteryAlienInit();
                    LastMATime = GetTime();
                }
                if (GetTime()-LastAlienFireTime > RateofAlienFire) { //Checks if aliens are firing at required intervals
                    AlienPewPew();
                    LastAlienFireTime = GetTime();
                }
                if (IsKeyPressed(KEY_SPACE)) { //Allows user to fire, raylib function is used as explained in one of the files, I forgot which it was
                    if (GetTime() - LastFireTime >= RateofPlayerFire) { //Prevents spamming by the player similarly
                        FireBullet(player);
                        LastFireTime = GetTime();
                    }
                }
                //Move game elements around and checks for collisions
                UpdateGameElements(player, boss);
                CollisionChecker(player, boss, obstacles);
            }
            if (boss.death == true) { //Player wins the game
                run = false;
                if (!isWinMusicPlaying) { //Play winning music
                    StopMusicStream(BGM);
                    SetMusicVolume(WinMusic, 0.5f);
                    PlayMusicStream(WinMusic);
                    UpdateMusicStream(WinMusic);
                    isWinMusicPlaying = true;
                }
                DrawTextEx(GameFont, "YOU WIN! PRESS ENTER TO RESTART", {130, 800}, 34, 1, yellow);
                if (IsKeyPressed(KEY_ENTER)) { //Resets the game
                    Reset(boss, player, obstacles);
                    StopMusicStream(WinMusic);
                    PlayMusicStream(BGM);
                    run = true;
                    isWinMusicPlaying = false;
                }
            }
            if (lives == 0) { //Player lost all their lives
                run = false;
                if (!isLossMusicPlaying) { //Play losing music
                    StopMusicStream(BGM);
                    SetMusicVolume(LossMusic, 0.5f);
                    PlayMusicStream(LossMusic);
                    UpdateMusicStream(LossMusic);
                    isLossMusicPlaying = true;
                }
                DrawTextEx(GameFont, "GAME OVER! PRESS ENTER TO RESTART", {100, 800}, 34, 2, yellow);
                if (IsKeyPressed(KEY_ENTER)) {
                    Reset(boss, player, obstacles);
                    StopMusicStream(LossMusic);
                    PlayMusicStream(BGM);
                    run = true;
                    isLossMusicPlaying = false;
                }
            }
        }
        EndDrawing();
    }
    //Cleans up everything nice and tidy
    CleanUpGame(MenuMusic, BGM, WinMusic, LossMusic, PauseMusic, GameFont, TitleFont);
    CleanUpUserElements(lifeindicator, player, obstacles, boss);
    CloseAudioDevice();
    CloseWindow();
    if (score > highscore) //Checks if new score is current high score
        SaveHighScore(score);
    return 0; //IDK kinda just there
}
