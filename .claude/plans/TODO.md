# TODO

Everything that is pending in the session of the port of 1oom (Master
of Orion) to Atmos: asked and not decided, reported and not
acknowledged, or known and not done. Keep it current.

Items are `#N` (standing rule of the author, 2026-11-18): everything put
to him has a number, unique in this session, taken in order, never
reused and never changed. Bare numbers enumerate nothing else. An item
of another session is `session#N` (`atmos-lang#22`). The decisions
settled before the rule keep their old numbers (1 to 7, see "Settled").

The initial instructions are in `ia-atmos/lang`,
`.claude/plans/261114-pico-1oom.md` (commit `354cf19`).

Last update: 2026-11-20

## Index

| # | Item | Kind | State |
|---|------|------|-------|
| #1 | Step 2 of the port: the data tables of the 5 LBX of the logic | work | waiting for the author's go |
| #2 | Three commits with the trailer in the title line | remark | open: history not rewritten unless he asks |
| #3 | The slot names and paths of the saves (`game_save_get_slot_fname`) | work | open, needs `os` |
| #4 | Headers ported in part (`game_shiptech.h`, `game_shipdesign.h`) | work | open, with their `.c` |
| #5 | `log.atm` writes errors to the standard output, and holds `hw_log_*` | remark | open, until the hardware of pico |
| #6 | Step 1 done, and how the C becomes Atmos | report | reported 2026-11-17; he asked about the structure 2026-11-18 |

## A. Decisions waiting for an answer

Each has the option recommended by this session. Asked one at a time.

- #1 Step 2, the data tables of the 5 LBX of the logic (`research`,
  `firing`, `diplomat`, `eventmsg`, `names`): recommended, go.
- #2 Three commits of 2026-11-17 (`0d492fe`, `90e0bd7`, `7c8e0d7`) have
  the trailer in the title line (a missing blank line). Recommended:
  leave them; rewriting needs a forced push to `master`.

## B. Work known and not done

The port goes in the order of decision 5 (see "Settled"):

- Step 1, the save: **done** (2026-11-17). `tst/save.sh` on 109 saves of
  5 games (2 to 6 players, all galaxy sizes, up to 27 turns, with
  nebulas, fleets, and transports): each is written back byte by byte,
  and its values are the same as the C, field by field (the text of
  `1oom_saveconv -o t`).
- #1 Step 2: next.
- #3 The slot names and paths of the saves (`game_save_get_slot_fname`),
  which need `os`.
- #4 Headers ported in part: `game_shiptech.h` (the enums; its tables
  come with `game_shiptech.c`) and `game_shipdesign.h` (its tables come
  with `game_shipdesign.c`).
- #5 `log.atm` writes the errors to the standard output (Atmos has no
  standard error), and holds `hw_log_*` until the hardware of pico.

The environment, to rebuild in a new container:

- The oracle of the logic, in `c/build-native/` (ignored by git), from
  `c/`: `autoreconf -fi`, then `../configure --disable-uiclassic
  --disable-hwsdl2 --disable-hwsdl1 --disable-hwalleg4
  --without-readline --without-samplerate`, then `make`. It gives
  `1oom_cmdline` (hardware `nop`) and the tools, with `1oom_saveconv`.
  It is deterministic: the same seed and commands give the same saves.
- The oracle of the interface of 1993 (`1oom_classic_sdl2`) builds once
  `libsdl2-dev` and `libsdl2-mixer-dev` are installed with `apt-get`.
- The LBX files: not in the repository; a new container needs the zip
  the author uploaded, unpacked outside the repository (they were in
  `/home/user/moo-data`).
- The compiler: `ia-atmos/lang`, `main`, built with `make`. Last checked
  at `8c9453c` (2026-11-18): `tst/save.sh` passes on the 109 saves.

## C. Reported or decided, and not acknowledged

- #6 2026-11-17: step 1 (the save) done, and how the C becomes Atmos (in
  `README.md`): the state is a tree of tables with every field of C,
  each value kept as C keeps it (`i16`, `u8`, ...), `bool` as booleans,
  `char[]` as vectors of bytes, `if (x)` as `if x != 0`. On 2026-11-18
  the author asked how the structure looked; answered with the C and
  the Atmos side by side.

## Settled

Before the rule of `#N`, with their old numbers:

- 1 (2026-11-14): the port goes on. The license stays the GPL-2: the
  port is a derivative work of 1oom, whose sources are GPL version 2
  with no "or later", so no more permissive license is possible. The
  readme has the notice at its top. Nothing goes back to the original.
- 2 (2026-11-17): the author sent the LBX files. The 33 of
  `c/doc/lbxmd5.txt` match (two more, `reqd.lbx` and `snddrv.lbx`, are
  not used by 1oom).
- 3 (2026-11-14): the version to port is `master` (`42e9c0b`).
- 4 (2026-11-17): everything is ported to Atmos, the state included:
  `struct game_s` becomes Atmos tables, and the save is rewritten.
- 5 (2026-11-17), as recommended: from the bottom, checked by the save at
  each step. (a) The save. (b) The data tables of the 5 LBX of the
  logic. (c) A new game from a seed: the save of turn 0 equal to the C.
  (d) The turn, one phase at a time (`game_turn_process` calls about 60
  functions): a small test driver in C (not part of the port) loads a
  save, runs one phase, and saves; the Atmos does the same; the saves
  must be equal. (e) The AI. (f) The textual interface, the game played
  whole with no screen. (g) The interface of 1993 over pico.
- 6 (2026-11-17), as recommended: for fidelity, the same buffer of
  320x200 with a palette, shown on pico as one image per frame, so the
  checksum of the screen per frame is the oracle. Later, the drawing
  redone with the operations of pico. The data tables of the LBX of the
  logic are decoded into Atmos tables from the start.
- 7 (2026-11-17), as recommended: the logic, the textual interface, and
  the interface of 1993 are ported. The tools stay only in `c/`, as help
  to the oracle; the three hardware backends are replaced by pico.
- 2026-11-17, asked by the author: the original C moved to `c/`, the
  same tree as `42e9c0b`. The root keeps the notice in `README.md`,
  `COPYING`, a `.gitignore` for the LBX files, and `.claude/`.

Other sessions:

- Findings about `pin` go to `atmos-pin`
  (session_011eECogSDhkVfyt7qme5DLh), with a small program; everything
  else of the compiler to `atmos-lang` (session_011eECogKVQ7ZzmWCoMST2wK).
- `t@0.x` is lexed as the invalid number `0.x` (write `t@(0).x`). Now in
  the manual's table of ambiguities; the change of the lexer is item 65
  of the compiler, waiting for the author.
- The rules of `pin` changed three times (2026-11-15, twice on
  2026-11-17), then were declared stable (`1746969`). The port was
  migrated once: five `pin` given away by their block became `val`.
  Later changes (`7480111`, `8c9453c`) needed nothing.
- 2026-11-19: the author declared the rules of `pin` stable
  (atmos-pin#9), as in `ia-atmos/lang` `8361f88` (manual: "Lexical Memory
  Management", "Pin", "Set"; summary in `.claude/plans/TODO-pin.md`,
  "Stable (2026-11-19)"). The port passed its tests with that compiler
  before the merge (atmos-lang#81): nothing to migrate.
- 2026-11-20: the compiler (`692af43`) has numeric build options, off by
  default. The port needs the default: `ATMOS_INT=32` would break
  `ctypes.atm` (`u32`, `i32` need integers wider than 32 bits), and
  `ATMOS_REAL=float` is not wanted where C uses `double`.
