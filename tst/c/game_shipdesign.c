/* The oracle of tst/game_shipdesign.atm: the tables of
   c/src/game/game_shipdesign.c. Not part of the port. */
#include <stdio.h>
#include "game_shipdesign.h"

int main(void)
{
    printf("startship_num = %i\n", startship_num);
    for (int i = 0; i < NUM_SHIPDESIGNS; ++i) {
        const shipdesign_t *sd = &tbl_startship[i];
        printf("tbl_startship[%i] = name", i);
        for (int k = 0; k < SHIP_NAME_LEN; ++k) { printf(" %i", sd->name[k]); }
        printf(" cost %i space %i hull %i look %i wpnt %i %i %i %i wpnn %i %i %i %i engine %i engines %i special %i %i %i shield %i jammer %i comp %i armor %i man %i hp %i\n",
               sd->cost, sd->space, sd->hull, sd->look, sd->wpnt[0], sd->wpnt[1], sd->wpnt[2], sd->wpnt[3],
               sd->wpnn[0], sd->wpnn[1], sd->wpnn[2], sd->wpnn[3], sd->engine, sd->engines,
               sd->special[0], sd->special[1], sd->special[2], sd->shield, sd->jammer, sd->comp, sd->armor, sd->man, sd->hp);
        printf("startfleet_ships[%i] = %i\n", i, startfleet_ships[i]);
    }
    return 0;
}
