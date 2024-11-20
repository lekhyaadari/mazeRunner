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
#include "mazeBackground.h"
#include "mazeOne.h"
#include "ViewMapOne.h"
//Maze Two Maps
#include "mazeTwo.h"
//Maze Three Maps
#include "mazeThree.h"
//Cutscene Maps
#include "cutscenes.h"
#include "cutscenesTiles.h"
//Game One (maze one) Header File
#include "game.h"

void initialize();

void drawDialogue(volatile unsigned char* dialogue);
int getTileIDForChar(char c);
int timeUntilNextLetter = 5;
int currentIndex = 0;

OBJ_ATTR shadowOAM[128];

//State Enum
enum {
    START,
    INSTRUCTIONS,
    PAUSE,
    GAMEONE,
    VIEWONE,
    CUTSCENEONE,
    GAMETWO,
    VIEWTWO,
    CUTSCENETWO,
    GAMETHREE,
    VIEWTHREE,
    WIN,
    LOSE
} state;

//Function Prototypes
void start();
void goToStart();
void instructions();
void goToInstructions();
void gameOne();
void goToGameOne();
void viewMapOne();
void goToViewMapOne();
void cutsceneOne();
void goToCutsceneOne();
void gameTwo();
void goToGameTwo();
void viewMapTwo();
void goToViewMapTwo();
void cutsceneTwo();
void goToCutsceneTwo();
void gameThree();
void goToGameThree();
void viewMapThree();
void goToViewMapThree();
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
            case CUTSCENEONE:
                cutsceneOne();
                break;
            case GAMETWO:
                gameTwo();
                break;
            case VIEWTWO:
                viewMapTwo();
                break;
            case CUTSCENETWO:
                cutsceneTwo();
                break;
            case GAMETHREE:
                gameThree();
                break;
            case VIEWTHREE:
                viewMapThree();
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
        // goToPause();
        winGame = 1; //used for testing
    }

    //TODO add timer for this
    if (BUTTON_PRESSED(BUTTON_B)) {
        goToViewMapOne();
    }

    if (winGame == 1) {
        goToCutsceneOne();
    }
    if (loseGame == 1) {
        goToLose();
    }

}
void goToGameOne() {
    REG_DISPCTL = MODE(0) | BG_ENABLE(1) | SPRITE_ENABLE;
    DMANow(3, &mazeBackgroundTiles, &CHARBLOCK[2], mazeBackgroundTilesLen/2);
    DMANow(3, &mazeOneMap, &SCREENBLOCK[10], mazeOneLen/2);
    DMANow(3, &mazeBackgroundPal, BG_PALETTE, mazeBackgroundPalLen/2);

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

void cutsceneOne() {
    waitForVBlank();

    // SCREENBLOCK[14].tilemap[OFFSET(1, 1, 32)] = TILEMAP_ENTRY_TILEID(2);
    volatile unsigned char dialogue[] = "HELLO";
    drawDialogue(dialogue);

    if (BUTTON_PRESSED(BUTTON_START)) {
        goToGameTwo();
    }

    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        goToStart();
    }

    if (BUTTON_PRESSED(BUTTON_RSHOULDER)) {
        goToWin(); //just used for testing, won't be part of final submission
    }
}
void goToCutsceneOne() {
    REG_DISPCTL = MODE(0) | BG_ENABLE(2);
    DMANow(3, &cutscenesTilesTiles, &CHARBLOCK[3], cutscenesTilesTilesLen/2);
    DMANow(3, &cutscenesMap, &SCREENBLOCK[14], cutscenesLen/2);
    DMANow(3, &cutscenesTilesPal, BG_PALETTE, cutscenesTilesPalLen/2);

    hideSprites();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);

    winGame = 0;
    loseGame = 0;
    heartActive = 0;

    state = CUTSCENEONE;
}

void gameTwo() {
    updateGameTwo();
    drawGame();
    REG_BG1HOFF = hOff;
    REG_BG1VOFF = vOff;

    // hideSprites();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);

    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        goToPause();
        // winGame = 1; //used for testing
    }

    //TODO add timer for this
    if (BUTTON_PRESSED(BUTTON_B)) {
        goToViewMapTwo();
    }

    if (winGame == 1) {
        goToCutsceneTwo();
    }
    if (loseGame == 1) {
        goToLose();
    }

}
void goToGameTwo() {
    REG_DISPCTL = MODE(0) | BG_ENABLE(1) | SPRITE_ENABLE;
    DMANow(3, &mazeBackgroundTiles, &CHARBLOCK[2], mazeBackgroundTilesLen/2);
    DMANow(3, &mazeTwoMap, &SCREENBLOCK[10], mazeTwoLen/2);
    DMANow(3, &mazeBackgroundPal, BG_PALETTE, mazeBackgroundPalLen/2);

    DMANow(3, spritesheetTiles, &CHARBLOCK[4], spritesheetTilesLen/2);
    DMANow(3, spritesheetPal, SPRITE_PAL, spritesheetPalLen/2);

    hideSprites();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);

    initGameTwo();
    state = GAMETWO;
}

void viewMapTwo() {

}
void goToViewMapTwo() {

}

void cutsceneTwo() {

}
void goToCutsceneTwo() {

}

void gameThree() {
    // updateGameThree();
    drawGame();
    REG_BG1HOFF = hOff;
    REG_BG1VOFF = vOff;

    // hideSprites();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);

    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        goToPause();
        // winGame = 1; //used for testing
    }

    //TODO add timer for this
    if (BUTTON_PRESSED(BUTTON_B)) {
        goToViewMapThree();
    }

    if (winGame == 1) {
        goToWin();
    }
    if (loseGame == 1) {
        goToLose();
    }
}
void goToGameThree() {
    REG_DISPCTL = MODE(0) | BG_ENABLE(1) | SPRITE_ENABLE;
    DMANow(3, &mazeBackgroundTiles, &CHARBLOCK[2], mazeBackgroundTilesLen/2);
    DMANow(3, &mazeThreeMap, &SCREENBLOCK[10], mazeThreeLen/2);
    DMANow(3, &mazeBackgroundPal, BG_PALETTE, mazeBackgroundPalLen/2);

    DMANow(3, spritesheetTiles, &CHARBLOCK[4], spritesheetTilesLen/2);
    DMANow(3, spritesheetPal, SPRITE_PAL, spritesheetPalLen/2);

    hideSprites();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);

    initGameThree();
    state = GAMETHREE;
}

void viewMapThree() {

}
void goToViewMapThree() {
    
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

//animate dialogue / words in the cutscene using tilemap modification
void drawDialogue(volatile unsigned char* dialogue) {
    int frameCounter = 0;

    if (timeUntilNextLetter == 0) {
        if (dialogue[currentIndex] != '\0') {
            int x = currentIndex % 32;
            int y = (currentIndex / 32) + 1;

            int tileID = getTileIDForChar(dialogue[currentIndex]);

            setTile(x, y, tileID, 14);

            currentIndex++;
        }
        timeUntilNextLetter = 5;
    } else {
        timeUntilNextLetter--;
    }
}

//Map character to tileID in cutscenes tileset
int getTileIDForChar(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 1;
    } else if (c == ' ') {
        return 0;
    } else {
        return 0;
    }
}