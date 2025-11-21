
//
// Created by hamda on 11/16/2025.
//

#include "Bullets.h"
#include<raylib.h>
#include"Spaceship.h"
#include"Aliens.h"

Bullet Tracker[MAX_BULLETS]; //Creates a global array of bullets available to the player
int currentbullet = 0;

void FireBullet(Spaceship &ship){
    //Creates a bullet in the current index
    Bullet &newBullet = Tracker[currentbullet];
    if (!newBullet.status) {
        newBullet.bposx = ship.sposx + ship.image_s.width / 2 - 2;
        newBullet.bposy = ship.sposy;
        newBullet.status = true;
        currentbullet = (currentbullet + 1) % MAX_BULLETS; //The modulus operator allows us to loop around if we reach the end of the array
    }
}
void MoveBullet() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        //We create a new variable for the current bullet and update its position, the &operator ensures that a copy doesnt get updated
        Bullet &brn = Tracker[i];
        if (brn.status) {
            brn.bposy -= 6;
            DrawRectangle(brn.bposx, brn.bposy, 4, 10, {243, 216, 63, 255});
            if (brn.bposy < 0) { //Checks if bullet goes off screen
                brn.status = false;
            }
        }
    }
}
//The functions below are used to get an invisible rectangle around the bullets to check for collisions
float GetBulletX() {
    return Tracker[currentbullet].bposx;
}
float GetBulletY() {
    return Tracker[currentbullet].bposy;
}
Rectangle GetBulletRect(const Bullet &blt) {
    return Rectangle{ blt.bposx, blt.bposy, 4.0, 10.0 };
}
void ResetBullets() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        Tracker[i].status = false;
    }
}