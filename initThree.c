#include "gba.h"
#include "sprites.h"
#include "game.h"
#include "mode0.h"
#include "spritesheet.h"
#include "mazeThreeCollision.h"

void initGameThree() {
    hideSprites();
    hOff = 0;
    vOff = 0;
    grieverInsideMaze = 1;
    spearInsideMaze = 1;
    gameTimer = 3600;
    loseGame = 0;
    winGame = 0;
    heartActive = 0;
    venomActive = 0;
    initDylanThree();
    initGrieversThree();
    initSpearThree();
    initHeartsThree();
    initLettersThree();
}

void initDylanThree() {
    dylan.x = 31;
    dylan.y = 184;
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

void initGrieversThree() {
    //griever 1
    griever[0].x = 236;
    griever[0].y = 71;
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
    griever[1].x = 367;
    griever[1].y = 260;
    griever[1].xVel = 1;
    griever[1].yVel = 1;
    griever[1].width = 16;
    griever[1].height = 16;
    griever[1].timeUntilNextFrame = 6;
    griever[1].direction = RIGHT;
    griever[1].isAnimating = 0;
    griever[1].currentFrame = 0;
    griever[1].numFrames = 4;
    griever[1].active = 1;
    griever[1].erased = 0;
    griever[1].hide = 0;
    griever[1].oamIndex = 2;

    //griever 3
    griever[2].x = 95;
    griever[2].y = 311;
    griever[2].xVel = 1;
    griever[2].yVel = 1;
    griever[2].width = 16;
    griever[2].height = 16;
    griever[2].timeUntilNextFrame = 6;
    griever[2].direction = RIGHT;
    griever[2].isAnimating = 0;
    griever[2].currentFrame = 0;
    griever[2].numFrames = 4;
    griever[2].active = 1;
    griever[2].erased = 0;
    griever[2].hide = 0;
    griever[2].oamIndex = 3;

    //griever 4
    griever[3].x = 107;
    griever[3].y = 235;
    griever[3].xVel = 1;
    griever[3].yVel = 1;
    griever[3].width = 16;
    griever[3].height = 16;
    griever[3].timeUntilNextFrame = 6;
    griever[3].direction = RIGHT;
    griever[3].isAnimating = 0;
    griever[3].currentFrame = 0;
    griever[3].numFrames = 4;
    griever[3].active = 1;
    griever[3].erased = 0;
    griever[3].hide = 0;
    griever[3].oamIndex = 4;

    //griever 5
    griever[4].x = 108;
    griever[4].y = 399;
    griever[4].xVel = 1;
    griever[4].yVel = 1;
    griever[4].width = 16;
    griever[4].height = 16;
    griever[4].timeUntilNextFrame = 6;
    griever[4].direction = RIGHT;
    griever[4].isAnimating = 0;
    griever[4].currentFrame = 0;
    griever[4].numFrames = 4;
    griever[4].active = 1;
    griever[4].erased = 0;
    griever[4].hide = 0;
    griever[4].oamIndex = 5;

    int j = 6;
    for (int i = 5; i < 16; i++) {
        griever[i].active = 0;
        griever[i].hide = 1;
        griever[i].erased = 1;
        griever[i].oamIndex = j;
        j++;
    }
}

void initNewGrieverThree() {
    int j = 6;
    for (int i = 5; i < 16; i++) {
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

void initSpearThree() {
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

void initHeartsThree() {
    int j = 18;
    for (int i = 0; i < 1; i++) {
        heart[i].x = 234;
        heart[i].y = 36;
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

void initLettersThree() {
    // Letter T
    letters[1].width = 8;
    letters[1].height = 8;
    letters[1].active = 0;
    letters[1].active = 1;
    letters[1].hide = 0;
    letters[1].oamIndex = 20;

    // Letter I
    letters[2].width = 8;
    letters[2].height = 8;
    letters[2].active = 0;
    letters[2].active = 1;
    letters[2].hide = 0;
    letters[2].oamIndex = 21;

    // Letter M
    letters[3].width = 8;
    letters[3].height = 8;
    letters[3].active = 0;
    letters[3].active = 1;
    letters[3].hide = 0;
    letters[3].oamIndex = 22;

    // Letter E
    letters[4].width = 8;
    letters[4].height = 8;
    letters[4].active = 0;
    letters[4].active = 1;
    letters[4].hide = 0;
    letters[4].oamIndex = 23;

    // Letter L
    letters[5].width = 8;
    letters[5].height = 8;
    letters[5].active = 0;
    letters[5].active = 1;
    letters[5].hide = 0;
    letters[5].oamIndex = 24;

    // Letter E
    letters[6].width = 8;
    letters[6].height = 8;
    letters[6].active = 0;
    letters[6].active = 1;
    letters[6].hide = 0;
    letters[6].oamIndex = 25;

    // Letter F
    letters[7].width = 8;
    letters[7].height = 8;
    letters[7].active = 0;
    letters[7].active = 1;
    letters[7].hide = 0;
    letters[7].oamIndex = 26;

    // Letter T
    letters[8].width = 8;
    letters[8].height = 8;
    letters[8].active = 0;
    letters[8].active = 1;
    letters[8].hide = 0;
    letters[8].oamIndex = 27;

    // SYMBOL :
    letters[9].width = 8;
    letters[9].height = 8;
    letters[9].active = 0;
    letters[9].active = 1;
    letters[9].hide = 0;
    letters[9].oamIndex = 28;

    // NUMBERS
    // (0)0 : 00
    letters[10].width = 8;
    letters[10].height = 8;
    letters[10].active = 0;
    letters[10].active = 1;
    letters[10].hide = 0;
    letters[10].oamIndex = 29;

    // 0(0) : 00
    letters[11].width = 8;
    letters[11].height = 8;
    letters[11].active = 0;
    letters[11].active = 1;
    letters[11].hide = 0;
    letters[11].oamIndex = 30;

    //:
    letters[12].width = 8;
    letters[12].height = 8;
    letters[12].active = 0;
    letters[12].active = 1;
    letters[12].hide = 0;
    letters[12].oamIndex = 31;

    // 00: (0)0
    letters[13].width = 8;
    letters[13].height = 8;
    letters[13].active = 0;
    letters[13].active = 1;
    letters[13].hide = 0;
    letters[13].oamIndex = 32;

    // 00 : 0(0)
    letters[14].width = 8;
    letters[14].height = 8;
    letters[14].active = 0;
    letters[14].active = 1;
    letters[14].hide = 0;
    letters[14].oamIndex = 33;
}