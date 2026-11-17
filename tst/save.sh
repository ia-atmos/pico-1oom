#!/bin/sh
# Step 1 of the port, the save: for each save written by the C, the port
# must (1) write it back byte by byte, and (2) read the same values as the C,
# field by field, compared as the text of `1oom_saveconv -o t`.
#
#   tst/save.sh SAVE...
#
# Needs the compiler of Atmos (ATMOS, default `atmos`) and the C built in
# c/build-native (see README.md).

set -e
ATMOS=${ATMOS:-atmos}
DIR=$(cd "$(dirname "$0")" && pwd)
C=$DIR/../c/build-native/src
TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT

"$ATMOS" -o "$TMP/rt" "$DIR/save-roundtrip.atm"
"$ATMOS" -o "$TMP/st" "$DIR/save-text.atm"

n=0; bad=0
for f in "$@"; do
    n=$((n+1))
    "$TMP/rt" "$f" "$TMP/out.bin" > /dev/null
    if ! cmp -s "$f" "$TMP/out.bin"; then
        echo "FAIL bytes: $f"; bad=$((bad+1)); continue
    fi
    "$TMP/st" "$f" "$TMP/atm.txt" > /dev/null
    "$C/1oom_saveconv" -o t "$f" "$TMP/c.txt" > /dev/null 2>&1
    if ! cmp -s "$TMP/c.txt" "$TMP/atm.txt"; then
        echo "FAIL values: $f"; bad=$((bad+1))
    fi
done
echo "$n saves, $bad failed"
[ "$bad" -eq 0 ]
