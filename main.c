#include "gba.h"
#include "mode0.h"
#include "sprites.h"
#include "print.h"
//state backgrounds
#include "startScreen.h"
#include "instructScreen.h"
#include "mazeOne.h"
#include "pauseScreen.h"
#include "game.h"
#include "spritesheet.h"

void initialize();

OBJ_ATTR shadowOAM[128];

enum {
    START,
    INSTRUCTIONS,
    PAUSE,
    GAME,
    WIN,
    LOSE
} state;

void start();
void goToStart();
void instructions();
void goToInstructions();
void game();
void goToGame();
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
            case GAME:
                game();
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
    REG_BG1CNT = BG_CHARBLOCK(2) | BG_SCREENBLOCK(24) | BG_SIZE_LARGE | BG_4BPP;

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
        goToGame();
    }
    
}
void goToStart() {
    REG_DISPCTL = MODE(0) | BG_ENABLE(0);
    DMANow(3, &startScreenTiles, &CHARBLOCK[0], startScreenTilesLen/2);
    DMANow(3, &startScreenMap, &SCREENBLOCK[8], startScreenMapLen/2);
    DMANow(3, &startScreenPal, BG_PALETTE, startScreenPalLen/2);

    hideSprites();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);

    state = START;
}

void instructions() {
    waitForVBlank();

    if (BUTTON_PRESSED(BUTTON_START)) {
        goToGame();
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

void game() {
    updateGame();
    drawGame();
    REG_BG1HOFF = hOff;
    REG_BG1VOFF = vOff;

    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);

    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        goToPause();
    }

    if (winGame == 1) {
        goToWin();
    }
    if (loseGame == 1) {
        goToLose();
    }

}
void goToGame() {
    REG_DISPCTL = MODE(0) | BG_ENABLE(1) | SPRITE_ENABLE;
    DMANow(3, &mazeOneTiles, &CHARBLOCK[2], mazeOneTilesLen/2);
    DMANow(3, &mazeOneMap, &SCREENBLOCK[24], mazeOneMapLen/2);
    DMANow(3, &mazeOnePal, BG_PALETTE, mazeOnePalLen/2);

    DMANow(3, spritesheetTiles, &CHARBLOCK[4], spritesheetTilesLen/2);
    DMANow(3, spritesheetPal, SPRITE_PAL, spritesheetPalLen/2);

    hideSprites();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);

    initGame();
    state = GAME;
}

void pause() {
    waitForVBlank();

    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        goToGame();
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

    state = LOSE;
}