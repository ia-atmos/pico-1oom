# TODO

Everything that is pending in the session of the port of 1oom (Master
of Orion) to Atmos: asked and not decided, reported and not
acknowledged, or known and not done. Keep it current: remove an item
when it is settled, add one whenever something is left open.

The numbers are the ones used in the conversation with the author, and
do not change.

The initial instructions are in `ia-atmos/lang`,
`.claude/plans/261114-pico-1oom.md` (commit `354cf19`). Nothing starts
before the author says so.

Last update: 2026-11-17

## A. Decisions waiting for an answer

Each has the option recommended by this session. They are asked one at
a time.

| # | Decision | Recommended |
|---|----------|-------------|

## B. Work known and not done

The author said to start (2026-11-17), in the order of item 5.

- The oracle of the logic is built (2026-11-14), in `c/build-native/`
  (ignored by git), from `c/`: `autoreconf -fi`, then `../configure
  --disable-uiclassic --disable-hwsdl2 --disable-hwsdl1
  --disable-hwalleg4 --without-readline --without-samplerate`, then
  `make`. It gives `1oom_cmdline` (hardware `nop`) and the tools,
  with `1oom_saveconv`.
- The oracle of the interface of 1993 (`1oom_classic_sdl2`) builds once
  `libsdl2-dev` and `libsdl2-mixer-dev` are installed with `apt-get`
  (not in the container by default, and lost with it).
- The oracle of the logic runs, and is deterministic (2026-11-17): from
  `-new 300:0:0:12345`, five turns by `n` on the standard input, two runs
  write the same saves byte by byte (`1oom_save_2300.bin` to `2304`,
  and slots 7 to 9), and `1oom_saveconv -o t` turns them into text.
- Before writing Atmos: the rules of `pin` changed twice (2026-11-15
  and 2026-11-17, `main` of `ia-atmos/lang`; told by the compiler
  session). As of 2026-11-17: `val` and `var` may hold a fresh value
  again, with a ceiling (the block of its outermost name), and may only
  be adopted there or outside; `pin` stays the explicit owner,
  recommended for natives, tasks, and pools; a `pin` variable, a field
  of a pinned table, and the `pub` of a pinned task may be assigned a
  fresh value, the old one finalized when its last reference goes.
  Read the manual ("Pin") and `.claude/plans/261115-pin.md` there. The
  initial instructions are outdated on this point.

- The port, in the order of item 5:
  1. The save: **done** (2026-11-17). `tst/save.sh` on 109 saves of 5
     games (2 to 6 players, all galaxy sizes, up to 27 turns, with
     nebulas, fleets, and transports): each is written back byte by byte,
     and its values are the same as the C, field by field (the text of
     `1oom_saveconv -o t`). Not covered yet: the slot names and paths of
     the saves (`game_save_get_slot_fname`, which needs `os`).
  2. The data tables of the 5 LBX of the logic: next.
- Headers ported only in part: `game_shiptech.h` (the enums; its tables
  come with `game_shiptech.c`) and `game_shipdesign.h` (its tables come
  with `game_shipdesign.c`).
- `log.atm` writes the errors to the standard output (Atmos has no
  standard error), and holds `hw_log_*` until the hardware of pico.
- Three commits of 2026-11-17 (`0d492fe`, `90e0bd7`, `7c8e0d7`) have the
  trailer in the title line (a missing blank line). History is not
  rewritten.

## C. Reported or decided, and not acknowledged

- 2026-11-17: step 1 (the save) done, and how the C becomes Atmos (in
  `README.md`): the state is a tree of tables with every field of C,
  each value kept as C keeps it (`i16`, `u8`, ...), `bool` as booleans,
  `char[]` as vectors of bytes, `if (x)` as `if x != 0`.

## Settled

- 1 (2026-11-14): the port goes on. The license stays the GPL-2: the
  port is a derivative work of 1oom, whose sources are GPL version 2
  with no "or later", so no more permissive license is possible. The
  readme has the notice at its top. Nothing goes back to the original.
- 2 (2026-11-17): the author sent the LBX files. The 33 of
  `c/doc/lbxmd5.txt` match (two more, `reqd.lbx` and `snddrv.lbx`, are
  not used by 1oom). They are in `/home/user/moo-data`, outside the
  repository; the container is ephemeral, so a new one needs them again
  (the zip the author uploaded).
- 2026-11-17, asked by the author: the original C moved to `c/`, the
  same tree as `42e9c0b` (its readme as `c/README.md`). The root keeps
  the notice in `README.md`, `COPYING`, a `.gitignore` for the LBX
  files, and `.claude/`. The oracle rebuilt from `c/` writes the same
  saves as before.
- 4 (2026-11-17): everything is ported to Atmos, the state included:
  `struct game_s` becomes Atmos tables, and the save is rewritten. So
  the port cannot keep the rest in C module by module through the
  state; how to go in steps is part of item 5.
- 6 (2026-11-17), as recommended: for fidelity, the same buffer of
  320x200 with a palette, shown on pico as one image per frame, so the
  checksum of the screen per frame is the oracle. Later, the drawing
  redone with the operations of pico (LBX converted once, on the
  machine of the player, to PNG, WAV/OGG, and tables). The data tables
  of the LBX of the logic are decoded into Atmos tables from the start.
- 5 (2026-11-17), as recommended: From the bottom, checked by the save at each step. (a) The save: Atmos reads a save written by the C into its tables and writes it back, byte by byte. (b) The data tables of the 5 LBX of the logic. (c) A new game from a seed: the save of turn 0 equal to the C. (d) The turn, one phase at a time (`game_turn_process` calls about 60 functions): a small test driver in C (not part of the port) loads a save, runs one phase, and saves; the Atmos does the same; the saves must be equal. (e) The AI. (f) The textual interface, the game played whole with no screen. (g) The interface of 1993 over pico
- 7 (2026-11-17), as recommended: the logic, the textual interface,
  and the interface of 1993 are ported. The tools (`lbxview`,
  `lbxedit`, `pbxmake`, `saveconv`, ...) stay only in `c/`, as help to
  the oracle; the three hardware backends are replaced by pico.
- 3 (2026-11-14): the version to port is `master` (`42e9c0b`).
