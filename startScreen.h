
//{{BLOCK(startScreen)

//======================================================================
//
//	startScreen, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 600 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 512 + 19200 + 2048 = 21760
//
//	Time-stamp: 2024-11-26, 11:28:55
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_STARTSCREEN_H
#define GRIT_STARTSCREEN_H

#define startScreenTilesLen 19200
extern const unsigned short startScreenTiles[9600];

#define startScreenMapLen 2048
extern const unsigned short startScreenMap[1024];

#define startScreenPalLen 512
extern const unsigned short startScreenPal[256];

#endif // GRIT_STARTSCREEN_H

//}}BLOCK(startScreen)
