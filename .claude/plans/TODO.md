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

Last update: 2026-11-14.

## A. Decisions waiting for an answer

Each has the option recommended by this session. They are asked one at
a time.

| # | Decision | Recommended |
|---|----------|-------------|
| 2 | The LBX files of Master of Orion v1.3, from an original copy (checksums in `doc/lbxmd5.txt`). The author said "we will look for them" (2026-11-14). They are never committed (`*.lbx` is already in `.gitignore`). Nothing can be run or compared until they are in the session | The author provides them, outside the repository; they are checked against `doc/lbxmd5.txt` |

After these, the questions of the instructions that the port must
answer early, also the author's:

| # | Decision | Recommended |
|---|----------|-------------|
| 4 | Where the state lives: `struct game_s` stays in C, reached by accessors, or becomes Atmos tables, with the save rewritten | Not studied yet |
| 5 | The order of the port: from the top down (the turn and the flow of screens first, calling the C below), since C cannot call Atmos | Not studied yet |
| 6 | What goes over pico: the buffer of 320x200 shown as one image per frame, or the drawing redone with the operations of pico | Not studied yet |
| 7 | What is ported at all: the tools, the textual interface, and the three hardware backends are candidates to stay out; and which slice comes first | Not studied yet |

## B. Work known and not done

Nothing may start before the author says so.

- The oracle of the logic is built (2026-11-14), in `build-native/`
  (ignored by git): `autoreconf -fi`, then `../configure
  --disable-uiclassic --disable-hwsdl2 --disable-hwsdl1
  --disable-hwalleg4 --without-readline --without-samplerate`, then
  `make`. It gives `1oom_cmdline` (hardware `nop`) and the tools,
  with `1oom_saveconv`. Not run yet: it needs the LBX files (item 2).
- The oracle of the interface of 1993 (`1oom_classic_*`) is not
  built: it needs SDL 2 and its mixer, which the container does not
  have.
- With the LBX files: a first run from a fixed seed (`-new`), with
  commands on the standard input, and its save converted to text, to
  confirm that two runs give the same bytes.

## C. Reported or decided, and not acknowledged

- Nothing yet.

## Settled

- 1 (2026-11-14): the port goes on. The license stays the GPL-2: the
  port is a derivative work of 1oom, whose sources are GPL version 2
  with no "or later", so no more permissive license is possible. The
  readme has the notice at its top. Nothing goes back to the original.
- 3 (2026-11-14): the version to port is `master` (`42e9c0b`).
