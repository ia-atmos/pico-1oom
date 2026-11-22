/* The oracle of tst/rnd.atm: c/src/rnd.c over a set of seeds and ranges.
   Not part of the port. */
#include <stdio.h>
#include "rnd.h"

int64_t hw_get_time_us(void) { return 0; }

int main(void)
{
    uint32_t seeds[] = { 0, 1, 0x3039, 0xfda3f, 118835000, 0x80000000u, 0xffffffffu, 0x38018553 };
    for (int k = 0; k < (int)(sizeof(seeds) / sizeof(seeds[0])); ++k) {
        uint32_t seed = seeds[k];
        printf("seed %u:", seed);
        for (int i = 0; i < 200; ++i) {
            uint16_t n = (uint16_t)(1 + (i * 37) % 1000);
            printf(" %u", (i & 1) ? rnd_1_n(n, &seed) : rnd_0_nm1(n, &seed));
        }
        printf(" -> %u\n", seed);
    }
    for (int i = 0; i < 70000; i += 7) {
        printf("bitfiddle %i = %u\n", i, rnd_bitfiddle((uint16_t)i));
    }
    return 0;
}
