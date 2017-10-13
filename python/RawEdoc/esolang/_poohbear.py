import math


def poohbear(code):
    out = []
    step = 1024
    capa = step
    mem = bytearray('\0' * capa, 'ascii')
    mc = capa // 2
    copied = None
    loop = []

    cl = len(code)
    cc = 0
    while cc < cl:
        c = code[cc]
        if c == '+':
            mem[mc] = 0 if mem[mc] == 255 else mem[mc] + 1
        elif c == '-':
            mem[mc] = 255 if mem[mc] == 0 else mem[mc] - 1
        elif c == '>':
            if mc == capa:
                mem += bytearray('\0' * step, 'ascii')
            mc += 1
        elif c == '<':
            if mc == 0:
                mem = bytearray('\0' * step, 'ascii') + mem
                mc = step
            mc -= 1
        elif c == 'c':
            copied = mem[mc]
        elif c == 'p':
            mem[mc] = copied
        elif c == 'W':
            if mem[mc] is not 0:
                loop.append(cc)
                print 'W', mem[mc], loop
            else:
                ec = code[cc:].find('E')
                if ec >= 0:
                    cc += ec + 1
                    continue
                else:
                    break
        elif c == 'E':
            cc = loop.pop()
            print 'E', loop, cc
            continue
        elif c == 'P':
            out.append(chr(mem[mc]))
        elif c == 'N':
            out.append(str(mem[mc]))
        elif c == 'T':
            mem[mc] = mem[mc] * 2 % 256
        elif c == 'Q':
            mem[mc] = mem[mc] ** 2 % 256
        elif c == 'U':
            mem[mc] = int(math.sqrt(mem[mc]))
        elif c == 'L':
            mem[mc] += 2
        elif c == 'I':
            mem[mc] -= 2
        elif c == 'V':
            mem[mc] //= 2
        elif c == 'A':
            mem[mc] += copied
        elif c == 'B':
            mem[mc] -= copied
        elif c == 'Y':
            mem[mc] *= copied
        elif c == 'D':
            mem[mc] //= copied

        cc += 1

    return ''.join(out)

if __name__ == '__main__':
    print(poohbear('LQTcQAP>pQBBTAI-PA-PPL+P<BVPAL+T+P>PL+PBLPBP<DLLLT+P'), 'Hello World!')
    print(poohbear('+LTQII>+WN<P>+E'))
