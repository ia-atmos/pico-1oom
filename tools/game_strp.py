# Converts the table game_str_id_tbl of c/src/game/game_strp.c into Atmos:
# each item has accessors `get(i)` and `put(i, s)` of its string (C has a
# pointer to the `const char *`). It replaces the part of
# src/game/game_strp.atm between the lines BEGIN and END of the table.
# usage: python3 tools/game_strp.py c/src/game/game_strp.c src/game/game_strp.atm
import re, sys
src = re.sub(r'/\*.*?\*/', '', open(sys.argv[1]).read(), flags=re.S)
body = src[src.index('game_str_id_tbl[] = {'):]
body = body[:body.index('DEFSTREND')]
out = []
for kind, name in re.findall(r'(DEFSTRITEMTBL|DEFSTRITEM)\((\w+)\)', body):
    v = 'game_str_' + name
    if kind == 'DEFSTRITEMTBL':
        out.append('    strtbl_s("%s", #%s, func (i) { %s@(i) }, func (i, s) { set %s@(i) = s }),' % (name, v, v, v))
    else:
        out.append('    strtbl_s("%s", 1, func (i) { %s }, func (i, s) { set %s = s }),' % (name, v, v))
atm = open(sys.argv[2]).read()
b = atm.index(';; BEGIN game_str_id_tbl')
e = atm.index(';; END game_str_id_tbl')
b = atm.index('\n', b) + 1
atm = atm[:b] + 'pin game_str_id_tbl = [\n' + '\n'.join(out) + '\n]\n' + atm[e:]
open(sys.argv[2], 'w').write(atm)
print(len(out), 'items', file=sys.stderr)
