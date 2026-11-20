#!/bin/sh
# util_math of the port against the C, on 3000 random points.
#   tst/util_math.sh       (ATMOS: the compiler of Atmos, default `atmos`)
set -e
ATMOS=${ATMOS:-atmos}
DIR=$(cd "$(dirname "$0")" && pwd)
TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT
cc -O1 -I"$DIR/../c/build-native/src" -I"$DIR/../c/src" -o "$TMP/c" "$DIR/c/util_math.c" "$DIR/../c/src/util_math.c"
"$TMP/c" > "$TMP/c.txt"
"$ATMOS" "$DIR/util_math.atm" > "$TMP/atm.txt"
if cmp -s "$TMP/c.txt" "$TMP/atm.txt"; then
    echo "util_math: $(wc -l < "$TMP/c.txt") lines, identical"
else
    diff "$TMP/c.txt" "$TMP/atm.txt" | head -10
    exit 1
fi
