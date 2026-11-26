# Converts the table game_num_id_tbl of c/src/game/game_nump.c into Atmos:
# each item has accessors `get(i)` and `put(i, v)` of its variable (C has
# a pointer and the step between the elements). It replaces the part of
# src/game/game_nump.atm between the lines BEGIN and END of the table.
# usage: python3 tools/game_nump.py c/src/game/game_nump.c src/game/game_nump.atm
import re, sys
src = re.sub(r'/\*.*?\*/', '', open(sys.argv[1]).read(), flags=re.S)
body = src[src.index('game_num_id_tbl[] = {'):]
body = body[:body.index('DEFNUMEND')]

def aexpr(c):
    # C lvalue expression -> Atmos: a[b][c] -> a@(b)@(c)
    return re.sub(r'\[([^\]]*)\]', r'@(\1)', c.strip())

def ntype(t):
    t = t.strip()
    if t.startswith('NUMTYPE_GUESS('):
        return 'NUMTYPE_U32'    # the enums of ship parts: 4 bytes (gcc)
    return t

# The items whose type is wider than their field (found by comparing the
# sizes in C): C reads and writes the bytes after the field too.
# st_shld_absorb is U16 on `uint8_t absorb`, which `uint8_t tech_i` follows.
WIDE = {
    'st_shld_absorb': ('func (i) { tbl_shiptech_shield@(i).absorb | (tbl_shiptech_shield@(i).tech_i << 8) }',
                       'func (i, v) {\n            set tbl_shiptech_shield@(i).absorb = v & 0xff\n            set tbl_shiptech_shield@(i).tech_i = (v >> 8) & 0xff\n        }'),
}

out = []
for m in re.finditer(r'(DEFNUMITEMLSTBL|DEFNUMITEMLTBLL|DEFNUMITEMLTBL|DEFNUMITEML|DEFNUMITEM)\((.*?)\),\s*\n', body):
    kind, args = m.group(1), m.group(2)
    a = []
    depth, cur = 0, ''
    for ch in args:
        if ch == '(':
            depth += 1
        elif ch == ')':
            depth -= 1
        if ch == ',' and depth == 0:
            a.append(cur.strip()); cur = ''
        else:
            cur += ch
    a.append(cur.strip())
    if kind == 'DEFNUMITEMLSTBL':
        nid, name, field, t, vmin, vmax = a
        tbl = aexpr(name)
        f = aexpr(field)
        get = 'func (i) { %s@(i).%s }' % (tbl, f)
        put = 'func (i, v) { set %s@(i).%s = v }' % (tbl, f)
        size = '#%s' % tbl
    elif kind == 'DEFNUMITEMLTBL':
        nid, name, t, vmin, vmax = a
        tbl = aexpr(name)
        get = 'func (i) { %s@(i) }' % tbl
        put = 'func (i, v) { set %s@(i) = v }' % tbl
        size = '#%s' % tbl
    elif kind == 'DEFNUMITEMLTBLL':
        nid, t, vmin, vmax = a
        tbl = 'game_num_' + nid
        get = 'func (i) { %s@(i) }' % tbl
        put = 'func (i, v) { set %s@(i) = v }' % tbl
        size = '#%s' % tbl
    else:
        if kind == 'DEFNUMITEML':
            nid, t, vmin, vmax = a
            var = 'game_num_' + nid
        else:
            nid, name, t, vmin, vmax = a
            var = aexpr(name)
        get = 'func (i) { %s }' % var
        put = 'func (i, v) { set %s = v }' % var
        size = '1'
    if nid in WIDE:
        get, put = WIDE[nid]
    out.append('    numtbl_s("%s", %s, %s, %s, %s,\n        %s,\n        %s),' % (nid, ntype(t), size, vmin, vmax, get, put))

atm = open(sys.argv[2]).read()
b = atm.index(';; BEGIN game_num_id_tbl')
e = atm.index(';; END game_num_id_tbl')
b = atm.index('\n', b) + 1
atm = atm[:b] + 'pin game_num_id_tbl = [\n' + '\n'.join(out) + '\n]\n' + atm[e:]
open(sys.argv[2], 'w').write(atm)
print(len(out), 'items', file=sys.stderr)
