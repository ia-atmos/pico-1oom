#!/bin/sh
# The textual interface of the port (src/main.atm) against 1oom_cmdline of
# the C: each case is a file in tst/cmdline/, its first line the options
# (after -data and -user), the rest the input typed; a file NAME.cfg next to
# the case NAME.txt is the config file in the user directory at the start
# (in the format of C; the port reads it as a table of Atmos, made by
# tst/cfg2atm.py, and its config written is compared with the C's made the
# same way; the lines of both about the config, "Cfg: ...", differ and are
# left out),
# and a file NAME.pbxin is made (by 1oom_pbxmake of the C) into patch.pbx
# there, for an option -file patch.pbx.
# What both print, their exit codes and the files they write in the user
# directory (saves, config, log) must be equal.
#   tst/cmdline.sh DATADIR [CASE...]     (ATMOS: the compiler, default `atmos`;
#                                        ATM: a port already built, not built again)
# The C writes its errors and warnings to stderr, the port to stdout (#5):
# those lines are left out of the output of the port.
set -e
ATMOS=${ATMOS:-atmos}
DIR=$(cd "$(dirname "$0")" && pwd)
C=$DIR/../c/build-native/src/1oom_cmdline
DATA=$1
shift
[ $# -gt 0 ] || set -- "$DIR"/cmdline/*.txt
TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT
if [ -n "$ATM" ]; then cp "$ATM" "$TMP/atm"; else "$ATMOS" -o "$TMP/atm" "$DIR/../src/main.atm"; fi
# a fixed time: the random seeds (the time in microseconds) equal in both
cc -shared -fPIC -o "$TMP/fixtime.so" "$DIR/c/fixtime.c"
n=0; bad=0
for f in "$@"; do
    n=$((n+1))
    opts=$(head -n 1 "$f")
    rm -rf "$TMP/uc" "$TMP/ua"; mkdir "$TMP/uc" "$TMP/ua"
    cfg=${f%.txt}.cfg
    if [ -e "$cfg" ]; then
        cp "$cfg" "$TMP/uc/1oom_config_game_cmdline_nop.txt"
        python3 -I "$DIR/cfg2atm.py" "$cfg" > "$TMP/ua/1oom_config_game_cmdline_nop.atm"
    fi
    pbxin=${f%.txt}.pbxin
    if [ -e "$pbxin" ]; then
        "$DIR/../c/build-native/src/1oom_pbxmake" "$pbxin" "$TMP/uc/patch.pbx" > /dev/null
        cp "$TMP/uc/patch.pbx" "$TMP/ua/patch.pbx"
    fi
    rc=0; ra=0
    tail -n +2 "$f" | (cd "$TMP/uc" && LD_PRELOAD="$TMP/fixtime.so" $C -data "$DATA" -user . $opts > "$TMP/c.out" 2> "$TMP/c.err") || rc=$?
    tail -n +2 "$f" | (cd "$TMP/ua" && LD_PRELOAD="$TMP/fixtime.so" "$TMP/atm" -data "$DATA" -user . $opts > "$TMP/a.raw") || ra=$?
    sed -i 's/1oom_config_game_cmdline_nop\.txt/1oom_config_game_cmdline_nop.atm/' "$TMP/c.err"
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
    for x in c a; do
        grep -v 'Cfg: ' "$TMP/$x.out" | sed 's/1oom_config_game_cmdline_nop\.\(txt\|atm\)/1oom_config_game_cmdline_nop/' > "$TMP/$x.cmp" || true
    done
    if [ -e "$TMP/uc/1oom_config_game_cmdline_nop.txt" ]; then
        python3 -I "$DIR/cfg2atm.py" "$TMP/uc/1oom_config_game_cmdline_nop.txt" > "$TMP/uc/1oom_config_game_cmdline_nop.atm"
        rm "$TMP/uc/1oom_config_game_cmdline_nop.txt"
    fi
    ok=1
    cmp -s "$TMP/c.cmp" "$TMP/a.cmp" || ok=0
    [ "$rc" = "$ra" ] || { ok=0; echo "exit codes: C $rc, port $ra"; }
    for s in "$TMP"/uc/*; do
        [ -e "$s" ] || continue
        cmp -s "$s" "$TMP/ua/$(basename "$s")" || { ok=0; echo "differs: $(basename "$s")"; }
    done
    for s in "$TMP"/ua/*; do
        [ -e "$s" ] || continue
        [ -e "$TMP/uc/$(basename "$s")" ] || { ok=0; echo "only in the port: $(basename "$s")"; }
    done
    if [ $ok = 0 ]; then
        bad=$((bad+1)); echo "FAIL: $f"
        [ -n "$KEEP" ] && cp "$TMP/c.cmp" "$TMP/a.cmp" "$KEEP/"
    fi
done
echo "cmdline: $n sessions, $bad failed"
[ "$bad" -eq 0 ]
