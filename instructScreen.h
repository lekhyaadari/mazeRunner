
//{{BLOCK(instructScreen)

//======================================================================
//
//	instructScreen, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 62 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 512 + 1984 + 2048 = 4544
//
//	Time-stamp: 2024-10-31, 22:45:48
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_INSTRUCTSCREEN_H
#define GRIT_INSTRUCTSCREEN_H

#define instructScreenTilesLen 1984
extern const unsigned short instructScreenTiles[992];

#define instructScreenMapLen 2048
extern const unsigned short instructScreenMap[1024];

#define instructScreenPalLen 512
extern const unsigned short instructScreenPal[256];

#endif // GRIT_INSTRUCTSCREEN_H

//}}BLOCK(instructScreen)
