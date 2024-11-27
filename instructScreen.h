
//{{BLOCK(instructScreen)

//======================================================================
//
//	instructScreen, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 601 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 512 + 19232 + 2048 = 21792
//
//	Time-stamp: 2024-11-27, 00:18:29
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_INSTRUCTSCREEN_H
#define GRIT_INSTRUCTSCREEN_H

#define instructScreenTilesLen 19232
extern const unsigned short instructScreenTiles[9616];

#define instructScreenMapLen 2048
extern const unsigned short instructScreenMap[1024];

#define instructScreenPalLen 512
extern const unsigned short instructScreenPal[256];

#endif // GRIT_INSTRUCTSCREEN_H

//}}BLOCK(instructScreen)
