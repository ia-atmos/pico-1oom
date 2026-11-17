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
