/*
 * speaker.c - pc speaker emulator
 *
 * (C) David Olofson, 2001
 */
#include <math.h>
#include <limits.h>
#include <SDL/SDL.h>
#include "speaker.h"

static void (*tickhandler)(void);
int freq = 0;
int per = (int)(1000.0/18.204);
int do_retrig = 0;

static SDL_AudioSpec audiospec;

struct oscillator {
	int	phase;
	int	k;
	int	facc;
};

static int timer = 0;
static int timer_period = 0;
static struct oscillator osc = { 0, 0, 0 };

static int hpf_shift = 5;

/* Called by SDL when there is space in the audio buffer */
static void pc_speaker_callback(void *dummy, Uint8 *stream, int len)
{
	int i = 0;
	int s = 0;
	int oscout;
	Sint16 *buf = (Sint16 *)stream;

	len >>= 2;
	while(s < len) {
		int s_end = s + timer;

		if(s_end > len - 1)
			s_end = len-1;

		timer -= s_end - s;

		if(do_retrig) {
			osc.k = 0;
			osc.phase = 0;
			do_retrig = 0;
		}

		if(freq)
			osc.k = (freq << 16) / audiospec.freq;

		while(s++ < s_end) {
			/* Oscillator */
			osc.phase += osc.k;
			oscout = (osc.phase & 0x8000) - 16384;

			/* IIR HP filter */
			osc.facc += (oscout - osc.facc) >> hpf_shift;
			oscout = oscout - osc.facc;

			/* Store the sample in both channels */
			buf[s << 1] = oscout >> 1;
			buf[(s << 1) + 1] = oscout >> 1;
		}

		/* Periodic callback */
		if(timer <= 0) {
			if(tickhandler)
				tickhandler();
			timer = timer_period;
		}
	}

}

int pc_speaker_init(int period, int bass)
{
	SDL_AudioSpec as;

	if(SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
		return -2;

	as.freq = 44100;
	as.format = AUDIO_S16SYS;
	as.channels = 2;
	as.samples = 8192;
	as.callback = pc_speaker_callback;
	if(SDL_OpenAudio(&as, &audiospec) < 0)
		return -3;

	if(audiospec.format != AUDIO_S16SYS)
		return -4;

	SPK_NoSound();
	timer_period = audiospec.freq * period / 1000;

	if(audiospec.freq < 3500)
		hpf_shift = 1;
	else if(audiospec.freq < 7000)
		hpf_shift = 1;
	else if(audiospec.freq < 15000)
		hpf_shift = 2;
	else if(audiospec.freq < 30000)
		hpf_shift = 3;
	else if(audiospec.freq < 60000)
		hpf_shift = 4;
	else
		hpf_shift = 5;

	hpf_shift += bass;

	SDL_PauseAudio(0);
	return 0;
}

void SPK_SetTickHandler(void (*handler)(void))
{
	tickhandler = handler;
}

void SPK_Close(void)
{
	SDL_CloseAudio();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
}


/*
 * Set sound frequency.
 * (Starts oscillator from phase 0
 * unless it's already playing.)
 */
void SPK_Sound(int frequency)
{
	freq = frequency;
}


void SPK_NoSound(void)
{
	do_retrig = 1;
	freq = 0;
}
