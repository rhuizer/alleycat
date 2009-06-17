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
#include <stdio.h>
#include <SDL/SDL.h>
#include "cat.h"
#include "sprites.h"

static struct sprite *cat_walk_right_table[] = {
	&sprite_cat_walk_right1,
	&sprite_cat_walk_right2,
	&sprite_cat_walk_right3,
	&sprite_cat_walk_right4,
	&sprite_cat_walk_right5,
	&sprite_cat_walk_right6
};

static struct sprite *cat_walk_left_table[] = {
	&sprite_cat_walk_left1,
	&sprite_cat_walk_left2,
	&sprite_cat_walk_left3,
	&sprite_cat_walk_left4,
	&sprite_cat_walk_left5,
	&sprite_cat_walk_left6
};

/* seg001:0F92 */
static struct sprite *cat_head_table[] = {
	&sprite_cat_head_front1,
	&sprite_cat_head_front2,
	&sprite_cat_head_front1,
	&sprite_cat_head_front2,
	&sprite_cat_head_front1,
	&sprite_cat_head_front2,
	&sprite_cat_head_front1,
	&sprite_cat_head_back
};

/* seg001:0FA2 */
static struct sprite *cat_body_table[] = {
	&sprite_cat_body1,
	&sprite_cat_body2,
	&sprite_cat_body3,
	&sprite_cat_body3
};

/* Create a SDL surface used for drawing the cat */
struct alleycat_cat *alleycat_cat_init(struct alleycat_cat *cat)
{
	Uint32 key;
	SDL_Surface *surface;

	/* Create a hardware accelerated surface.  The original alleycat
	 * clips are of different sizes, so we simply create a 30x30
	 * surface and will clip it properly when blitting.
	 */
	surface = SDL_CreateRGBSurface(SDL_HWSURFACE,
	                               30, 30, 8, 0, 0, 0, 0);
	if (surface == NULL)
		return NULL;

	/* Optimize the surface for use with the current display format.
	 * We create a second surface for holding the original background.
	 */
	cat->surface = SDL_DisplayFormat(surface);
	cat->background = SDL_DisplayFormat(surface);
	SDL_FreeSurface(surface);
	if (cat->surface == NULL || cat->background == NULL) {
		SDL_FreeSurface(cat->surface);
		SDL_FreeSurface(cat->background);
		return NULL;
	}

	/* Convert the color white to the one in the pixelformat of the
	 * surface.
	 */
	key = SDL_MapRGB(cat->surface->format, 0xFF, 0xFF, 0xFF);

	/* Set this white value as the alpha channel in the source image. */
	if (SDL_SetColorKey(cat->surface, SDL_SRCCOLORKEY, key) == -1) {
		SDL_FreeSurface(cat->surface);
		SDL_FreeSurface(cat->background);
		return NULL;
	}

	cat->direction = ALLEYCAT_CAT_DIRECTION_RIGHT;
	cat->frame_index = 0;
	cat->x = cat->y = 0;
	cat->width = cat->height = 0;
	cat->background_dirty = 0;
	cat->timer = 0;
	cat->counter = 0;

	return cat;
}

/* Loosely resembles seg002:1020 */
void alleycat_cat_walk(struct alleycat_cat *cat, int direction)
{
	struct sprite *sprite, *sprite2 = NULL;

	/* XXX: stub */
	if (cat->direction == direction) {
	} else {
	}

	if (direction == ALLEYCAT_CAT_DIRECTION_RIGHT) {
		cat->x += 4;
		sprite = cat_walk_right_table[cat->frame_index];
	} else if (direction == ALLEYCAT_CAT_DIRECTION_LEFT) {
		cat->x -= 4;
		sprite = cat_walk_left_table[cat->frame_index];
	} else if (direction == 0) {
		/* If cat already sat down, wait for a bit before turning body. */
		if (cat->direction == 0 && cat->counter++ != 7)
			return;

		sprite = cat_head_table[rand_uint32_range(0, 7)];
		sprite2 = cat_body_table[rand_uint32_range(0, 3)];

		/* XXX: check for same widths */
		cat->counter = 0;
		cat->direction = direction;
		cat->width = sprite->width;
		cat->height = sprite->height + sprite2->height;
		alleycat_draw_struct_sprite(cat->surface, sprite, 0, 0);
		alleycat_draw_struct_sprite(cat->surface, sprite2, 0, sprite->height);
		return;
	}

	cat->direction = direction;
	cat->width = sprite->width;
	cat->height = sprite->height;
	alleycat_draw_struct_sprite(cat->surface, sprite, 0, 0);
	cat->frame_index = (cat->frame_index + 1) % 6;
}

int
alleycat_cat_blit(struct alleycat_cat *cat, SDL_Surface *screen, int x, int y)
{
	SDL_Rect rect_src = { .x = 0, .y = 0 };

	/* Restore background of old location if dirtied */
	if (cat->background_dirty) {
		rect_src.w = cat->background_location.w;
		rect_src.h = cat->background_location.h;
		SDL_BlitSurface(cat->background, &rect_src, screen, &cat->background_location);
		cat->background_dirty = 0;
	}

	/* Initialize source rectangle */
	rect_src.w = cat->width;
	rect_src.h = cat->height;

	/* Store the original background surface */
	cat->background_location.x = x;
	cat->background_location.y = y;
	cat->background_location.w = cat->width;
	cat->background_location.h = cat->height;

	if (SDL_BlitSurface(screen, &cat->background_location, cat->background, &rect_src) == -1)
		return -1;

	if (SDL_BlitSurface(cat->surface, &rect_src, screen, &cat->background_location) == -1)
		return -1;

	/* And store the background location again, as SDL can modify it
	 * during SDL_BlitSurface() when there is clipping.
	 */
	cat->background_location.x = x;
	cat->background_location.y = y;
	cat->background_location.w = cat->width;
	cat->background_location.h = cat->height;
	cat->background_dirty = 1;

	return 0;
}

void alleycat_cat_destroy(struct alleycat_cat *cat)
{
	SDL_FreeSurface(cat->surface);
	SDL_FreeSurface(cat->background);
}
