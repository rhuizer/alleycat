#ifndef __ALLEYCAT_CAT_H
#define __ALLEYCAT_CAT_H

#include <SDL/SDL.h>

#define ALLEYCAT_CAT_DIRECTION_RIGHT 1
#define ALLEYCAT_CAT_DIRECTION_LEFT -1

struct alleycat_cat {
	SDL_Surface	*surface;
	int		direction;
	int		frame_index;

	/* stores the background overwritten by this sprite */
	int		background_dirty;
	SDL_Surface	*background;
	SDL_Rect	background_location;

	/* dimensions of the sprite and location */
	int		x;
	int		y;
	int		width;
	int		height;
};

struct alleycat_cat *alleycat_cat_init(struct alleycat_cat *cat);
void alleycat_cat_walk(struct alleycat_cat *cat, int direction);
void alleycat_cat_destroy(struct alleycat_cat *cat);

#endif
