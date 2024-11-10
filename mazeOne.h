
//{{BLOCK(mazeOne)

//======================================================================
//
//	mazeOne, 512x512@4, 
//	+ palette 256 entries, not compressed
//	+ 4 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x64 
//	Total size: 512 + 128 + 8192 = 8832
//
//	Time-stamp: 2024-11-06, 14:13:19
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MAZEONE_H
#define GRIT_MAZEONE_H

#define mazeOneTilesLen 128
extern const unsigned short mazeOneTiles[64];

#define mazeOneMapLen 8192
extern const unsigned short mazeOneMap[4096];

#define mazeOnePalLen 512
extern const unsigned short mazeOnePal[256];

#endif // GRIT_MAZEONE_H

//}}BLOCK(mazeOne)
