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
