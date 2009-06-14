#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL/SDL.h>
#include "cat.h"
#include "rand.h"
#include "sprites.h"
#include "sound.h"
#include "wrapper_sdl.h"

#define ALLEYCAT_COMPANY_LOGO_REDRAW_EVENT	1

/* Timer measured in IBM PC BIOS system time ticks */
struct timer
{
	int		type;
	uint32_t	expires;
	void		*cookie;
};


/* Prototypes */
void alleycat_draw_company_logo(SDL_Surface *screen);

/* Global variables */

/* Initialize SDL layer, check arguments for sanity and so on.
 */
void init(int argc, char **argv)
{
	rand_init();

	/* Bah, such bollocks... */
	putenv("SDL_VIDEO_CENTERED=1");
	xSDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	SDL_WM_SetCaption("AlleyCat", "AlleyCat");

	/* Enable key repetition */
	xSDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,
	                     SDL_DEFAULT_REPEAT_INTERVAL);
}

void
handleEvents(SDL_Surface *screen, struct alleycat_cat *cat)
{
	SDL_Event event;

	while( 1 ) {
		xSDL_WaitEvent(&event);
		switch(event.type) {
		case SDL_USEREVENT:
			if (event.user.code == ALLEYCAT_COMPANY_LOGO_REDRAW_EVENT) {
				alleycat_draw_company_logo(screen);
				SDL_Flip(screen);
			}
			break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym) {
			case SDLK_ESCAPE:
				xSDL_Quit();
				exit(EXIT_SUCCESS);
			case SDLK_RETURN:
				if ( (SDL_GetModState() & KMOD_ALT) != 0)
					SDL_WM_ToggleFullScreen(screen);
				break;
			case SDLK_RIGHT:
				alleycat_cat_walk(cat, 1);
				alleycat_cat_blit(cat, screen, 0, 0);
				SDL_Flip(screen);
				break;
			default:
				break;
			}
			break;
		case SDL_QUIT:
			xSDL_Quit();
			exit(EXIT_SUCCESS);
		}
	}
}

/* The full internal CGI 16-color palette */
SDL_Color cga_palette[16] = {
	/* Low intensity palette */
	{ 0x00, 0x00, 0x00, 0x00 },	{ 0x00, 0x00, 0xAA, 0x00 },
	{ 0x00, 0xAA, 0x00, 0x00 },	{ 0x00, 0xAA, 0xAA, 0x00 },
	{ 0xAA, 0x00, 0x00, 0x00 },	{ 0xAA, 0x00, 0xAA, 0x00 },
	{ 0xAA, 0x55, 0x00, 0x00 },	{ 0xAA, 0xAA, 0xAA, 0x00 },
	/* High intensity palette */
	{ 0x55, 0x55, 0x55, 0x00 },	{ 0x55, 0x55, 0xFF, 0x00 },
	{ 0x55, 0xFF, 0x55, 0x00 },	{ 0x55, 0xFF, 0xFF, 0x00 },
	{ 0xFF, 0x55, 0x55, 0x00 },	{ 0xFF, 0x55, 0xFF, 0x00 },
	{ 0xFF, 0xFF, 0x55, 0x00 },	{ 0xFF, 0xFF, 0xFF, 0x00 }
};

const size_t cga_palette_entries = 16;

int cga_palette_0[] = { 0, 10, 12, 14 };
int cga_palette_1[] = { 0, 11, 13, 15 };

static inline int map_cga_location(int loc)
{
	if (loc >= 0x1F30 && loc < 0x2000 || loc >= 0x3E80) {
		printf("WTF?\n");
		xSDL_Quit();
	}

	/* odd scanlines */
	if (loc >= 0x2000) {
		loc -= 0x2000;
		return (loc + (loc / 80) * 80) * 4 + 320;
	}

	return (loc + (loc / 80) * 80) * 4;
}

void alleycat_draw_fill(SDL_Surface *screen, uint8_t val)
{
	uint8_t *pixel = screen->pixels;
	uint8_t *end = screen->pixels + screen->w * screen->h;

	while (pixel < end) {
		*pixel++ = cga_palette_1[(val >> 6) & 0x3];
		*pixel++ = cga_palette_1[(val >> 4) & 0x3];
		*pixel++ = cga_palette_1[(val >> 2) & 0x3];
		*pixel++ = cga_palette_1[(val >> 0) & 0x3];
	}
}

void alleycat_draw_fill_word(SDL_Surface *screen, int loc, uint16_t val, int times)
{
	unsigned int i;
	uint8_t *pixel = screen->pixels + (loc + (loc / 80) * 80) * 4;

	for (i = 0; i < times; i++) {
		*pixel++ = cga_palette_1[(val >>  6) & 0x3];
		*pixel++ = cga_palette_1[(val >>  4) & 0x3];
		*pixel++ = cga_palette_1[(val >>  2) & 0x3];
		*pixel++ = cga_palette_1[(val >>  0) & 0x3];
		*pixel++ = cga_palette_1[(val >> 14) & 0x3];
		*pixel++ = cga_palette_1[(val >> 12) & 0x3];
		*pixel++ = cga_palette_1[(val >> 10) & 0x3];
		*pixel++ = cga_palette_1[(val >>  8) & 0x3];
	}
}

void alleycat_draw_overlay(SDL_Surface *screen, uint8_t *sprite, int w, int h, int loc)
{
	int i, j;
	uint8_t *pixel = screen->pixels + map_cga_location(loc);

	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			*pixel++ &= cga_palette_1[(*sprite >> 6) & 0x3];
			*pixel++ &= cga_palette_1[(*sprite >> 4) & 0x3];
			*pixel++ &= cga_palette_1[(*sprite >> 2) & 0x3];
			*pixel++ &= cga_palette_1[(*sprite >> 0) & 0x3];
			sprite++;
		}
		pixel += 320 - w * 4;
	}
}

void alleycat_draw_sprite(SDL_Surface *screen, uint8_t *sprite, int w, int h, int loc)
{
	int i, j;
	uint8_t *pixel = screen->pixels + map_cga_location(loc);

	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			*pixel++ = cga_palette_1[(*sprite >> 6) & 0x3];
			*pixel++ = cga_palette_1[(*sprite >> 4) & 0x3];
			*pixel++ = cga_palette_1[(*sprite >> 2) & 0x3];
			*pixel++ = cga_palette_1[(*sprite >> 0) & 0x3];
			sprite++;
		}
		pixel += 320 - w * 4;
	}
}

int alleycat_draw_struct_sprite(SDL_Surface *screen, struct sprite *sprite)
{
	int i, j;
	uint8_t *data = sprite->data;
	uint8_t *pixel = screen->pixels; // + map_cga_location(loc);
	uint8_t *start = screen->pixels;

	/* We do not clip, but only draw if there is space.  Clipping will be done in
	 * SDL itself with SDL_BlitSurface().
	 */
	if (screen->w < sprite->width || screen->h < sprite->height)
		return -1;

	for (i = 0; i < sprite->height; i++) {
		for (j = 0; j < sprite->width / 4; j++) {
			*pixel++ = cga_palette_1[(*data >> 6) & 0x3];
			*pixel++ = cga_palette_1[(*data >> 4) & 0x3];
			*pixel++ = cga_palette_1[(*data >> 2) & 0x3];
			*pixel++ = cga_palette_1[(*data >> 0) & 0x3];
			data++;
		}

		/* Handle remainder bits */
		switch(sprite->width % 4) {
		case 3:
			*pixel++ = cga_palette_1[(*data >> 6) & 0x3];
		case 2:
			*pixel++ = cga_palette_1[(*data >> 4) & 0x3];
		case 1:
			*pixel++ = cga_palette_1[(*data >> 2) & 0x3];
			printf("REM!\n");
		}
		pixel += screen->pitch -
		         sprite->width * screen->format->BytesPerPixel;
	}
}

void alleycat_draw_fence(SDL_Surface *screen)
{
	unsigned int i, j;

	/* Build randomized top of the fence */
	rand_no_repeat_last(1);
	for (i = 4160; i < 4240; i += 2) {
		uint32_t n = rand_uint32_range(0, 3);

		alleycat_draw_sprite(screen, gate_top[n], 0x01 * 2, 0x08, i);
	}

	/* Build the rest of the fence */
	alleycat_draw_fill_word(screen, 4480, 0x5655, 1280 * 2);

	rand_no_repeat_last(0);
	for (i = 0; i < 4; i++) {
		for (j = 9; j != 0; j--) {
			uint32_t n = rand_uint32() & 0x776;

			alleycat_draw_sprite(screen, gate_hole[i],
			                     0x01 * 2, 0x05, 4800 + n);
		}
	}

	for (i = 5; i != 0; i--) {
		uint32_t n = rand_uint32() & 0x3E;

		alleycat_draw_sprite(screen, gate_underside_hole,
		                     0x01 * 2, 0x05, 15000 + n);
	}
}

void alleycat_draw_trashcan(SDL_Surface *screen, int loc)
{
	unsigned int i;

	alleycat_draw_sprite(screen, sprite_trashcan_lid, 0x05 * 2, 0x0C, loc);
	loc += 0x1E0;

	for (i = loc > 0x1720 + 0x1E0 ? 2 : 3; i > 0; i--) {
		alleycat_draw_sprite(screen, sprite_trashcan_middle, 0x04 * 2, 0x08, loc);
		loc += 0x140;
	}

	alleycat_draw_sprite(screen, sprite_trashcan_bottom, 0x04 * 2, 0x0B, loc);
}

void alleycat_draw_score(SDL_Surface *screen, uint8_t *score, int loc)
{
	unsigned int i;

	for (i = 0; i < 3; i++) {
		alleycat_draw_sprite(screen, sprite_digits[score[i]], 2, 8, loc);
		loc += 2;
	}

	for (i = 3; i < 7; i++) {
		loc += 2;
		alleycat_draw_sprite(screen, sprite_digits[score[i]], 2, 8, loc);
	}
}

void alleycat_draw_cats(SDL_Surface *screen, uint8_t cats, int loc)
{
	if (cats == 255)
		return;

	alleycat_draw_sprite(screen, sprite_digits[cats], 2, 8, loc);
}

void alleycat_draw_company_logo(SDL_Surface *screen)
{
	static int flag = 0;

	flag += 2;
	alleycat_draw_sprite(screen, flag & 2 ? sprite_synsoft : sprite_ibm_corp, 0x0A * 2, 0x0C, 7480);
}

void alleycat_surface_load_cat(SDL_Surface *cat)
{
	
}

static Uint32 timer_handler(Uint32 interval, void *param)
{
	SDL_Event event;
	SDL_UserEvent userevent;
	struct timer *timer = (struct timer *) param;

	userevent.type = SDL_USEREVENT;
	userevent.code = timer->type;
	userevent.data1 = timer->cookie;
	userevent.data2 = NULL;

	event.type = SDL_USEREVENT;
	event.user = userevent;

	SDL_PushEvent(&event);
	return interval;
}

int alleycat_register_timer(struct timer *timer)
{
	xSDL_AddTimer((Uint32)(timer->expires * 1000.0 / 18.204),
	              timer_handler, timer);
}

int main(int argc, char **argv)
{
	int i, bla;
	SDL_Rect block;
	SDL_Surface *screen;
	uint8_t cats = 9;
	struct alleycat_cat cat;
	struct timer timer_company;
	uint8_t score[7], hi_score[7];

	init(argc, argv);
	
	screen = xSDL_SetVideoMode(320, 200, 8, SDL_HWSURFACE | SDL_HWPALETTE);
	SDL_SetColors(screen, cga_palette, 0, 16);

	memset(score, 0, sizeof(score));
	memset(hi_score, 0, sizeof(hi_score));
	
	SDL_LockSurface(screen);
#if 0
	block.x = block.y = 0;
	block.h	= 200;
	block.w = 20;

	for (i = 0; i < cga_palette_entries; i++) {
	SDL_FillRect(screen, &block, SDL_MapRGB(screen->format,
		cga_palette[i].r, cga_palette[i].g, cga_palette[i].b));

	block.x += block.w;
	}
#endif

	alleycat_draw_fill(screen, 0xAA);
	alleycat_draw_fence(screen);

	alleycat_draw_sprite(screen, sprite_letter_H, 0x02, 0x08, 4804);
	alleycat_draw_sprite(screen, sprite_letter_I, 0x02, 0x08, 4646);
	alleycat_draw_sprite(screen, sprite_exclamation_mark, 0x02, 0x08, 4488);
	alleycat_draw_sprite(screen, sprite_hyphen, 0x02, 0x08, 4816);
	alleycat_draw_sprite(screen, sprite_hyphen, 0x02, 0x08, 5186);
	alleycat_draw_sprite(screen, sprite_letter_C, 0x02, 0x08, 4548);
	alleycat_draw_sprite(screen, sprite_letter_A, 0x02, 0x08, 4550);
	alleycat_draw_sprite(screen, sprite_letter_T, 0x02, 0x08, 4552);
	alleycat_draw_sprite(screen, sprite_letter_L, 0x02, 0x08, 6404);
	alleycat_draw_sprite(screen, sprite_letter_L, 0x02, 0x08, 5150);
	alleycat_draw_sprite(screen, sprite_digits[0], 0x02, 0x08, 5312);
	alleycat_draw_sprite(screen, sprite_letter_V, 0x02, 0x08, 5634);
	alleycat_draw_sprite(screen, sprite_letter_E, 0x02, 0x08, 5796);
	alleycat_draw_sprite(screen, sprite_letter_T, 0x02, 0x08, 4520);
	alleycat_draw_sprite(screen, sprite_letter_H, 0x02, 0x08, 4682);
	alleycat_draw_sprite(screen, sprite_letter_E, 0x02, 0x08, 5004);
	alleycat_draw_sprite(screen, sprite_letter_M, 0x02, 0x08, 5326);
	alleycat_draw_sprite(screen, sprite_letter_M, 0x02, 0x08, 6132);
	alleycat_draw_sprite(screen, sprite_digits[0], 0x02, 0x08, 5974);
	alleycat_draw_sprite(screen, sprite_letter_U, 0x02, 0x08, 5816);
	alleycat_draw_sprite(screen, sprite_letter_S, 0x02, 0x08, 5818);
	alleycat_draw_sprite(screen, sprite_letter_I, 0x02, 0x08, 5980);
	alleycat_draw_sprite(screen, sprite_letter_E, 0x02, 0x08, 6142);
	alleycat_draw_sprite(screen, sprite_letter_S, 0x02, 0x08, 6464);

	alleycat_draw_sprite(screen, sprite_letter_K, 0x02, 0x08, 6402);

	alleycat_draw_trashcan(screen, 0x15F0);
	alleycat_draw_trashcan(screen, 0x1748);
	alleycat_draw_trashcan(screen, 0x1622);

	alleycat_draw_sprite(screen, sprite, 0x0B * 2, 0x1D, 189);
	alleycat_draw_sprite(screen, sprite2, 0x0E * 2, 0x16, 1694);
	alleycat_draw_sprite(screen, sprite3, 0x03 * 2, 0x0C, 2680);
	alleycat_draw_sprite(screen, sprite4, 0x0E * 2, 0x08, 3240);
	alleycat_draw_sprite(screen, sprite_copyright, 0x0C * 2, 0x0B, 7534);
	alleycat_draw_sprite(screen, sprite6, 0x04 * 2, 0x08, 7660);
//	alleycat_draw_sprite(screen, sprite_ibm_corp, 0x0A * 2, 0x0C, 7480);
	alleycat_draw_company_logo(screen);

	alleycat_draw_score(screen, hi_score, 0x12CA);
	alleycat_draw_score(screen, score, 0x143C);
	alleycat_draw_cats(screen, cats, 0x1260);

//	alleycat_draw_overlay(screen, sprite_cat, 0x02 * 2, 0x09, 1694);
//	alleycat_draw_sprite(screen, sprite_cat_walk_right1, 0x03 * 2, 0x0b, 1694);
//	alleycat_draw_struct_sprite(screen, &sprite_cat_walk_right1, 1694);

	if (alleycat_cat_init(&cat) == NULL) {
		printf("%s\n", SDL_GetError());
		xSDL_Quit();
		exit(EXIT_FAILURE);
	}

	SDL_UnlockSurface(screen);

	alleycat_cat_walk(&cat, 1);
	alleycat_cat_blit(&cat, screen, 30, 30);

	SDL_Flip(screen);

	/* timer tests */
	timer_company.type = ALLEYCAT_COMPANY_LOGO_REDRAW_EVENT;
	timer_company.expires = 32;
	timer_company.cookie = NULL;
	alleycat_register_timer(&timer_company);

	PCS_Init(0);

	PCS_StartProgramming();
	bla = PCS_Current();
	PCS_Push(2);
	for (i = 0; i < intro_music_size; i++) {
		uint16_t tone = tones[intro_music[i] / 2];

		if (tone == 0)
			PCS_Push(1);
		else
			PCS_Push(1193180 / tone);
	}
	PCS_Push(0);
	PCS_EndProgramming();

	PCS_Start(bla);

	handleEvents(screen, &cat);

	xSDL_Quit();
}
