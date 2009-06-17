/* alleycat, an opensource IBM AlleyCat 1984 implementation.
 *
 * Dedicated to Kanna Ishihara.
 *
 * Copyright (C) 2009 Ronald Huizer
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */
#ifndef __ALLEYCAT_CAT_H
#define __ALLEYCAT_CAT_H

#include <SDL/SDL.h>

#define ALLEYCAT_CAT_DIRECTION_RIGHT 1
#define ALLEYCAT_CAT_DIRECTION_LEFT -1

struct alleycat_cat {
	SDL_Surface	*surface;
	int		direction;
	int		direction_old;
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

	/* timers for periodic cat movement */
	uint32_t	timer;
	int		counter;
};

struct alleycat_cat *alleycat_cat_init(struct alleycat_cat *cat);
void alleycat_cat_walk(struct alleycat_cat *cat, int direction);
void alleycat_cat_destroy(struct alleycat_cat *cat);

#endif
