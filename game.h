// #include "sprites.h"
#define MAPONEWIDTH 256
#define MAPONEHEIGHT 256
#define SCREENWIDTH 240
#define SCREENHEIGHT 160
#define MAPTWOWIDTH 512
#define MAPTWOHEIGHT 512

int hOff;
int vOff;

SPRITE dylan;
SPRITE griever[10];
SPRITE heart[3];
typedef enum {UP, DOWN, RIGHT, LEFT} DIRECTION;

int insideMaze;
int winGame;
int loseGame;
int heartActive;

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
void initHearts();
void updateHearts();
void drawHearts();

