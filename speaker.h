/*
 * speaker.h - PC Speaker Driver + Emulator
 *
 * © David Olofson, 2001
 */

#ifndef _SPEAKER_H_
#define _SPEAKER_H_

int SPK_Init(int period, int bass, int flags);
void SPK_SetTickHandler(void (* handler)(void));
void SPK_Close(void);

/*
 * Set sound frequency.
 * (Starts oscillator from phase 0
 * unless it's already playing.)
 */
void SPK_Sound(int frequency);

void SPK_NoSound(void);

#endif /* _SPEAKER_H_ */
