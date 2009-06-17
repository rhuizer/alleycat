/*
 * pcsound.c - PC Sound Effects Driver
 *
 * © David Olofson, 2001
 */

#define	PCS_STEPS	4096

#include <stdlib.h>
#include "speaker.h"
#include "pcsound.h"

static short *PCS_SoundBank;

static int highplaying = 0;

static int hpr_step, PCS_Step;

/*
 * To be called 60 times/s.
 */
static void PCS_Driver(void)
{
	if(PCS_SoundBank[PCS_Step] == PCS_RETRIG)
	{
		SPK_NoSound();
		++PCS_Step;
	}

	if(PCS_SoundBank[PCS_Step] >= PCS_MIN_FREQ)
	{
		SPK_Sound(PCS_SoundBank[PCS_Step]);
		++PCS_Step;
	}
	else
	{
		SPK_NoSound();
		if(PCS_SoundBank[PCS_Step] == PCS_STOP)
			++PCS_Step;
		else if(PCS_SoundBank[PCS_Step] == PCS_END)
			highplaying = 0;
	}
}


int PCS_Init(int bass)
{
	PCS_SoundBank = malloc(PCS_STEPS);
	if(!PCS_SoundBank)
		return -1;
	if(pc_speaker_init((int)(1000.0 / 18.204), bass) < 0)
		return -2;
	SPK_SetTickHandler(PCS_Driver);
	PCS_Stop();
	return 0;
}


void PCS_Close()
{
	SPK_Close();
}


/*
 * Start a normal sound effect
 */
void PCS_Start(int pos)
{
	if(!highplaying)
		PCS_Step = pos;
}


/*
 * Start a high priority sound effect
 * (cannot be interrupted by a normal sfx)
 */
void PCS_StartHigh(int pos)
{
	highplaying = 1;
	PCS_Step = pos;
}

/*
 * Start a high priority sound unless one is playing
 */
void PCS_StartMedium(int pos)
{
	if(!highplaying)
	{
		hpr_step = PCS_Step;
		highplaying = 1;
		PCS_Step = pos;
	}
}


void PCS_Stop()
{
	PCS_Step = 0;
	highplaying = 0;
	SPK_NoSound();
}


void PCS_StartProgramming(void)
{
	PCS_Step = 1;
}

void PCS_Push(short freq)
{
	PCS_SoundBank[PCS_Step] = freq;
	++PCS_Step;
}

int PCS_Current(void)
{
	return PCS_Step;
}

void PCS_EndProgramming(void)
{
	PCS_Push(PCS_END);
	PCS_Step = 0;
}
