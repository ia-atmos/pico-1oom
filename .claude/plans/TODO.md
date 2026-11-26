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

Last update: 2026-11-25

## Index

| # | Item | Kind | State |
|---|------|------|-------|
| #1 | Step 2 of the port: the data tables of the 5 LBX of the logic | work | done 2026-11-20, by the session, to be confirmed |
| #2 | Three commits with the trailer in the title line | remark | open: history not rewritten unless he asks |
| #3 | The slot names and paths of the saves (`game_save_get_slot_fname`) | work | done 2026-11-20 |
| #4 | Headers ported in part (`game_shiptech.h`, `game_shipdesign.h`) | work | done 2026-11-20, with their `.c` |
| #5 | `log.atm` writes errors to the standard output, and holds `hw_log_*` | remark | open, until the hardware of pico |
| #6 | Step 1 done, and how the C becomes Atmos | report | reported 2026-11-17; he asked about the structure 2026-11-18 |
| #7 | Work with no input (atmos-lang#95): #1, #3, #4 done without his answer | report | reported 2026-11-20 |
| #8 | Step 3 of the port: a new game from a seed | work | done 2026-11-22 |
| #9 | Step 4 of the port: the turn, one phase at a time | work | done 2026-11-25, with step (e), the AI |
| #10 | The C compiler takes ~50 s to build a test program of the port (the generated C of the tables) | remark | open, not a blocker |
| #11 | `game_turn_transport` reads `eto[PLAYER_NONE]` (past the table) in C; the port throws there | remark | open |
| #12 | The enums of C are unsigned (gcc): a negative `int` with an enum is unsigned arithmetic | remark | open: a check to keep doing |
| #14 | Step 5 of the port, (f): the textual interface (`ui/cmdline`), with `main.c`, `game.c`, the options | work | in course |
| #13 | The battle AI reads `bt->item[-1]` in C; the port gives the same bytes | remark | open, by the session, to be confirmed |

## A. Decisions waiting for an answer

Each has the option recommended by this session. Asked one at a time.

- #2 Three commits of 2026-11-17 (`0d492fe`, `90e0bd7`, `7c8e0d7`) have
  the trailer in the title line (a missing blank line). Recommended:
  leave them; rewriting needs a forced push to `master` (and the rule of
  work with no input forbids rewriting history).

## B. Work known and not done

The port goes in the order of decision 5 (see "Settled"). The checks are
in `tst/` (`tst/all.sh DATADIR SAVE...` runs them all).

- Step 1, the save: **done** (2026-11-17). `tst/save.sh`: 109 saves of 5
  games, byte by byte and field by field against the C. The slots and
  paths of the saves (#3): **done** (2026-11-20), `tst/save-slots.atm`.
- Step 2 (#1), the data tables of the LBX of the logic: **done**
  (2026-11-20, by the session, to be confirmed). `lbx.c` (`tst/lbx.sh`:
  every item of the 33 files), `game_aux.c` (`tst/game_aux.sh`: the
  tables of `research`, `diplomat`, `eventmsg`, `firing`, and the
  distances of the stars of 5 saves), with `util_math.c`
  (`tst/util_math.sh`: 3000 random points) and `os/unix/os.c`.
  `names.lbx` is read by `lbx.atm`; the code that uses it is in
  `game_new.c`, step 3.
- #4 **done** (2026-11-20): `game_shiptech.c` (its tables, converted by
  `tools/game_shiptech.py`; `tst/game_shiptech.sh`: 2231 fields),
  `game_techtypes.h`, `game_shipdesign.c` (`tst/game_shipdesign.sh`),
  and `game_str.c` (converted by `tools/game_str.py`; `tst/game_str.sh`:
  1177 strings).
- #8 Step 3, a new game from a seed: **done** (2026-11-22).
  `game_new.c`, with `rnd.c`, `comp.h`, `game_num.c` (converted by
  `tools/game_num.py`), `lib_strcpy`, `util_trim_whitespace`, and the two
  functions of the classic AI for a new game. `tst/game_new.sh`: 336 new
  games (2 to 6 players, all sizes and difficulties, fixed and random
  races and banners, one or more humans, both galaxy generators, with
  and without nebulas, 6 seeds), each saved byte by byte as the C. The C
  driver (`tst/c/game_new.c`) gives the same save as the init save of
  `1oom_cmdline`. Not ported: `game_generate_load` (it throws), which is
  only called when `game_num_update_on_load` is false (it is true).
- #9 Step 4, the turn: **done** (2026-11-25). Done (2026-11-22): `game_tech.c` and
  `game_misc.c` (all of them), with two functions of `game_planet.c` and
  `lib_sprintf`. Done (2026-11-23): the logic of `game_planet.c`; all of
  `game_fleet.c`, `game_stat.c`, `game_design.c`, `game_diplo.c`,
  `game_spy.c`, `game_bomb.c`, `game_ground.c`, `game_news.c`,
  `game_election.c`, `game_event.c`, `game_audience.c`, `game_end.h`, the
  ship names (`game_str_shipnames.c`), `strbuild` and `lib_strcat`; and
  every phase of `game_turn.c`. Done (2026-11-25): `game_turn_process`,
  `game_parsed.c`, `game_battle.c`, `game_battle_human.c`,
  and all of `game_ai_classic.c` (step (e) of decision 5, done with the
  turn: new game, techs, bombs, ground combat, votes, events, diplomacy,
  audiences, the battle AI, and the turn p1/p2/p3). `src/ui.atm` holds the
  functions of `ui.h` that the logic calls: each is a `var` that an
  interface sets; unset, it throws (by the session, reversible).
  Checked by `tst/state.sh`: on the 109 saves, 22 groups of operations
  (2398 runs; the earlier sixteen, plus battles, the AI diplomacy twice,
  the AI designs/sliders/spies by year, eight turns of the AI fleets, and
  ten whole turns of `game_turn_process`),
  the whole state and what the operations print compared with the C after
  each. The C driver includes `game_turn.c` to reach its static phases.
  Both drivers have an interface that prints each call and answers by
  fixed rules; no function of the AI is replaced any more. Where C reads
  memory that was never set (the stack of an earlier call, a pointer to a
  stack that is gone), the checks leave that value out of what they print.
  `game_ai.atm` no longer includes `game_ai_classic.atm` (an include cycle
  left a table undeclared): the main program includes it, and at its end
  it sets `game_ai` and `game_ais` (by the session, reversible).
  Found on the way: in `tbl_shiptech_weap` the weapon "none" had
  `is_bio = 0`, which is true in Atmos; `tools/game_shiptech.py` now
  writes a C bool as `false`/`true`. Next: step (f), the textual
  interface (`c/src/ui/cmdline`).
- #14 Step (f), the textual interface, in course (approved: decision 7).
  The oracle: `1oom_cmdline` (hardware `nop`) fed from the standard input
  is deterministic (with a fixed time of day, `tst/c/fixtime.c`, for the
  random seeds); its output, exit code and every file it writes are
  compared (`tst/cmdline.sh`: 41 sessions). Done: (1) the logic it needs
  (`game_turn_start.c`, `game_cheat.c`, 2026-11-26, group 23 of
  `tst/state.sh`); (2) the input, the turn loop and `main_do`; (3) every
  screen of `ui/cmdline`; (4) `options.c`, `cfg.c` (the config file),
  `main.c`, the PBX files (`pbx.c`, `game_strp.c`, `game_nump.c`, with
  `-dumpstr`/`-dumpnum`; tables generated by `tools/game_strp.py` and
  `tools/game_nump.py`), all 2026-11-26. In course: the saves of MOO 1.3
  (`game_save_moo13.c`, generated by `tools/game_save_moo13.py`;
  `tst/moo13.sh` makes each save of the C into a `SAVE1.GAM` with
  `1oom_saveconv`, in a temporary directory, and compares the loaded
  state). In C `st_shld_absorb` is U16 over a `uint8_t` field: the port
  reads and writes the next byte (`tech_i`) as C does. At each big step,
  screenshots for the author (his request, 2026-11-26): `tst/shots/shot.sh`
  opens a save of the port in the interface of 1993 (the C) on a virtual
  display.
- #13 With no target (`target_i == -1`), `game_battle_ai_best_range` and
  `get_possible_distance_increase` read `bt->item[-1]` (undefined
  behaviour, before the table). On x86-64 these are the bytes of `bt->s[0]`
  and `bt->s[1]`; `bt_item` in `game_ai_classic.atm` builds that item from
  them, so the result is the C's (the checks met it on 5 of 8 saves). By
  the session, to be confirmed; a bug to report to the original project
  is not reported (nothing goes upstream).
- #11 In `game_turn_transport`, when the owner of the transports has
  combat transporters and the planet has no owner, C reads
  `g->eto[p->owner].have_sub_space_int` with `p->owner == PLAYER_NONE`,
  past the end of `eto` (undefined behavior: it reads the bytes of
  `srd[0]`). The port throws there instead of guessing. Not met in the
  checks yet. To decide when it is met (it may be a bug to report to the
  original project, which is not done: nothing goes upstream).
- #12 gcc gives an enum with no negative value the type `unsigned int`
  (`player_id_t`, `difficulty_t`, `treaty_t`, ...). An `int` that may be
  negative, divided by or compared with such a field, is converted to
  unsigned. Met twice: `game_diplo_act` (`dv /= (g->difficulty / 2 + 1)`
  with `dv < 0` gives a huge positive `dv`: relations go to 65 instead of
  down), and `-1` kept in a `player_id_t` (`sabotage_spy`), which reads
  back as `0xffffffff`. Both reproduced in the port (`u32`, `i32`). To
  look for in every module still to port (the AI above all).
- #10 A test program of the port takes ~50 s for the C compiler (the
  generated C of the tables of strings and ships); it then runs in
  0.1 s. Not a blocker; to tell `atmos-lang` if it grows.
- #5 `log.atm` writes the errors to the standard output (Atmos has no
  standard error), and holds `hw_log_*` until the hardware of pico.
- Reading a file is slow (`cfile_read` takes byte by byte with
  `string.byte`): `tst/lbx.sh` takes 30 s. Not a problem yet.
- The pointers of C into the LBX data that the logic only reads are
  copies here (`game_aux.atm`, see its top). A pointer that is written
  through will need a buffer and a position, as `lbx.atm` does.

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

- #7 2026-11-20: by the rule of work with no input (atmos-lang#95,
  relayed by `atmos-lang` from the author's words; read in
  `ia-atmos/lang` `.claude/plans/TODO.md`), #1 (step 2), #3, and #4 were
  done without his answer, each checked against the C. #1 is marked "by
  the session, to be confirmed": it can be undone by reverting its
  commits.

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

- Since 2026-11-24 (atmos-lang#119, approved by the author; handoff in
  `ia-atmos/lang` `.claude/plans/261124-atmos.md`): coordination, status
  and questions for the author go to `atmos`
  (session_011eECohhJbc4GMpAj3yyeEo); measurements of the ports and the
  merges into `main` stay with `atmos-lang`. Item numbers stay local to
  this session (`#N` here, `pico-1oom#N` outside), as confirmed by the
  author on 2026-11-25 (only `atmos` and `atmos-lang` share `ISSUES.md`).
  The pause until next week's credits ended on 2026-11-25 (relayed by
  `atmos`): approved work and the rule of work with no input resume.
- Findings about `pin` go to `atmos-pin`
  (session_011eECogSDhkVfyt7qme5DLh), with a small program; everything
  else of the compiler to `atmos-lang` (session_011eECogKVQ7ZzmWCoMST2wK).
- `t@0.x` was lexed as the invalid number `0.x`. Since `ia-atmos/lang`
  `61979ce` (2026-11-20) a dot belongs to a number only before a digit,
  so `t@0.x` is the field `x` of `t@0`. The port still writes `t@(0).x`,
  which stays valid.
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
  default. (renamed in `d19d40f`: `ATMOS_FLOAT`, `ATMOS_INTEGER`, `ATMOS_CLOCK`). The port needs the default: `ATMOS_INTEGER=32` would break
  `ctypes.atm` (`u32`, `i32` need integers wider than 32 bits), and
  `ATMOS_FLOAT=32` is not wanted where C uses `double`.
