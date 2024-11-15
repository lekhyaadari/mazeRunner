//Part of Scaffold
#include "gba.h"
#include "mode0.h"
#include "sprites.h"
#include "print.h"
//State Screen Maps and Spritesheet
#include "startScreen.h"
#include "instructScreen.h"
#include "pauseScreen.h"
#include "spritesheet.h"
//Maze One Maps
#include "mazeOne.h"
#include "ViewMapOne.h"
//Maze Two Maps

//Maze Three Maps

//Game One (maze one) Header File
#include "gameOne.h"

void initialize();

OBJ_ATTR shadowOAM[128];

//State Enum
enum {
    START,
    INSTRUCTIONS,
    PAUSE,
    GAMEONE,
    VIEWONE,
    WIN,
    LOSE
} state;

void start();
void goToStart();
void instructions();
void goToInstructions();
void gameOne();
void goToGameOne();
void viewMapOne();
void goToViewMapOne();
void pause();
void goToPause();
void win();
void goToWin();

//button variables
unsigned short buttons;
unsigned short oldButtons;

//surrogate variables
int hOff;
int vOff;

//win and lose game
int winGame;
int loseGame;

int main() {
    
    initialize();

    while(1) {

        //update buttons
        oldButtons = buttons;
        buttons = REG_BUTTONS;

        switch (state) {
            case START:
                start();
                break;
            case PAUSE:
                pause();
                break;
            case INSTRUCTIONS:
                instructions();
                break;
            case GAMEONE:
                gameOne();
                break;
            case VIEWONE:
                viewMapOne();
                break;
            case WIN:
                win();
                break;
            case LOSE:
                lose();
                break;
        }
    }
}

void initialize() {
    mgba_open();

    REG_DISPCTL = MODE(0) | BG_ENABLE(0);
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(8) | BG_SIZE_SMALL | BG_4BPP;
    REG_BG1CNT = BG_CHARBLOCK(2) | BG_SCREENBLOCK(10) | BG_SIZE_LARGE | BG_4BPP;
    REG_BG2CNT = BG_CHARBLOCK(3) | BG_SCREENBLOCK(14) | BG_SIZE_SMALL | BG_4BPP;

    // REG_BG0HOFF = hOff;
    // REG_BG0VOFF = vOff;

    goToStart();
}

void start() {
    waitForVBlank();

    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        goToInstructions();
    }
    if (BUTTON_PRESSED(BUTTON_START)) {
        goToGameOne();
    }
    
}
void goToStart() {
    REG_DISPCTL = MODE(0) | BG_ENABLE(0);
    DMANow(3, &startScreenTiles, &CHARBLOCK[0], startScreenTilesLen/2);
    DMANow(3, &startScreenMap, &SCREENBLOCK[8], startScreenMapLen/2);
    DMANow(3, &startScreenPal, BG_PALETTE, startScreenPalLen/2);

    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);

    state = START;
}

void instructions() {
    waitForVBlank();

    if (BUTTON_PRESSED(BUTTON_START)) {
        goToGameOne();
    }
}
void goToInstructions() {
    REG_DISPCTL = MODE(0) | BG_ENABLE(0);
    DMANow(3, &instructScreenTiles, &CHARBLOCK[0], instructScreenTilesLen/2);
    DMANow(3, &instructScreenMap, &SCREENBLOCK[8], instructScreenMapLen/2);
    DMANow(3, &instructScreenPal, BG_PALETTE, instructScreenPalLen/2);

    hideSprites();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);
    
    state = INSTRUCTIONS;
}

void gameOne() {
    updateGame();
    drawGame();
    REG_BG1HOFF = hOff;
    REG_BG1VOFF = vOff;

    // hideSprites();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);

    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        goToPause();
    }

    //TODO add timer for this
    if (BUTTON_PRESSED(BUTTON_B)) {
        goToViewMapOne();
    }

    if (winGame == 1) {
        goToWin();
    }
    if (loseGame == 1) {
        goToLose();
    }

}
void goToGameOne() {
    REG_DISPCTL = MODE(0) | BG_ENABLE(1) | SPRITE_ENABLE;
    DMANow(3, &mazeOneTiles, &CHARBLOCK[2], mazeOneTilesLen/2);
    DMANow(3, &mazeOneMap, &SCREENBLOCK[10], mazeOneMapLen/2);
    DMANow(3, &mazeOnePal, BG_PALETTE, mazeOnePalLen/2);

    DMANow(3, spritesheetTiles, &CHARBLOCK[4], spritesheetTilesLen/2);
    DMANow(3, spritesheetPal, SPRITE_PAL, spritesheetPalLen/2);

    hideSprites();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);

    initGame();
    state = GAMEONE;
}

void viewMapOne() {
    waitForVBlank();

    if (BUTTON_PRESSED(BUTTON_LSHOULDER)) {
        goToGameOne();
    }
}
void goToViewMapOne() {
    REG_DISPCTL = MODE(0) | BG_ENABLE(2);
    DMANow(3, &ViewMapOneTiles, &CHARBLOCK[3], ViewMapOneTilesLen/2);
    DMANow(3, &ViewMapOneMap, &SCREENBLOCK[14], ViewMapOneMapLen/2);
    DMANow(3, &ViewMapOnePal, BG_PALETTE, ViewMapOnePalLen/2);

    hideSprites();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);

    state = VIEWONE;
}

void pause() {
    waitForVBlank();

    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        goToGameOne();
    }
    if (BUTTON_PRESSED(BUTTON_START)) {
        goToStart();
    }

}
void goToPause() {
    REG_DISPCTL = MODE(0) | BG_ENABLE(0);
    DMANow(3, &pauseScreenTiles, &CHARBLOCK[0], pauseScreenTilesLen/2);
    DMANow(3, &pauseScreenMap, &SCREENBLOCK[8], pauseScreenMapLen/2);
    DMANow(3, &pauseScreenPal, BG_PALETTE, pauseScreenPalLen/2);

    hideSprites();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);

    state = PAUSE;
}

void win() {
    waitForVBlank();

    if (BUTTON_PRESSED(BUTTON_START)){
        goToStart();
    }
}
void goToWin() {
    REG_DISPCTL = MODE(0) | BG_ENABLE(0);
    DMANow(3, &instructScreenTiles, &CHARBLOCK[0], instructScreenTilesLen/2);
    DMANow(3, &instructScreenMap, &SCREENBLOCK[8], instructScreenMapLen/2);
    DMANow(3, &instructScreenPal, BG_PALETTE, instructScreenPalLen/2);

    hideSprites();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);

    winGame = 0;
    state = WIN;
}

void lose() {
    waitForVBlank();

    if (BUTTON_PRESSED(BUTTON_START)){
        goToStart();
    }
}
void goToLose() {
    REG_DISPCTL = MODE(0) | BG_ENABLE(0);
    DMANow(3, &instructScreenTiles, &CHARBLOCK[0], instructScreenTilesLen/2);
    DMANow(3, &instructScreenMap, &SCREENBLOCK[8], instructScreenMapLen/2);
    DMANow(3, &instructScreenPal, BG_PALETTE, instructScreenPalLen/2);

    hideSprites();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);

    loseGame = 0;
    state = LOSE;
}