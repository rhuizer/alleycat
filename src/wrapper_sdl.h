/* alleycat, an opensource IBM AlleyCat 1984 implementation.
 *
 * Dedicated to Kanna Ishihara.
 *
 * Copyright (C) 2009 Ronald Huizer
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
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
#ifndef __WRAPPER_SDL_H
#define __WRAPPER_SDL_H

#include <SDL/SDL.h>

void xSDL_Init(Uint32);
SDL_Surface *xSDL_SetVideoMode(int, int, int, Uint32);
SDL_Surface *xSDL_LoadBMP(const char *);
SDL_Surface *xSDL_DisplayFormat(SDL_Surface *);
void xSDL_Flip(SDL_Surface *);
void xSDL_WaitEvent(SDL_Event *);
void xSDL_Quit(void);
void xSDL_EnableKeyRepeat(int, int);

#endif
