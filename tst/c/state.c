/* The oracle of tst/state.atm: a state of the game (new from options, or
   loaded from a save), then operations of the logic in order, then the
   whole state as text (tst/c/gamedump.h). Not part of the port.
   usage: state DATADIR OUT new OPT RACES BANNERS GSEED HUMANS IMPROVED NEBULAE [OP...]
          state DATADIR OUT load SAVE [OP...]
   An OP is a name with its arguments after ':' (see ops below). */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "game.h"
#include "game_aux.h"
#include "game_misc.h"
#include "game_planet.h"
#include "game_new.h"
#include "game_save.h"
#include "game_tech.h"
#include "lbx.h"
#include "os.h"
#include "gamedump.h"

int64_t hw_get_time_us(void) { struct timeval tv; gettimeofday(&tv, NULL); return (int64_t)tv.tv_usec + 1000000ll * (int64_t)tv.tv_sec; }
void hw_log_message(const char *msg) { (void)msg; }
void hw_log_warning(const char *msg) { (void)msg; }
void hw_log_error(const char *msg) { fputs(msg, stdout); }

static struct game_s g;
static struct game_aux_s gaux;

static int arg(const char *op, int k)
{
    const char *p = op;
    for (int i = 0; i <= k; ++i) {
        p = strchr(p, ':');
        if (!p) { return 0; }
        ++p;
    }
    return atoi(p);
}

static void do_op(const char *op)
{
    char name[64];
    int i = 0;
    while (op[i] && (op[i] != ':') && (i < 63)) { name[i] = op[i]; ++i; }
    name[i] = 0;
#define OP(n_) else if (strcmp(name, #n_) == 0)
    if (0) {}
    OP(start) { game_aux_start(&gaux, &g); }
    OP(have_reserve_fuel) { game_update_have_reserve_fuel(&g); }
    OP(maint_costs) { game_update_maint_costs(&g); }
    OP(production) { game_update_production(&g); }
    OP(total_research) { game_update_total_research(&g); }
    OP(eco_on_waste) { game_update_eco_on_waste(&g, arg(op, 0), arg(op, 1)); }
    OP(seen_by_orbit) { game_update_seen_by_orbit(&g, arg(op, 0)); }
    OP(within_range) { game_update_within_range(&g); }
    OP(reloc_dest) { game_update_reloc_dest(&g); }
    OP(empire_contact) { game_update_empire_contact(&g); }
    OP(visibility) { game_update_visibility(&g); }
    OP(rng_step) { game_rng_step(&g); }
    OP(planet_destroy) { game_planet_destroy(&g, arg(op, 0), arg(op, 1)); }
    OP(adjust_percent2) { game_planet_adjust_percent2(&g, arg(op, 0), arg(op, 1), arg(op, 2), arg(op, 3)); }
    OP(adjust_percent) { game_planet_adjust_percent(&g, arg(op, 0), arg(op, 1), arg(op, 2), arg(op, 3)); }
    OP(update_home) { game_planet_update_home(&g); }
    OP(tech_util) { game_update_tech_util(&g); }
    OP(finish_new) { game_tech_finish_new(&g, arg(op, 0)); }
    OP(start_next) { game_tech_start_next(&g, arg(op, 0), arg(op, 1), arg(op, 2)); }
    OP(set_to_max_bonus) { game_tech_set_to_max_bonus(&g, arg(op, 0), arg(op, 1)); }
    OP(orion_loot) { game_tech_get_orion_loot(&g, arg(op, 0)); }
    OP(artifact_loot) { game_tech_get_artifact_loot(&g, arg(op, 0), arg(op, 1)); }
    OP(atmos_tform) { game_turn_atmos_tform(&g.planet[arg(op, 0)]); }
    OP(soil_enrich) { game_turn_soil_enrich(&g.planet[arg(op, 0)], arg(op, 1), arg(op, 2)); }
    OP(equalize_tech) { game_equalize_slider_group(g.eto[arg(op, 0)].tech.slider, TECH_FIELD_NUM, g.eto[arg(op, 0)].tech.slider_lock); }
    OP(adjust_tech) { game_adjust_slider_group(g.eto[arg(op, 0)].tech.slider, arg(op, 1), arg(op, 2), TECH_FIELD_NUM, g.eto[arg(op, 0)].tech.slider_lock); }
    else { printf("unknown op %s\n", op); exit(1); }
}

int main(int argc, char **argv)
{
    int k;
    os_set_path_data(argv[1]);
    lbxfile_init();
    game_aux_init(&gaux, &g);
    if (strcmp(argv[3], "new") == 0) {
        struct game_new_options_s opt = GAME_NEW_OPTS_DEFAULT;
        uint32_t o = strtoul(argv[4], 0, 0), races = strtoul(argv[5], 0, 0), banners = strtoul(argv[6], 0, 0);
        uint32_t humans = strtoul(argv[8], 0, 0);
        opt.players = o / 100;
        opt.galaxy_size = (o / 10) % 10;
        opt.difficulty = o % 10;
        opt.galaxy_seed = strtoul(argv[7], 0, 0);
        opt.improved_galaxy_generator = atoi(argv[9]);
        opt.nebulae = atoi(argv[10]);
        for (int i = 0, m = 1; i < PLAYER_NUM; ++i, m *= 10) {
            int r = (races >> (4 * i)) & 0xf, b = (banners / m) % 10;
            opt.pdata[i].race = r ? (r - 1) : RACE_RANDOM;
            opt.pdata[i].banner = b ? (b - 1) : BANNER_RANDOM;
            opt.pdata[i].is_ai = !((humans / m) % 10);
        }
        game_new(&g, &gaux, &opt);
        k = 11;
    } else {
        if (game_save_do_load_fname(argv[4], NULL, &g) != 0) { return 1; }
        k = 5;
    }
    for (; k < argc; ++k) {
        do_op(argv[k]);
    }
    {
        FILE *f = fopen(argv[2], "w");
        gamedump(f, &g);
        fclose(f);
    }
    return 0;
}
