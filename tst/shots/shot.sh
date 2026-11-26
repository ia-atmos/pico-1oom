#!/bin/sh
# Screenshots of the interface of 1993 (the C, 1oom_classic_sdl2) on a
# virtual X display, for the author at each big step.
#   tst/shots/shot.sh CLASSIC DATADIR OUT.png SAVE [KEY|wait ...]
# CLASSIC: 1oom_classic_sdl2 (configure c/ with SDL2, see TODO.md).
# KEY: an X keysym (Return, Escape, r, p, ...), sent with XTest; `wait`
# waits 2 s. Needs Xvfb, ImageMagick (import, convert) and libXtst.
DIR=$(cd "$(dirname "$0")" && pwd)
CLASSIC=$1; DATA=$2; OUT=$3; SAVE=$4
shift 4
U=$(mktemp -d)
cp "$SAVE" "$U/save.bin"
Xvfb :77 -screen 0 1280x800x24 >/dev/null 2>&1 & XP=$!
sleep 1
DISPLAY=:77 SDL_AUDIODRIVER=dummy "$CLASSIC" -data "$DATA" -user "$U" -cro -nolog -noaudio -window -winw 960 -winh 600 -load "$U/save.bin" >/dev/null 2>&1 & GP=$!
sleep 12
for k in "$@"; do
    if [ "$k" = "wait" ]; then sleep 2; else DISPLAY=:77 python3 -I "$DIR/xkey.py" "$k"; sleep 1; fi
done
DISPLAY=:77 import -window root "$OUT"
convert "$OUT" -trim +repage "$OUT"
kill $GP $XP 2>/dev/null
rm -rf "$U"
