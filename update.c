#include "gba.h"
#include "sprites.h"
#include "game.h"
#include "mode0.h"
#include "spritesheet.h"
#include "mazeOneCollision.h"

inline unsigned char colorAt(int x, int y){
    return ((unsigned char *) mazeOneCollisionBitmap) [OFFSET(x, y, MAPTWOWIDTH)];

}

void updateGame() {
    updateDylan();
    updateGriever();
    updateHearts();
}

void updateDylan() {
    int leftX = dylan.x;
    int rightX = dylan.x + dylan.width - 1;
    int topY = dylan.y;
    int bottomY = dylan.y + dylan.height - 1;

    dylan.isAnimating = 0;

    if (BUTTON_HELD(BUTTON_RIGHT)) {
        dylan.isAnimating = 1;
        if (colorAt(rightX + dylan.xVel, topY) && colorAt(rightX + dylan.xVel, bottomY)) {
            dylan.x += dylan.xVel;
            dylan.direction = RIGHT;
        }
    }
    if (BUTTON_HELD(BUTTON_LEFT)) {
        dylan.isAnimating = 1;
        if (colorAt(leftX - dylan.xVel, topY) && colorAt(leftX - dylan.xVel, bottomY)) {
            dylan.x -= dylan.xVel;
            dylan.direction = LEFT;
        }
    }
    if (BUTTON_HELD(BUTTON_UP)) {
        dylan.isAnimating = 1;
        if (colorAt(leftX, topY - dylan.yVel) && colorAt(rightX, topY - dylan.yVel)) {
            dylan.y -= dylan.yVel;
            dylan.direction = UP;
        }
    }
    if (BUTTON_HELD(BUTTON_DOWN)) {
        dylan.isAnimating = 1;
        if (colorAt(leftX, bottomY + dylan.yVel) && colorAt(rightX, bottomY + dylan.yVel)) {
            dylan.y += dylan.yVel;
            dylan.direction = DOWN;
        }
    }

    if (dylan.isAnimating == 1) {
        dylan.timeUntilNextFrame--;
        if(dylan.timeUntilNextFrame == 0) {
            dylan.currentFrame = (dylan.currentFrame + 1) % dylan.numFrames;
            dylan.timeUntilNextFrame = 6;
        }
    } else {
        dylan.currentFrame = 0;
        dylan.timeUntilNextFrame = 6;
    }

    hOff = dylan.x - (SCREENWIDTH - dylan.width) / 2;
    vOff = dylan.y - (SCREENHEIGHT - dylan.height) / 2;

    if (dylan.x < 0) dylan.x = 0;
    if (dylan.y < 0) dylan.y = 0;
    if ((dylan.x + dylan.width) > MAPTWOWIDTH) dylan.x = MAPTWOWIDTH - dylan.width;
    if ((dylan.y + dylan.height) > MAPTWOHEIGHT) dylan.y = MAPTWOHEIGHT - dylan.height;

    if (hOff < 0) hOff = 0;
    if (vOff < 0) vOff = 0;
    if (hOff > (MAPTWOWIDTH - SCREENWIDTH)) hOff = (MAPTWOWIDTH - SCREENWIDTH);
    if (vOff > (MAPTWOHEIGHT - SCREENHEIGHT)) vOff = (MAPTWOHEIGHT - SCREENHEIGHT);

    //either go to next level or win
    if (collision(dylan.x, dylan.y, dylan.width, dylan.height, 254, 508, 32, 4)) {
        winGame = 1;
        hideSprites();
    }

    if (heartActive) {
            dylan.active = 1;
            dylan.erased = 0;
            dylan.hide = 0;
    }
}

void updateGriever() {
    for (int i = 0; i < 10; i++) {
        int leftX = griever[i].x;
        int rightX = griever[i].x + griever[i].width - 1;
        int topY = griever[i].y;
        int bottomY = griever[i].y + griever[i].height - 1;

        if ((colorAt(rightX - 1, topY + 1) == 1) && (colorAt(rightX - 1, bottomY - 1) == 1) && (colorAt(leftX + 1, topY + 1) == 1) && (colorAt(leftX + 1, bottomY - 1) == 1)) {
            insideMaze = 1;
        } else { 
            insideMaze = 0;
        }

        if (griever[i].active) {
            griever[i].isAnimating = 0;

            if (insideMaze) {
                griever[i].isAnimating = 1;
                if (griever[i].x < dylan.x) {
                    griever[i].x += griever[i].xVel;
                    griever[i].direction = RIGHT;
                } else if (griever[i].x > dylan.x) {
                    griever[i].x -= griever[i].xVel;
                    griever[i].direction = LEFT;
                }
                if (griever[i].y < dylan.y) {
                    griever[i].y += griever[i].yVel;
                    griever[i].direction = DOWN;
                } else if (griever[i].y > dylan.y) {
                    griever[i].y -= griever[i].yVel;
                    griever[i].direction = UP;
                }
            }

            if (griever[i].isAnimating == 1) {
                griever[i].timeUntilNextFrame--;
                if(griever[i].timeUntilNextFrame == 0) {
                    griever[i].currentFrame = (griever[i].currentFrame + 1) % griever[i].numFrames;
                    griever[i].timeUntilNextFrame = 6;
                }
            } else {
                griever[i].currentFrame = 0;
                griever[i].timeUntilNextFrame = 6;
            }
        }

        if (heartActive) {
            if (BUTTON_PRESSED(BUTTON_RSHOULDER)) {
                griever[i].active = 0;
                griever[i].erased = 1;
                griever[i].hide = 1;
            } else {
                griever[i].active = 1;
                griever[i].erased = 0;
                griever[i].hide = 0;
            }
        }

        if (collision(dylan.x, dylan.y, dylan.width, dylan.height, griever[i].x, griever[i].y, griever[i].width, griever[i].height)) {
            dylan.active = 0;
            dylan.erased = 1;
            dylan.hide = 1;
            loseGame = 1;
        }
    }
}

void updateHearts() {
    for (int i = 0; i < 3; i++) {
        if (collision(dylan.x, dylan.y, dylan.width, dylan.height, heart[i].x, heart[i].y, heart[i].width, heart[i].height)) {
            heart[i].active = 0;
            heart[i].erased = 1;
            heart[i].hide = 1;
            heartActive = 1;
        }
    }
}