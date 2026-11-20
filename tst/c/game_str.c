/* The oracle of tst/game_str.atm: every string of c/src/game/game_str.c.
   Generated with it. Not part of the port. */
#include <stdio.h>
#include "game_str.h"

static void p(const char *n, int i, const char *s) { printf("%s[%i] = %s\n", n, i, s ? s : "(null)"); }

int main(void)
{
    p("game_str_mm_continue", 0, game_str_mm_continue);
    p("game_str_mm_load", 0, game_str_mm_load);
    p("game_str_mm_new", 0, game_str_mm_new);
    p("game_str_mm_quit", 0, game_str_mm_quit);
    for (int i = 0; i < (int)(sizeof(game_str_tbl_race) / sizeof(game_str_tbl_race[0])); ++i) { p("game_str_tbl_race", i, game_str_tbl_race[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_tbl_races) / sizeof(game_str_tbl_races[0])); ++i) { p("game_str_tbl_races", i, game_str_tbl_races[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_tbl_banner) / sizeof(game_str_tbl_banner[0])); ++i) { p("game_str_tbl_banner", i, game_str_tbl_banner[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_tbl_gsize) / sizeof(game_str_tbl_gsize[0])); ++i) { p("game_str_tbl_gsize", i, game_str_tbl_gsize[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_tbl_diffic) / sizeof(game_str_tbl_diffic[0])); ++i) { p("game_str_tbl_diffic", i, game_str_tbl_diffic[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_tbl_oppon) / sizeof(game_str_tbl_oppon[0])); ++i) { p("game_str_tbl_oppon", i, game_str_tbl_oppon[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_tbl_traits) / sizeof(game_str_tbl_traits[0])); ++i) { p("game_str_tbl_traits", i, game_str_tbl_traits[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_tbl_trait1) / sizeof(game_str_tbl_trait1[0])); ++i) { p("game_str_tbl_trait1", i, game_str_tbl_trait1[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_tbl_trait2) / sizeof(game_str_tbl_trait2[0])); ++i) { p("game_str_tbl_trait2", i, game_str_tbl_trait2[i]); }
    p("game_str_ng_choose_race", 0, game_str_ng_choose_race);
    p("game_str_ng_choose_banner", 0, game_str_ng_choose_banner);
    p("game_str_ng_your_name", 0, game_str_ng_your_name);
    p("game_str_ng_home_name", 0, game_str_ng_home_name);
    p("game_str_ng_ai", 0, game_str_ng_ai);
    p("game_str_ng_computer", 0, game_str_ng_computer);
    p("game_str_ng_player", 0, game_str_ng_player);
    p("game_str_ng_cancel", 0, game_str_ng_cancel);
    p("game_str_ng_ok", 0, game_str_ng_ok);
    p("game_str_ng_allai", 0, game_str_ng_allai);
    for (int i = 0; i < (int)(sizeof(game_str_tbl_planet_names) / sizeof(game_str_tbl_planet_names[0])); ++i) { p("game_str_tbl_planet_names", i, game_str_tbl_planet_names[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_tbl_home_names) / sizeof(game_str_tbl_home_names[0])); ++i) { p("game_str_tbl_home_names", i, game_str_tbl_home_names[i]); }
    p("game_str_rndempname", 0, game_str_rndempname);
    p("game_str_planet_name_orion", 0, game_str_planet_name_orion);
    for (int i = 0; i < (int)(sizeof(game_str_tbl_stship_names) / sizeof(game_str_tbl_stship_names[0])); ++i) { p("game_str_tbl_stship_names", i, game_str_tbl_stship_names[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_tbl_copyprotection_ship_names) / sizeof(game_str_tbl_copyprotection_ship_names[0])); ++i) { p("game_str_tbl_copyprotection_ship_names", i, game_str_tbl_copyprotection_ship_names[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_tbl_monsh_names) / sizeof(game_str_tbl_monsh_names[0])); ++i) { p("game_str_tbl_monsh_names", i, game_str_tbl_monsh_names[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_tbl_mon_names) / sizeof(game_str_tbl_mon_names[0])); ++i) { p("game_str_tbl_mon_names", i, game_str_tbl_mon_names[i]); }
    p("game_str_ai_colonyship", 0, game_str_ai_colonyship);
    p("game_str_st_none", 0, game_str_st_none);
    p("game_str_st_none2", 0, game_str_st_none2);
    for (int i = 0; i < (int)(sizeof(game_str_tbl_st_weap) / sizeof(game_str_tbl_st_weap[0])); ++i) { p("game_str_tbl_st_weap", i, game_str_tbl_st_weap[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_tbl_st_weapx) / sizeof(game_str_tbl_st_weapx[0])); ++i) { p("game_str_tbl_st_weapx", i, game_str_tbl_st_weapx[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_tbl_st_comp) / sizeof(game_str_tbl_st_comp[0])); ++i) { p("game_str_tbl_st_comp", i, game_str_tbl_st_comp[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_tbl_st_engine) / sizeof(game_str_tbl_st_engine[0])); ++i) { p("game_str_tbl_st_engine", i, game_str_tbl_st_engine[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_tbl_st_armor) / sizeof(game_str_tbl_st_armor[0])); ++i) { p("game_str_tbl_st_armor", i, game_str_tbl_st_armor[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_tbl_st_shield) / sizeof(game_str_tbl_st_shield[0])); ++i) { p("game_str_tbl_st_shield", i, game_str_tbl_st_shield[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_tbl_st_jammer) / sizeof(game_str_tbl_st_jammer[0])); ++i) { p("game_str_tbl_st_jammer", i, game_str_tbl_st_jammer[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_tbl_st_specsh) / sizeof(game_str_tbl_st_specsh[0])); ++i) { p("game_str_tbl_st_specsh", i, game_str_tbl_st_specsh[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_tbl_st_special) / sizeof(game_str_tbl_st_special[0])); ++i) { p("game_str_tbl_st_special", i, game_str_tbl_st_special[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_tbl_st_specialx) / sizeof(game_str_tbl_st_specialx[0])); ++i) { p("game_str_tbl_st_specialx", i, game_str_tbl_st_specialx[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_tbl_st_hull) / sizeof(game_str_tbl_st_hull[0])); ++i) { p("game_str_tbl_st_hull", i, game_str_tbl_st_hull[i]); }
    p("game_str_sm_crystal", 0, game_str_sm_crystal);
    p("game_str_sm_amoeba", 0, game_str_sm_amoeba);
    p("game_str_sm_game", 0, game_str_sm_game);
    p("game_str_sm_design", 0, game_str_sm_design);
    p("game_str_sm_fleet", 0, game_str_sm_fleet);
    p("game_str_sm_map", 0, game_str_sm_map);
    p("game_str_sm_races", 0, game_str_sm_races);
    p("game_str_sm_planets", 0, game_str_sm_planets);
    p("game_str_sm_tech", 0, game_str_sm_tech);
    p("game_str_sm_next_turn", 0, game_str_sm_next_turn);
    for (int i = 0; i < (int)(sizeof(game_str_tbl_sm_stinfo) / sizeof(game_str_tbl_sm_stinfo[0])); ++i) { p("game_str_tbl_sm_stinfo", i, game_str_tbl_sm_stinfo[i]); }
    p("game_str_sm_range", 0, game_str_sm_range);
    p("game_str_sm_parsec", 0, game_str_sm_parsec);
    p("game_str_sm_parsecs", 0, game_str_sm_parsecs);
    p("game_str_sm_parsecs2", 0, game_str_sm_parsecs2);
    p("game_str_sm_colony", 0, game_str_sm_colony);
    p("game_str_sm_lastrep", 0, game_str_sm_lastrep);
    p("game_str_sm_stargate", 0, game_str_sm_stargate);
    p("game_str_sm_prodnone", 0, game_str_sm_prodnone);
    p("game_str_sm_prod_y", 0, game_str_sm_prod_y);
    p("game_str_sm_defupg", 0, game_str_sm_defupg);
    p("game_str_sm_defshld", 0, game_str_sm_defshld);
    p("game_str_sm_refit", 0, game_str_sm_refit);
    for (int i = 0; i < 6; ++i) { p("game_str_sm_irc", i, game_str_sm_irc[i]); }
    p("game_str_sm_indmax", 0, game_str_sm_indmax);
    p("game_str_sm_indres", 0, game_str_sm_indres);
    p("game_str_sm_ecowaste", 0, game_str_sm_ecowaste);
    p("game_str_sm_ecoclean", 0, game_str_sm_ecoclean);
    p("game_str_sm_ecoatmos", 0, game_str_sm_ecoatmos);
    p("game_str_sm_ecotform", 0, game_str_sm_ecotform);
    p("game_str_sm_ecosoil", 0, game_str_sm_ecosoil);
    p("game_str_sm_ecogaia", 0, game_str_sm_ecogaia);
    p("game_str_sm_ecopop", 0, game_str_sm_ecopop);
    p("game_str_sm_unexplored", 0, game_str_sm_unexplored);
    p("game_str_sm_nohabit", 0, game_str_sm_nohabit);
    p("game_str_sm__planets", 0, game_str_sm__planets);
    for (int i = 0; i < (int)(sizeof(game_str_tbl_sm_pltype) / sizeof(game_str_tbl_sm_pltype[0])); ++i) { p("game_str_tbl_sm_pltype", i, game_str_tbl_sm_pltype[i]); }
    p("game_str_sm_plague", 0, game_str_sm_plague);
    p("game_str_sm_nova", 0, game_str_sm_nova);
    p("game_str_sm_comet", 0, game_str_sm_comet);
    p("game_str_sm_pirates", 0, game_str_sm_pirates);
    p("game_str_sm_rebellion", 0, game_str_sm_rebellion);
    p("game_str_sm_unrest", 0, game_str_sm_unrest);
    p("game_str_sm_accident", 0, game_str_sm_accident);
    for (int i = 0; i < (int)(sizeof(game_str_tbl_sm_pgrowth) / sizeof(game_str_tbl_sm_pgrowth[0])); ++i) { p("game_str_tbl_sm_pgrowth", i, game_str_tbl_sm_pgrowth[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_tbl_sm_pspecial) / sizeof(game_str_tbl_sm_pspecial[0])); ++i) { p("game_str_tbl_sm_pspecial", i, game_str_tbl_sm_pspecial[i]); }
    p("game_str_sm_pop", 0, game_str_sm_pop);
    p("game_str_sm_max", 0, game_str_sm_max);
    p("game_str_sm_hasreached", 0, game_str_sm_hasreached);
    p("game_str_sm_indmaxof", 0, game_str_sm_indmaxof);
    p("game_str_sm_factories", 0, game_str_sm_factories);
    p("game_str_sm_extrares", 0, game_str_sm_extrares);
    p("game_str_sm_popmaxof", 0, game_str_sm_popmaxof);
    p("game_str_sm_colonists", 0, game_str_sm_colonists);
    p("game_str_sm_hasterraf", 0, game_str_sm_hasterraf);
    for (int i = 0; i < (int)(sizeof(game_str_tbl_sm_terraf) / sizeof(game_str_tbl_sm_terraf[0])); ++i) { p("game_str_tbl_sm_terraf", i, game_str_tbl_sm_terraf[i]); }
    p("game_str_sm_envwith", 0, game_str_sm_envwith);
    for (int i = 0; i < (int)(sizeof(game_str_tbl_sm_envmore) / sizeof(game_str_tbl_sm_envmore[0])); ++i) { p("game_str_tbl_sm_envmore", i, game_str_tbl_sm_envmore[i]); }
    p("game_str_sm_stdgrow", 0, game_str_sm_stdgrow);
    p("game_str_sm_hasfsgate", 0, game_str_sm_hasfsgate);
    p("game_str_sm_hasfshield", 0, game_str_sm_hasfshield);
    p("game_str_sm_planshield", 0, game_str_sm_planshield);
    p("game_str_sm_planratio", 0, game_str_sm_planratio);
    p("game_str_sm_fleetdep", 0, game_str_sm_fleetdep);
    p("game_str_sm_destoor", 0, game_str_sm_destoor);
    p("game_str_sm_destoor2", 0, game_str_sm_destoor2);
    p("game_str_sm_parsfromcc", 0, game_str_sm_parsfromcc);
    p("game_str_sm_eta", 0, game_str_sm_eta);
    p("game_str_sm_turn", 0, game_str_sm_turn);
    p("game_str_sm_turns", 0, game_str_sm_turns);
    p("game_str_sm_chdest", 0, game_str_sm_chdest);
    p("game_str_sm_outsr", 0, game_str_sm_outsr);
    p("game_str_sm_sreloc", 0, game_str_sm_sreloc);
    p("game_str_sm_sreloc2", 0, game_str_sm_sreloc2);
    p("game_str_sm_delay", 0, game_str_sm_delay);
    p("game_str_sm_seltr", 0, game_str_sm_seltr);
    p("game_str_sm_notrange", 0, game_str_sm_notrange);
    p("game_str_sm_notrange1", 0, game_str_sm_notrange1);
    p("game_str_sm_notrange2", 0, game_str_sm_notrange2);
    p("game_str_sm_notrange3", 0, game_str_sm_notrange3);
    p("game_str_sm_trfirste", 0, game_str_sm_trfirste);
    p("game_str_sm_trcontr1", 0, game_str_sm_trcontr1);
    p("game_str_sm_trcontr2", 0, game_str_sm_trcontr2);
    p("game_str_sm_trfirstc", 0, game_str_sm_trfirstc);
    p("game_str_sm_trwarna", 0, game_str_sm_trwarna);
    p("game_str_sm_trwarnm1", 0, game_str_sm_trwarnm1);
    p("game_str_sm_trwarnm2", 0, game_str_sm_trwarnm2);
    p("game_str_sm_trchnum1", 0, game_str_sm_trchnum1);
    p("game_str_sm_trchnum2", 0, game_str_sm_trchnum2);
    p("game_str_sm_trans1", 0, game_str_sm_trans1);
    p("game_str_sm_transs", 0, game_str_sm_transs);
    p("game_str_sm_tdest", 0, game_str_sm_tdest);
    p("game_str_sm_bomb1", 0, game_str_sm_bomb1);
    p("game_str_sm_bomb2", 0, game_str_sm_bomb2);
    p("game_str_sm_trinb1", 0, game_str_sm_trinb1);
    p("game_str_sm_trinb1s", 0, game_str_sm_trinb1s);
    p("game_str_sm_trinb2", 0, game_str_sm_trinb2);
    p("game_str_sm_obomb1", 0, game_str_sm_obomb1);
    p("game_str_sm_obomb2", 0, game_str_sm_obomb2);
    p("game_str_sm_cdest1", 0, game_str_sm_cdest1);
    p("game_str_sm_cdest2", 0, game_str_sm_cdest2);
    p("game_str_sm_ineff1", 0, game_str_sm_ineff1);
    p("game_str_sm_ineff2", 0, game_str_sm_ineff2);
    p("game_str_sm_bkill1", 0, game_str_sm_bkill1);
    p("game_str_sm_bkill2", 0, game_str_sm_bkill2);
    p("game_str_sm_bfact1", 0, game_str_sm_bfact1);
    p("game_str_sm_bfact1s", 0, game_str_sm_bfact1s);
    p("game_str_sm_bfact2", 0, game_str_sm_bfact2);
    p("game_str_sm_traad1", 0, game_str_sm_traad1);
    p("game_str_sm_traad2", 0, game_str_sm_traad2);
    p("game_str_sm_trbdb1", 0, game_str_sm_trbdb1);
    p("game_str_sm_trbdb2", 0, game_str_sm_trbdb2);
    p("game_str_sm_inorbit", 0, game_str_sm_inorbit);
    p("game_str_sm_ship_everywhere", 0, game_str_sm_ship_everywhere);
    p("game_str_sm_ship_replace", 0, game_str_sm_ship_replace);
    for (int i = 0; i < (int)(sizeof(game_str_tbl_roman) / sizeof(game_str_tbl_roman[0])); ++i) { p("game_str_tbl_roman", i, game_str_tbl_roman[i]); }
    p("game_str_no_events", 0, game_str_no_events);
    p("game_str_no_elections", 0, game_str_no_elections);
    p("game_str_bc", 0, game_str_bc);
    p("game_str_y", 0, game_str_y);
    p("game_str_year", 0, game_str_year);
    p("game_str_year0", 0, game_str_year0);
    p("game_str_year1", 0, game_str_year1);
    p("game_str_player", 0, game_str_player);
    p("game_str_pl_reserve", 0, game_str_pl_reserve);
    p("game_str_pl_plague", 0, game_str_pl_plague);
    p("game_str_pl_nova", 0, game_str_pl_nova);
    p("game_str_pl_comet", 0, game_str_pl_comet);
    p("game_str_pl_pirates", 0, game_str_pl_pirates);
    p("game_str_pl_rebellion", 0, game_str_pl_rebellion);
    p("game_str_pl_unrest", 0, game_str_pl_unrest);
    p("game_str_pl_accident", 0, game_str_pl_accident);
    p("game_str_pl_spending", 0, game_str_pl_spending);
    p("game_str_pl_tincome", 0, game_str_pl_tincome);
    p("game_str_pl_transof", 0, game_str_pl_transof);
    p("game_str_pl_resto", 0, game_str_pl_resto);
    p("game_str_sd_cancel", 0, game_str_sd_cancel);
    p("game_str_sd_build", 0, game_str_sd_build);
    p("game_str_sd_clear", 0, game_str_sd_clear);
    p("game_str_sd_comp", 0, game_str_sd_comp);
    p("game_str_sd_shield", 0, game_str_sd_shield);
    p("game_str_sd_ecm", 0, game_str_sd_ecm);
    p("game_str_sd_armor", 0, game_str_sd_armor);
    p("game_str_sd_engine", 0, game_str_sd_engine);
    p("game_str_sd_man", 0, game_str_sd_man);
    for (int i = 0; i < (int)(sizeof(game_str_tbl_sd_spec) / sizeof(game_str_tbl_sd_spec[0])); ++i) { p("game_str_tbl_sd_spec", i, game_str_tbl_sd_spec[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_tbl_sd_weap) / sizeof(game_str_tbl_sd_weap[0])); ++i) { p("game_str_tbl_sd_weap", i, game_str_tbl_sd_weap[i]); }
    p("game_str_sd_count", 0, game_str_sd_count);
    p("game_str_sd_sweap", 0, game_str_sd_sweap);
    p("game_str_sd_damage", 0, game_str_sd_damage);
    p("game_str_sd_rng", 0, game_str_sd_rng);
    p("game_str_sd_notes", 0, game_str_sd_notes);
    p("game_str_sd_hp", 0, game_str_sd_hp);
    p("game_str_sd_warp", 0, game_str_sd_warp);
    p("game_str_sd_def", 0, game_str_sd_def);
    p("game_str_sd_cspeed", 0, game_str_sd_cspeed);
    p("game_str_sd_absorbs", 0, game_str_sd_absorbs);
    p("game_str_sd_hit", 0, game_str_sd_hit);
    p("game_str_sd_hits", 0, game_str_sd_hits);
    p("game_str_sd_misdef", 0, game_str_sd_misdef);
    p("game_str_sd_att", 0, game_str_sd_att);
    p("game_str_sd_comptype", 0, game_str_sd_comptype);
    p("game_str_sd_cost", 0, game_str_sd_cost);
    p("game_str_sd_size", 0, game_str_sd_size);
    p("game_str_sd_power", 0, game_str_sd_power);
    p("game_str_sd_space", 0, game_str_sd_space);
    p("game_str_sd_comps", 0, game_str_sd_comps);
    p("game_str_sd_shieldtype", 0, game_str_sd_shieldtype);
    p("game_str_sd_shields", 0, game_str_sd_shields);
    p("game_str_sd_ecmtype", 0, game_str_sd_ecmtype);
    p("game_str_sd_ecm2", 0, game_str_sd_ecm2);
    p("game_str_sd_armortype", 0, game_str_sd_armortype);
    p("game_str_sd_armor2", 0, game_str_sd_armor2);
    p("game_str_sd_engtype", 0, game_str_sd_engtype);
    p("game_str_sd_numengs", 0, game_str_sd_numengs);
    p("game_str_sd_engs", 0, game_str_sd_engs);
    p("game_str_sd_man1", 0, game_str_sd_man1);
    p("game_str_sd_man2", 0, game_str_sd_man2);
    p("game_str_sd_class", 0, game_str_sd_class);
    p("game_str_sd_speed", 0, game_str_sd_speed);
    p("game_str_sd_max", 0, game_str_sd_max);
    p("game_str_sd_weapname", 0, game_str_sd_weapname);
    p("game_str_sd_descr", 0, game_str_sd_descr);
    p("game_str_sd_dmg", 0, game_str_sd_dmg);
    p("game_str_sd_weaps", 0, game_str_sd_weaps);
    p("game_str_sd_specname", 0, game_str_sd_specname);
    p("game_str_sd_specs", 0, game_str_sd_specs);
    for (int i = 0; i < (int)(sizeof(game_str_sd_wgroup_names) / sizeof(game_str_sd_wgroup_names[0])); ++i) { p("game_str_sd_wgroup_names", i, game_str_sd_wgroup_names[i]); }
    p("game_str_sp_only6", 0, game_str_sp_only6);
    p("game_str_sp_wantscrap", 0, game_str_sp_wantscrap);
    p("game_str_sp_before", 0, game_str_sp_before);
    p("game_str_sp_cost", 0, game_str_sp_cost);
    p("game_str_fl_station", 0, game_str_fl_station);
    p("game_str_fl_inorbit", 0, game_str_fl_inorbit);
    p("game_str_fl_moving", 0, game_str_fl_moving);
    p("game_str_fl_unknown", 0, game_str_fl_unknown);
    p("game_str_fl_system", 0, game_str_fl_system);
    p("game_str_gm_tchar", 0, game_str_gm_tchar);
    for (int i = 0; i < (int)(sizeof(game_str_tbl_gm_spec) / sizeof(game_str_tbl_gm_spec[0])); ++i) { p("game_str_tbl_gm_spec", i, game_str_tbl_gm_spec[i]); }
    p("game_str_gm_unable", 0, game_str_gm_unable);
    p("game_str_gm_prod", 0, game_str_gm_prod);
    p("game_str_gm_tech", 0, game_str_gm_tech);
    p("game_str_gm_1_3", 0, game_str_gm_1_3);
    p("game_str_gm_1_2", 0, game_str_gm_1_2);
    p("game_str_gm_2x", 0, game_str_gm_2x);
    p("game_str_gm_3x", 0, game_str_gm_3x);
    p("game_str_gm_4x", 0, game_str_gm_4x);
    p("game_str_gm_prodb1", 0, game_str_gm_prodb1);
    p("game_str_gm_prodb2", 0, game_str_gm_prodb2);
    p("game_str_gm_prodb3", 0, game_str_gm_prodb3);
    p("game_str_gm_gmap", 0, game_str_gm_gmap);
    p("game_str_gm_mapkey", 0, game_str_gm_mapkey);
    p("game_str_bs_line1", 0, game_str_bs_line1);
    p("game_str_bs_line2", 0, game_str_bs_line2);
    p("game_str_bs_bases", 0, game_str_bs_bases);
    for (int i = 0; i < (int)(sizeof(game_str_tbl_te_field) / sizeof(game_str_tbl_te_field[0])); ++i) { p("game_str_tbl_te_field", i, game_str_tbl_te_field[i]); }
    p("game_str_te_adv", 0, game_str_te_adv);
    p("game_str_te_tech", 0, game_str_te_tech);
    p("game_str_te_techno", 0, game_str_te_techno);
    p("game_str_te_techno2", 0, game_str_te_techno2);
    p("game_str_te_genimp", 0, game_str_te_genimp);
    p("game_str_te_nmis", 0, game_str_te_nmis);
    p("game_str_te_nbomb", 0, game_str_te_nbomb);
    p("game_str_te_scrange", 0, game_str_te_scrange);
    p("game_str_te_rctrl", 0, game_str_te_rctrl);
    p("game_str_te_col", 0, game_str_te_col);
    p("game_str_te_fwaste", 0, game_str_te_fwaste);
    p("game_str_te_gcombat", 0, game_str_te_gcombat);
    p("game_str_te_tform", 0, game_str_te_tform);
    p("game_str_te_wasteel", 0, game_str_te_wasteel);
    p("game_str_te_shrange", 0, game_str_te_shrange);
    p("game_str_te_max", 0, game_str_te_max);
    p("game_str_te_rp", 0, game_str_te_rp);
    p("game_str_nt_achieve", 0, game_str_nt_achieve);
    p("game_str_nt_break", 0, game_str_nt_break);
    p("game_str_nt_infil", 0, game_str_nt_infil);
    p("game_str_nt_ruins", 0, game_str_nt_ruins);
    p("game_str_nt_discover", 0, game_str_nt_discover);
    p("game_str_nt_orion", 0, game_str_nt_orion);
    p("game_str_nt_scouts", 0, game_str_nt_scouts);
    p("game_str_nt_choose", 0, game_str_nt_choose);
    p("game_str_nt_reveal", 0, game_str_nt_reveal);
    p("game_str_nt_secrets", 0, game_str_nt_secrets);
    p("game_str_nt_frame", 0, game_str_nt_frame);
    p("game_str_nt_victim", 0, game_str_nt_victim);
    p("game_str_nt_doyou", 0, game_str_nt_doyou);
    p("game_str_nt_inc", 0, game_str_nt_inc);
    p("game_str_nt_redueco", 0, game_str_nt_redueco);
    p("game_str_nt_ind", 0, game_str_nt_ind);
    p("game_str_nt_ecoall", 0, game_str_nt_ecoall);
    p("game_str_nt_terra", 0, game_str_nt_terra);
    p("game_str_nt_def", 0, game_str_nt_def);
    p("game_str_nt_ecostd", 0, game_str_nt_ecostd);
    p("game_str_nt_ecohost", 0, game_str_nt_ecohost);
    for (int i = 0; i < (int)(sizeof(game_str_tbl_nt_adj) / sizeof(game_str_tbl_nt_adj[0])); ++i) { p("game_str_tbl_nt_adj", i, game_str_tbl_nt_adj[i]); }
    p("game_str_adj_set", 0, game_str_adj_set);
    p("game_str_adj_ratios", 0, game_str_adj_ratios);
    p("game_str_adj_max", 0, game_str_adj_max);
    for (int i = 0; i < (int)(sizeof(game_str_adj_slider) / sizeof(game_str_adj_slider[0])); ++i) { p("game_str_adj_slider", i, game_str_adj_slider[i]); }
    p("game_str_adj_colonies", 0, game_str_adj_colonies);
    p("game_str_adj_lock", 0, game_str_adj_lock);
    p("game_str_adj_lock2", 0, game_str_adj_lock2);
    for (int i = 0; i < (int)(sizeof(game_str_adj_special) / sizeof(game_str_adj_special[0])); ++i) { p("game_str_adj_special", i, game_str_adj_special[i]); }
    p("game_str_ra_nocont", 0, game_str_ra_nocont);
    p("game_str_ra_notpres", 0, game_str_ra_notpres);
    p("game_str_ra_secline1", 0, game_str_ra_secline1);
    p("game_str_ra_secline2", 0, game_str_ra_secline2);
    p("game_str_ra_alloc", 0, game_str_ra_alloc);
    p("game_str_ra_planres", 0, game_str_ra_planres);
    p("game_str_ra_diplo", 0, game_str_ra_diplo);
    p("game_str_ra_gone", 0, game_str_ra_gone);
    p("game_str_ra_nospies", 0, game_str_ra_nospies);
    p("game_str_ra_spy", 0, game_str_ra_spy);
    p("game_str_ra_spies", 0, game_str_ra_spies);
    for (int i = 0; i < (int)(sizeof(game_str_tbl_ra_treaty) / sizeof(game_str_tbl_ra_treaty[0])); ++i) { p("game_str_tbl_ra_treaty", i, game_str_tbl_ra_treaty[i]); }
    p("game_str_ra_trade", 0, game_str_ra_trade);
    p("game_str_ra_notrade", 0, game_str_ra_notrade);
    for (int i = 0; i < (int)(sizeof(game_str_tbl_ra_relat) / sizeof(game_str_tbl_ra_relat[0])); ++i) { p("game_str_tbl_ra_relat", i, game_str_tbl_ra_relat[i]); }
    p("game_str_ra_stats", 0, game_str_ra_stats);
    p("game_str_re_reportis", 0, game_str_re_reportis);
    p("game_str_re_current", 0, game_str_re_current);
    p("game_str_re_yearsold", 0, game_str_re_yearsold);
    p("game_str_re_alliance", 0, game_str_re_alliance);
    p("game_str_re_wars", 0, game_str_re_wars);
    p("game_str_re_environ", 0, game_str_re_environ);
    p("game_str_sc_caught", 0, game_str_sc_caught);
    p("game_str_bp_scombat", 0, game_str_bp_scombat);
    p("game_str_bp_attack", 0, game_str_bp_attack);
    p("game_str_bp_attacks", 0, game_str_bp_attacks);
    p("game_str_bp_won", 0, game_str_bp_won);
    p("game_str_bt_auto_move", 0, game_str_bt_auto_move);
    p("game_str_bt_pop", 0, game_str_bt_pop);
    p("game_str_bt_ind", 0, game_str_bt_ind);
    p("game_str_bt_bases", 0, game_str_bt_bases);
    p("game_str_bt_subint", 0, game_str_bt_subint);
    p("game_str_bt_launch", 0, game_str_bt_launch);
    p("game_str_bt_coldest", 0, game_str_bt_coldest);
    p("game_str_es_youresp1", 0, game_str_es_youresp1);
    p("game_str_es_youresp2", 0, game_str_es_youresp2);
    p("game_str_es_youresp3", 0, game_str_es_youresp3);
    p("game_str_es_thesp1", 0, game_str_es_thesp1);
    p("game_str_es_thesp2", 0, game_str_es_thesp2);
    p("game_str_es_unkn", 0, game_str_es_unkn);
    p("game_str_sb_choose", 0, game_str_sb_choose);
    p("game_str_sb_lastrep", 0, game_str_sb_lastrep);
    p("game_str_sb_pop", 0, game_str_sb_pop);
    p("game_str_sb_fact", 0, game_str_sb_fact);
    p("game_str_sb_bases", 0, game_str_sb_bases);
    p("game_str_sb_unkn", 0, game_str_sb_unkn);
    p("game_str_sb_your", 0, game_str_sb_your);
    p("game_str_sb_spies", 0, game_str_sb_spies);
    p("game_str_sb_increv", 0, game_str_sb_increv);
    p("game_str_sb_inc1", 0, game_str_sb_inc1);
    p("game_str_sb_inc2", 0, game_str_sb_inc2);
    p("game_str_sb_destr", 0, game_str_sb_destr);
    p("game_str_sb_fact2", 0, game_str_sb_fact2);
    p("game_str_sb_facts", 0, game_str_sb_facts);
    p("game_str_sb_mbase", 0, game_str_sb_mbase);
    p("game_str_sb_mbases", 0, game_str_sb_mbases);
    p("game_str_sb_failed", 0, game_str_sb_failed);
    p("game_str_sb_nofact", 0, game_str_sb_nofact);
    p("game_str_sb_nobases", 0, game_str_sb_nobases);
    p("game_str_sb_noinc", 0, game_str_sb_noinc);
    p("game_str_sb_frame", 0, game_str_sb_frame);
    p("game_str_ex_planeta", 0, game_str_ex_planeta);
    p("game_str_ex_scanner", 0, game_str_ex_scanner);
    p("game_str_ex_scout", 0, game_str_ex_scout);
    p("game_str_ex_explore", 0, game_str_ex_explore);
    p("game_str_ex_starsys", 0, game_str_ex_starsys);
    p("game_str_ex_build", 0, game_str_ex_build);
    p("game_str_ex_colony", 0, game_str_ex_colony);
    p("game_str_ex_popgr", 0, game_str_ex_popgr);
    p("game_str_ex_resopnt", 0, game_str_ex_resopnt);
    p("game_str_ex_fromind", 0, game_str_ex_fromind);
    p("game_str_ex_techpnt", 0, game_str_ex_techpnt);
    p("game_str_ex_fromres", 0, game_str_ex_fromres);
    p("game_str_ex_aredbl", 0, game_str_ex_aredbl);
    p("game_str_ex_arequad", 0, game_str_ex_arequad);
    for (int i = 0; i < (int)(sizeof(game_str_ex_pg1) / sizeof(game_str_ex_pg1[0])); ++i) { p("game_str_ex_pg1", i, game_str_ex_pg1[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_ex_pg2) / sizeof(game_str_ex_pg2[0])); ++i) { p("game_str_ex_pg2", i, game_str_ex_pg2[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_ex_pg3) / sizeof(game_str_ex_pg3[0])); ++i) { p("game_str_ex_pg3", i, game_str_ex_pg3[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_ex_ps1) / sizeof(game_str_ex_ps1[0])); ++i) { p("game_str_ex_ps1", i, game_str_ex_ps1[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_ex_ps2) / sizeof(game_str_ex_ps2[0])); ++i) { p("game_str_ex_ps2", i, game_str_ex_ps2[i]); }
    p("game_str_la_colony", 0, game_str_la_colony);
    p("game_str_la_inyear", 0, game_str_la_inyear);
    p("game_str_la_the", 0, game_str_la_the);
    p("game_str_la_formnew", 0, game_str_la_formnew);
    p("game_str_gr_carmor", 0, game_str_gr_carmor);
    p("game_str_gr_outof", 0, game_str_gr_outof);
    p("game_str_gr_transs", 0, game_str_gr_transs);
    p("game_str_gr_reclaim", 0, game_str_gr_reclaim);
    p("game_str_gr_penetr", 0, game_str_gr_penetr);
    p("game_str_gr_defenss", 0, game_str_gr_defenss);
    p("game_str_gr_troops", 0, game_str_gr_troops);
    p("game_str_gr_rebel", 0, game_str_gr_rebel);
    p("game_str_gr_gcon", 0, game_str_gr_gcon);
    p("game_str_gr_scapt", 0, game_str_gr_scapt);
    p("game_str_gr_itroops", 0, game_str_gr_itroops);
    p("game_str_gr_succd", 0, game_str_gr_succd);
    p("game_str_gr_fcapt", 0, game_str_gr_fcapt);
    p("game_str_gr_tsteal", 0, game_str_gr_tsteal);
    p("game_str_gr_tnew", 0, game_str_gr_tnew);
    p("game_str_el_no", 0, game_str_el_no);
    p("game_str_el_vote", 0, game_str_el_vote);
    p("game_str_el_votes", 0, game_str_el_votes);
    p("game_str_el_total", 0, game_str_el_total);
    p("game_str_el_start", 0, game_str_el_start);
    p("game_str_el_emperor", 0, game_str_el_emperor);
    p("game_str_el_ofthe", 0, game_str_el_ofthe);
    p("game_str_el_and", 0, game_str_el_and);
    p("game_str_el_for", 0, game_str_el_for);
    p("game_str_el_nomin", 0, game_str_el_nomin);
    p("game_str_el_abs1", 0, game_str_el_abs1);
    p("game_str_el_abs2", 0, game_str_el_abs2);
    p("game_str_el_dots", 0, game_str_el_dots);
    p("game_str_el_your", 0, game_str_el_your);
    p("game_str_el_bull", 0, game_str_el_bull);
    p("game_str_el_self", 0, game_str_el_self);
    p("game_str_el_abs", 0, game_str_el_abs);
    p("game_str_el_chose1", 0, game_str_el_chose1);
    p("game_str_el_chose2", 0, game_str_el_chose2);
    p("game_str_el_chose3", 0, game_str_el_chose3);
    p("game_str_el_neither", 0, game_str_el_neither);
    p("game_str_el_accept", 0, game_str_el_accept);
    p("game_str_el_yes", 0, game_str_el_yes);
    p("game_str_el_no2", 0, game_str_el_no2);
    p("game_str_el_sobeit", 0, game_str_el_sobeit);
    p("game_str_el_isnow", 0, game_str_el_isnow);
    p("game_str_au_facts", 0, game_str_au_facts);
    p("game_str_au_bases", 0, game_str_au_bases);
    p("game_str_au_treaty", 0, game_str_au_treaty);
    p("game_str_au_allian", 0, game_str_au_allian);
    p("game_str_au_nonagg", 0, game_str_au_nonagg);
    p("game_str_au_tradea", 0, game_str_au_tradea);
    p("game_str_au_amreca", 0, game_str_au_amreca);
    p("game_str_au_tech", 0, game_str_au_tech);
    p("game_str_au_framed", 0, game_str_au_framed);
    p("game_str_au_bull", 0, game_str_au_bull);
    p("game_str_au_inxchng", 0, game_str_au_inxchng);
    p("game_str_au_whatif1", 0, game_str_au_whatif1);
    p("game_str_au_whatif2", 0, game_str_au_whatif2);
    p("game_str_au_perrec1", 0, game_str_au_perrec1);
    p("game_str_au_ques", 0, game_str_au_ques);
    p("game_str_au_howmay", 0, game_str_au_howmay);
    p("game_str_au_youprte", 0, game_str_au_youprte);
    p("game_str_au_youprta", 0, game_str_au_youprta);
    p("game_str_au_youract", 0, game_str_au_youract);
    p("game_str_au_whatech", 0, game_str_au_whatech);
    p("game_str_au_whatrad", 0, game_str_au_whatrad);
    p("game_str_au_whatoff", 0, game_str_au_whatoff);
    p("game_str_au_perthr1", 0, game_str_au_perthr1);
    p("game_str_au_perthr2", 0, game_str_au_perthr2);
    p("game_str_au_alsoof1", 0, game_str_au_alsoof1);
    p("game_str_au_alsoof2", 0, game_str_au_alsoof2);
    p("game_str_au_whowar", 0, game_str_au_whowar);
    p("game_str_au_whobrk", 0, game_str_au_whobrk);
    p("game_str_au_bcpery", 0, game_str_au_bcpery);
    p("game_str_au_whattr", 0, game_str_au_whattr);
    p("game_str_au_techn", 0, game_str_au_techn);
    p("game_str_au_nextp", 0, game_str_au_nextp);
    p("game_str_au_back", 0, game_str_au_back);
    for (int i = 0; i < (int)(sizeof(game_str_au_opts_main) / sizeof(game_str_au_opts_main[0])); ++i) { p("game_str_au_opts_main", i, game_str_au_opts_main[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_au_opts_treaty) / sizeof(game_str_au_opts_treaty[0])); ++i) { p("game_str_au_opts_treaty", i, game_str_au_opts_treaty[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_au_opts_agree) / sizeof(game_str_au_opts_agree[0])); ++i) { p("game_str_au_opts_agree", i, game_str_au_opts_agree[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_au_opts_accept) / sizeof(game_str_au_opts_accept[0])); ++i) { p("game_str_au_opts_accept", i, game_str_au_opts_accept[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_au_opts_threaten) / sizeof(game_str_au_opts_threaten[0])); ++i) { p("game_str_au_opts_threaten", i, game_str_au_opts_threaten[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_au_optsmp1) / sizeof(game_str_au_optsmp1[0])); ++i) { p("game_str_au_optsmp1", i, game_str_au_optsmp1[i]); }
    p("game_str_tr_cont1", 0, game_str_tr_cont1);
    p("game_str_tr_cont2", 0, game_str_tr_cont2);
    p("game_str_tr_fuel1", 0, game_str_tr_fuel1);
    p("game_str_tr_fuel2", 0, game_str_tr_fuel2);
    p("game_str_sv_envir", 0, game_str_sv_envir);
    p("game_str_sv_stargt", 0, game_str_sv_stargt);
    p("game_str_sv_shild1", 0, game_str_sv_shild1);
    p("game_str_sv_shild2", 0, game_str_sv_shild2);
    p("game_str_sv_psize", 0, game_str_sv_psize);
    p("game_str_sv_fact", 0, game_str_sv_fact);
    p("game_str_sv_waste", 0, game_str_sv_waste);
    p("game_str_sv_pop", 0, game_str_sv_pop);
    p("game_str_sv_growth", 0, game_str_sv_growth);
    p("game_str_sv_techp", 0, game_str_sv_techp);
    p("game_str_sv_resp", 0, game_str_sv_resp);
    p("game_str_sv_1_3x", 0, game_str_sv_1_3x);
    p("game_str_sv_1_2x", 0, game_str_sv_1_2x);
    p("game_str_sv_2x", 0, game_str_sv_2x);
    p("game_str_sv_3x", 0, game_str_sv_3x);
    p("game_str_sv_4x", 0, game_str_sv_4x);
    p("game_str_sv_popgr", 0, game_str_sv_popgr);
    for (int i = 0; i < (int)(sizeof(game_str_sv_pg1) / sizeof(game_str_sv_pg1[0])); ++i) { p("game_str_sv_pg1", i, game_str_sv_pg1[i]); }
    for (int i = 0; i < (int)(sizeof(game_str_sv_pg2) / sizeof(game_str_sv_pg2[0])); ++i) { p("game_str_sv_pg2", i, game_str_sv_pg2[i]); }
    p("game_str_in_loading", 0, game_str_in_loading);
    p("game_str_wl_won_1", 0, game_str_wl_won_1);
    p("game_str_wl_won_2", 0, game_str_wl_won_2);
    p("game_str_wl_won_3", 0, game_str_wl_won_3);
    p("game_str_wl_3_good_1", 0, game_str_wl_3_good_1);
    p("game_str_wl_3_good_2", 0, game_str_wl_3_good_2);
    p("game_str_wl_3_tyrant_1", 0, game_str_wl_3_tyrant_1);
    p("game_str_wl_3_tyrant_2", 0, game_str_wl_3_tyrant_2);
    p("game_str_wl_3_tyrant_3", 0, game_str_wl_3_tyrant_3);
    p("game_str_wl_3_tyrant_4", 0, game_str_wl_3_tyrant_4);
    p("game_str_wl_exile_1", 0, game_str_wl_exile_1);
    p("game_str_wl_exile_2", 0, game_str_wl_exile_2);
    p("game_str_wl_exile_3", 0, game_str_wl_exile_3);
    p("game_str_wl_exile_4", 0, game_str_wl_exile_4);
    p("game_str_gnn_end_good", 0, game_str_gnn_end_good);
    p("game_str_gnn_end_tyrant", 0, game_str_gnn_end_tyrant);
    p("game_str_gnn_also", 0, game_str_gnn_also);
    return 0;
}
