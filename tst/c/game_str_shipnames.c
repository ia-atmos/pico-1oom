/* The oracle of tst/game_str_shipnames.atm: every string of c/src/game/game_str_shipnames.c.
   Generated with it. Not part of the port. */
#include <stdio.h>
#include "game_str.h"

static void p(const char *n, int i, const char *s) { printf("%s[%i] = %s\n", n, i, s ? s : "(null)"); }

int main(void)
{
    for (int i = 0; i < (int)(sizeof(game_str_tbl_ship_names) / sizeof(game_str_tbl_ship_names[0])); ++i) { p("game_str_tbl_ship_names", i, game_str_tbl_ship_names[i]); }
    return 0;
}
