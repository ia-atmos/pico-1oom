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
OPS11="start tech_util production set_trans:0:0:2:300 set_trans:0:1:2:300 set_trans:0:2:2:300 set_trans:0:3:1:300 set_trans:1:0:2:300 set_trans:1:1:2:300 send_transport move_ships transport ground bomb move_ships transport ground bomb move_ships transport ground bomb move_ships transport ground bomb move_ships transport ground bomb move_ships transport ground bomb move_ships transport ground bomb move_ships transport ground bomb move_ships transport ground bomb move_ships transport ground bomb"
OPS12="start tech_util production news:1:0:3:2:1:5 news:1:1:4:0:1:6 news:1:2:0:3:1:7 news:1:3:1:1:1:8 news:2:0:1:4:2:10 news:2:1:2:2:2:11 news:2:2:3:0:2:12 news:2:3:4:3:2:13 news:3:0:4:1:3:15 news:3:1:0:4:3:16 news:3:2:1:2:3:17 news:3:3:2:0:3:18 news:4:0:2:3:4:0 news:4:1:3:1:4:1 news:4:2:4:4:4:2 news:4:3:0:2:4:3 news:5:0:0:0:5:5 news:5:1:1:3:5:6 news:5:2:2:1:5:7 news:5:3:3:4:5:8 news:6:0:3:2:6:10 news:6:1:4:0:6:11 news:6:2:0:3:6:12 news:6:3:1:1:6:13 news:7:0:1:4:7:15 news:7:1:2:2:7:16 news:7:2:3:0:7:17 news:7:3:4:3:7:18 news:8:0:4:1:8:0 news:8:1:0:4:8:1 news:8:2:1:2:8:2 news:8:3:2:0:8:3 news:9:0:2:3:9:5 news:9:1:3:1:9:6 news:9:2:4:4:9:7 news:9:3:0:2:9:8 news:10:0:0:0:0:10 news:10:1:1:3:0:11 news:10:2:2:1:0:12 news:10:3:3:4:0:13 news:11:0:3:2:1:15 news:11:1:4:0:1:16 news:11:2:0:3:1:17 news:11:3:1:1:1:18 news:12:0:1:4:2:0 news:12:1:2:2:2:1 news:12:2:3:0:2:2 news:12:3:4:3:2:3 news:13:0:4:1:3:5 news:13:1:0:4:3:6 news:13:2:1:2:3:7 news:13:3:2:0:3:8 news:14:0:2:3:4:10 news:14:1:3:1:4:11 news:14:2:4:4:4:12 news:14:3:0:2:4:13 news:15:0:0:0:5:15 news:15:1:1:3:5:16 news:15:2:2:1:5:17 news:15:3:3:4:5:18 news:16:0:3:2:6:0 news:16:1:4:0:6:1 news:16:2:0:3:6:2 news:16:3:1:1:6:3 news:17:0:1:4:7:5 news:17:1:2:2:7:6 news:17:2:3:0:7:7 news:17:3:4:3:7:8 news:18:0:4:1:8:10 news:18:1:0:4:8:11 news:18:2:1:2:8:12 news:18:3:2:0:8:13 news:19:0:2:3:9:15 news:19:1:3:1:9:16 news:19:2:4:4:9:17 news:19:3:0:2:9:18 news:20:0:0:0:0:0 news:20:1:1:3:0:1 news:20:2:2:1:0:2 news:20:3:3:4:0:3 news:21:0:3:2:1:5 news:21:1:4:0:1:6 news:21:2:0:3:1:7 news:21:3:1:1:1:8 news:22:0:1:4:2:10 news:22:1:2:2:2:11 news:22:2:3:0:2:12 news:22:3:4:3:2:13 election production election"
OPS13="start tech_util production set_event_roll:1 set_year:120 event_new event_run production event_new event_run production event_new event_run production event_new event_run production event_new event_run production event_new event_run production event_new event_run production event_new event_run production event_new event_run production event_new event_run production event_new event_run production event_new event_run production event_new event_run production event_new event_run production"
OPS14="start tech_util production set_event_roll:1 set_year:250 event_new event_run production event_new event_run production event_new event_run production event_new event_run production event_new event_run production event_new event_run production event_new event_run production event_new event_run production event_new event_run production event_new event_run production event_new event_run production event_new event_run production event_new event_run production event_new event_run production"
OPS15="start tech_util production check_end set_end:1 set_winner:0 check_end set_winner:1 check_end set_end:2 check_end set_end:0 check_end"
OPS16="start tech_util production audience:0:1:0 audience:0:1:24 audience:0:1:25 audience:0:1:26 audience:0:1:27 audience:0:1:29 audience:0:1:30 audience:0:1:76 audience:0:1:12 audience:0:1:22 audience:0:1:32 audience:0:1:0 audience:0:1:0 audience:0:1:0 set_diplo_type:0:1:24 set_diplo_type:0:2:12 audiences audience:0:1:0 audience:0:1:0 audience:0:1:0 audience:0:1:0"
OPS17="start tech_util production send_near:0:0 send_near:1:0 send_near:2:0 send_near:0:1 send_near:1:1 send_near:3:0 move_ships battles transport ground move_ships battles transport ground move_ships battles transport ground move_ships battles transport ground move_ships battles transport ground move_ships battles transport ground move_ships battles transport ground move_ships battles transport ground move_ships battles transport ground move_ships battles transport ground"
OPS18="start tech_util production ai_diplo_p1 ai_diplo_p2 audiences ai_diplo_p1 ai_diplo_p2 audiences ai_diplo_p1 ai_diplo_p2 audiences ai_diplo_p1 ai_diplo_p2 audiences ai_diplo_p1 ai_diplo_p2 audiences ai_diplo_p1 ai_diplo_p2 audiences set_end:2 ai_diplo_p1 ai_diplo_p2"
OPS19="start tech_util production diplo_act:-10000:0:1:5:3:7 diplo_act:-10000:1:2:9:4:0 diplo_act:-10000:2:3:6:1:2 diplo_act:-10000:3:0:6:1:2 diplo_act:-10000:4:5:6:1:2 diplo_act:-10000:1:0:6:1:2 set_treaty:1:2:2 set_treaty:0:3:1 set_treaty:2:4:2 set_treaty:0:2:2 ai_diplo_p1 ai_diplo_p2 audiences ai_diplo_p1 ai_diplo_p2 audiences ai_diplo_p1 ai_diplo_p2 audiences ai_diplo_p1 ai_diplo_p2 audiences ai_diplo_p1 ai_diplo_p2 audiences ai_diplo_p1 ai_diplo_p2 audiences ai_diplo_p1 ai_diplo_p2 audiences ai_diplo_p1 ai_diplo_p2 audiences"
OPS20="start tech_util production set_year:24 ai_p2 ai_p3 production set_year:25 ai_p2 ai_p3 production set_year:26 ai_p2 ai_p3 production set_year:27 ai_p2 ai_p3 production set_year:28 ai_p2 ai_p3 production set_year:29 ai_p2 ai_p3 production set_year:30 ai_p2 ai_p3 production set_year:31 ai_p2 ai_p3 production set_year:32 ai_p2 ai_p3 production set_year:33 ai_p2 ai_p3 production set_year:34 ai_p2 ai_p3 production set_year:35 ai_p2 ai_p3 production set_year:36 ai_p2 ai_p3 production set_year:37 ai_p2 ai_p3 production set_year:38 ai_p2 ai_p3 production set_year:39 ai_p2 ai_p3 production"
OPS21="start tech_util production within_range have_reserve_fuel ai_p1 move_ships battles transport ground ai_p2 ai_p3 production within_range have_reserve_fuel ai_p1 move_ships battles transport ground ai_p2 ai_p3 production within_range have_reserve_fuel ai_p1 move_ships battles transport ground ai_p2 ai_p3 production within_range have_reserve_fuel ai_p1 move_ships battles transport ground ai_p2 ai_p3 production within_range have_reserve_fuel ai_p1 move_ships battles transport ground ai_p2 ai_p3 production within_range have_reserve_fuel ai_p1 move_ships battles transport ground ai_p2 ai_p3 production within_range have_reserve_fuel ai_p1 move_ships battles transport ground ai_p2 ai_p3 production within_range have_reserve_fuel ai_p1 move_ships battles transport ground ai_p2 ai_p3 production"
OPS22="start tech_util production within_range visibility turn turn turn turn turn turn turn turn turn turn"
OPS23="start tech_util production within_range visibility cheat_events:0 cheat_elections:0 turn start_messages:0 start_messages:1 turn start_messages:0 start_messages:1 turn start_messages:0 start_messages:1 turn start_messages:0 start_messages:1 cheat_moola:0 cheat_galaxy:0 cheat_traits:0 turn start_messages:0 turn start_messages:0 turn start_messages:0 turn start_messages:0"
OPS24="start tech_util production within_range visibility planet_texts turn planet_texts turn planet_texts turn planet_texts"
n=0; bad=0
for f in "$@"; do
    for ops in "$OPS1" "$OPS2" "$OPS3" "$OPS4" "$OPS5" "$OPS6" "$OPS7" "$OPS8" "$OPS9" "$OPS10" "$OPS11" "$OPS12" "$OPS13" "$OPS14" "$OPS15" "$OPS16" "$OPS17" "$OPS18" "$OPS19" "$OPS20" "$OPS21" "$OPS22" "$OPS23" "$OPS24"; do
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
