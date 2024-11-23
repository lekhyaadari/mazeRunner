#include "gba.h"
#include "sprites.h"
#include "game.h"
#include "mode0.h"
#include "spritesheet.h"
#include "mazeOneCollision.h"

void drawGame() {
    hideSprites();
    drawDylan();
    drawGriever();
    drawSpear();
    drawHearts();
    drawLetters();
}

void drawDylan() {
    if (dylan.hide) {
        shadowOAM[dylan.oamIndex].attr0 |= ATTR0_HIDE;
    } else {
        shadowOAM[dylan.oamIndex].attr0 = ATTR0_Y(dylan.y - vOff) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[dylan.oamIndex].attr1 = ATTR1_X(dylan.x - hOff) | ATTR1_SMALL;
        shadowOAM[dylan.oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(0) | ATTR2_TILEID(dylan.currentFrame*2, 0);

        if (dylan.direction == RIGHT) {
            shadowOAM[dylan.oamIndex].attr1 = ATTR1_HFLIP | ATTR1_X(dylan.x - hOff) | ATTR1_SMALL;
        }
        if (dylan.direction == UP) {
            shadowOAM[dylan.oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(0) | ATTR2_TILEID(dylan.currentFrame*2, 2);
        }
        if (dylan.direction == DOWN) {
            shadowOAM[dylan.oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(0) | ATTR2_TILEID(dylan.currentFrame*2, 4);
        }

        if (heartActive) {
            shadowOAM[dylan.oamIndex].attr0 = ATTR0_Y(dylan.y - vOff) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
            shadowOAM[dylan.oamIndex].attr1 = ATTR1_X(dylan.x - hOff) | ATTR1_SMALL;
            shadowOAM[dylan.oamIndex].attr2 = ATTR2_PALROW(1) | ATTR2_PRIORITY(0) | ATTR2_TILEID(dylan.currentFrame*2, 0);
            if (dylan.direction == RIGHT) {
                shadowOAM[dylan.oamIndex].attr1 = ATTR1_HFLIP | ATTR1_X(dylan.x - hOff) | ATTR1_SMALL;
            }
            if (dylan.direction == UP) {
                shadowOAM[dylan.oamIndex].attr2 = ATTR2_PALROW(1) | ATTR2_PRIORITY(0) | ATTR2_TILEID(dylan.currentFrame*2, 2);
            }
            if (dylan.direction == DOWN) {
                shadowOAM[dylan.oamIndex].attr2 = ATTR2_PALROW(1) | ATTR2_PRIORITY(0) | ATTR2_TILEID(dylan.currentFrame*2, 4);
            }
        }
    }
}

void drawGriever() {
    for (int i = 0; i < 3; i++) {
        if (griever[i].active && griever[i].hide) {
            shadowOAM[griever[i].oamIndex].attr0 = ATTR0_HIDE;
        } else if (griever[i].active && !griever[i].erased && !griever[i].hide && (collision(griever[i].x, griever[i].y, griever[i].width, griever[i].height, hOff, vOff, SCREENWIDTH, SCREENHEIGHT))) {
            shadowOAM[griever[i].oamIndex].attr0 = ATTR0_Y(griever[i].y - vOff) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
            shadowOAM[griever[i].oamIndex].attr1 = ATTR1_X(griever[i].x - hOff) | ATTR1_SMALL;
            shadowOAM[griever[i].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(0) | ATTR2_TILEID(griever[i].currentFrame*2, 6);

            if (griever[i].direction == RIGHT) {
                shadowOAM[griever[i].oamIndex].attr1 = ATTR1_X(griever[i].x - hOff) | ATTR1_SMALL | ATTR1_HFLIP;
            }
            if (griever[i].direction == UP) {
                shadowOAM[griever[i].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(0) | ATTR2_TILEID(griever[i].currentFrame*2, 8);
            }
            if (griever[i].direction == DOWN) {
                shadowOAM[griever[i].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(0) | ATTR2_TILEID(griever[i].currentFrame*2, 10);
            }
        }
    }
}

//!collision(sprite.x, y, width, height, hoff, voff, screenwi, screenhe)

void drawSpear() {
    if (spear.hide) {
        shadowOAM[spear.oamIndex].attr0 |= ATTR0_HIDE;
    } else {
        shadowOAM[spear.oamIndex].attr0 = ATTR0_Y(spear.y - vOff) | ATTR0_4BPP | ATTR0_REGULAR | ATTR0_SQUARE;
        shadowOAM[spear.oamIndex].attr1 = ATTR1_X(spear.x - hOff) | ATTR1_TINY;
        shadowOAM[spear.oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(0) | ATTR2_TILEID(0, 12);
    }
}

void drawHearts() {
    for (int i = 0; i < 3; i++) {
        if (heart[i].hide && !heart[i].active) {
            shadowOAM[heart[i].oamIndex].attr0 |= ATTR0_HIDE;
        } else if (heart[i].active && !heart[i].hide && collision(heart[i].x, heart[i].y, heart[i].width, heart[i].height, hOff, vOff, SCREENWIDTH, SCREENHEIGHT)) {
            shadowOAM[heart[i].oamIndex].attr0 = ATTR0_Y(heart[i].y - vOff) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
            shadowOAM[heart[i].oamIndex].attr1 = ATTR1_X(heart[i].x - hOff) | ATTR1_TINY;
            shadowOAM[heart[i].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(0) | ATTR2_TILEID(0, 12);
        }
    }
}

void drawLetters() {
    shadowOAM[letters[19].oamIndex].attr0 = ATTR0_Y(2) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_TALL;
    shadowOAM[letters[19].oamIndex].attr1 = ATTR1_X(2) | ATTR1_TINY;
    shadowOAM[letters[19].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY (0) | ATTR2_TILEID(27, 0);
}