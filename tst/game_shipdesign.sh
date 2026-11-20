#!/bin/sh
# game_shipdesign.c of the port against the C: its tables.
#   tst/game_shipdesign.sh       (ATMOS: the compiler of Atmos, default `atmos`)
set -e
ATMOS=${ATMOS:-atmos}
DIR=$(cd "$(dirname "$0")" && pwd)
C=$DIR/../c/src
TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT
cc -O1 -I"$DIR/../c/build-native/src" -I"$C" -I"$C/game" -o "$TMP/c" "$DIR/c/game_shipdesign.c" "$C/game/game_shipdesign.c"
"$TMP/c" > "$TMP/c.txt"
"$ATMOS" "$DIR/game_shipdesign.atm" > "$TMP/atm.txt"
if cmp -s "$TMP/c.txt" "$TMP/atm.txt"; then
    echo "game_shipdesign: $(wc -l < "$TMP/c.txt") lines, identical"
else
    diff "$TMP/c.txt" "$TMP/atm.txt" | head -10
    exit 1
fi
