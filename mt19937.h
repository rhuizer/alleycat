#ifndef __MT19937_H
#define __MT19937_H

#include <inttypes.h>

void init_genrand(uint32_t);
void init_by_array(unsigned long [], int);
uint32_t rand_uint32(void);

#endif
