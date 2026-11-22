#!/bin/sh
# game_num.c of the port against the C: every number.
#   tst/game_num.sh       (ATMOS: the compiler of Atmos, default `atmos`)
set -e
ATMOS=${ATMOS:-atmos}
DIR=$(cd "$(dirname "$0")" && pwd)
C=$DIR/../c/src
TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT
cc -O1 -I"$DIR/../c/build-native/src" -I"$C" -I"$C/game" -o "$TMP/c" "$DIR/c/game_num.c" "$C/game/game_num.c"
"$TMP/c" > "$TMP/c.txt"
"$ATMOS" "$DIR/game_num.atm" > "$TMP/atm.txt"
if cmp -s "$TMP/c.txt" "$TMP/atm.txt"; then
    echo "game_num: $(wc -l < "$TMP/c.txt") numbers, identical"
else
    diff "$TMP/c.txt" "$TMP/atm.txt" | head -10
    exit 1
fi
