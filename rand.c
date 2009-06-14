/* libaosc, an encoding library for randomized i386 ASCII-only shellcode.
 *
 * Dedicated to Kanna Ishihara.
 *
 * Copyright (C) 2001-2009 Ronald Huizer
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unistd.h>
#include <time.h>
#include "mt19937.h"
#include "rand.h"

uint64_t last = -1;
int no_repeat_last = 0;

void
rand_init(void)
{
	init_genrand(time(NULL) + getpid());
	no_repeat_last = 0;
}

void rand_no_repeat_last(int b)
{
	no_repeat_last = !!b;
}

/*  Generates a random number mod-n in an unbiased way.
 *  Simply generate a random number which is the biggest possible multiple
 *  of 'n' by discarding unfit results, and return this mod-n.
 */
uint32_t
rand_uint32_mod(uint32_t mod)
{
	uint32_t rmod, rnd;

	if (!mod)
		return rand_uint32();

	rmod = ( (-mod) / mod + 1) * mod;

	do {
		rnd = rand_uint32();
	} while (rmod && rnd >= rmod);

	return rnd % mod;
}

/*  Generate a secure random number using aes_random(), and selecting
 *  only numbers in the given range [lo, hi]
 *  Tosses away results to compensate for the bias mod-n arithmetic
 *  introduces when n is not a power of 2.
 */
uint32_t
rand_uint32_range(uint32_t lo, uint32_t hi)
{
	uint32_t ret;

	do {
		ret = rand_uint32_mod(hi - lo + 1) + lo;
	} while (last != -1 && no_repeat_last && last == ret);

	return last = ret;
}

/*  Generate a secure random number using aes_random() quickly, bumping the
 *  result in range [lo, hi].
 *  This uses only mod-n arithmetic and therefore this function !!IS BIASED!!
 *  when n is not a power of 2.
 *  Use for quick random number generation where the mod-n bias can be
 *  safely ignored.
 */
uint32_t
rand_uint32_range_fast(uint32_t lo, uint32_t hi)
{
	return (rand_uint32() % (hi - lo + 1)) + lo;
}
