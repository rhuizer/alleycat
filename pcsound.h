/*
 * pcsound.h - PC Sound Effects Driver
 *
 * (From Project Spitfire; Converted from Objects Pascal.)
 *
 * © David Olofson, 2001
 */

#ifndef _PCSOUND_H_
#define _PCSOUND_H_

/*
 * The sound bank is a table of frequencies.
 * Values above PCS_MIN_FREQ are treated as
 * frequencies, PCS_STOP stops the sound for one
 * frame and PCS_RETRIG just restarts the osc.
 * PCS_END ends playback.
 */
#define	PCS_END		0
#define	PCS_STOP	1
#define	PCS_RETRIG	2
#define	PCS_MIN_FREQ	66

/*
 * Init/close
 */
int PCS_Init(int bass);
void PCS_Close(void);

/*
 * Programming
 */
void PCS_StartProgramming(void);
void PCS_Push(short freq);
int PCS_Current(void);
void PCS_EndProgramming(void);

/*
 * Playing
 */
void PCS_Start(int pos);
void PCS_StartMedium(int pos);
void PCS_StartHigh(int pos);
void PCS_Stop();

#endif /* _PCSOUND_H_ */
