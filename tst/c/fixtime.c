/* For tst/cmdline.sh: a fixed time of day (LD_PRELOAD), so that the random
   seeds of 1oom (rnd_get_new_seed: the time in microseconds) are the same
   in the C and in the port. Not part of the port. */
#include <sys/time.h>
#include <stddef.h>

int gettimeofday(struct timeval *tv, void *tz)
{
    if (tv) {
        tv->tv_sec = 1764115200;
        tv->tv_usec = 123456;
    }
    return 0;
}
