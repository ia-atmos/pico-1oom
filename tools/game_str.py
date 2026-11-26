# Converts c/src/game/game_str.c into Atmos (src/game/game_str.atm), and
# writes the two dumps that check it (tst/c/game_str.c, tst/game_str.atm).
# usage: python3 tools/game_str.py c/src/game/game_str.c src/game/game_str.atm tst/c/game_str.c tst/game_str.atm
# (also for game_str_shipnames.c, with its own four names)
import re, sys
src = open(sys.argv[1]).read()
base = sys.argv[2].split('/')[-1][:-4]   # game_str, game_str_shipnames
body = re.sub(r'/\*.*?\*/', '', src, flags=re.S)
decls = re.findall(r'const char \*(\w+)(\[[^\]]*\])?\s*=\s*(.*?);', body, flags=re.S)
lit = re.compile(r'"((?:[^"\\]|\\.)*)"')
atm = [';; Port of c/src/game/%s.c: the strings of the game.' % base,
       ';; Generated from the C by a converter, which also writes the check',
       ';; (tst/game_str.sh). In C each is a `const char *`, which a PBX file may',
       ';; replace: here a `var`, or a vector of strings.', '']
cdump = ['/* The oracle of tst/%s.atm: every string of c/src/game/%s.c.' % (base, base),
         '   Generated with it. Not part of the port. */',
         '#include <stdio.h>', '#include "game_str.h"', '',
         'static void p(const char *n, int i, const char *s) { printf("%s[%i] = %s\\n", n, i, s ? s : "(null)"); }',
         '', 'int main(void)', '{']
adump = [';; %s.atm of the port: every string, as tst/c/%s.c prints it.' % (base, base),
         ';; Generated with it.', '', 'include "../src/game/%s.atm"' % base, '',
         'pin out = []', 'func p (n, i, s) {', '    set out@+ = string.format("%s[%i] = %s\\n", n, i, if s == nil => "(null)" => s)', '}', '']
for name, arr, init in decls:
    if arr:
        items = lit.findall(init)
        # an initializer is a list of literals separated by commas
        rest = lit.sub('', init).replace('{', '').replace('}', '')
        assert set(rest.replace(',', '').split()) == set(), (name, rest)
        atm.append('pin %s = [' % name)
        for k in range(0, len(items), 4):
            atm.append('    ' + ', '.join('"%s"' % x for x in items[k:k+4]) + ',')
        atm.append(']')
        n = ('(int)(sizeof(%s) / sizeof(%s[0]))' % (name, name)) if arr != '[]' else str(len(items))
        cdump.append('    for (int i = 0; i < %s; ++i) { p("%s", i, %s[i]); }' % (n, name, name))
        adump.append('loop i in #%s { p("%s", i, %s@(i)) }' % (name, name, name))
    else:
        items = lit.findall(init)
        assert len(items) == 1, (name, init)
        atm.append('var %s = "%s"' % (name, items[0]))
        cdump.append('    p("%s", 0, %s);' % (name, name))
        adump.append('p("%s", 0, %s)' % (name, name))
cdump += ['    return 0;', '}']
adump += ['io.write(string.join(out, ""))']
open(sys.argv[2], 'w').write('\n'.join(atm) + '\n')
open(sys.argv[3], 'w').write('\n'.join(cdump) + '\n')
open(sys.argv[4], 'w').write('\n'.join(adump) + '\n')
print(len(decls), 'declarations')
