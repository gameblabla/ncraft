#include "buffer.h"
#include <eris/v810.h>
#include <eris/king.h>
#include <eris/tetsu.h>
#include <eris/romfont.h>
#include <eris/cd.h>
#include <eris/low/pad.h>
#include <eris/low/scsi.h>

#ifdef _16BPP
unsigned short framebuffer[(SCREEN_GAME_WIDTH*SCREEN_GAME_HEIGHT)];
#else
unsigned char framebuffer[(SCREEN_GAME_WIDTH*SCREEN_GAME_HEIGHT)];
#endif

const u16 pornpal[] =
{
0x79A7, 0x57A7, 0x35A7, 0x0088, 0xA687, 0xD987, 0x7387, 0x5187, 0x8C6A, 0xC16A, 0xDB79, 0x4F6B, 0xE779, 0xFF88, 0xA66B, 0x907C, 
};

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

u32 padtype, paddata;

void Init_display()
{
	unsigned short i;
	u16 microprog[8];
	eris_king_init();
	eris_tetsu_init();
	
	eris_tetsu_set_priorities(0, 0, 1, 0, 0, 0, 0);
	eris_tetsu_set_king_palette(0, 0, 0, 0);
	eris_tetsu_set_rainbow_palette(0);

	eris_king_set_bg_prio(KING_BGPRIO_0, KING_BGPRIO_HIDE, KING_BGPRIO_HIDE, KING_BGPRIO_HIDE, 0);
	#ifndef _16BPP
	eris_king_set_bg_mode(KING_BGMODE_256_PAL, KING_BGPRIO_HIDE, KING_BGPRIO_HIDE, KING_BGPRIO_HIDE);
	#else
	eris_king_set_bg_mode(KING_BGMODE_64K, KING_BGPRIO_HIDE, KING_BGPRIO_HIDE, KING_BGPRIO_HIDE);
	#endif
	eris_king_set_kram_pages(0, 0, 0, 0);

	for(i = 0; i < 8; i++) {
		microprog[i] = KING_CODE_NOP;
	}

	#ifndef _16BPP
	microprog[0] = KING_CODE_BG0_CG_0;
	microprog[1] = KING_CODE_BG0_CG_1;
	microprog[2] = KING_CODE_BG0_CG_2;
	microprog[3] = KING_CODE_BG0_CG_3;
	#else
	microprog[0] = KING_CODE_BG0_CG_0;
	microprog[1] = KING_CODE_BG0_CG_1;
	microprog[2] = KING_CODE_BG0_CG_2;
	microprog[3] = KING_CODE_BG0_CG_3;
	microprog[4] = KING_CODE_BG0_CG_4;
	microprog[5] = KING_CODE_BG0_CG_5;
	microprog[6] = KING_CODE_BG0_CG_6;
	microprog[7] = KING_CODE_BG0_CG_7;	
	#endif

	eris_king_disable_microprogram();
	eris_king_write_microprogram(microprog, 0, 16);
	eris_king_enable_microprogram();
	
	#ifndef _16BPP
	eris_tetsu_set_rainbow_palette(0);
	for(i = 0; i < ARRAY_SIZE(pornpal); i++) {
		eris_tetsu_set_palette(i, pornpal[i]);
	}
	#endif

	eris_tetsu_set_video_mode(TETSU_LINES_262, 0, TETSU_DOTCLOCK_5MHz, TETSU_COLORS_16, TETSU_COLORS_16, 0, 0, 1, 0, 0, 0, 0);
	eris_king_set_bat_cg_addr(KING_BG0, 0, 0);
	eris_king_set_bat_cg_addr(KING_BG0SUB, 0, 0);
	eris_king_set_scroll(KING_BG0, 0, 0);
	eris_king_set_bg_size(KING_BG0, KING_BGSIZE_256, KING_BGSIZE_256, KING_BGSIZE_256, KING_BGSIZE_256);
	eris_pad_init(0);
	
	eris_king_set_kram_read(0, 1);
	eris_king_set_kram_write(0, 1);
	// Clear BG0's RAM
	for(i = 0x0; i < SCREEN_BYTES_SIZE; i++) {
		eris_king_kram_write(0x8080);
	}
}

void bufDisplay(void *buffer)
{
	int i;
	((void)buffer);
	
	padtype = eris_pad_type(0);
	paddata = eris_pad_read(0);
	paddata = eris_pad_read(0);
	
	eris_king_set_kram_read(0xA00, 1);
	eris_king_set_kram_write(0xA00, 1);
	// Clear BG0's RAM
	#ifdef _16BPP
	for(i = 0x0; i < SCREEN_BYTES_SIZE; i++) {
		eris_king_kram_write(framebuffer[i]);
	}
	#else
	for(i = 0x0; i < SCREEN_BYTES_SIZE; i+=2) {
		eris_king_kram_write(framebuffer[i] << 8 | framebuffer[i+1]);
	}
	#endif
}

void securedBufSetPixel(void *buffer,unsigned int x, unsigned int y,int color)
{
	if (x<SCREEN_GAME_WIDTH && y<SCREEN_GAME_HEIGHT)
	{
		bufSetPixel(buffer,x,y,color);
	}
}

void bufHorizLine(void *buffer,int x,int y,int x2, int color)
{
	int i;
	if (x>x2)
	{
		invertVars(&x,&x2);
	}
	if(x2>=0 && x<SCREEN_GAME_WIDTH && y>=0 && y<SCREEN_GAME_HEIGHT)
	{
		if(x<0)
		  x=0;
		if(x2>SCREEN_GAME_WIDTH-1)
		  x2=SCREEN_GAME_WIDTH-1;
		for(i=x;i<=x2;i++)
		{
			bufSetPixel(buffer,i,y,color);
		}
	}
}

