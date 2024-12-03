#include "gba.h"
#include "sprites.h"
#include "game.h"
#include "mode0.h"
#include "spritesheet.h"

void initGameBonus() {
    hideSprites();
    hOff = 0;
    vOff = 0;
    grieverInsideMaze = 1;
    spearInsideMaze = 1;
    loseGame = 0;
    winGame = 0;
    heartActive = 0;
    initDylanBonus();
    initGrieversBonus();
    initSpearBonus();
    deInitSprites();
}

void initDylanBonus() {
    dylan.x = 240;
    dylan.y = 250;
    dylan.xVel = 1;
    dylan.yVel = 1;
    dylan.width = 16;
    dylan.height = 16;
    dylan.timeUntilNextFrame = 6;
    dylan.direction = LEFT;
    dylan.isAnimating = 0;
    dylan.currentFrame = 0;
    dylan.numFrames = 4;
    dylan.active = 1;
    dylan.erased = 0;
    dylan.hide = 0;
    dylan.oamIndex = 0;
}

void initGrieversBonus() {
    int j = 1;
    for (int i = 0; i < 14; i++) {
        griever[i].x = rand() % 496;
        griever[i].y = rand() % 496;
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

void initSpearBonus() {
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

void deInitSprites() {
    int k = 21;
    for (int i = 0; i < 15; i++) {
        letters[i].oamIndex = k;
        letters[i].active = 0;
        letters[i].hide = 1;
        letters[i].erased = 1;
        k++;
    }
}