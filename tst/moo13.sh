#!/bin/sh
# game_save_moo13.c of the port against the C: each save of the C is made
# into a save of MOO1 v1.3 (by 1oom_saveconv of the C, in a temporary
# directory: never kept), then loaded by both (tst/c/state.c and
# tst/state.atm, mode moo13), and the whole state compared, also after a
# few operations.
#   tst/moo13.sh DATADIR SAVE...       (ATMOS: the compiler, default `atmos`)
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
n=0; bad=0
for f in "$@"; do
    n=$((n+1))
    rm -f "$TMP/SAVE1.GAM"
    (cd "$TMP" && HOME="$TMP" "$B/1oom_saveconv" -i 1 -o m "$f" SAVE1.GAM > /dev/null 2>&1) || { echo "saveconv failed: $f"; bad=$((bad+1)); continue; }
    "$TMP/c" "$DATA" "$TMP/c.txt" moo13 "$TMP/SAVE1.GAM" start tech_util production > "$TMP/c.out" || echo "C failed: $f"
    "$TMP/atm" "$DATA" "$TMP/a.txt" moo13 "$TMP/SAVE1.GAM" start tech_util production | grep -v '^Save: ' > "$TMP/a.out" || true
    if ! cmp -s "$TMP/c.txt" "$TMP/a.txt" || ! cmp -s "$TMP/c.out" "$TMP/a.out"; then
        bad=$((bad+1)); echo "FAIL: $f"
    fi
done
echo "moo13: $n saves, $bad failed"
[ "$bad" -eq 0 ]
