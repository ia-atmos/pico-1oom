#!/bin/sh
# Every check of the port against the C.
#   tst/all.sh DATADIR SAVE...
# DATADIR: the LBX files of MOO1 (the user's own copy, not in the repository).
# SAVE: saves written by the C (1oom_cmdline), e.g. from a game with -yearsave.
# ATMOS: the compiler of Atmos (default `atmos`). The C must be built in
# c/build-native (see README.md).
set -e
DIR=$(cd "$(dirname "$0")" && pwd)
DATA=$1
shift
"$DIR/util_math.sh"
"$DIR/rnd.sh"
"$DIR/game_str.sh"
"$DIR/game_num.sh"
"$DIR/game_shiptech.sh"
"$DIR/game_shipdesign.sh"
"$DIR/lbx.sh" "$DATA"
"$DIR/game_aux.sh" "$DATA" "$@"
"$DIR/save.sh" "$@"
