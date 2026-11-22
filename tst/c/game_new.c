/* The oracle of tst/game_new.atm: c/src/game/game_new.c from the options
   of `-new GAMESEED` (as in usage_common.txt), then the save of the new
   game. Not part of the port.
   usage: game_new DATADIR OPT RACES BANNERS GSEED HUMANS IMPROVED NEBULAE OUT */
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "game_aux.h"
#include "game_new.h"
#include "game_save.h"
#include "lbx.h"
#include "os.h"

#include <sys/time.h>
int64_t hw_get_time_us(void) { struct timeval tv; gettimeofday(&tv, NULL); return (int64_t)tv.tv_usec + 1000000ll * (int64_t)tv.tv_sec; }
void hw_log_message(const char *msg) { (void)msg; }
void hw_log_warning(const char *msg) { (void)msg; }
void hw_log_error(const char *msg) { fputs(msg, stdout); }

static struct game_s g;
static struct game_aux_s gaux;

int main(int argc, char **argv)
{
    struct game_new_options_s opt = GAME_NEW_OPTS_DEFAULT;
    uint32_t o = strtoul(argv[2], 0, 0), races = strtoul(argv[3], 0, 0), banners = strtoul(argv[4], 0, 0);
    uint32_t gseed = strtoul(argv[5], 0, 0), humans = strtoul(argv[6], 0, 0);
    (void)argc;
    os_set_path_data(argv[1]);
    lbxfile_init();
    game_aux_init(&gaux, &g);
    opt.players = o / 100;
    opt.galaxy_size = (o / 10) % 10;
    opt.difficulty = o % 10;
    opt.galaxy_seed = gseed;
    opt.improved_galaxy_generator = atoi(argv[7]);
    opt.nebulae = atoi(argv[8]);
    for (int i = 0; i < PLAYER_NUM; ++i) {
        int r = (races >> (4 * i)) & 0xf, b = (banners / (i ? (int)(1e0 * 1) : 1)) ;
        (void)b;
        opt.pdata[i].race = r ? (r - 1) : RACE_RANDOM;
        opt.pdata[i].is_ai = true;
    }
    for (int i = 0, m = 1; i < PLAYER_NUM; ++i, m *= 10) {
        int b = (banners / m) % 10;
        opt.pdata[i].banner = b ? (b - 1) : BANNER_RANDOM;
        opt.pdata[i].is_ai = !((humans / m) % 10);
    }
    game_new(&g, &gaux, &opt);
    return game_save_do_save_fname(argv[9], "new", &g, 0) ? 1 : 0;
}
