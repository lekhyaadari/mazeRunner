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
}

void initDylanBonus() {
    // dylan.x = 488;
    // dylan.y = 169;
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

void initGrieversBonus() {
    int j = 1;
    for (int i = 0; i < 14; i++) {
        // griever[i].x = 236;
        // griever[i].y = 71;
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

void initSpearTwo() {
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