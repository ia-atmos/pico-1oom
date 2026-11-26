# Converts the tables of c/src/game/game_shiptech.c into Atmos, with the
# fields named as in the structures of game_shiptech.h, and writes the two
# dumps that check them.
# usage: python3 tools/hdr2atm.py c/src/game/game_shiptech.h > ENUMS.atm
#        python3 tools/game_shiptech.py c/src/game src/game/game_shiptech.atm \
#            tst/c/game_shiptech.c tst/game_shiptech.atm ENUMS.atm
import re, sys
d = sys.argv[1]
hdr = re.sub(r'/\*.*?\*/', '', open(d + '/game_shiptech.h').read(), flags=re.S)
src = re.sub(r'/\*.*?\*/', '', open(d + '/game_shiptech.c').read(), flags=re.S)

structs = {}
for name, body in re.findall(r'struct (shiptech_\w+_s) \{(.*?)\};', hdr, flags=re.S):
    fields = []
    for line in body.split(';'):
        line = line.strip()
        if not line:
            continue
        m = re.match(r'(.*?)(\w+)\s*(\[[^\]]*\])?$', line)
        ctype, fname, arr = m.group(1).strip(), m.group(2), m.group(3)
        fields.append((fname, ctype, arr))
    structs[name] = fields

def split_top(s):
    out, depth, cur = [], 0, ''
    for ch in s:
        if ch == '{':
            depth += 1
        elif ch == '}':
            depth -= 1
        if ch == ',' and depth == 0:
            out.append(cur.strip()); cur = ''
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out

def unbrace(s):
    s = s.strip()
    assert s[0] == '{' and s[-1] == '}', s
    return s[1:-1]

def value(v):
    v = v.strip()
    if v.startswith('{'):
        return '[' + ', '.join(value(x) for x in split_top(unbrace(v))) + ']'
    m = re.fullmatch(r'&(\w+)\[(\d+)\]', v)
    if m:
        return '\\{ %s@(%s) }' % m.groups()
    m = re.fullmatch(r'&(\w+)', v)
    if m:
        return '\\{ %s }' % m.group(1)
    return v

atm = [';; Port of c/src/game/game_shiptech.c and game_shiptech.h.',
       ';; The enums by tools/hdr2atm.py; the tables by tools/game_shiptech.py.',
       ';; A `char const * const *` (a pointer to a string of game_str, which a PBX',
       ';; file may replace) is a function that gives the string: `*p->nameptr` is',
       ';; `p.nameptr()`.', '',
       'include "../ctypes.atm"', 'include "game_str.atm"', 'include "game_techtypes.atm"', 'include "game_types.atm"', '']
enums = open(sys.argv[5]).read() if len(sys.argv) > 5 else ''
atm.append(enums)
atm += ['var strspace = " "', 'var strempty = ""', '']
cd = ['/* The oracle of tst/game_shiptech.atm: every field of the tables of',
      '   c/src/game/game_shiptech.c. Generated with it. Not part of the port. */',
      '#include <stdio.h>', '#include "game_shiptech.h"', '', 'int main(void)', '{']
ad = [';; game_shiptech.atm of the port: every field of its tables, as',
      ';; tst/c/game_shiptech.c prints them. Generated with it.', '',
      'include "../src/game/game_shiptech.atm"', '', 'pin out = []', '']
for sname, tname, size, init in re.findall(r'struct (shiptech_\w+_s) (\w+)\[(\w+)\] = \{(.*?)\n\};', src, flags=re.S):
    fields = structs[sname]
    entries = split_top(init)
    atm.append('pin %s = [' % tname)
    for e in entries:
        vals = split_top(unbrace(e))
        assert len(vals) <= len(fields), (tname, len(vals), len(fields))
        atm.append('    [')
        for k, (fname, ctype, arr) in enumerate(fields):
            if k < len(vals):
                v = value(vals[k])
            else:   # C zeroes the fields that the initializer leaves out
                v = ('carray(%s)' % arr[1:-1]) if arr else '0'
            if (ctype == 'bool') and (v in ('0', '1')):  # 0 is true in Atmos
                v = 'false' if v == '0' else 'true'
            atm.append('        %s = %s,    ;; %s%s' % (fname, v, ctype, ' ' + arr if arr else ''))
        atm.append('    ],')
    atm.append(']')
    atm.append('')
    cd.append('    for (int i = 0; i < %s; ++i) {' % size)
    ad.append('loop i in #%s {' % tname)
    ad.append('    val e = %s@(i)' % tname)
    for fname, ctype, arr in fields:
        if '* const *' in ctype:
            cd.append('        printf("%s[%%i].%s = %%s\\n", i, *%s[i].%s);' % (tname, fname, tname, fname))
            ad.append('    set out@+ = string.format("%s[%%i].%s = %%s\\n", i, e.%s())' % (tname, fname, fname))
        elif arr:
            n = arr[1:-1]
            cd.append('        printf("%s[%%i].%s =", i); for (int k = 0; k < %s; ++k) { printf(" %%i", %s[i].%s[k]); } printf("\\n");' % (tname, fname, n, tname, fname))
            ad.append('    set out@+ = string.format("%s[%%i].%s =", i)' % (tname, fname))
            ad.append('    loop k in %s { set out@+ = string.format(" %%i", e.%s@(k)) }' % (n, fname))
            ad.append('    set out@+ = "\\n"')
        else:
            cd.append('        printf("%s[%%i].%s = %%i\\n", i, %s[i].%s);' % (tname, fname, tname, fname))
            ad.append('    set out@+ = string.format("%s[%%i].%s = %%i\\n", i, if e.%s == true => 1 => (if e.%s == false => 0 => e.%s))' % (tname, fname, fname, fname, fname))
    cd.append('    }')
    ad.append('}')
cd += ['    return 0;', '}']
ad += ['io.write(string.join(out, ""))']
open(sys.argv[2], 'w').write('\n'.join(atm) + '\n')
open(sys.argv[3], 'w').write('\n'.join(cd) + '\n')
open(sys.argv[4], 'w').write('\n'.join(ad) + '\n')
