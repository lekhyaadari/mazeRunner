
//{{BLOCK(loseScreen)

//======================================================================
//
//	loseScreen, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 589 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 512 + 18848 + 2048 = 21408
//
//	Time-stamp: 2024-11-27, 00:38:54
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_LOSESCREEN_H
#define GRIT_LOSESCREEN_H

#define loseScreenTilesLen 18848
extern const unsigned short loseScreenTiles[9424];

#define loseScreenMapLen 2048
extern const unsigned short loseScreenMap[1024];

#define loseScreenPalLen 512
extern const unsigned short loseScreenPal[256];

#endif // GRIT_LOSESCREEN_H

//}}BLOCK(loseScreen)
