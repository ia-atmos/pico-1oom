#!/bin/sh
# rnd.c of the port against the C.
#   tst/rnd.sh       (ATMOS: the compiler of Atmos, default `atmos`)
set -e
ATMOS=${ATMOS:-atmos}
DIR=$(cd "$(dirname "$0")" && pwd)
C=$DIR/../c/src
TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT
cc -O1 -I"$DIR/../c/build-native/src" -I"$C" -o "$TMP/c" "$DIR/c/rnd.c" "$C/rnd.c"
"$TMP/c" > "$TMP/c.txt"
"$ATMOS" "$DIR/rnd.atm" > "$TMP/atm.txt"
if cmp -s "$TMP/c.txt" "$TMP/atm.txt"; then
    echo "rnd: $(wc -l < "$TMP/c.txt") lines, identical"
else
    diff "$TMP/c.txt" "$TMP/atm.txt" | head -10
    exit 1
fi
