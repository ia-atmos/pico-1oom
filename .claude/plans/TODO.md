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
| 1 | The original project forbids code made by AI ("Direct use of AI-generated code is prohibited in 1oom", in its readme). Whether to go on in view of that rule | Go on, as another work in this fork, under the GPL-2, which allows it. Nothing made here goes back to the original project (no pull request, no issue, no patch), and the readme of this repository says at its top that it is a port to Atmos made with AI, not affiliated with 1oom |
| 2 | The game needs the LBX files of Master of Orion v1.3, from an original copy (checksums in `doc/lbxmd5.txt`). They cannot be fetched and must never be committed. Nothing can be run or compared until the author provides them | The author provides them to the session, outside the repository, in a directory that `.gitignore` also covers; they are checked against `doc/lbxmd5.txt` |
| 3 | Which version to port. The fork has only `master` (`42e9c0b`), whose readme says this version is no longer developed and points to a branch `vanilla` that the fork does not have | The `master` that is here: it is what the instructions measured, and it has the textual interface and `saveconv`, which make fidelity checkable. To confirm after a look at `vanilla` of the original, if the author wants it brought to the fork |

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

- The notice at the top of `README.md` (item 1), once he confirms.
- Build the original C with the hardware `nop` and the textual
  interface, as the oracle (needs item 2 to run).

## C. Reported or decided, and not acknowledged

- Nothing yet.
