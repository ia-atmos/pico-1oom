#!/bin/sh
# The textual interface of the port (src/main.atm) against 1oom_cmdline of
# the C: each case is a file in tst/cmdline/, its first line the options
# (after -data and -user), the rest the input typed. What both print and
# the saves they write must be equal.
#   tst/cmdline.sh DATADIR [CASE...]     (ATMOS: the compiler, default `atmos`)
# The C writes its errors and warnings to stderr, the port to stdout (#5):
# those lines are left out of the output of the port. For now (#14) the
# output is compared from the line "USER: ..." (options.c is not ported).
set -e
ATMOS=${ATMOS:-atmos}
DIR=$(cd "$(dirname "$0")" && pwd)
C=$DIR/../c/build-native/src/1oom_cmdline
DATA=$1
shift
[ $# -gt 0 ] || set -- "$DIR"/cmdline/*.txt
TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT
"$ATMOS" -o "$TMP/atm" "$DIR/../src/main.atm"
# a fixed time: the random seeds (the time in microseconds) equal in both
cc -shared -fPIC -o "$TMP/fixtime.so" "$DIR/c/fixtime.c"
n=0; bad=0
for f in "$@"; do
    n=$((n+1))
    opts=$(head -n 1 "$f")
    rm -rf "$TMP/uc" "$TMP/ua"; mkdir "$TMP/uc" "$TMP/ua"
    tail -n +2 "$f" | (cd "$TMP/uc" && LD_PRELOAD="$TMP/fixtime.so" $C -data "$DATA" -user . -cro -nolog $opts > "$TMP/c.out" 2> "$TMP/c.err") || true
    tail -n +2 "$f" | (cd "$TMP/ua" && LD_PRELOAD="$TMP/fixtime.so" "$TMP/atm" -data "$DATA" -user . -cro -nolog $opts > "$TMP/a.raw") || true
    python3 -I - "$TMP/c.err" "$TMP/a.raw" "$TMP/a.out" <<'PY'
import sys
err = open(sys.argv[1], encoding='latin-1').read().splitlines(True)
out = open(sys.argv[2], encoding='latin-1').read()
for e in err:
    k = out.find(e)
    if k >= 0:
        out = out[:k] + out[k + len(e):]
open(sys.argv[3], 'w', encoding='latin-1').write(out)
PY
    sed -n '/^USER: /,$p' "$TMP/c.out" > "$TMP/c.cmp"
    sed -n '/^USER: /,$p' "$TMP/a.out" > "$TMP/a.cmp"
    ok=1
    cmp -s "$TMP/c.cmp" "$TMP/a.cmp" || ok=0
    for s in "$TMP"/uc/*.bin; do
        [ -e "$s" ] || continue
        cmp -s "$s" "$TMP/ua/$(basename "$s")" || ok=0
    done
    for s in "$TMP"/ua/*.bin; do
        [ -e "$s" ] || continue
        [ -e "$TMP/uc/$(basename "$s")" ] || ok=0
    done
    if [ $ok = 0 ]; then
        bad=$((bad+1)); echo "FAIL: $f"
        [ -n "$KEEP" ] && cp "$TMP/c.cmp" "$TMP/a.cmp" "$KEEP/"
    fi
done
echo "cmdline: $n sessions, $bad failed"
[ "$bad" -eq 0 ]
