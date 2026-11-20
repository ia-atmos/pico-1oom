/* The oracle of tst/game_aux.atm: the tables that c/src/game/game_aux.c
   reads from the LBX files, and the distances of the stars of each save.
   Not part of the port.  usage: game_aux DATADIR SAVE... */
#include <stdio.h>
#include "game.h"
#include "game_aux.h"
#include "game_save.h"
#include "lbx.h"
#include "os.h"

void hw_log_message(const char *msg) { (void)msg; }
void hw_log_warning(const char *msg) { (void)msg; }
void hw_log_error(const char *msg) { fputs(msg, stdout); }

static struct game_s g;
static struct game_aux_s gaux;

static void dump(const char *name, const uint8_t *p, int len)
{
    uint32_t sum = 0;
    for (int j = 0; j < len; ++j) {
        sum = (sum * 31 + p[j]) & 0xffffff;
    }
    printf("%s len %i sum %u first", name, len, sum);
    for (int j = 0; (j < 16) && (j < len); ++j) {
        printf(" %i", p[j]);
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    os_set_path_data(argv[1]);
    lbxfile_init();
    game_aux_init(&gaux, &g);
    dump("research.d0", gaux.research.d0, lbxfile_item_len(LBXFILE_RESEARCH, 0) - 4);
    dump("research.names", (const uint8_t *)gaux.research.names, lbxfile_item_len(LBXFILE_RESEARCH, 1) - 4);
    dump("research.descr", (const uint8_t *)gaux.research.descr, lbxfile_item_len(LBXFILE_RESEARCH, 2) - 4);
    dump("diplomat.msg", (const uint8_t *)gaux.diplomat.msg, lbxfile_item_len(LBXFILE_DIPLOMAT, 1) - 4);
    dump("diplomat.d0", gaux.diplomat.d0, DIPLOMAT_D0_NUM);
    dump("eventmsg", (const uint8_t *)gaux.eventmsg, lbxfile_item_len(LBXFILE_EVENTMSG, 0) - 4);
    for (int j = 0; j < NUM_SHIPLOOKS; ++j) {
        printf("firing[%i]", j);
        for (int i = 0; i < 12; ++i) {
            printf(" %i", gaux.firing[j].d0[i]);
        }
        printf(" target %i %i param", gaux.firing[j].target_x, gaux.firing[j].target_y);
        for (int a2 = 1; a2 <= 3; ++a2) {
            for (int dir = 0; dir < 2; ++dir) {
                printf(" %i,%i", game_aux_get_firing_param_x(&gaux, j, a2, dir), game_aux_get_firing_param_y(&gaux, j, a2, dir));
            }
        }
        printf("\n");
    }
    for (int k = 2; k < argc; ++k) {
        if (game_save_do_load_fname(argv[k], NULL, &g) != 0) {
            printf("load failed\n");
            continue;
        }
        game_aux_start(&gaux, &g);
        printf("save %i local_players %i move_temp %i\n", k - 2, gaux.local_players, gaux.move_temp != NULL);
        for (int i = 0; i < g.galaxy_stars; ++i) {
            printf("star_dist[%i]", i);
            for (int j = 0; j < g.galaxy_stars; ++j) {
                printf(" %i", gaux.star_dist[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}
