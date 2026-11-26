# Converts c/src/game/game_save_moo13.c into Atmos (src/game/game_save_moo13.atm).
# Each value read from the save is converted to the C type of the field it
# goes to: the types come from the C itself, by compiling the functions
# with the macros M13_* redefined to print the size and the signedness of
# their destination (run with the maximum counts, so that every loop runs).
# usage: python3 tools/game_save_moo13.py c src/game/game_save_moo13.atm
#   (c: the directory of the C, with build-native built)
import re, subprocess, sys, tempfile, os
cdir = sys.argv[1]
src = open(cdir + '/src/game/game_save_moo13.c').read()
src_nc = re.sub(r'/\*.*?\*/', '', src, flags=re.S)
a = src_nc.index('static int savetype_de_moo13_sd')
funcs = src_nc[a:]

# 1. The types of the destinations, from the C.
probe = r'''
#include "config.h"
#include <stdio.h>
#include <string.h>
#include "bits.h"
#include "comp.h"
#include "game.h"
#include "types.h"
#include "util.h"
static uint8_t savebuf_[65536];
static uint8_t *savebuf = NULL;
static uint32_t savelen = 0;
#define TI(x) printf("%s|%zu|%d|%d\n", #x, sizeof(x), (int)((__typeof__(x))-1 < 0), _Generic((x), _Bool: 1, default: 0))
#define TT(x) printf("%s|%zu|%d|%d|%zu\n", #x, sizeof((x)[0]), (int)((__typeof__((x)[0]))-1 < 0), _Generic(((x)[0]), _Bool: 1, default: 0), sizeof(x) / sizeof((x)[0]))
#define M13_GET_8(item_, addr_)     TI(item_)
#define M13_GET_16(item_, addr_)    TI(item_)
#define M13_GET_32(item_, addr_)    TI(item_)
#define M13_GET_16_OWNER(item_, addr_) TI(item_)
#define M13_GET_16_KILLER(item_, addr_) TI(item_)
#define M13_GET_16_CHECK(item_, addr_, l_, h_) do { TI(item_); item_ = h_; } while (0)
#define M13_GET_TBL_16(item_, addr_) TT(item_)
#define M13_GET_TBL_16_OWNER(item_, addr_) TT(item_)
#define M13_GET_TBL_16_HATED(item_, addr_) TT(item_)
#define M13_GET_TBL_BVN_8(item_, addr_, n_) (void)0
#define M13_GET_TBL_BV_16(item_, addr_) (void)0
#define M13_GET_TBL_BVN_16(item_, addr_, n_) (void)0
#define M13_GET_TBL_32(item_, addr_) TT(item_)
#define util_file_load(f_, l_) (*(l_) = SAVE_MOO13_LEN, savebuf_)
#define lib_free(x_) (void)0
#define log_error(...) (void)0
#define SAVE_MOO13_LEN  59036
''' + funcs.replace('static int savetype_de_moo13_sd', 'int savetype_de_moo13_sd') + r'''
int main(void) { static struct game_s g; game_save_de_moo13(&g, "x"); return 0; }
'''
tmp = tempfile.mkdtemp()
open(tmp + '/p.c', 'w').write(probe)
b = cdir + '/build-native/src'
subprocess.check_call(['cc', '-w', '-I' + b, '-I' + cdir + '/src', '-I' + cdir + '/src/game', '-o', tmp + '/p', tmp + '/p.c'])
types = {}
for line in subprocess.check_output([tmp + '/p']).decode().splitlines():
    f = line.split('|')
    types[f[0]] = f[1:]

def conv(cexpr):
    t = types[cexpr]
    size, signed, isbool = int(t[0]), t[1] == '1', t[2] == '1'
    if isbool:
        return 'm13_bool'
    return ('i' if signed else 'u') + str(size * 8)

def tbllen(cexpr):
    return types[cexpr][3]

# 2. The expressions of C in Atmos.
def ex(c):
    c = c.strip()
    c = c.replace('->', '.')
    c = re.sub(r'\[', '@(', c)
    c = c.replace(']', ')')
    c = re.sub(r'&\((\w[\w.@()]*)\)', r'\1', c)
    c = re.sub(r'^&', '', c)
    c = c.replace('!g.end', '(g.end == 0)')
    c = c.replace('~1', '(~1)')
    return c

def args(s):
    out, depth, cur = [], 0, ''
    for ch in s:
        if ch in '([':
            depth += 1
        elif ch in ')]':
            depth -= 1
        if ch == ',' and depth == 0:
            out.append(cur.strip()); cur = ''
        else:
            cur += ch
    out.append(cur.strip())
    return out

out = []
ind = 0
def emit(s):
    out.append('    ' * ind + s)

for raw in funcs.splitlines():
    line = raw.strip()
    if not line:
        continue
    m = re.match(r'(static )?int (savetype_de_moo13_sd|game_save_de_moo13)\((.*)\)$', line)
    if m:
        names = [x.split()[-1].lstrip('*') for x in m.group(3).split(',')]
        emit('func %s (%s) {' % (m.group(2), ', '.join(names)))
        continue
    if line == '{':
        if ind == 0:
            ind = 1
        else:
            emit('do {'); ind += 1
        continue
    if line == '}':
        ind -= 1; emit('}')
        if ind == 0:
            out.append('')
        continue
    m = re.match(r'(M13_\w+)\((.*)\);$', line)
    if m:
        mac, a = m.group(1), args(m.group(2))
        d = ex(a[0]); ad = ex(a[1])
        if mac == 'M13_GET_8':
            emit('set %s = %s(savebuf@(%s))' % (d, conv(a[0]), ad))
        elif mac == 'M13_GET_16':
            emit('set %s = %s(GET_LE_16(savebuf, %s))' % (d, conv(a[0]), ad))
        elif mac == 'M13_GET_32':
            emit('set %s = %s(GET_LE_32(savebuf, %s))' % (d, conv(a[0]), ad))
        elif mac == 'M13_GET_16_OWNER':
            emit('set %s = %s(m13_owner(GET_LE_16(savebuf, %s)))' % (d, conv(a[0]), ad))
        elif mac == 'M13_GET_16_KILLER':
            emit('set %s = %s(m13_killer(GET_LE_16(savebuf, %s)))' % (d, conv(a[0]), ad))
        elif mac == 'M13_GET_16_CHECK':
            emit('do {')
            emit('    val t_ = GET_LE_16(savebuf, %s)' % ad)
            emit('    if (t_ < %s) || (t_ > %s) {' % (ex(a[2]), ex(a[3])))
            emit('        log_error("%s at 0x%%04x is %%i and not in range %%i..%%i\\n", %s, t_, %s, %s)' % (a[0], ad, ex(a[2]), ex(a[3])))
            emit('        return -1')
            emit('    }')
            emit('    set %s = %s(t_)' % (d, conv(a[0])))
            emit('}')
        elif mac in ('M13_GET_TBL_16', 'M13_GET_TBL_16_OWNER', 'M13_GET_TBL_16_HATED', 'M13_GET_TBL_32'):
            g = {'M13_GET_TBL_16': 'GET_LE_16(savebuf, (%s) + (i_ * 2))',
                 'M13_GET_TBL_16_OWNER': 'm13_owner(GET_LE_16(savebuf, (%s) + (i_ * 2)))',
                 'M13_GET_TBL_16_HATED': 'm13_hated(GET_LE_16(savebuf, (%s) + (i_ * 2)))',
                 'M13_GET_TBL_32': 'GET_LE_32(savebuf, (%s) + (i_ * 4))'}[mac] % ad
            emit('loop i_ in %s {' % tbllen(a[0]))
            emit('    set %s@(i_) = %s(%s)' % (d, conv(a[0]), g))
            emit('}')
        elif mac == 'M13_GET_TBL_BVN_8':
            emit('loop i_ in %s {' % ex(a[2]))
            emit('    if savebuf@((%s) + i_) != 0 {' % ad)
            emit('        BOOLVEC_SET1(%s, i_)' % d)
            emit('    }')
            emit('}')
        elif mac in ('M13_GET_TBL_BV_16', 'M13_GET_TBL_BVN_16'):
            n = 'PLAYER_NUM' if mac == 'M13_GET_TBL_BV_16' else ex(a[2])
            emit('loop i_ in %s {' % n)
            emit('    if GET_LE_16(savebuf, (%s) + (i_ * 2)) != 0 {' % ad)
            emit('        BOOLVEC_SET1(%s, i_)' % d)
            emit('    }')
            emit('}')
        else:
            raise SystemExit('macro ' + mac)
        continue
    m = re.match(r'memcpy\((.*)\);$', line)
    if m:
        a = args(m.group(1))
        src_ = re.match(r'&savebuf\[(.*)\]$', a[1]).group(1)
        emit('m13_memcpy(%s, %s, %s)' % (ex(a[0]), ex(src_), ex(a[2])))
        continue
    m = re.match(r'for \(int (\w+) = (\w+); \1 < ([^;]+); \+\+\1\) \{$', line)
    if m:
        v, lo, hi = m.group(1), m.group(2), ex(m.group(3))
        if lo == '0' or lo == 'PLAYER_0':
            emit('loop %s in %s {' % (v, hi))
        else:
            emit('loop %s in (%s, (%s) - 1) {' % (v, ex(lo), hi))
        ind += 1
        continue
    m = re.match(r'if \((.*)\) \{$', line)
    if m:
        cnd = ex(m.group(1))
        cnd = re.sub(r'^savebuf$', 'savebuf != nil', cnd)
        # a number as a condition of C: 0 is false (and true in Atmos)
        cnd = re.sub(r'^(v & \(1 << \(i & 7\)\))$', r'(\1) != 0', cnd)
        emit('if %s {' % cnd); ind += 1
        continue
    m = re.match(r'(\w+_t|struct \w+|void|uint8_t|int) \*?(\w+)( = (.*))?;$', line)
    if m:
        t, v, init = m.group(1), m.group(2), m.group(4)
        if init is None:
            emit('var %s = 0' % v)
        else:
            emit('var %s = %s' % (v, ex(init)))
        continue
    m = re.match(r'int (\w+), (\w+);$', line)
    if m:
        emit('var %s = 0' % m.group(1)); emit('var %s = 0' % m.group(2))
        continue
    m = re.match(r'(const int) (\w+) = (.*);$', line)
    if m:
        emit('val %s = %s' % (m.group(2), ex(m.group(3))))
        continue
    m = re.match(r'\+\+(\w+);$', line)
    if m:
        emit('set %s = %s + 1' % (m.group(1), m.group(1)))
        continue
    if line == 'lib_free(savebuf);':
        continue
    if line == 'memset(g, 0, sizeof(*g));':
        emit('memset(g, 0, sizeof(*g))')
        continue
    m = re.match(r'(log_error|BOOLVEC_SET1)\((.*)\);$', line)
    if m:
        a = args(m.group(2))
        if m.group(1) == 'log_error':
            emit('%s(%s)' % (m.group(1), ', '.join([a[0]] + [ex(x) for x in a[1:]])))
        else:
            emit('%s(%s)' % (m.group(1), ', '.join([ex(x) for x in a])))
        continue
    m = re.match(r'return (.*);$', line)
    if m:
        emit('return %s' % ex(m.group(1)))
        continue
    m = re.match(r'(.*) = (.*);$', line)
    if m:
        emit('set %s = %s' % (ex(m.group(1)), ex(m.group(2))))
        continue
    raise SystemExit('line: ' + line)

head = ''';; Port of c/src/game/game_save_moo13.c: loads a save of MOO1 v1.3
;; (SAVEn.GAM). Generated from the C by tools/game_save_moo13.py: each value
;; is converted to the C type of its field. The file is read whole
;; (`util_file_load` of C); `savebuf` is a vector of bytes.

include "../bits.atm"
include "../boolvec.atm"
include "../cfile.atm"
include "../ctypes.atm"
include "../log.atm"
include "game.atm"
include "game_types.atm"

val SAVE_MOO13_LEN = 59036

var savebuf = nil
var savelen = 0

func m13_owner (t) {
    if t == 0xffff => PLAYER_NONE => t
}

func m13_killer (t) {
    if t == 0 => PLAYER_NONE => (t - 1)
}

func m13_hated (t) {
    if t == 0 => PLAYER_NONE => t
}

func m13_bool (v) {
    v != 0
}

func m13_memcpy (dst, offs, n) {
    loop k in n {
        set dst@(k) = savebuf@(offs + k)
    }
}

;; `util_file_load(fname, &len)`: the bytes, and their number (0 if none).
func util_file_load (fname) {
    val bs = cfile_read(fname)
    if bs == nil => (nil, 0) => (bs, #bs)
}

;; `memset(g, 0, sizeof(*g))`: the game back to its zeros, but its gaux.
func m13_clear_game (g) {
    val ga = g.gaux
    loop k, v in game_s() {
        set g@(k) = v
    }
    set g.gaux = ga
}

'''
body = '\n'.join(out)
body = body.replace('set savebuf = util_file_load(fname, &savelen)', 'set savebuf, savelen = util_file_load(fname)')
body = body.replace('set savebuf = NULL', 'set savebuf = nil')
# the bytes of a BOOLVEC (uint8_t) written by C as a whole
body = body.replace('set g.is_ai@(0) = ((1 << g.players) - 1) & (~1)', 'set g.is_ai@(0) = u8(((1 << g.players) - 1) & (~1))')
body = body.replace('set g.refuse@(0) = ((g.end == 0)) ? 0 : 1', 'set g.refuse@(0) = u8(if g.end == 0 => 0 => 1)')
body = body.replace('''    do {
        var t = g.gaux
        memset(g, 0, sizeof(*g))
        set g.gaux = t
    }''', '    m13_clear_game(g)')
open(sys.argv[2], 'w').write(head + body.rstrip() + '\n')
