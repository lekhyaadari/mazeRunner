#ifndef GBA_MODE0_H
#define GBA_MODE0_H

#include "gba.h"

// Background Control Registers
#define REG_BG0CNT (*(volatile unsigned short*) 0x4000008) // Background 0 control register
#define REG_BG1CNT (*(volatile unsigned short*) 0x400000A) // Background 1 control register
#define REG_BG2CNT (*(volatile unsigned short*) 0x400000C) // Background 2 control register
#define REG_BG3CNT (*(volatile unsigned short*) 0x400000E) // Background 3 control register

#define REG_BG0HOFF (*(volatile unsigned short*) 0x04000010) // Background 0 horizontal offset register
#define REG_BG0VOFF (*(volatile unsigned short*) 0x04000012) // Background 0 vertical offset register
#define REG_BG1HOFF (*(volatile unsigned short*) 0x04000014) // Background 1 horizontal offset register
#define REG_BG1VOFF (*(volatile unsigned short*) 0x04000016) // Background 1 vertical offset register
#define REG_BG2HOFF (*(volatile unsigned short*) 0x04000018) // Background 2 horizontal offset register
#define REG_BG2VOFF (*(volatile unsigned short*) 0x0400001A) // Background 2 vertical offset register
#define REG_BG3HOFF (*(volatile unsigned short*) 0x0400001C) // Background 3 horizontal offset register
#define REG_BG3VOFF (*(volatile unsigned short*) 0x0400001E) // Background 3 vertical offset register

// Background Control Register bits
#define BG_CHARBLOCK(n) ((n) << 2)   // Sets which charblock this background should use
#define BG_SCREENBLOCK(n) ((n) << 8) // Sets which screenblock this background should use
#define BG_4BPP (0 << 7) 		     // Sets background to 4bpp mode
#define BG_8BPP (1 << 7) 			 // Sets background to 8bpp mode
#define BG_SIZE_SMALL (0 << 14) 	 // Sets background size to 32x32 tiles
#define BG_SIZE_WIDE (1 << 14)  	 // Sets background size to 64x32 tiles
#define BG_SIZE_TALL (2 << 14)   	 // Sets background size to 32x64 tiles
#define BG_SIZE_LARGE (3 << 14)  	 // Sets background size to 64x64 tiles

// Charblocks
typedef struct {
	u16 tileimg[8192];
} CB;
#define CHARBLOCK ((CB*) 0x6000000) // Character blocks (tilesets)

// Screenblocks
typedef struct {
	u16 tilemap[1024];
} SB;
#define SCREENBLOCK ((SB*) 0x6000000) // Screen blocks (tilemaps)

// Tilemap Entry Bits
#define TILEMAP_ENTRY_TILEID(x) (x & 1023)
#define TILEMAP_ENTRY_HFLIP (1 << 10)
#define TILEMAP_ENTRY_VFLIP (1 << 11)
#define TILEMAP_ENTRY_PALROW(x) ((x & 15) << 12)

#define setTile(tileX, tileY, tileEntry, sb) (SCREENBLOCK[sb].tilemap[OFFSET(tileX, tileY, 32)] = (tileEntry))

#endif
