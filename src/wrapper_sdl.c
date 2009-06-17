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
#include <stdlib.h>
#include <SDL/SDL.h>
#include "wrapper_sdl.h"

static unsigned int __is_init = 0;

void
xSDL_Init(Uint32 flags) {
	if(SDL_Init(flags) != 0) {
		fprintf(stderr, "SDL_Init(0x%.8x) failed: %s\n", flags,
				SDL_GetError());
		exit(EXIT_FAILURE);
	}
	__is_init = 1;
}

SDL_Surface *
xSDL_SetVideoMode(int width, int height, int bpp, Uint32 flags) {
	SDL_Surface *ret;

	if( (ret = SDL_SetVideoMode(width, height, bpp, flags)) == NULL) {
		fprintf(stderr, "SDL_SetVideoMode(%d, %d, %d, 0x%.8x) "
				"failed: %s\n", width, height, bpp, flags,
				SDL_GetError());
		xSDL_Quit();
		exit(EXIT_FAILURE);
	}
	return ret;
}

SDL_Surface *
xSDL_LoadBMP(const char *file) {
	SDL_Surface *ret;

	if( (ret = SDL_LoadBMP(file)) == NULL) {
		fprintf(stderr, "SDL_LoadBMP(\"%s\") failed: %s\n",
				file, SDL_GetError());
		xSDL_Quit();
		exit(EXIT_FAILURE);
	}
	return ret;
}

SDL_Surface *
xSDL_DisplayFormat(SDL_Surface *surface) {
	SDL_Surface *ret;

	if( (ret = SDL_DisplayFormat(surface)) == NULL) {
		fprintf(stderr, "SDL_DisplayFormat(0x%.8x) failed: %s\n",
				(unsigned int)surface, SDL_GetError());
		xSDL_Quit();
		exit(EXIT_FAILURE);
	}
	return ret;
}

void
xSDL_Flip(SDL_Surface *screen) {
	if(SDL_Flip(screen) != 0) {
		fprintf(stderr, "SDL_Flip(0x%.8x) failed: %s\n",
				(unsigned int)screen, SDL_GetError());
		xSDL_Quit();
		exit(EXIT_FAILURE);
	}
}

void
xSDL_WaitEvent(SDL_Event *event) {
	if (SDL_WaitEvent(event) == 0) {
		fprintf(stderr, "SDL_WaitEvent(0x%.8x) failed: %s\n",
				(unsigned int)event, SDL_GetError());
		xSDL_Quit();
		exit(EXIT_FAILURE);
	}
}

void
xSDL_Quit(void) {
	if(__is_init != 0)
		SDL_Quit();
}

SDL_TimerID
xSDL_AddTimer(Uint32 interval, SDL_NewTimerCallback callback, void *param)
{
	SDL_TimerID ret;

	if ( (ret = SDL_AddTimer(interval, callback, param)) == NULL) {
		fprintf(stderr, "SDL_AddTimer failed: %s\n", SDL_GetError());
		xSDL_Quit();
		exit(EXIT_FAILURE);
	}

	return ret;
}

void xSDL_EnableKeyRepeat(int delay, int interval)
{
	if (SDL_EnableKeyRepeat(delay, interval) == -1) {
		fprintf(stderr, "SDL_EnableKeyRepeat failed: %s\n",
		        SDL_GetError());
		xSDL_Quit();
		exit(EXIT_FAILURE);
	}
}

void xSDL_OpenAudio(SDL_AudioSpec *desired, SDL_AudioSpec *obtained)
{
	if (SDL_OpenAudio(desired, obtained) == -1) {
		fprintf(stderr, "SDL_OpenAudio failed: %s\n",
		        SDL_GetError());
		xSDL_Quit();
		exit(EXIT_FAILURE);
	}
}
