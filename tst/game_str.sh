#!/bin/sh
# game_str.c of the port against the C: every string.
#   tst/game_str.sh       (ATMOS: the compiler of Atmos, default `atmos`)
set -e
ATMOS=${ATMOS:-atmos}
DIR=$(cd "$(dirname "$0")" && pwd)
C=$DIR/../c/src
TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT
cc -O1 -I"$DIR/../c/build-native/src" -I"$C" -I"$C/game" -o "$TMP/c" "$DIR/c/game_str.c" "$C/game/game_str.c"
"$TMP/c" > "$TMP/c.txt"
"$ATMOS" "$DIR/game_str.atm" > "$TMP/atm.txt"
if cmp -s "$TMP/c.txt" "$TMP/atm.txt"; then
    echo "game_str: $(wc -l < "$TMP/c.txt") strings, identical"
else
    diff "$TMP/c.txt" "$TMP/atm.txt" | head -10
    exit 1
fi
