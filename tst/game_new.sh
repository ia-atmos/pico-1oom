#!/bin/sh
# game_new.c of the port against the C: new games from many options and
# seeds, each saved and compared byte by byte.
#   tst/game_new.sh DATADIR       (ATMOS: the compiler, default `atmos`)
set -e
DATA=$1
ATMOS=${ATMOS:-atmos}
DIR=$(cd "$(dirname "$0")" && pwd)
C=$DIR/../c/src
B=$DIR/../c/build-native/src
TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT
# The game library of the C, with stubs for what a new game never calls
# (the interface, the options of main): each aborts if it is called.
echo '#include <stdlib.h>' > "$TMP/stubs.c"
L="$B/game/libgame.a $B/lbx.o $B/lib.o $B/log.o $B/util.o $B/util_math.o $B/rnd.o $B/util_cstr.o $B/os/unix/libos.a"
for k in 1 2 3; do
    if cc -O1 -I"$B" -I"$C" -I"$C/game" -I"$C/os/unix" -o "$TMP/c" "$DIR/c/game_new.c" "$TMP/stubs.c" $L -lm 2> "$TMP/ld.txt"; then
        break
    fi
    grep -o "undefined reference to \`[a-zA-Z_0-9]*'" "$TMP/ld.txt" | sed "s/undefined reference to \`//; s/'//" | sort -u |
        while read s; do echo "void $s(void) { abort(); }" >> "$TMP/stubs.c"; done
done
"$ATMOS" -o "$TMP/atm" "$DIR/game_new.atm"
n=0; bad=0
# OPT RACES BANNERS HUMANS: see doc/usage_common.txt of the C (-new GAMESEED)
for cfg in "200 0 0 1" "300 0 0 1" "312 0 0 1" "421 0 0 1" "534 0 0 1" "634 0 0 1" \
           "603 0 0 1" "644 0 0 1" "220 0x21 0x12 1" "500 0x54321 12345 11" "610 0xa98765 654321 1" \
           "633 0 0 0" "600 0 0 111111" "434 0x3333 0 1"; do
    set -- $cfg
    for seed in 1 12345 0xfda3f 118835000 3735928559 77777; do
        for imp in 0 1; do
            for neb in 1 0; do
                n=$((n+1))
                "$TMP/c" "$DATA" $1 $2 $3 $seed $4 $imp $neb "$TMP/c.bin" > "$TMP/c.log"
                "$TMP/atm" "$DATA" $1 $2 $3 $seed $4 $imp $neb "$TMP/a.bin" > "$TMP/a.log"
                if ! cmp -s "$TMP/c.bin" "$TMP/a.bin"; then
                    bad=$((bad+1)); echo "FAIL: $1 $2 $3 $seed $4 improved $imp nebulae $neb"
                fi
            done
        done
    done
done
echo "game_new: $n new games, $bad failed"
[ "$bad" -eq 0 ]
