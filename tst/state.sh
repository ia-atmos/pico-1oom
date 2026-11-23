#!/bin/sh
# Operations of the logic (game_misc.c, game_tech.c, game_turn.c, ...) on
# saves of the C, against the C: the whole state compared after each group
# (tst/c/state.c, tst/state.atm, the dump of tools/gamedump.py), and what the
# operations print (the log of the port, also on the output, is left out).
#   tst/state.sh DATADIR SAVE...       (ATMOS: the compiler, default `atmos`)
set -e
ATMOS=${ATMOS:-atmos}
DIR=$(cd "$(dirname "$0")" && pwd)
C=$DIR/../c/src
B=$DIR/../c/build-native/src
DATA=$1
shift
TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT
echo '#include <stdlib.h>' > "$TMP/stubs.c"
L="$B/game/libgame.a $B/lbx.o $B/lib.o $B/log.o $B/util.o $B/util_math.o $B/rnd.o $B/util_cstr.o $B/os/unix/libos.a"
for k in 1 2 3 4 5 6; do
    if cc -O1 -I"$B" -I"$C" -I"$C/game" -I"$C/os/unix" -I"$DIR/c" -o "$TMP/c" "$DIR/c/state.c" "$TMP/stubs.c" $L -lm 2> "$TMP/ld.txt"; then
        break
    fi
    grep -o "undefined reference to \`[a-zA-Z_0-9]*'" "$TMP/ld.txt" | sed "s/undefined reference to \`//; s/'//" | sort -u |
        while read s; do echo "void $s(void) { abort(); }" >> "$TMP/stubs.c"; done
done
"$ATMOS" -o "$TMP/atm" "$DIR/state.atm"
OPS1="start have_reserve_fuel tech_util production total_research eco_on_waste:0:0 eco_on_waste:1:1 seen_by_orbit:0 seen_by_orbit:1 within_range empire_contact visibility reloc_dest rng_step"
OPS3="start production adjust_percent:0:2:20:0 adjust_percent:1:3:30:1 adjust_percent2:0:4:25:0 planet_destroy:1:2 planet_destroy:2:0 update_home production"
OPS2="start production total_research finish_new:0 start_next:1:2:5 set_to_max_bonus:0:3 equalize_tech:2 adjust_tech:0:1:40 soil_enrich:3:20:0 soil_enrich:4:40:1 atmos_tform:5 artifact_loot:7:0 orion_loot:0 tech_util"
OPS4="start tech_util production limit_ships countdown_ceasefire mood_blunder init_z_finished send_transport build_eco update_trade build_def build_ship reserve build_ind remove_empty_fleets fleet_unrefuel disable_slider:5:3:1 disable_slider:6:2:0"
OPS5="start tech_util production stats:0 stats:1 any_dest:0:1 send_half:0:0:5:0 send_half:1:3:7:1 fleet_speed:0:255:4 redirect:0:255:3 redirect:1:2:2 remove_player_fleets:2 design_ai:0:1:3 design_ai:1:2:5 design_scrap:0:1:1 design_fit:0:0 design_fit:1:1 stats:0"
OPS6="start tech_util production moods diplo_adjust moods diplo_act:20:0:1:5:3:7 diplo_act:-30:1:2:9:4:0 diplo_act:-10000:0:2:6:1:2 set_trade:0:1:40 set_trade:1:2:25 annoy:2:0:3 esp_frame:1:2 battle_finish:1:0:3:20:0:10:4 battle_finish:0:2:-2:5:1:60:5 stop_war:0:2 break_treaty:1:2 start_war:0:3 start_war_swap:2:1 break_trade:1:0 set_treaty:0:1:2 diplo_adjust limit_mood_treaty mood_relax moods"
OPS7="start tech_util production transport_shoot:0:1:20:2:0:5:2 transport_shoot:1:0:300:1:1:0:0 set_trans:0:0:0:5 set_trans:1:0:2:40 set_trans:0:1:1:12 set_trans:2:0:2:90 set_trans:1:1:1:3 send_transport move_ships transport explore move_ships transport explore move_ships transport explore coup have_met move_ships transport explore move_ships transport explore move_ships transport explore"
OPS8="start tech_util production build_eco build_def build_ship build_ind finished_slider contact_broken:0:62 contact_broken:1:63 update_seen claim visibility update_seen set_refuse:5 set_end:3 final_war production total_research"
OPS9="start tech_util production set_spy:0:1:200:1:3 set_spy:1:0:150:2:5 set_spy:0:2:100:2:4 set_spy:2:0:80:1:6 set_spy:1:2:50:1:2 set_spy:2:1:120:2:3 spy_build spy_report spy_turn spy_esp_human spy_sab_human spy_build spy_turn spy_esp_human spy_sab_human"
OPS10="start tech_util production set_spy:0:1:200:1:10 set_spy:0:2:200:1:2 set_spy:0:3:200:1:1 set_spy:1:0:150:1:5 set_spy:2:0:150:2:5 spy_turn spy_esp_human spy_sab_human spy_turn spy_esp_human spy_sab_human spy_turn spy_esp_human spy_sab_human"
n=0; bad=0
for f in "$@"; do
    for ops in "$OPS1" "$OPS2" "$OPS3" "$OPS4" "$OPS5" "$OPS6" "$OPS7" "$OPS8" "$OPS9" "$OPS10"; do
        n=$((n+1))
        "$TMP/c" "$DATA" "$TMP/c.txt" load "$f" $ops > "$TMP/c.out"
        "$TMP/atm" "$DATA" "$TMP/a.txt" load "$f" $ops | grep -v '^Save: ' > "$TMP/a.out" || true
        if ! cmp -s "$TMP/c.txt" "$TMP/a.txt" || ! cmp -s "$TMP/c.out" "$TMP/a.out"; then
            bad=$((bad+1)); echo "FAIL: $f: $ops"
        fi
    done
done
echo "state: $n runs, $bad failed"
[ "$bad" -eq 0 ]
