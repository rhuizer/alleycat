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
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>

/* IBM PC BIOS system timer ticks 18.204 times per second */
#define FREQUENCY	18.204

/* Quick and dirty system timer emulation.
 * Just convert POSIX gettimeofday() to IBM PC BIOS system time ticks.
 * 
 * XXX: should consider start of 24 hour uptime interval?
 */
uint32_t system_time_get(void)
{
	double result;
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1) {
		perror("gettimeofday()");
		exit(EXIT_FAILURE);
	}

	return (tv.tv_sec + tv.tv_usec / 1000000.0) * FREQUENCY;
}
