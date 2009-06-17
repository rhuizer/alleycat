#ifndef __ALLEYCAT_SPRITES_H
#define __ALLEYCAT_SPRITES_H

#include <stdio.h>
#include <stdint.h>

struct sprite
{
	uint8_t		*data;
	size_t		size;

	/* dimensions of the sprite in pixels */
	uint16_t	width;
	uint16_t	height;
};

extern unsigned char sprite[];
extern unsigned char sprite2[];
extern unsigned char sprite3[];
extern unsigned char sprite4[];
extern unsigned char sprite_copyright[];
extern unsigned char sprite6[];
extern unsigned char sprite_ibm_corp[];
extern unsigned char sprite_synsoft[];
extern unsigned char gate_top[4][16];
extern unsigned char gate_hole[4][10];
extern unsigned char gate_underside_hole[];
extern unsigned char tmp[];
extern unsigned char tmp2[];
extern unsigned char tmp3[];


extern unsigned char sprite_digits[10][16];
extern unsigned char sprite_letter_I[];
extern unsigned char sprite_exclamation_mark[];
extern unsigned char sprite_letter_H[];
extern unsigned char sprite_hyphen[];
extern unsigned char sprite_letter_C[];
extern unsigned char sprite_letter_A[];
extern unsigned char sprite_letter_T[];
extern unsigned char sprite_letter_L[];
extern unsigned char sprite_letter_V[];
extern unsigned char sprite_letter_E[];
extern unsigned char sprite_letter_M[];
extern unsigned char sprite_letter_U[];
extern unsigned char sprite_letter_S[];
extern unsigned char sprite_letter_K[];
extern unsigned char sprite_trashcan_lid[];
extern unsigned char sprite_trashcan_middle[];
extern unsigned char sprite_trashcan_bottom[];

extern unsigned char sprite_cat_swim_right[];
extern unsigned char sprite_cat[];
extern unsigned char unknown1[];
extern unsigned char unknown2[];
extern unsigned char unknown3[];
extern unsigned char unknown4[];
extern unsigned char unknown5[];

extern struct sprite sprite_cat_walk_right1;
extern struct sprite sprite_cat_walk_right2;
extern struct sprite sprite_cat_walk_right3;
extern struct sprite sprite_cat_walk_right4;
extern struct sprite sprite_cat_walk_right5;
extern struct sprite sprite_cat_walk_right6;
extern struct sprite sprite_cat_walk_left1;
extern struct sprite sprite_cat_walk_left2;
extern struct sprite sprite_cat_walk_left3;
extern struct sprite sprite_cat_walk_left4;
extern struct sprite sprite_cat_walk_left5;
extern struct sprite sprite_cat_walk_left6;

extern struct sprite sprite_cat_head_front1;
extern struct sprite sprite_cat_head_front2;
extern struct sprite sprite_cat_head_back;
extern struct sprite sprite_cat_body1;
extern struct sprite sprite_cat_body2;
extern struct sprite sprite_cat_body3;

#endif
