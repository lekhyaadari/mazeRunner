#include "gba.h"
#include "sprites.h"
#include "game.h"
#include "mode0.h"
#include "spritesheet.h"
#include "mazeThreeCollision.h"
#include "digitalSound.h"
#include "shotSound.h"

inline unsigned char colorAt(int x, int y){
    return ((unsigned char *) mazeThreeCollisionBitmap) [OFFSET(x, y, 512)];

}

void updateGameThree() {
    updateDylanThree();
    updateGrieversThree();
    updateSpearThree();
    updateHeartsThree();
    updateLettersThree();
    setupSoundInterrupts();
    setupSounds();
}

void updateDylanThree() {
    int leftX = dylan.x;
    int rightX = dylan.x + dylan.width - 1;
    int topY = dylan.y;
    int bottomY = dylan.y + dylan.height - 1;
    int middleX = dylan.width / 2;
    int middleY = dylan.height / 2;

    dylan.isAnimating = 0;

    if (BUTTON_HELD(BUTTON_RIGHT) && colorAt(rightX + dylan.xVel, topY) && colorAt(rightX + dylan.xVel, bottomY) && (dylan.x + dylan.width < 512) && colorAt(rightX + dylan.xVel, topY + 8)) {
        dylan.isAnimating = 1;
            dylan.x += dylan.xVel;
            dylan.direction = RIGHT;
    }
    if (BUTTON_HELD(BUTTON_LEFT) && colorAt(leftX - dylan.xVel, topY) && colorAt(leftX - dylan.xVel, bottomY) && (dylan.x > 0) && colorAt(leftX - dylan.xVel, topY + 8)) {
        dylan.isAnimating = 1;
            dylan.x -= dylan.xVel;
            dylan.direction = LEFT;
    }
    if (BUTTON_HELD(BUTTON_UP) && colorAt(leftX, topY - dylan.yVel) && colorAt(rightX, topY - dylan.yVel) && (dylan.y > 0) && colorAt(leftX + 8, topY - dylan.yVel)) {
        dylan.isAnimating = 1;
            dylan.y -= dylan.yVel;
            dylan.direction = UP;
    }
    if (BUTTON_HELD(BUTTON_DOWN) && colorAt(leftX, bottomY + dylan.yVel) && colorAt(rightX, bottomY + dylan.yVel) && (dylan.y + dylan.height < 512) && colorAt(leftX + 8, bottomY + dylan.yVel)) {
        dylan.isAnimating = 1;
            dylan.y += dylan.yVel;
            dylan.direction = DOWN;
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
    if (collision(dylan.x, dylan.y, dylan.width, dylan.height, 508, 222, 8, 52)) {
        winGame = 1;
        hideSprites();
    }

    if (heartActive) {
            dylan.active = 1;
            dylan.erased = 0;
            dylan.hide = 0;
    }

    if (venomActive == 0) {
        if (BUTTON_PRESSED(BUTTON_LSHOULDER)) {
            venomActive = 1;
        }
    }
}

void updateGrieversThree() {
    for (int i = 0; i < 10; i++) {
        int leftX = griever[i].x;
        int rightX = griever[i].x + griever[i].width - 1;
        int topY = griever[i].y;
        int bottomY = griever[i].y + griever[i].height - 1;

        if ((colorAt(rightX, topY) == 1) && (colorAt(rightX, bottomY) == 1) && (colorAt(leftX, topY) == 1) && (colorAt(leftX, bottomY) == 1)) {
            grieverInsideMaze = 1;
        } else { 
            grieverInsideMaze = 0;
        }

        if (griever[i].active) {
            griever[i].isAnimating = 1;

            if (griever[i].direction == RIGHT) {
                griever[i].x += griever[i].xVel;
                if ((colorAt(rightX + 1, topY) == 0) && (colorAt(rightX + 1, bottomY) == 0) && (colorAt(rightX + 1, topY + 8) == 0)) {
                    griever[i].direction = rand() % 4;
                }
            } else if (griever[i].direction == LEFT) {
                griever[i].x -= griever[i].xVel;
                if ((colorAt(leftX - 1, topY) == 0) && (colorAt(leftX - 1, bottomY) == 0) && (colorAt(leftX - 1, topY + 8) == 0)) {
                    griever[i].direction = rand() % 4;
                }
            }
            if (griever[i].direction == UP) {
                griever[i].y -= griever[i].yVel;
                if ((colorAt(leftX, topY - 1) == 0) && (colorAt(rightX, topY - 1) == 0)  && (colorAt(leftX + 8, topY - 1) == 0)) {
                    griever[i].direction = rand() % 4;
                }
            } else if (griever[i].direction == DOWN) {
                griever[i].y += griever[i].yVel;
                if ((colorAt(leftX, bottomY + 1) == 0) && (colorAt(rightX, bottomY + 1) == 0) && (colorAt(leftX + 8, bottomY + 1) == 0)) {
                    griever[i].direction = rand() % 4;
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

        if (heartActive == 1 || heartActive == 2) {
            if (BUTTON_HELD(BUTTON_RSHOULDER)) {
                griever[i].x = 0;
                griever[i].y = 0;
                griever[i].active = 0;
                griever[i].erased = 1;
                griever[i].hide = 1;
                griever[i].xVel = 0;
                griever[i].yVel = 0;
                heartActive = 2;
            } else {
                griever[i].active = 1;
                griever[i].erased = 0;
                griever[i].hide = 0;
            }
        }

        if (collision(dylan.x, dylan.y, dylan.width, dylan.height, griever[i].x, griever[i].y, griever[i].width, griever[i].height)) {
            if (venomActive) {
                griever[i].x = 0;
                griever[i].y = 0;
                griever[i].active = 0;
                griever[i].erased = 1;
                griever[i].hide = 1;
                griever[i].xVel = 0;
                griever[i].yVel = 0;
                venomActive = 2;
            } else {
                dylan.active = 0;
                dylan.erased = 1;
                dylan.hide = 1;
                loseGame = 1;
            }
        }

        if (collision(spear.x, spear.y, spear.width, spear.height, griever[i].x, griever[i].y, griever[i].width, griever[i].height)) {
            //return sprite
            spear.hide = 1;
            spear.x = dylan.x;
            spear.y = dylan.y;
            spear.xVel = 0;
            spear.yVel = 0;
            launchSpearBool = 0;

            //kill griever
            griever[i].x = 0;
            griever[i].y = 0;
            griever[i].active = 0;
            griever[i].erased = 1;
            griever[i].hide = 1;
            griever[i].xVel = 0;
            griever[i].yVel = 0;

            initNewGrieverThree();
            initNewGrieverThree();
            initNewGrieverThree();
        }
    }
}

void updateSpearThree() {
    if (!spear.hide) {
        spear.x += spear.xVel;
        spear.y += spear.yVel;

        int leftX = spear.x;
        int rightX = spear.x + spear.width - 1;
        int topY = spear.y;
        int bottomY = spear.y + spear.height - 1;

        if ((colorAt(rightX - 1, topY + 1) == 0) || (colorAt(rightX - 1, bottomY - 1) == 0) || (colorAt(leftX + 1, topY + 1) == 0) || (colorAt(leftX + 1, bottomY - 1) == 0)) {
            spearInsideMaze = 0;
        } else { 
            spearInsideMaze = 1;
        }

        if (!spearInsideMaze) {
            spear.hide = 1;
            spear.x = dylan.x;
            spear.y = dylan.y;
            spear.xVel = 0;
            spear.yVel = 0;
            launchSpearBool = 0;
        }
    } 

    spear.direction = dylan.direction;
    if (BUTTON_PRESSED(BUTTON_A)) {
        playSoundB(shotSound_data, shotSound_length, 0);
        launchSpear();
    }
}

void updateHeartsThree() {
    for (int i = 0; i < 3; i++) {
        if (collision(dylan.x, dylan.y, dylan.width, dylan.height, heart[i].x, heart[i].y, heart[i].width, heart[i].height)) {
            heart[i].active = 0;
            heart[i].erased = 1;
            heart[i].hide = 1;
            heart[i].x = 0;
            heart[i].y = 0;
            heartActive = 1;
        }
    }
}

void updateLettersThree() {
    if (gameTimer == 0) {
        loseGame = 1;
        gameTimer = 7200;
    } else {
        gameTimer--;
    }

    minutes = (gameTimer / 3600) % 60;
    int seconds = (gameTimer / 60) % 60;
    minOnes = minutes % 10;
    secTens = seconds / 10;
    secOnes = seconds % 10;
}