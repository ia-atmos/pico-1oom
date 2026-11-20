#!/bin/sh
# lbx.c of the port against the C, on the LBX files of MOO1 (not in the
# repository: the user's own copy).
#   tst/lbx.sh DATADIR       (ATMOS: the compiler of Atmos, default `atmos`)
set -e
ATMOS=${ATMOS:-atmos}
DIR=$(cd "$(dirname "$0")" && pwd)
C=$DIR/../c/src
TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT
cc -O1 -I"$DIR/../c/build-native/src" -I"$C" -I"$C/os/unix" -o "$TMP/c" "$DIR/c/lbx.c" \
    "$C/lbx.c" "$C/lib.c" "$C/log.c" "$C/util.c" "$C/os/unix/os.c"
"$TMP/c" "$1" > "$TMP/c.txt"
"$ATMOS" "$DIR/lbx.atm" "$1" > "$TMP/atm.txt"
if cmp -s "$TMP/c.txt" "$TMP/atm.txt"; then
    echo "lbx: $(wc -l < "$TMP/c.txt") lines, identical"
else
    diff "$TMP/c.txt" "$TMP/atm.txt" | head -10
    exit 1
fi
