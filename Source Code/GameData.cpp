//
// Created by hamda on 11/20/2025.
//

#include "GameData.h"
#include<fstream>
#include <iostream>
#include<raylib.h>
using namespace std;
//Defines the basic measurements in game
int level = 1;
int score = 0;
int lives = 3;
int LoadHighScore() { //Loads previous highscores from a local file
    ifstream HighScore("HighScore.txt");
    int highscore = 0;
    if (HighScore.is_open()) {
        HighScore >> highscore;
        HighScore.close();
    }
    else {
        cout << "HighScore.txt could not be opened" << endl;
    }
    return highscore;
}
void SaveHighScore(int n) { //Saves highscore if conditions are met
    ofstream HighScore("HighScore.txt");
    if (HighScore.is_open()) {
        HighScore << n;
        HighScore.close();
    }
    else {
        cout << "HighScore.txt could not be opened" << endl;
    }
}
void ResetData() { //Resets game data
    score = 0;
    lives = 3;
}
int Level(int n) { //Checks level according to
    if (score < 1000)
        return 1;
    else if (score < 2000)
        return 2;
    else if (score < 3000)
        return 3;
    else if (score < 4000)
        return 4;
    else
        return 5;
}
double DifficultyAlienFire(int n) { //Changes the rate of alien fire according to level
    switch (n) {
        case 1:
            return 0.75;
        case 2:
            return 0.65;
        case 3:
            return 0.55;
        case 4:
            return 0.45;
        case 5:
            return 0.35;
    }
}
double DifficultyPlayerFire(int n) { //Changes the rate of player fire according to level
    switch (n) {
        case 1:
            return 0.55;
        case 2:
            return 0.60;
        case 3:
            return 0.70;
        case 4:
            return 0.75;
        case 5:
            return 0.80;
    }
}