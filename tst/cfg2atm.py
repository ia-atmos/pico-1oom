# A config file of C (`module.item = value` lines) as the config of the
# port (a table of Atmos, as src/cfg.atm writes it), with the values read
# as C reads them (util_parse_number, util_cstr_parse_in_place). A value
# that C rejects is copied as it is, so that the port rejects it too.
#   python3 -I tst/cfg2atm.py IN.txt > OUT.atm
import sys

def cnum(s):
    # strtoul base 0, the whole string, then (int)
    t = s.strip()
    neg = t[:1] == '-'
    if t[:1] in '+-':
        t = t[1:]
    try:
        if t[:2].lower() == '0x' and len(t) > 2:
            v = int(t[2:], 16)
        elif t[:1] == '0' and len(t) > 1:
            v = int(t[1:], 8)
        else:
            v = int(t, 10)
    except ValueError:
        return None
    v = (-v if neg else v) & 0xffffffff
    return v - (1 << 32) if v >= (1 << 31) else v

def cstr(s):
    out = ''
    i = 0
    while i < len(s) and s[i] != '"':
        c = s[i]; i += 1
        if c == '\\':
            c = s[i] if i < len(s) else '\0'; i += 1
            c = {'\\': '\\', '"': '"', 'n': '\n', 't': '\t'}.get(c)
            if c is None:
                return None
        out += c
    return out

def astr(s):
    r = '"'
    for c in s:
        o = ord(c)
        if c == '\\': r += '\\\\'
        elif c == '"': r += '\\"'
        elif c == '\n': r += '\\n'
        elif c == '\t': r += '\\t'
        elif o < 32 or o == 127: r += '\\x%02x' % o
        else: r += c
    return r + '"'

pre, mods = [], []          # mods: [name, [lines]]
for line in open(sys.argv[1], encoding='latin-1').read().split('\n'):
    line = line.strip(' \r')
    if not line:
        continue
    if line[0] == '#':
        c = ';;' + line[1:]
        (mods[-1][1] if mods else pre).append(('c', c))
        continue
    mod, _, rest = line.partition('.')
    item, _, val = rest.partition(' =')
    val = val[1:] if val[:1] == ' ' else val
    if val == '':
        v = 'nil'
    elif val in ('true', 'false'):
        v = val
    elif val[0] == '"':
        s = cstr(val[1:])
        v = astr(s) if s is not None else val
    else:
        n = cnum(val)
        v = str(n) if n is not None else val
    if not mods or mods[-1][0] != mod:
        mods.append([mod, []])
    mods[-1][1].append(('i', '%s = %s,' % (item, v)))

hdr = pre[:1] if pre and pre[0][1] == ';; 1oom configuration file' else []
out = [c for _, c in pre[len(hdr):]]
out = ([';; 1oom configuration file'] if hdr else []) + out + ['[']
for mod, lines in mods:
    out.append('    %s = [' % mod)
    for k, l in lines:
        out.append('        ' + l)
    out.append('    ],')
out.append(']')
sys.stdout.write('\n'.join(out) + '\n')
