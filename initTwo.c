#include "gba.h"
#include "sprites.h"
#include "game.h"
#include "mode0.h"
#include "spritesheet.h"
#include "mazeTwoCollision.h"

void initGameTwo() {
    hideSprites();
    hOff = 0;
    vOff = 0;
    grieverInsideMaze = 1;
    spearInsideMaze = 1;
    loseGame = 0;
    winGame = 0;
    heartActive = 0;
    initDylanTwo();
    initGrieversTwo();
    initHeartsTwo();
    initLettersTwo();
}

void initDylanTwo() {
    dylan.x = 488;
    dylan.y = 169;
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

void initGrieversTwo() {

}

void initHeartsTwo() {

}

void initLettersTwo() {

}