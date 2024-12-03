#include "gba.h"
#include "sprites.h"
#include "game.h"
#include "mode0.h"
#include "spritesheet.h"

void drawGame() {
    hideSprites();
    drawDylan();
    drawGriever();
    drawSpear();
    drawHearts();
    drawTimer();
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

        if (heartActive == 1) {
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
        if (venomActive == 1) {
            shadowOAM[dylan.oamIndex].attr0 = ATTR0_Y(dylan.y - vOff) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
            shadowOAM[dylan.oamIndex].attr1 = ATTR1_X(dylan.x - hOff) | ATTR1_SMALL;
            shadowOAM[dylan.oamIndex].attr2 = ATTR2_PALROW(2) | ATTR2_PRIORITY(0) | ATTR2_TILEID(dylan.currentFrame*2, 0);
            if (dylan.direction == RIGHT) {
                shadowOAM[dylan.oamIndex].attr1 = ATTR1_HFLIP | ATTR1_X(dylan.x - hOff) | ATTR1_SMALL;
            }
            if (dylan.direction == UP) {
                shadowOAM[dylan.oamIndex].attr2 = ATTR2_PALROW(2) | ATTR2_PRIORITY(0) | ATTR2_TILEID(dylan.currentFrame*2, 2);
            }
            if (dylan.direction == DOWN) {
                shadowOAM[dylan.oamIndex].attr2 = ATTR2_PALROW(2) | ATTR2_PRIORITY(0) | ATTR2_TILEID(dylan.currentFrame*2, 4);
            }
        }
    }
}

void drawGriever() {
    for (int i = 0; i < 16; i++) {
        if (griever[i].active && !griever[i].erased && !griever[i].hide && (collision(griever[i].x, griever[i].y, griever[i].width, griever[i].height, hOff, vOff, SCREENWIDTH, SCREENHEIGHT)) && (heartActive == 0 || heartActive == 1)) {
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
        } else {
            shadowOAM[griever[i].oamIndex].attr0 |= ATTR0_HIDE;
        }
    }
}

void drawSpear() {
    if (spear.hide) {
        shadowOAM[spear.oamIndex].attr0 |= ATTR0_HIDE;
    } else {
        if (dylan.direction == DOWN) {
            shadowOAM[spear.oamIndex].attr0 = ATTR0_Y(spear.y - vOff) | ATTR0_4BPP | ATTR0_REGULAR | ATTR0_SQUARE;
            shadowOAM[spear.oamIndex].attr1 = ATTR1_X(spear.x - hOff) | ATTR1_TINY;
            shadowOAM[spear.oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(0) | ATTR2_TILEID(0, 13);
        } else if (dylan.direction == UP) {
            shadowOAM[spear.oamIndex].attr0 = ATTR0_Y(spear.y - vOff) | ATTR0_4BPP | ATTR0_REGULAR | ATTR0_SQUARE;
            shadowOAM[spear.oamIndex].attr1 = ATTR1_X(spear.x - hOff) | ATTR1_TINY;
            shadowOAM[spear.oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(0) | ATTR2_TILEID(1, 13);
        } else if (dylan.direction == RIGHT) {
            shadowOAM[spear.oamIndex].attr0 = ATTR0_Y(spear.y - vOff) | ATTR0_4BPP | ATTR0_REGULAR | ATTR0_SQUARE;
            shadowOAM[spear.oamIndex].attr1 = ATTR1_X(spear.x - hOff) | ATTR1_TINY;
            shadowOAM[spear.oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(0) | ATTR2_TILEID(2, 13);
        } else if (dylan.direction == LEFT) {
            shadowOAM[spear.oamIndex].attr0 = ATTR0_Y(spear.y - vOff) | ATTR0_4BPP | ATTR0_REGULAR | ATTR0_SQUARE;
            shadowOAM[spear.oamIndex].attr1 = ATTR1_X(spear.x - hOff) | ATTR1_TINY;
            shadowOAM[spear.oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(0) | ATTR2_TILEID(3, 13);
        }
    }
}

void drawHearts() {
    for (int i = 0; i < 3; i++) {
        if (heart[i].hide && !heart[i].active) {
            shadowOAM[heart[i].oamIndex].attr0 |= ATTR0_HIDE;
        } else if ((heart[i].active == 1 || heartActive == 2) && !heart[i].hide && collision(heart[i].x, heart[i].y, heart[i].width, heart[i].height, hOff, vOff, SCREENWIDTH, SCREENHEIGHT)) {
            shadowOAM[heart[i].oamIndex].attr0 = ATTR0_Y(heart[i].y - vOff) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_WIDE;
            shadowOAM[heart[i].oamIndex].attr1 = ATTR1_X(heart[i].x - hOff) | ATTR1_TINY;
            shadowOAM[heart[i].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(0) | ATTR2_TILEID(0, 12);
        }
    }
}

void drawTimer() {
    if (letters[1].hide) {
        for (int i = 0; i < 15; i++) {
            shadowOAM[letters[i].oamIndex].attr0 = ATTR0_HIDE;
        }
    } else  {
        //T
        shadowOAM[letters[1].oamIndex].attr0 = ATTR0_Y(2) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[letters[1].oamIndex].attr1 = ATTR1_X(2) | ATTR1_TINY;
        shadowOAM[letters[1].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY (0) | ATTR2_TILEID(27, 0);

        //I
        shadowOAM[letters[2].oamIndex].attr0 = ATTR0_Y(2) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[letters[2].oamIndex].attr1 = ATTR1_X(10) | ATTR1_TINY;
        shadowOAM[letters[2].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY (0) | ATTR2_TILEID(16, 0);

        //M
        shadowOAM[letters[3].oamIndex].attr0 = ATTR0_Y(2) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[letters[3].oamIndex].attr1 = ATTR1_X(18) | ATTR1_TINY;
        shadowOAM[letters[3].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY (0) | ATTR2_TILEID(20, 0);

        //E
        shadowOAM[letters[4].oamIndex].attr0 = ATTR0_Y(2) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[letters[4].oamIndex].attr1 = ATTR1_X(26) | ATTR1_TINY;
        shadowOAM[letters[4].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY (0) | ATTR2_TILEID(12, 0);

        //L
        shadowOAM[letters[5].oamIndex].attr0 = ATTR0_Y(2) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[letters[5].oamIndex].attr1 = ATTR1_X(42) | ATTR1_TINY;
        shadowOAM[letters[5].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY (0) | ATTR2_TILEID(19, 0);

        //E
        shadowOAM[letters[6].oamIndex].attr0 = ATTR0_Y(2) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[letters[6].oamIndex].attr1 = ATTR1_X(50) | ATTR1_TINY;
        shadowOAM[letters[6].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY (0) | ATTR2_TILEID(12, 0);

        //F
        shadowOAM[letters[7].oamIndex].attr0 = ATTR0_Y(2) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[letters[7].oamIndex].attr1 = ATTR1_X(58) | ATTR1_TINY;
        shadowOAM[letters[7].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY (0) | ATTR2_TILEID(13, 0);

        //T
        shadowOAM[letters[8].oamIndex].attr0 = ATTR0_Y(2) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[letters[8].oamIndex].attr1 = ATTR1_X(66) | ATTR1_TINY;
        shadowOAM[letters[8].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY (0) | ATTR2_TILEID(27, 0);

        //:
        shadowOAM[letters[9].oamIndex].attr0 = ATTR0_Y(2) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[letters[9].oamIndex].attr1 = ATTR1_X(74) | ATTR1_TINY;
        shadowOAM[letters[9].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY (0) | ATTR2_TILEID(18, 1);

        // //(0)0 : 00
        // shadowOAM[letters[10].oamIndex].attr0 = ATTR0_Y(2) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
        // shadowOAM[letters[10].oamIndex].attr1 = ATTR1_X(90) | ATTR1_TINY;
        // shadowOAM[letters[10].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY (0) | ATTR2_TILEID(8, 1);

        //0(0) : 00
        shadowOAM[letters[11].oamIndex].attr0 = ATTR0_Y(2) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[letters[11].oamIndex].attr1 = ATTR1_X(90) | ATTR1_TINY;
        shadowOAM[letters[11].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY (0) | ATTR2_TILEID(8 + minOnes, 1);

        //:
        shadowOAM[letters[12].oamIndex].attr0 = ATTR0_Y(2) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[letters[12].oamIndex].attr1 = ATTR1_X(98) | ATTR1_TINY;
        shadowOAM[letters[12].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY (0) | ATTR2_TILEID(18, 1);

        //00 : (0)0
        shadowOAM[letters[13].oamIndex].attr0 = ATTR0_Y(2) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[letters[13].oamIndex].attr1 = ATTR1_X(106) | ATTR1_TINY;
        shadowOAM[letters[13].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY (0) | ATTR2_TILEID(8 + secTens, 1);

        //00 : 0(0)
        shadowOAM[letters[14].oamIndex].attr0 = ATTR0_Y(2) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[letters[14].oamIndex].attr1 = ATTR1_X(114) | ATTR1_TINY;
        shadowOAM[letters[14].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY (0) | ATTR2_TILEID(8 + secOnes, 1);
    }
}