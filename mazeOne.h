
//{{BLOCK(mazeOne)

//======================================================================
//
//	mazeOne, 512x512@4, 
//	+ palette 256 entries, not compressed
//	+ 3 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x64 
//	Total size: 512 + 96 + 8192 = 8800
//
//	Time-stamp: 2024-11-15, 14:04:50
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MAZEONE_H
#define GRIT_MAZEONE_H

#define mazeOneTilesLen 96
extern const unsigned short mazeOneTiles[48];

#define mazeOneMapLen 8192
extern const unsigned short mazeOneMap[4096];

#define mazeOnePalLen 512
extern const unsigned short mazeOnePal[256];

#endif // GRIT_MAZEONE_H

//}}BLOCK(mazeOne)
