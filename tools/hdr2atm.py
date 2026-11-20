# Converts the enums and the numeric #defines of a C header to Atmos `val`s,
# in the order of the header. Prints to stdout. Structs are skipped.
# usage: python3 tools/hdr2atm.py HEADER.h
import re, sys
src = open(sys.argv[1]).read()
src = re.sub(r'/\*.*?\*/', '', src, flags=re.S)
out = []
pos = 0
tok = re.compile(r'(typedef\s+)?enum\s*\w*\s*\{(.*?)\}\s*(\w*)\s*;|#define[ \t]+(\w+)[ \t]+([^\n]+)|typedef\s+struct\s+\w*\s*\{.*?\}\s*\w*\s*;|struct\s+\w+\s*\{.*?\}\s*;', re.S)
for m in tok.finditer(src):
    if m.group(2) is not None:
        val = -1
        if m.group(3): out.append(';; ' + m.group(3))
        for item in [x.strip() for x in m.group(2).split(',') if x.strip()]:
            if '=' in item:
                n, v = [x.strip() for x in item.split('=')]
                val = int(v, 0)
            else:
                n = item; val += 1
            out.append('val %s = %d' % (n, val))
        out.append('')
    elif m.group(4):
        n, v = m.group(4), m.group(5).strip()
        if n.startswith('INC_1OOM') or '(' in n: continue
        v = re.sub(r'\b(\d+)u\b', r'\1', v)
        if re.fullmatch(r'[\w\s\+\-\*/\(\)]+', v):
            v = v.replace('/', '//')
            out.append('val %s = %s' % (n, v))
print('\n'.join(out))
