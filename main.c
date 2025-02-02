//Part of Scaffold
#include "gba.h"
#include "mode0.h"
#include "mode4.h"
#include "sprites.h"
#include "print.h"
#include "digitalSound.h"
//State Screen Maps and Spritesheet
#include "startScreen.h"
#include "mazeStart.h"
#include "instructScreen.h"
#include "pauseScreen.h"
#include "pauseParallax.h"
#include "loseScreen.h"
#include "winScreen.h"
#include "spritesheet.h"
//Maze One Maps
#include "mazeBackground.h"
#include "mazeOne.h"
#include "ViewMapOne.h"
//Maze Two Maps
#include "mazeTwo.h"
#include "ViewMapTwo.h"
//Maze Three Maps
#include "mazeThree.h"
#include "ViewMapThree.h"
//Bonus Maze
#include "mazeBonus.h"
//Cutscene Maps
#include "cutscenes.h"
#include "cutscenesTiles.h"
//Game One (maze one) Header File
#include "game.h"
//Background Game Sound
#include "mazeRunnerOST.h"

//Initialization Function Prototype
void initialize();

//Timers for cutscenes and view maps
void drawDialogue(volatile unsigned char* dialogue);
int getTileIDForChar(char c);
int timeUntilNextLetter = 5;
int currentIndex = 0;
int viewTimer = 120;

//Pause State Function Prototypes
void initPauseSprites();
void updatePauseSprites();
void drawPauseSprites();

//Declare shadowOAM
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
    LOSE,
    CUTSCENEBONUS,
    GAMEBONUS
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
void bonusCutscene();
void goToBonusCutscene();
void bonusGame();
void goToBonusGame();

//Button Variables
unsigned short buttons;
unsigned short oldButtons;

//Surrogate Variables
int hOff;
int vOff;
int hOffStart;
int vOffStart;
int hOffStartTwo;

//Win and Lose Game Variables
int winGame;
int loseGame;
//Level Tracker Variable
int level;

//Main Function
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
                level = 1;
                gameOne();
                break;
            case VIEWONE:
                viewMapOne();
                break;
            case CUTSCENEONE:
                cutsceneOne();
                break;
            case GAMETWO:
                level = 2;
                gameTwo();
                break;
            case VIEWTWO:
                viewMapTwo();
                break;
            case CUTSCENETWO:
                cutsceneTwo();
                break;
            case GAMETHREE:
                level = 3;
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
            case CUTSCENEBONUS:
                bonusCutscene();
                break;
            case GAMEBONUS:
                level = 4;
                bonusGame();
                break;
        }
    }
}

//Initialization Function
void initialize() {
    mgba_open();

    //set display control register and background control registers
    REG_DISPCTL = MODE(0) | BG_ENABLE(0);
    //Background 0 used for start, instruction, win, lose, pause, view map states, and cut scene states
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(14) | BG_SIZE_SMALL | BG_4BPP | 0;
    //Baackground 1 only used during game play for maze backgrounds
    REG_BG1CNT = BG_CHARBLOCK(2) | BG_SCREENBLOCK(10) | BG_SIZE_LARGE | BG_4BPP;
    //Background 2 used only during pause state for parallax movement
    REG_BG2CNT = BG_CHARBLOCK(3) | BG_SCREENBLOCK(8) | BG_SIZE_SMALL | BG_4BPP | 1;

    //set up sound functions
    setupSounds();
    setupSoundInterrupts();

    //go to start state
    goToStart();
}

//state functions
void start() {
    waitForVBlank();

    //button controls in satrt state
    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        goToInstructions();
    }
    if (BUTTON_PRESSED(BUTTON_START)) {
        initGame();
        playSoundA(mazeRunnerOST_data, mazeRunnerOST_length, 0);
        goToGameOne();
    }
    
}
void goToStart() {
    //set up start states
    REG_DISPCTL = MODE(0) | BG_ENABLE(0);
    DMANow(3, &startScreenTiles, &CHARBLOCK[0], startScreenTilesLen/2);
    DMANow(3, &startScreenMap, &SCREENBLOCK[14], startScreenMapLen/2);
    DMANow(3, &startScreenPal, BG_PALETTE, startScreenPalLen/2);

    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);
    

    state = START;
}

void instructions() {
    waitForVBlank();

    if (BUTTON_PRESSED(BUTTON_START)) {
        initGame();
        playSoundA(mazeRunnerOST_data, mazeRunnerOST_length, 0);
        goToGameOne();
    }
}
void goToInstructions() {
    REG_DISPCTL = MODE(0) | BG_ENABLE(0);
    DMANow(3, &instructScreenTiles, &CHARBLOCK[0], instructScreenTilesLen/2);
    DMANow(3, &instructScreenMap, &SCREENBLOCK[14], instructScreenMapLen/2);
    DMANow(3, &instructScreenPal, BG_PALETTE, instructScreenPalLen/2);

    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);
    
    state = INSTRUCTIONS;
}

void gameOne() {
    updateGame();
    drawGame();
    REG_BG1HOFF = hOff;
    REG_BG1VOFF = vOff;

    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);

    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        pauseSounds();
        goToPause();
    }

    if (BUTTON_PRESSED(BUTTON_B)) {
        pauseSounds();
        goToViewMapOne();
    }

    if (winGame == 1) {
        stopSounds();
        goToCutsceneOne();
    }
    if (loseGame == 1) {
        stopSounds();
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

    state = GAMEONE;
}

void viewMapOne() {
    waitForVBlank();

    if (viewTimer == 0) {
        unpauseSounds();
        goToGameOne();
        viewTimer = 120;
    } else {
        viewTimer--;
    }

}
void goToViewMapOne() {
    REG_DISPCTL = MODE(0) | BG_ENABLE(0);
    DMANow(3, &ViewMapOneTiles, &CHARBLOCK[0], ViewMapOneTilesLen/2);
    DMANow(3, &ViewMapOneMap, &SCREENBLOCK[14], ViewMapOneMapLen/2);
    DMANow(3, &ViewMapOnePal, BG_PALETTE, ViewMapOnePalLen/2);

    hideSprites();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);

    state = VIEWONE;
}

void cutsceneOne() {
    waitForVBlank();

    volatile unsigned char dialogue[] = "YOU MADE IT BACK IN TIME!     BUT... EVERYONE IS STILL      STUCK IN THE GLADE   VENTURE  BACK INTO THE MAZE TO FIND    ANOTHER WAY TO ESCAPE!        PRESS START TO BEGIN LEVEL    TWO!";
    drawDialogue(dialogue);

    if (BUTTON_PRESSED(BUTTON_START)) {
        currentIndex = 0;
        initGameTwo();
        playSoundA(mazeRunnerOST_data, mazeRunnerOST_length, 0);
        goToGameTwo();
    }

    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        currentIndex = 0;
        goToStart();
    }
}
void goToCutsceneOne() {
    REG_DISPCTL = MODE(0) | BG_ENABLE(0);
    DMANow(3, &cutscenesTilesTiles, &CHARBLOCK[0], cutscenesTilesTilesLen/2);
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

    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);

    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        pauseSounds();
        goToPause();
    }

    if (BUTTON_PRESSED(BUTTON_B)) {
        pauseSounds();
        goToViewMapTwo();
    }

    if (winGame == 1) {
        stopSounds();
        goToCutsceneTwo();
    }
    if (loseGame == 1) {
        stopSounds();
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

    state = GAMETWO;
}

void viewMapTwo() {
    waitForVBlank();

    if (viewTimer == 0) {
        unpauseSounds();
        goToGameTwo();
        viewTimer = 120;
    } else {
        viewTimer--;
    }
}
void goToViewMapTwo() {
    REG_DISPCTL = MODE(0) | BG_ENABLE(0);
    DMANow(3, &ViewMapTwoTiles, &CHARBLOCK[0], ViewMapTwoTilesLen/2);
    DMANow(3, &ViewMapTwoMap, &SCREENBLOCK[14], ViewMapTwoMapLen/2);
    DMANow(3, &ViewMapTwoPal, BG_PALETTE, ViewMapTwoPalLen/2);

    hideSprites();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);

    state = VIEWTWO;
}

void cutsceneTwo() {
    waitForVBlank();

    volatile unsigned char dialogue[] = "STILL NO LUCK ESCAPING. AND   YOU MISSED A NEW ARRIVAL AT   THE GLADE! SHE EVEN BROUGHT   ANTI VENOM TO USE FOR YOUR    LAST TRY.    PRESS THE LEFT   SHOULDER BUTTON TO INJECT.    THIS WILL PROTECT YOU FROM A  SINGLE COLLISION WITH A       GRIEVER! PRESS START TO BEGIN LEVEL THREE. GOOD LUCK!";
    drawDialogue(dialogue);

    if (BUTTON_PRESSED(BUTTON_START)) {
        initGameThree();
        playSoundA(mazeRunnerOST_data, mazeRunnerOST_length, 0);
        goToGameThree();
    }

    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        goToStart();
    }
}
void goToCutsceneTwo() {
    REG_DISPCTL = MODE(0) | BG_ENABLE(0);
    DMANow(3, &cutscenesTilesTiles, &CHARBLOCK[0], cutscenesTilesTilesLen/2);
    DMANow(3, &cutscenesMap, &SCREENBLOCK[14], cutscenesLen/2);
    DMANow(3, &cutscenesTilesPal, BG_PALETTE, cutscenesTilesPalLen/2);

    hideSprites();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);

    winGame = 0;
    loseGame = 0;
    heartActive = 0;
    currentIndex = 0;

    state = CUTSCENETWO;
}

void gameThree() {
    updateGameThree();
    drawGame();
    REG_BG1HOFF = hOff;
    REG_BG1VOFF = vOff;

    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);

    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        pauseSounds();
        goToPause();
    }

    if (BUTTON_PRESSED(BUTTON_B)) {
        pauseSounds();
        goToViewMapThree();
    }

    if (winGame == 1) {
        stopSounds();
        goToWin();
    }
    if (loseGame == 1) {
        stopSounds();
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

    state = GAMETHREE;
}

void viewMapThree() {
    waitForVBlank();

    if (viewTimer == 0) {
        unpauseSounds();
        goToGameThree();
        viewTimer = 120;
    } else {
        viewTimer--;
    }
}
void goToViewMapThree() {
    REG_DISPCTL = MODE(0) | BG_ENABLE(0);
    DMANow(3, &ViewMapThreeTiles, &CHARBLOCK[0], ViewMapThreeTilesLen/2);
    DMANow(3, &ViewMapThreeMap, &SCREENBLOCK[14], ViewMapThreeMapLen/2);
    DMANow(3, &ViewMapThreePal, BG_PALETTE, ViewMapThreePalLen/2);

    hideSprites();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);

    state = VIEWTHREE;
}

void pause() {
    hOffStart += 1;
    hOffStartTwo -= 1;
    updatePauseSprites();
    drawPauseSprites();

    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);
    REG_BG2HOFF = hOffStart;
    REG_BG0HOFF = hOffStartTwo;

    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        REG_BG0HOFF = 0;
        unpauseSounds();
        if (level == 1) {
            goToGameOne();
        } else if (level == 2) {
            goToGameTwo();
        } else if (level == 3) {
            goToGameThree();
        } else if (level == 4) {
            goToBonusGame();
        }
    }
    if (BUTTON_PRESSED(BUTTON_START)) {
        REG_BG0HOFF = 0;
        goToStart();
    }
}
void goToPause() {
    REG_DISPCTL = MODE(0) | BG_ENABLE(0) | BG_ENABLE(2) | SPRITE_ENABLE;
    DMANow(3, &pauseScreenTiles, &CHARBLOCK[0], pauseScreenTilesLen/2);
    DMANow(3, &pauseScreenMap, &SCREENBLOCK[14], pauseScreenMapLen/2);

    DMANow(3, &pauseParallaxTiles, &CHARBLOCK[3], pauseParallaxTilesLen/2);
    DMANow(3, &pauseParallaxMap, &SCREENBLOCK[8], pauseParallaxMapLen/2);
    DMANow(3, &pauseParallaxPal, BG_PALETTE, pauseParallaxPalLen/2);

    DMANow(3, spritesheetTiles, &CHARBLOCK[4], spritesheetTilesLen/2);
    DMANow(3, spritesheetPal, SPRITE_PAL, spritesheetPalLen/2);

    initPauseSprites();

    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);

    hOffStart = 0;
    vOffStart = 0;
    hOffStartTwo = 0;

    state = PAUSE;
}
//initializes sprites used during pause state (letters & dylan)
void initPauseSprites() {
    dylanPause.x = 112;
    dylanPause.y = 116;
    dylanPause.xVel = 0;
    dylanPause.yVel = 0;
    dylanPause.width = 16;
    dylanPause.height = 16;
    dylanPause.timeUntilNextFrame = 4;
    dylanPause.direction = RIGHT;
    dylanPause.isAnimating = 1;
    dylanPause.currentFrame = 0;
    dylanPause.numFrames = 4;
    dylanPause.active = 1;
    dylanPause.erased = 0;
    dylanPause.hide = 0;
    dylanPause.oamIndex = 0;

    //PAUSED
    letters[15].width = 8;
    letters[15].height = 8;
    letters[15].active = 1;
    letters[15].hide = 0;
    letters[15].oamIndex = 1;

    letters[16].width = 8;
    letters[16].height = 8;
    letters[16].active = 1;
    letters[16].hide = 0;
    letters[16].oamIndex = 2;

    letters[17].width = 8;
    letters[17].height = 8;
    letters[17].active = 1;
    letters[17].hide = 0;
    letters[17].oamIndex = 3;

    letters[18].width = 8;
    letters[18].height = 8;
    letters[18].active = 1;
    letters[18].hide = 0;
    letters[18].oamIndex = 4;

    letters[19].width = 8;
    letters[19].height = 8;
    letters[19].active = 1;
    letters[19].hide = 0;
    letters[19].oamIndex = 5;

    letters[20].width = 8;
    letters[20].height = 8;
    letters[20].active = 1;
    letters[20].hide = 0;
    letters[20].oamIndex = 6;
}
//animatesdylan sprite during pause state
void updatePauseSprites() {
    if (dylanPause.isAnimating == 1) {
        dylanPause.timeUntilNextFrame--;
        if(dylanPause.timeUntilNextFrame == 0) {
            dylanPause.currentFrame = (dylanPause.currentFrame + 1) % dylanPause.numFrames;
            dylanPause.timeUntilNextFrame = 4;
        }
    } else {
        dylanPause.currentFrame = 0;
        dylanPause.timeUntilNextFrame = 4;
    }
}
//draws the letters and dylan sprite during pause state
void drawPauseSprites() {
    shadowOAM[dylanPause.oamIndex].attr0 = ATTR0_Y(dylanPause.y) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
    shadowOAM[dylanPause.oamIndex].attr1 = ATTR1_X(dylanPause.x) | ATTR1_SMALL;
    shadowOAM[dylanPause.oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(0) | ATTR2_TILEID(dylanPause.currentFrame*2, 0);

    if (dylanPause.direction == RIGHT) {
        shadowOAM[dylanPause.oamIndex].attr1 = ATTR1_HFLIP | ATTR1_X(dylanPause.x) | ATTR1_SMALL;
    }

    for (int i = 7; i < 128; i++) {
        shadowOAM[i].attr0 = ATTR0_HIDE;
    }

    //PAUSED Letter Sprites
    shadowOAM[letters[15].oamIndex].attr0 = ATTR0_Y(60) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
    shadowOAM[letters[15].oamIndex].attr1 = ATTR1_X(96) | ATTR1_TINY;
    shadowOAM[letters[15].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY (0) | ATTR2_TILEID(23, 0);

    shadowOAM[letters[16].oamIndex].attr0 = ATTR0_Y(60) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
    shadowOAM[letters[16].oamIndex].attr1 = ATTR1_X(104) | ATTR1_TINY;
    shadowOAM[letters[16].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY (0) | ATTR2_TILEID(8, 0);

    shadowOAM[letters[17].oamIndex].attr0 = ATTR0_Y(60) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
    shadowOAM[letters[17].oamIndex].attr1 = ATTR1_X(112) | ATTR1_TINY;
    shadowOAM[letters[17].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY (0) | ATTR2_TILEID(28, 0);

    shadowOAM[letters[18].oamIndex].attr0 = ATTR0_Y(60) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
    shadowOAM[letters[18].oamIndex].attr1 = ATTR1_X(120) | ATTR1_TINY;
    shadowOAM[letters[18].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY (0) | ATTR2_TILEID(26, 0);

    shadowOAM[letters[19].oamIndex].attr0 = ATTR0_Y(60) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
    shadowOAM[letters[19].oamIndex].attr1 = ATTR1_X(128) | ATTR1_TINY;
    shadowOAM[letters[19].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY (0) | ATTR2_TILEID(12, 0);

    shadowOAM[letters[20].oamIndex].attr0 = ATTR0_Y(60) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_SQUARE;
    shadowOAM[letters[20].oamIndex].attr1 = ATTR1_X(136) | ATTR1_TINY;
    shadowOAM[letters[20].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY (0) | ATTR2_TILEID(11, 0);
}

void win() {
    waitForVBlank();

    if (BUTTON_PRESSED(BUTTON_START)){
        goToStart();
    }

    if (BUTTON_PRESSED(BUTTON_RSHOULDER)) {
        goToBonusCutscene();
    }
}
void goToWin() {
    REG_DISPCTL = MODE(0) | BG_ENABLE(0);
    DMANow(3, &winScreenTiles, &CHARBLOCK[0], winScreenTilesLen/2);
    DMANow(3, &winScreenMap, &SCREENBLOCK[14], winScreenMapLen/2);
    DMANow(3, &winScreenPal, BG_PALETTE, winScreenPalLen/2);

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
    DMANow(3, &loseScreenTiles, &CHARBLOCK[0], loseScreenTilesLen/2);
    DMANow(3, &loseScreenMap, &SCREENBLOCK[14], loseScreenMapLen/2);
    DMANow(3, &loseScreenPal, BG_PALETTE, loseScreenPalLen/2);

    hideSprites();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);

    loseGame = 0;
    state = LOSE;
}

void bonusCutscene() {
    waitForVBlank();

    volatile unsigned char dialogue[] = "OMG YOU FOUND THE HIDDEN      LEVEL! TRY TO ESCAPE THIS ONE WITH NO ANTI VENOM. HIDDEN    HEARTS. OR BEING ABLE TO SEE  THE MAP. HOWEVER YOU CAN      STILL USE YOUR SPEAR! PRESS   START TO BEGIN OR SELECT TO   GO BACK TO START SCREEN. GOOD LUCK!";
    drawDialogue(dialogue);

    if (BUTTON_PRESSED(BUTTON_START)) {
        initGameBonus();
        playSoundA(mazeRunnerOST_data, mazeRunnerOST_length, 0);
        goToBonusGame();
    }

    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        goToStart();
    }
}
void goToBonusCutscene() {
    REG_DISPCTL = MODE(0) | BG_ENABLE(0);
    DMANow(3, &cutscenesTilesTiles, &CHARBLOCK[0], cutscenesTilesTilesLen/2);
    DMANow(3, &cutscenesMap, &SCREENBLOCK[14], cutscenesLen/2);
    DMANow(3, &cutscenesTilesPal, BG_PALETTE, cutscenesTilesPalLen/2);

    hideSprites();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);

    winGame = 0;
    loseGame = 0;
    heartActive = 0;
    currentIndex = 0;

    state = CUTSCENEBONUS;
}

void bonusGame() {
    updateGameBonus();
    drawGame();
    REG_BG1HOFF = hOff;
    REG_BG1VOFF = vOff;

    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);

    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        pauseSounds();
        goToPause();
    }

    if (winGame == 1) {
        stopSounds();
        goToWin();
    }
    if (loseGame == 1) {
        stopSounds();
        goToLose();
    }
}
void goToBonusGame() {
    REG_DISPCTL = MODE(0) | BG_ENABLE(1) | SPRITE_ENABLE;
    DMANow(3, &mazeBackgroundTiles, &CHARBLOCK[2], mazeBackgroundTilesLen/2);
    DMANow(3, &mazeBonusMap, &SCREENBLOCK[10], mazeBonusLen/2);
    DMANow(3, &mazeBackgroundPal, BG_PALETTE, mazeBackgroundPalLen/2);

    DMANow(3, spritesheetTiles, &CHARBLOCK[4], spritesheetTilesLen/2);
    DMANow(3, spritesheetPal, SPRITE_PAL, spritesheetPalLen/2);

    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);

    state = GAMEBONUS;
}

//animate dialogue / words in the cutscene using tilemap modification
void drawDialogue(volatile unsigned char* dialogue) {
    int frameCounter = 0;

    if (timeUntilNextLetter == 0) {
        if (dialogue[currentIndex] != '\0') {
            int x = 1 + (currentIndex % 30);
            int y = 1 + (currentIndex / 30);

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
    } else if (c == '!') {
        return 28;
    } else if (c == '.') {
        return 27;
    } else {
        return 0;
    }
}