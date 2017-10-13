#


def infini_tick(code):
    code = ''.join([c for c in code if c in '><+-*&/\\'])
    out = []
    step = 1024
    capa = step
    mem = bytearray('\0' * capa, 'ascii')
    cursor = capa // 2
    skip = False
    run = True

    while run is True:
        for c in code:
            if skip is True:
                skip = False
            elif c == '>':
                if cursor == capa:
                    mem += bytearray('\0' * step, 'ascii')
                cursor += 1
            elif c == '<':
                if cursor == 0:
                    mem = bytearray('\0' * step, 'ascii') + mem
                    cursor = step
                cursor -= 1
            elif c == '+':
                mem[cursor] = 0 if mem[cursor] == 255 else mem[cursor] + 1
            elif c == '-':
                mem[cursor] = 255 if mem[cursor] == 0 else mem[cursor] - 1
            elif c == '*':
                out.append(chr(mem[cursor]))
            elif c == '/':
                if mem[cursor] is 0:
                    skip = True
            elif c == '\\':
                if mem[cursor] is not 0:
                    skip = True
            elif c == '&':
                run = False
                break
            # else pass

    return ''.join(out)


if __name__ == '__main__':
    _code = '++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*>+++++++++++++++++++++++++++++' \
            '++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*>+++++++++++++++++++++++++++++' \
            '+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++**>+++++++++++++++++++++' \
            '++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*>+++++++++++' \
            '+++++++++++++++++++++*>++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++' \
            '+++++++++++++++++++++++++++++++++++++++*<<*>>>+++++++++++++++++++++++++++++++++++++++++++++++++++++++++' \
            '+++++++++++++++++++++++++++++++++++++++++++++++++++++++++*<<<<*>>>>>+++++++++++++++++++++++++++++++++++' \
            '+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*>+++++++++++++++++++++++++++++++++*& '
    # print(infini_tick(_code), 'Hello, world!')

    _code = '+*\\&'
    print(infini_tick(_code))
