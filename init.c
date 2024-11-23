#include "gba.h"
#include "sprites.h"
#include "game.h"
#include "mode0.h"
#include "spritesheet.h"
#include "mazeOneCollision.h"

void initGame() {
    hideSprites();
    hOff = 0;
    vOff = 0;
    grieverInsideMaze = 1;
    spearInsideMaze = 1;
    loseGame = 0;
    winGame = 0;
    heartActive = 0;
    initDylan();
    initGriever();
    initSpear();
    initHearts();
    initLetters();
}

void initDylan() {
    dylan.x = 230;
    dylan.y = 24;
    dylan.xVel = 1;
    dylan.yVel = 1;
    dylan.width = 16;
    dylan.height = 16;
    dylan.timeUntilNextFrame = 6;
    dylan.direction = RIGHT;
    dylan.isAnimating = 0;
    dylan.currentFrame = 0;
    dylan.numFrames = 4;
    dylan.active = 1;
    dylan.erased = 0;
    dylan.hide = 0;
    dylan.oamIndex = 0;
}

void initGriever() {
    //griever 1
    griever[0].x = 180;
    griever[0].y = 24;
    griever[0].xVel = 1;
    griever[0].yVel = 1;
    griever[0].width = 16;
    griever[0].height = 16;
    griever[0].timeUntilNextFrame = 6;
    griever[0].direction = RIGHT;
    griever[0].isAnimating = 0;
    griever[0].currentFrame = 0;
    griever[0].numFrames = 4;
    griever[0].active = 1;
    griever[0].erased = 0;
    griever[0].hide = 0;
    griever[0].oamIndex = 1;

    //griever 2
    // griever[1].x = 450;
    // griever[1].y = 45;
    // griever[1].xVel = 1;
    // griever[1].yVel = 1;
    // griever[1].width = 16;
    // griever[1].height = 16;
    // griever[1].timeUntilNextFrame = 6;
    // griever[1].direction = RIGHT;
    // griever[1].isAnimating = 0;
    // griever[1].currentFrame = 0;
    // griever[1].numFrames = 4;
    // griever[1].active = 1;
    // griever[1].erased = 0;
    // griever[1].hide = 0;
    // griever[1].oamIndex = 2;

    // //griever 3
    // griever[2].x = 480;
    // griever[2].y = 255;
    // griever[2].xVel = 1;
    // griever[2].yVel = 1;
    // griever[2].width = 16;
    // griever[2].height = 16;
    // griever[2].timeUntilNextFrame = 6;
    // griever[2].direction = RIGHT;
    // griever[2].isAnimating = 0;
    // griever[2].currentFrame = 0;
    // griever[2].numFrames = 4;
    // griever[2].active = 1;
    // griever[2].erased = 0;
    // griever[2].hide = 0;
    // griever[2].oamIndex = 3;

    int j = 4;
    for (int i = 3; i < 10; i++) {
        griever[i].active = 0;
        griever[i].hide = 1;
        griever[i].erased = 1;
        griever[i].oamIndex = j;
        j++;
    }
}

void initNewGriever() {
    int j = 4;
    for (int i = 3; i < 10; i++) {
        if (!griever[i].active) {
            griever[i].x = rand() % (MAPTWOWIDTH - 16);
            griever[i].y = rand() % ((MAPTWOHEIGHT - 16)/2);
            griever[i].xVel = 1;
            griever[i].yVel = 1;
            griever[i].width = 16;
            griever[i].height = 16;
            griever[i].timeUntilNextFrame = 6;
            griever[i].direction = RIGHT;
            griever[i].isAnimating = 0;
            griever[i].currentFrame = 0;
            griever[i].numFrames = 4;
            griever[i].active = 1;
            griever[i].erased = 0;
            griever[i].hide = 0;
            griever[i].oamIndex = j;
            j++;
        }
    }
}

void initSpear() {
    spear.x = dylan.x;
    spear.y = dylan.y;
    spear.xVel = 0;
    spear.yVel = 0;
    spear.direction = dylan.direction;
    spear.active = 0;
    spear.hide = 1;
    spear.oamIndex = 19;
    spear.width = 8;
    spear.height = 8;
    launchSpearBool = 0;
}

void initHearts() {
    int j = 11;
    for (int i = 0; i < 3; i++) {
        heart[i].x = rand() % (MAPTWOWIDTH - 8);
        heart[i].y = rand() % ((MAPTWOHEIGHT - 8)/2);
        // TODO: add if checks for if hearts generate in a bush +  move them accordingly
        heart[i].xVel = 0;
        heart[i].yVel = 0;
        heart[i].width = 8;
        heart[i].height = 8;
        heart[i].timeUntilNextFrame = 6;
        heart[i].direction = RIGHT;
        heart[i].isAnimating = 0;
        heart[i].currentFrame = 0;
        heart[i].numFrames = 4;
        heart[i].active = 1;
        heart[i].erased = 0;
        heart[i].hide = 0;
        heart[i].oamIndex = j;
        j++;
    }
}

void initLetters() {
    // Letter T
    letters[19].width = 8;
    letters[19].height = 16;
    letters[19].active = 0;
    letters[19].active = 1;
    letters[19].hide = 0;
    letters[19].oamIndex = 20;

    // TODO finish initializing letters
    // Letter I

    // Letter M

    // Letter E

    // Letter R

    // SYMBOL :

    // NUMBERS
}