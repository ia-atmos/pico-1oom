#!/bin/sh
# game_aux.c of the port against the C: the tables of the LBX files of the
# logic, and the distances of the stars of the given saves.
#   tst/game_aux.sh DATADIR SAVE...   (ATMOS: the compiler, default `atmos`)
set -e
ATMOS=${ATMOS:-atmos}
DIR=$(cd "$(dirname "$0")" && pwd)
C=$DIR/../c/src
TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT
cc -O1 -I"$DIR/../c/build-native/src" -I"$C" -I"$C/game" -I"$C/os/unix" -o "$TMP/c" "$DIR/c/game_aux.c" \
    "$C/game/game_aux.c" "$C/game/game_save.c" "$C/game/game_nebula.c" \
    "$C/lbx.c" "$C/lib.c" "$C/log.c" "$C/util.c" "$C/util_math.c" "$C/os/unix/os.c"
"$TMP/c" "$@" > "$TMP/c.txt"
"$ATMOS" "$DIR/game_aux.atm" "$@" | grep -v "^Save: load " > "$TMP/atm.txt"
if cmp -s "$TMP/c.txt" "$TMP/atm.txt"; then
    echo "game_aux: $(wc -l < "$TMP/c.txt") lines, identical"
else
    diff "$TMP/c.txt" "$TMP/atm.txt" | head -10
    exit 1
fi
