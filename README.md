> **This repository is not 1oom.** It is a port of 1oom to the
> [Atmos](https://github.com/ia-atmos/lang) language, **made with AI**, and it
> is **not affiliated with the 1oom project**. 1oom prohibits AI-generated
> code: nothing from this repository may be submitted to it (no pull request,
> no issue, no patch). The port is a derivative work of 1oom and is distributed
> under the same license, the GNU GPL version 2 (see [COPYING](COPYING)).

pico-1oom
=========

A port of [1oom](https://github.com/1oom-fork/1oom), a reproduction of the
DOS game Master of Orion (1993), to Atmos. First one to one, with
fidelity: the port follows the C as it is, with the same results.

- [`c/`](c/): the original C of 1oom, untouched, at the commit the port
  starts from (`42e9c0b`). It is the oracle of the port. Its readme is
  [`c/README.md`](c/README.md).
- [`src/`](src/): the port, with the same files as `c/src/` (`game_save.c`
  becomes `game_save.atm`), and a few of its own: `ctypes.atm` (the
  conversions that C does when it stores a value) and `cfile.atm` (whole
  files of bytes).
- [`tst/`](tst/): the checks against the C.

How the C becomes Atmos:

- The state of the game (`struct game_s`) is a tree of Atmos tables, made by
  `game_s()` in `src/game/game.atm`, with every field of C. A field keeps
  the value that C would have: `set p.pop = i16(v)` where `p->pop` is an
  `int16_t`. A `bool` is an Atmos boolean; an array of C is a vector from
  index 0; a `char[]` is a vector of bytes, as saved.
- A C test of an integer is written out: `if (x)` becomes `if x != 0`, since
  `0` is true in Atmos.

The game needs the LBX files of Master of Orion v1.3, from an original copy
that one must own (checksums in [`c/doc/lbxmd5.txt`](c/doc/lbxmd5.txt)).
They are not distributed here.

Building the oracle (the textual interface, with no screen):

    cd c
    autoreconf -fi
    mkdir build-native && cd build-native
    ../configure --disable-uiclassic --disable-hwsdl2 --disable-hwsdl1 \
        --disable-hwalleg4 --without-readline --without-samplerate
    make
    ./src/1oom_cmdline -data PATH_TO_LBX -new 300:0:0:12345

Checking the port against the C (needs the compiler of Atmos,
`ia-atmos/lang`, the C built as above, and saves written by the C):

    ATMOS=PATH_TO/atmos tst/all.sh PATH_TO_LBX SAVE...

Each check builds a small C program over the original sources (in
`tst/c/`, not part of the port) and compares its output with the same
program in Atmos. Some tables are converted from the C by the scripts in
`tools/`, which also write their checks.
