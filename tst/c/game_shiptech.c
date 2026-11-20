/* The oracle of tst/game_shiptech.atm: every field of the tables of
   c/src/game/game_shiptech.c. Generated with it. Not part of the port. */
#include <stdio.h>
#include "game_shiptech.h"

int main(void)
{
    for (int i = 0; i < WEAPON_NUM; ++i) {
        printf("tbl_shiptech_weap[%i].nameptr = %s\n", i, *tbl_shiptech_weap[i].nameptr);
        printf("tbl_shiptech_weap[%i].extratextptr = %s\n", i, *tbl_shiptech_weap[i].extratextptr);
        printf("tbl_shiptech_weap[%i].damagemin = %i\n", i, tbl_shiptech_weap[i].damagemin);
        printf("tbl_shiptech_weap[%i].damagemax = %i\n", i, tbl_shiptech_weap[i].damagemax);
        printf("tbl_shiptech_weap[%i].range = %i\n", i, tbl_shiptech_weap[i].range);
        printf("tbl_shiptech_weap[%i].extraacc = %i\n", i, tbl_shiptech_weap[i].extraacc);
        printf("tbl_shiptech_weap[%i].halveshield = %i\n", i, tbl_shiptech_weap[i].halveshield);
        printf("tbl_shiptech_weap[%i].is_bomb = %i\n", i, tbl_shiptech_weap[i].is_bomb);
        printf("tbl_shiptech_weap[%i].damagefade = %i\n", i, tbl_shiptech_weap[i].damagefade);
        printf("tbl_shiptech_weap[%i].misstype = %i\n", i, tbl_shiptech_weap[i].misstype);
        printf("tbl_shiptech_weap[%i].damagemul = %i\n", i, tbl_shiptech_weap[i].damagemul);
        printf("tbl_shiptech_weap[%i].numfire = %i\n", i, tbl_shiptech_weap[i].numfire);
        printf("tbl_shiptech_weap[%i].numshots = %i\n", i, tbl_shiptech_weap[i].numshots);
        printf("tbl_shiptech_weap[%i].cost = %i\n", i, tbl_shiptech_weap[i].cost);
        printf("tbl_shiptech_weap[%i].space = %i\n", i, tbl_shiptech_weap[i].space);
        printf("tbl_shiptech_weap[%i].power = %i\n", i, tbl_shiptech_weap[i].power);
        printf("tbl_shiptech_weap[%i].is_bio = %i\n", i, tbl_shiptech_weap[i].is_bio);
        printf("tbl_shiptech_weap[%i].tech_i = %i\n", i, tbl_shiptech_weap[i].tech_i);
        printf("tbl_shiptech_weap[%i].v24 = %i\n", i, tbl_shiptech_weap[i].v24);
        printf("tbl_shiptech_weap[%i].dtbl =", i); for (int k = 0; k < 7; ++k) { printf(" %i", tbl_shiptech_weap[i].dtbl[k]); } printf("\n");
        printf("tbl_shiptech_weap[%i].sound = %i\n", i, tbl_shiptech_weap[i].sound);
        printf("tbl_shiptech_weap[%i].nummiss = %i\n", i, tbl_shiptech_weap[i].nummiss);
    }
    for (int i = 0; i < SHIP_COMP_NUM; ++i) {
        printf("tbl_shiptech_comp[%i].nameptr = %s\n", i, *tbl_shiptech_comp[i].nameptr);
        printf("tbl_shiptech_comp[%i].power =", i); for (int k = 0; k < SHIP_HULL_NUM; ++k) { printf(" %i", tbl_shiptech_comp[i].power[k]); } printf("\n");
        printf("tbl_shiptech_comp[%i].space =", i); for (int k = 0; k < SHIP_HULL_NUM; ++k) { printf(" %i", tbl_shiptech_comp[i].space[k]); } printf("\n");
        printf("tbl_shiptech_comp[%i].cost =", i); for (int k = 0; k < SHIP_HULL_NUM; ++k) { printf(" %i", tbl_shiptech_comp[i].cost[k]); } printf("\n");
        printf("tbl_shiptech_comp[%i].tech_i = %i\n", i, tbl_shiptech_comp[i].tech_i);
        printf("tbl_shiptech_comp[%i].level = %i\n", i, tbl_shiptech_comp[i].level);
    }
    for (int i = 0; i < SHIP_ENGINE_NUM; ++i) {
        printf("tbl_shiptech_engine[%i].nameptr = %s\n", i, *tbl_shiptech_engine[i].nameptr);
        printf("tbl_shiptech_engine[%i].power = %i\n", i, tbl_shiptech_engine[i].power);
        printf("tbl_shiptech_engine[%i].space = %i\n", i, tbl_shiptech_engine[i].space);
        printf("tbl_shiptech_engine[%i].cost = %i\n", i, tbl_shiptech_engine[i].cost);
        printf("tbl_shiptech_engine[%i].warp = %i\n", i, tbl_shiptech_engine[i].warp);
        printf("tbl_shiptech_engine[%i].tech_i = %i\n", i, tbl_shiptech_engine[i].tech_i);
    }
    for (int i = 0; i < SHIP_ARMOR_NUM; ++i) {
        printf("tbl_shiptech_armor[%i].nameptr = %s\n", i, *tbl_shiptech_armor[i].nameptr);
        printf("tbl_shiptech_armor[%i].cost =", i); for (int k = 0; k < SHIP_HULL_NUM; ++k) { printf(" %i", tbl_shiptech_armor[i].cost[k]); } printf("\n");
        printf("tbl_shiptech_armor[%i].space =", i); for (int k = 0; k < SHIP_HULL_NUM; ++k) { printf(" %i", tbl_shiptech_armor[i].space[k]); } printf("\n");
        printf("tbl_shiptech_armor[%i].armor = %i\n", i, tbl_shiptech_armor[i].armor);
        printf("tbl_shiptech_armor[%i].tech_i = %i\n", i, tbl_shiptech_armor[i].tech_i);
    }
    for (int i = 0; i < SHIP_SHIELD_NUM; ++i) {
        printf("tbl_shiptech_shield[%i].nameptr = %s\n", i, *tbl_shiptech_shield[i].nameptr);
        printf("tbl_shiptech_shield[%i].cost =", i); for (int k = 0; k < SHIP_HULL_NUM; ++k) { printf(" %i", tbl_shiptech_shield[i].cost[k]); } printf("\n");
        printf("tbl_shiptech_shield[%i].space =", i); for (int k = 0; k < SHIP_HULL_NUM; ++k) { printf(" %i", tbl_shiptech_shield[i].space[k]); } printf("\n");
        printf("tbl_shiptech_shield[%i].power =", i); for (int k = 0; k < SHIP_HULL_NUM; ++k) { printf(" %i", tbl_shiptech_shield[i].power[k]); } printf("\n");
        printf("tbl_shiptech_shield[%i].absorb = %i\n", i, tbl_shiptech_shield[i].absorb);
        printf("tbl_shiptech_shield[%i].tech_i = %i\n", i, tbl_shiptech_shield[i].tech_i);
    }
    for (int i = 0; i < SHIP_JAMMER_NUM; ++i) {
        printf("tbl_shiptech_jammer[%i].nameptr = %s\n", i, *tbl_shiptech_jammer[i].nameptr);
        printf("tbl_shiptech_jammer[%i].power =", i); for (int k = 0; k < SHIP_HULL_NUM; ++k) { printf(" %i", tbl_shiptech_jammer[i].power[k]); } printf("\n");
        printf("tbl_shiptech_jammer[%i].space =", i); for (int k = 0; k < SHIP_HULL_NUM; ++k) { printf(" %i", tbl_shiptech_jammer[i].space[k]); } printf("\n");
        printf("tbl_shiptech_jammer[%i].cost =", i); for (int k = 0; k < SHIP_HULL_NUM; ++k) { printf(" %i", tbl_shiptech_jammer[i].cost[k]); } printf("\n");
        printf("tbl_shiptech_jammer[%i].tech_i = %i\n", i, tbl_shiptech_jammer[i].tech_i);
        printf("tbl_shiptech_jammer[%i].level = %i\n", i, tbl_shiptech_jammer[i].level);
    }
    for (int i = 0; i < SHIP_SPECIAL_NUM; ++i) {
        printf("tbl_shiptech_special[%i].nameptr = %s\n", i, *tbl_shiptech_special[i].nameptr);
        printf("tbl_shiptech_special[%i].extratextptr = %s\n", i, *tbl_shiptech_special[i].extratextptr);
        printf("tbl_shiptech_special[%i].cost =", i); for (int k = 0; k < SHIP_HULL_NUM; ++k) { printf(" %i", tbl_shiptech_special[i].cost[k]); } printf("\n");
        printf("tbl_shiptech_special[%i].space =", i); for (int k = 0; k < SHIP_HULL_NUM; ++k) { printf(" %i", tbl_shiptech_special[i].space[k]); } printf("\n");
        printf("tbl_shiptech_special[%i].power =", i); for (int k = 0; k < SHIP_HULL_NUM; ++k) { printf(" %i", tbl_shiptech_special[i].power[k]); } printf("\n");
        printf("tbl_shiptech_special[%i].tech_i = %i\n", i, tbl_shiptech_special[i].tech_i);
        printf("tbl_shiptech_special[%i].field = %i\n", i, tbl_shiptech_special[i].field);
        printf("tbl_shiptech_special[%i].type = %i\n", i, tbl_shiptech_special[i].type);
        printf("tbl_shiptech_special[%i].repair = %i\n", i, tbl_shiptech_special[i].repair);
        printf("tbl_shiptech_special[%i].extraman = %i\n", i, tbl_shiptech_special[i].extraman);
        printf("tbl_shiptech_special[%i].misshield = %i\n", i, tbl_shiptech_special[i].misshield);
        printf("tbl_shiptech_special[%i].extrarange = %i\n", i, tbl_shiptech_special[i].extrarange);
        printf("tbl_shiptech_special[%i].pulsar = %i\n", i, tbl_shiptech_special[i].pulsar);
        printf("tbl_shiptech_special[%i].stream = %i\n", i, tbl_shiptech_special[i].stream);
        printf("tbl_shiptech_special[%i].boolmask = %i\n", i, tbl_shiptech_special[i].boolmask);
    }
    for (int i = 0; i < SHIP_HULL_NUM; ++i) {
        printf("tbl_shiptech_hull[%i].nameptr = %s\n", i, *tbl_shiptech_hull[i].nameptr);
        printf("tbl_shiptech_hull[%i].cost = %i\n", i, tbl_shiptech_hull[i].cost);
        printf("tbl_shiptech_hull[%i].space = %i\n", i, tbl_shiptech_hull[i].space);
        printf("tbl_shiptech_hull[%i].hits = %i\n", i, tbl_shiptech_hull[i].hits);
        printf("tbl_shiptech_hull[%i].power = %i\n", i, tbl_shiptech_hull[i].power);
        printf("tbl_shiptech_hull[%i].defense = %i\n", i, tbl_shiptech_hull[i].defense);
    }
    return 0;
}
