//macros
#include "sprites.h"
#define MAPONEWIDTH 256
#define MAPONEHEIGHT 256
#define SCREENWIDTH 240
#define SCREENHEIGHT 160
#define MAPTWOWIDTH 512
#define MAPTWOHEIGHT 512

//surrogate variables
int hOff;
int vOff;

//sprites used
SPRITE dylan;
SPRITE dylanPause;
SPRITE grieverPause;
SPRITE griever[10];
SPRITE heart[3];
SPRITE letters[20];
SPRITE spear;
//direction enum
typedef enum {UP, DOWN, RIGHT, LEFT} DIRECTION;

//int variables used
int grieverInsideMaze;
int spearInsideMaze;
int winGame;
int loseGame;
int heartActive;
int launchSpearBool;
int gameTimer;
int heartTimer;
int minutes;
int minOnes;
int secTens;
int secOnes;
int venomActive;

//Game One Function Prototypes
void initGame();
void updateGame();
void drawGame();
void initDylan();
void updateDylan();
void drawDylan();
void initGriever();
void initNewGriever();
void updateGriever();
void drawGriever();
void initSpear();
void updateSpear();
void drawSpear();
void initHearts();
void updateHearts();
void launchSpears();
void drawHearts();
void initTimer();
void updateTimer();
void drawTimer();

//Game Two Function Prototypes
void initGameTwo();
void initDylanTwo();
void initGrieversTwo();
void initNewGrieverTwo();
void initSpearTwo();
void initHeartsTwo();
void initLettersTwo();
void updateGameTwo();
void updateDylanTwo();
void updateGrieversTwo();
void updateHeartsTwo();
void updateLettersTwo();
void launchSpearTwo();

//Game Three Function Prototypes
void initGameThree();
void initDylanThree();
void initGrieversThree();
void initNewGrieverThree();
void initSpearThree();
void initHeartsThree();
void initLettersThree();
void updateGameThree();
void updateDylanThree();
void updateGrieversThree();
void updateHeartsThree();
void updateLettersThree();
void launchSpearThree();

//Hidden Level Function Prototypes
void initGameBonus();
void initDylanBonus();
void initGrieversBonus();
void initSpearBonus();
void updateGameBonus();
void updateDylanBonus();
void updateGrieversBonus();
void updateSpearBonus();
void launchSpearBonus();
void deInitSprites();

// Letters
// A - 0, B - 1, C - 2, D - 3, E - 4, F - 5, G - 6, H - 7, I - 8, J - 9, K - 10
// L - 11, M - 12, N - 13, O - 14, P - 15, Q - 16, R - 17, S - 18, T - 19, U - 20
// V - 21, W - 22, X - 23, Y - 24, Z - 25