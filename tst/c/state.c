/* The oracle of tst/state.atm: a state of the game (new from options, or
   loaded from a save), then operations of the logic in order, then the
   whole state as text (tst/c/gamedump.h). Not part of the port.
   usage: state DATADIR OUT new OPT RACES BANNERS GSEED HUMANS IMPROVED NEBULAE [OP...]
          state DATADIR OUT load SAVE [OP...]
   An OP is a name with its arguments after ':' (see ops below). Some ops
   also print (game_stat, game_design): the output is compared too.
   game_turn.c is included, for its static phases. */
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
#include "game_ai.h"
#include "game_design.h"
#include "game_election.h"
#include "game_ground.h"
#include "game_news.h"
#include "game_diplo.h"
#include "game_fleet.h"
#include "game_spy.h"
#include "game_stat.h"
#include "gamedump.h"
#include "../../c/src/game/game_turn.c"

int64_t hw_get_time_us(void) { struct timeval tv; gettimeofday(&tv, NULL); return (int64_t)tv.tv_usec + 1000000ll * (int64_t)tv.tv_sec; }
void hw_log_message(const char *msg) { (void)msg; }
void hw_log_warning(const char *msg) { (void)msg; }
void hw_log_error(const char *msg) { fputs(msg, stdout); }

/* Of game.c (not linked): an option, all false by default. */
bool game_opt_message_filter[FINISHED_NUM] = { false, false, false, false, false, false };

/* The interface (ui.h) that the logic calls: each call printed, and a fixed
   answer to ui_explore (colonize at the planets of odd index). */
char *ui_get_strbuf(void) { static char buf[UI_STRBUF_SIZE]; return buf; }
bool ui_explore(struct game_s *g_, int pi, uint8_t planet_i, bool by_scanner, bool flag_colony_ship) { printf("explore %d %d %d %d\n", pi, planet_i, by_scanner, flag_colony_ship); return (planet_i & 1) != 0; }
void ui_landing(struct game_s *g_, int pi, uint8_t planet_i) { printf("landing %d %d\n", pi, planet_i); }
void ui_turn_msg(struct game_s *g_, int pi, const char *str) { printf("msg %d %s\n", pi, str); }

void ui_newtech(struct game_s *g_, int pi) { printf("newtech %d\n", pi); }
int ui_spy_steal(struct game_s *g_, int spy, int target, uint8_t flags_field)
{
    int f = 0;
    while ((f < TECH_FIELD_NUM) && !(flags_field & (1 << f))) { ++f; }
    printf("steal %d %d %d -> %d\n", spy, target, flags_field, f);
    return f;
}
void ui_spy_stolen(struct game_s *g_, int pi, int spy, int field, uint8_t tech) { printf("stolen %d %d %d %d\n", pi, spy, field, tech); }
ui_sabotage_t ui_spy_sabotage_ask(struct game_s *g_, int spy, int target, uint8_t *planetptr)
{
    int pl = 0;
    for (int i = 0; i < g_->galaxy_stars; ++i) { if (g_->planet[i].owner == target) { pl = i; break; } }
    *planetptr = pl;
    printf("sabotage_ask %d %d -> %d %d\n", spy, target, (spy + target) % 4, pl);
    return (spy + target) % 4;
}
int ui_spy_sabotage_done(struct game_s *g_, int pi, int spy, int target, ui_sabotage_t act, int other1, int other2, uint8_t planet, int snum)
{
    printf("sabotage_done %d %d %d %d %d %d %d %d\n", pi, spy, target, act, other1, other2, planet, snum);
    return other1;
}
bool ui_bomb_ask(struct game_s *g_, int pi, uint8_t planet_i, int pop_inbound) { printf("bomb_ask %d %d %d\n", pi, planet_i, pop_inbound); return (planet_i & 1) == 0; }
void ui_bomb_show(struct game_s *g_, int pi, int attacker_i, int owner_i, uint8_t planet_i, int popdmg, int factdmg, bool play_music, bool hide_other) { printf("bomb_show %d %d %d %d %d %d %d %d\n", pi, attacker_i, owner_i, planet_i, popdmg, factdmg, play_music, hide_other); }
void ui_ground(struct game_s *g_, struct ground_s *gr)
{
    printf("ground %u %d %d %d %d %d %d %d", gr->seed, gr->planet_i, gr->flag_swap, gr->flag_rebel, gr->inbound, gr->total_inbound, gr->fact, gr->techchance);
    for (int i = 0; i < TECH_SPY_MAX; ++i) { printf(" %d,%d", gr->got[i].tech, gr->got[i].field); }
    for (int i = 0; i < 2; ++i) {
        const struct ground_side_s *s = &gr->s[i];
        printf(" | %d %d %d %d %d %d %d %d %d %d", s->player, s->human, s->force, s->pop1, s->pop2, s->armori, s->suiti, s->shieldi, s->weapi, s->strnum);
        for (int j = 0; j < s->strnum; ++j) { printf(" '%s'", s->str[j]); }
    }
    printf("\n");
}

static void el_print(const char *what, struct election_s *el)
{
    printf("%s %d %d %d %d %d %d %d %d %d %d %d '%s'\n", what, el->num, el->candidate[0], el->candidate[1], el->total_votes, el->got_votes[0], el->got_votes[1], el->first_human, el->last_human, el->cur_i, el->flag_show_votes, el->ui_delay, el->str ? el->str : "(null)");
}
void ui_election_start(struct election_s *el) { el_print("el_start", el); }
void ui_election_show(struct election_s *el) { el_print("el_show", el); }
void ui_election_delay(struct election_s *el, int delay) { printf("el_delay %d\n", delay); el_print("el_delay", el); }
int ui_election_vote(struct election_s *el, int player_i) { el_print("el_vote", el); return (player_i + 1) % 3; }
bool ui_election_accept(struct election_s *el, int player_i) { el_print("el_accept", el); return (player_i & 1) == 0; }
void ui_election_end(struct election_s *el) { el_print("el_end", el); }

/* The functions of the AI that are not ported yet, replaced by fixed
   answers that print each call. */
static bool test_ai_bomb(struct game_s *g_, player_id_t player, uint8_t planet, int pop_inbound) { printf("ai_bomb %d %d %d\n", player, planet, pop_inbound); return ((planet + player) & 1) == 0; }
static void test_ai_ground(struct game_s *g_, player_id_t def, player_id_t att, uint8_t planet, int pop_killed, bool owner_changed) { printf("ai_ground %d %d %d %d %d\n", def, att, planet, pop_killed, owner_changed); }
static uint8_t test_ai_tech_next(struct game_s *g_, player_id_t player, tech_field_t field, uint8_t *tbl, int num) { printf("ai_tech_next %d %d %d\n", player, field, num); return tbl[(player + field) % num]; }
static int test_ai_vote(struct election_s *el, player_id_t player) { printf("ai_vote %d\n", player); return (player + el->g->year) % 3; }
static struct game_ai_s test_ai;

void *ui_gmap_basic_init(struct game_s *g_, bool show_player_switch) { return 0; }
void ui_gmap_basic_start_player(void *ctx, int pi) { }
void ui_gmap_basic_start_frame(void *ctx, int pi) { }
void ui_gmap_basic_draw_frame(void *ctx, int pi) { }
void ui_gmap_basic_finish_frame(void *ctx, int pi) { }
void ui_gmap_basic_shutdown(void *ctx) { }

static struct game_s g;
static struct spy_turn_s spy_st;
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
    OP(limit_ships) { game_turn_limit_ships(&g); }
    OP(countdown_ceasefire) { game_turn_countdown_ceasefire(&g); }
    OP(mood_blunder) { game_turn_update_mood_blunder(&g); }
    OP(init_z_finished) { game_turn_init_z_finished(&g); }
    OP(send_transport) { game_turn_send_transport(&g); }
    OP(build_eco) { game_turn_build_eco(&g); }
    OP(update_trade) { game_turn_update_trade(&g); }
    OP(build_def) { game_turn_build_def(&g); }
    OP(build_ship) { game_turn_build_ship(&g); }
    OP(reserve) { game_turn_reserve(&g); }
    OP(build_ind) { game_turn_build_ind(&g); }
    OP(disable_slider) { game_turn_finished_disable_slider(&g, &g.planet[arg(op, 0)], arg(op, 1), arg(op, 2)); }
    OP(remove_empty_fleets) { game_remove_empty_fleets(&g); }
    OP(remove_player_fleets) { game_remove_player_fleets(&g, arg(op, 0)); }
    OP(fleet_unrefuel) { game_fleet_unrefuel(&g); }
    OP(any_dest) { printf("any_dest %d\n", game_fleet_any_dest_player(&g, arg(op, 0), arg(op, 1))); }
    OP(send_half) {
        /* half of the ships of each design of a player at a planet */
        int pi = arg(op, 0), from = arg(op, 1), n = g.eto[pi].shipdesigns_num;
        shipcount_t ships[NUM_SHIPDESIGNS];
        uint8_t types[NUM_SHIPDESIGNS];
        for (int i = 0; i < n; ++i) { types[i] = n - 1 - i; ships[i] = g.eto[pi].orbit[from].ships[n - 1 - i] / 2; }
        printf("send %d\n", arg(op, 3) ? game_send_fleet_retreat(&g, pi, from, arg(op, 2), ships, types, n)
                                        : game_send_fleet_from_orbit(&g, pi, from, arg(op, 2), ships, types, n));
    }
    OP(redirect) { if (arg(op, 0) < g.enroute_num) { game_fleet_redirect(&g, &g.enroute[arg(op, 0)], arg(op, 1), arg(op, 2)); } }
    OP(fleet_speed) { if (arg(op, 0) < g.enroute_num) { printf("speed %d\n", game_fleet_get_speed(&g, &g.enroute[arg(op, 0)], arg(op, 1), arg(op, 2))); } }
    OP(stats) {
        struct game_stats_s d;
        game_stats_all(&g, arg(op, 0), &d);
        printf("stats %d:", d.num);
        for (int i = 0; i < d.num; ++i) { printf(" %d", d.p[i]); for (int s = 0; s < 6; ++s) { printf(",%d", d.v[s][i]); } }
        printf("\n");
    }
    OP(design_ai) {
        struct game_design_s gd;
        /* the look: arg 2 within those of the hull and banner of the player */
        game_design_prepare_ai(&g, &gd, arg(op, 0), arg(op, 1), g.eto[arg(op, 0)].banner * SHIP_LOOK_PER_BANNER + arg(op, 1) * SHIP_LOOK_PER_HULL + arg(op, 2));
        printf("design_ai %s %d %d %d\n", gd.sd.name, gd.sd.space, gd.sd.cost, gd.sd.engines);
        game_design_add(&g, arg(op, 0), &gd.sd, true);
    }
    OP(design_scrap) { game_design_scrap(&g, arg(op, 0), arg(op, 1), arg(op, 2)); }
    OP(design_fit) {
        /* every table of the design screen, for a design of a player */
        struct game_design_s gd;
        struct design_data_s d;
        int8_t buf[WEAPON_NUM];
        int pi = arg(op, 0);
        game_design_prepare(&g, &gd, pi, &g.srd[pi].design[arg(op, 1)]);
        printf("prepare %d %d:", gd.lookbase, gd.sd_num);
        for (int i = 0; i < SHIP_HULL_NUM; ++i) { printf(" %d %s", gd.tbl_shiplook_hull[i], gd.names[i]); }
        printf("\n");
        d.g = &g; d.gd = &gd; d.api = pi;
        game_design_init_maxtech_haveflags(&d);
        printf("flags %d %d %d %d %d %d %d %d %d:", d.last_avail_tech_weap, d.last_avail_tech_special, d.flag_disable_cspeed, d.flag_disable_comp, d.flag_disable_jammer, d.flag_disable_shield, d.flag_disable_armor, d.flag_disable_engine, gd.sd.hp);
        for (int i = 0; i < WEAPON_SLOT_NUM; ++i) { printf(" %d,%d,%d", d.flag_tbl_weapon[i], d.flag_tbl_weap_up[i], d.flag_tbl_weap_dn[i]); }
        for (int i = 0; i < SPECIAL_SLOT_NUM; ++i) { printf(" %d", d.flag_tbl_special[i]); }
        for (int i = 0; i < SHIP_HULL_NUM; ++i) { printf(" %d", d.flag_tbl_hull[i]); }
        printf("\n");
#define FIT(n_, ...) { int last = game_design_build_tbl_fit_##n_(&g, &gd, buf __VA_ARGS__); printf(#n_ " %d:", last); for (int i = 0; i <= last; ++i) { printf(" %d", buf[i]); } printf("\n"); }
        FIT(comp) FIT(shield) FIT(jammer) FIT(armor) FIT(engine) FIT(man)
        FIT(weapon, , 0, WEAPON_GROUP_ALL) FIT(weapon, , 1, WEAPON_GROUP_BEAMS) FIT(weapon, , 2, WEAPON_GROUP_MISSILES) FIT(weapon, , 3, WEAPON_GROUP_BOMBS)
        FIT(special, , 0) FIT(special, , 2)
        for (int i = 0; i < 13; ++i) { printf(" %d/%d", game_design_calc_cost_item(&gd, i, 1), game_design_calc_space_item(&gd, i, 1)); }
        printf("\n");
        game_design_look_next(&gd); printf("look %d", gd.sd.look);
        game_design_look_prev(&gd); game_design_look_prev(&gd); printf(" %d", gd.sd.look);
        game_design_look_fix(&g, pi, &gd.sd); printf(" %d", gd.sd.look);
        game_design_compact_slots(&gd.sd);
        game_design_clear(&gd); printf(" %s %d %d\n", gd.sd.name, gd.sd.space, gd.sd.cost);
    }
    OP(diplo_adjust) { game_turn_diplo_adjust(&g); }
    OP(diplo_act) { game_diplo_act(&g, arg(op, 0), arg(op, 1), arg(op, 2), arg(op, 3), arg(op, 4), arg(op, 5)); }
    OP(break_treaty) { game_diplo_break_treaty(&g, arg(op, 0), arg(op, 1)); }
    OP(start_war) { game_diplo_start_war(&g, arg(op, 0), arg(op, 1)); }
    OP(start_war_swap) { game_diplo_start_war_swap(&g, arg(op, 0), arg(op, 1)); }
    OP(break_trade) { game_diplo_break_trade(&g, arg(op, 0), arg(op, 1)); }
    OP(annoy) { game_diplo_annoy(&g, arg(op, 0), arg(op, 1), arg(op, 2)); }
    OP(battle_finish) { game_diplo_battle_finish(&g, arg(op, 0), arg(op, 1), arg(op, 2), arg(op, 3), arg(op, 4), arg(op, 5), arg(op, 6)); }
    OP(set_treaty) { game_diplo_set_treaty(&g, arg(op, 0), arg(op, 1), arg(op, 2)); }
    OP(set_trade) { game_diplo_set_trade(&g, arg(op, 0), arg(op, 1), arg(op, 2)); }
    OP(stop_war) { game_diplo_stop_war(&g, arg(op, 0), arg(op, 1)); }
    OP(esp_frame) { game_diplo_esp_frame(&g, arg(op, 0), arg(op, 1)); }
    OP(limit_mood_treaty) { game_diplo_limit_mood_treaty(&g); }
    OP(mood_relax) { game_diplo_mood_relax(&g); }
    OP(moods) {
        /* the mood and is_gone of each pair */
        printf("moods");
        for (int i = 0; i < g.players; ++i) { for (int j = 0; j < g.players; ++j) { printf(" %d,%d", game_diplo_get_mood(&g, i, j), game_diplo_is_gone(&g, i, j)); } }
        printf("\n");
    }
    OP(set_trans) {
        /* transports of the k-th planet of a player (arg 1) to: the planet
           itself (mode 0), the nearest planet of another or no owner (1),
           the nearest planet of another player (2) */
        int pi = arg(op, 0), k = arg(op, 1), mode = arg(op, 2);
        for (int i = 0; i < g.galaxy_stars; ++i) {
            planet_t *p = &g.planet[i];
            if ((p->owner == pi) && (k-- == 0)) {
                int best = i, bestd = 0x7fffffff;
                for (int j = 0; (mode != 0) && (j < g.galaxy_stars); ++j) {
                    const planet_t *q = &g.planet[j];
                    int d = (q->x - p->x) * (q->x - p->x) + (q->y - p->y) * (q->y - p->y);
                    if ((q->owner != pi) && ((mode == 1) || (q->owner != PLAYER_NONE)) && (d < bestd)) { best = j; bestd = d; }
                }
                p->trans_dest = best;
                p->trans_num = arg(op, 3);
                break;
            }
        }
    }
    OP(contact_broken) { BOOLVEC_DECLARE(bv, PLAYER_NUM); bv[0] = arg(op, 1); game_turn_contact_broken(&g, arg(op, 0), bv); }
    OP(update_seen) { game_turn_update_seen(&g); }
    OP(finished_slider) { game_turn_finished_slider(&g); }
    OP(claim) { game_turn_claim(&g); }
    OP(final_war) { game_turn_update_final_war(&g); }
    OP(set_end) { g.end = arg(op, 0); }
    OP(set_refuse) { g.refuse[0] = arg(op, 0); }
    OP(set_spy) {
        empiretechorbit_t *e = &g.eto[arg(op, 0)];
        int t = arg(op, 1);
        e->spying[t] = arg(op, 2); e->spymode[t] = arg(op, 3); e->spies[t] = arg(op, 4);
    }
    OP(spy_build) { game_spy_build(&g); }
    OP(spy_report) { game_spy_report(&g); }
    OP(spy_turn) { game_spy_turn(&g, &spy_st); }
    OP(spy_esp_human) { game_spy_esp_human(&g, &spy_st); }
    OP(spy_sab_human) { game_spy_sab_human(&g); }
    OP(bomb) { game_turn_bomb(&g); }
    OP(ground) { const uint8_t *buf = game_turn_ground_resolve_all(&g); printf("ground_show %d\n", game_turn_ground_show_all(&g, buf)); }
    OP(election) { game_election(&g); }
    OP(news) {
        /* the message of a news item: type subtype num1 num2 race planet */
        struct news_s ns;
        char buf[0x200];
        memset(&ns, 0, sizeof(ns));
        ns.type = arg(op, 0); ns.subtype = arg(op, 1); ns.num1 = arg(op, 2); ns.num2 = arg(op, 3); ns.race = arg(op, 4); ns.planet_i = arg(op, 5);
        game_news_get_msg(&g, &ns, buf, sizeof(buf));
        printf("news '%s' %d", buf, ns.statsnum);
        for (int i = 0; i < ns.statsnum; ++i) { printf(" %s", ns.stats[i]); }
        printf("\n");
    }
    OP(move_ships) { game_turn_move_ships(&g); }
    OP(explore) { game_turn_explore(&g); }
    OP(transport) { game_turn_transport(&g); }
    OP(coup) { game_turn_coup(&g); }
    OP(have_met) { game_turn_update_have_met(&g); }
    OP(transport_shoot) { printf("killed %d\n", game_turn_transport_shoot(&g, arg(op, 0), arg(op, 1), arg(op, 2), arg(op, 3), arg(op, 4), arg(op, 5), arg(op, 6))); }
    else { printf("unknown op %s\n", op); exit(1); }
}

int main(int argc, char **argv)
{
    int k;
    memcpy(&test_ai, game_ai, sizeof(test_ai));
    test_ai.bomb = test_ai_bomb;
    test_ai.ground = test_ai_ground;
    test_ai.tech_next = test_ai_tech_next;
    test_ai.vote = test_ai_vote;
    game_ai = &test_ai;
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
