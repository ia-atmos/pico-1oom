/* The oracle of tst/util_math.atm: the functions of c/src/util_math.c over
   a set of points, one line per call. Not part of the port. */
#include <stdio.h>
#include "util_math.h"

static unsigned int seed = 12345;
static int rnd(int n) { seed = seed * 1103515245u + 12345u; return (int)((seed >> 16) % (unsigned)n); }

int main(void)
{
    for (int k = 0; k < 3000; ++k) {
        int x0 = rnd(600) - 50, y0 = rnd(400) - 50, x1 = rnd(600) - 50, y1 = rnd(400) - 50;
        int tx[1000], ty[1000], len;
        printf("angle %i %i = %i\n", x1 - x0, y1 - y0, util_math_calc_angle(x1 - x0, y1 - y0));
        printf("cos %i = %i, sin = %i\n", k % 361, util_math_angle_dist_cos(k % 361, k % 50), util_math_angle_dist_sin(k % 361, k % 50));
        printf("steps %i %i %i %i = %i\n", x0, y0, x1, y1, util_math_dist_steps(x0, y0, x1, y1));
        printf("fast = %i, maxabs = %i\n", util_math_dist_fast(x0, y0, x1, y1), util_math_dist_maxabs(x0, y0, x1, y1));
        len = util_math_line_plot(x0, y0, x1, y1, tx, ty);
        printf("plot = %i", len);
        if (len > 0) {
            printf(" (%i,%i) (%i,%i) route = %i", tx[0], ty[0], tx[len - 1], ty[len - 1], util_math_get_route_len(x0, y0, tx, ty, len));
        }
        printf("\n");
    }
    return 0;
}
