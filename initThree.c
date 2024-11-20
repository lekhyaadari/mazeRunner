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
    loseGame = 0;
    winGame = 0;
    heartActive = 0;
    initDylanThree();
    initGrieversThree();
    initSpearThree();
    initHeartsThree();
    initLettersThree();
}

void initDylanThree() {

}

void initGrieversThree() {

}

void initSpearThree() {

}

void initHeartsThree() {

}

void initLettersThree() {

}