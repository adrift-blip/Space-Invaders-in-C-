# Space Invaders in C++
<p align="center">
  <img src = "https://i.ytimg.com/vi/-YQ2orY4yyg/maxresdefault.jpg">
</p>

---

## Overview
This project is a simplified remake of the classic **Space Invaders** game developed in **C++** using the **raylib** graphics engine.  
The player controls a spaceship positioned at the bottom of the screen and moves left and right to shoot incoming alien enemies.

Unlike the original game, enemies are not randomly generated. Instead, alien ships move toward the player and shoot back, creating the primary challenge. Once all enemies are defeated (after reaching a certain score), a **final boss battle** begins.  

The game includes:
- Player movement  
- Alien movement
- A mystery ship which gives the player an extra life
- Firing mechanics (player and enemy)  
- Collision detection  
- Scoring  
- Game ending  

Raylib handles rendering, input, and the game loop, while programming logic is written entirely using **fundamental C++ concepts**, such as basic statements and arrays, without object-oriented programming.

---

## Libraries Used

### 1. `<iostream>`
Used for simple debugging output and console messages during development.

### 2. `"raylib.h"`
Core graphics library responsible for:
- Game window creation  
- Rendering shapes, sprites, and text  
- Keyboard and input handling  
- Collision detection  
- Maintaining the game loop
  
### 3. Other Libraries
Some other libraries used are cstdlib and time.h for the rand function and to set its seed

---

## GitHub Implementation
GitHub is used as the collaborative version-control tool for this group project.  
A shared repository allows all team members to:
- Upload and modify code  
- Review contributions  
- Work on separate branches  
- Merge changes cleanly  

The repository link will be included in the final project submission.

---

## Technical Overview

### I. Graphics
Game graphics and UI assets are taken from the GitHub repository:

https://github.com/educ8s/CPP-Space-Invaders-Game-with-raylib/tree/main/Graphics

Only the **graphics** folder is used; **no code** has been taken from the repository.  
This can be verified easily because the referenced project uses **object-oriented programming**, whereas this project is built entirely using fundamental programming concepts.

### II. Special Features
A unique feature of this project is the **final boss fight**.  
After the player eliminates all alien ships, a mystery boss enemy appears.  
Defeating this boss ends the game.  
This fulfills the “levels” requirement mentioned in the project guidelines.


### III. General Gameplay Overview
- The player begins the game
- They can choose to pause or return to the main menu
- A simple 2D array of aliens will move across the screen and shoot
- The player must avoid the lasers by dodging or hiding behind the obstacles
- Eliminating the aliens will lead to use gaining points
- With more pints gained the level will increase, causing the aliens to fire more often and the player to fire less
- Eventually with all the aliens defeated the boss fight will start
- The boss also fires lasers but his eliminate an entire row from all the obstacles or take away the player's two lives
- Eliminate the boss and you win! You can then choose to play again or return to the main menu

### IV. Division of Work
The game is divided into the following functional components:

- Game Loop  
- Spaceship & Player Lasers  
- Aliens & Alien Lasers  
- Obstacles  
- Boss Fight  

---

## Team Members
**Muhammad Hamdan Subzwari — 25L-2018**  
**Muhammad Ayaan — 25L-2015**  
**Ahmed Tariq — 25L-2008**  
BCY-1A  
FAST School of Computing 

---

## Credits for Other Things
Run Amok by Kevin MacLeod | https://incompetech.com/
Music promoted by https://www.chosic.com/free-music/all/
Groovy Vibe by Bransboynd | https://pixabay.com/music/beats-groovy-vibe-427121/
Creative Commons CC BY 3.0
https://creativecommons.org/licenses/by/3.0/
Note: You can use any music, however in order to avoid copyright (stupid I know) I used non-copyrighted music for the upload
