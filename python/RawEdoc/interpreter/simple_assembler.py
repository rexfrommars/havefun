#
import re


def assembler_interpreter(program):
    def _s(s):
        cut = s.find(';')
        if cut >= 0:
            s = s[:cut]
        return s.strip()

    def _v(s):
        try:
            return int(s)
        except ValueError:
            return regs[s]

    regs = {}
    result = None
    lines = [re.findall("'[^']*'|[-]?\d+|\w+[:]?", _line)
             for _line in [_s(_line) for _line in program.splitlines()] if len(_line)]

    labels = {}
    for i, line in enumerate(lines):
        print('%3d:\t%s' % (i, '\t'.join(line)))
        if line[0].endswith(':'):
            labels[line[0][:-1]] = i + 1

    cursor = 0
    cmp = 0
    calls = []
    while cursor < len(lines):
        line = lines[cursor]
        print(line, '\t', regs)
        ins, arg, ext = (line + [None, None, None])[:3]
        if ins == 'mov':
            regs[arg] = _v(line[2])
        elif ins == 'inc':
            regs[arg] += 1
        elif ins == 'dec':
            regs[arg] -= 1
        elif ins == 'add':
            regs[arg] += _v(line[2])
        elif ins == 'sub':
            regs[arg] -= _v(line[2])
        elif ins == 'mul':
            regs[arg] *= _v(line[2])
        elif ins == 'div':
            regs[arg] //= _v(line[2])
        elif ins == 'jmp':
            cursor = labels[arg]
            continue
        elif ins == 'cmp':
            cmp = _v(arg) - _v(ext)
        elif ins == 'jne':
            if cmp != 0:
                cursor = labels[arg]
                continue
        elif ins == 'je':
            if cmp == 0:
                cursor = labels[arg]
                continue
        elif ins == 'jge':
            if cmp >= 0:
                cursor = labels[arg]
                continue
        elif ins == 'jg':
            if cmp > 0:
                cursor = labels[arg]
                continue
        elif ins == 'jle':
            if cmp <= 0:
                cursor = labels[arg]
                continue
        elif ins == 'jl':
            if cmp < 0:
                cursor = labels[arg]
                continue
        elif ins == 'call':
            calls.append(cursor+1)
            cursor = labels[arg]
            continue
        elif ins == 'ret':
            cursor = calls.pop()
            continue
        elif ins == 'msg':
            result = ''.join([x.strip("'") if x.startswith("'") else str(_v(x)) for x in line[1:]])
        elif ins == 'end':
            break
        elif ins == ';':
            pass
        # else pass
        cursor += 1

    return -1 if calls else result if result else regs


if __name__ == '__main__':
    code = '''\
    mov a 5
    inc a
    dec a
    dec a
    jnz a -1
    inc a'''
    # print(simple_assembler(code.splitlines()), {'a': 1})

    code = '''\
    mov c 12
    mov b 0
    mov a 200
    dec a
    inc b
    jnz a -2
    dec c
    mov a b
    jnz c -5
    jnz 0 1
    mov c a'''
    # print(simple_assembler(code.splitlines()), {'a': 409600, 'c': 409600, 'b': 409600})

    code = '''\
    mov a -10
    mov b a
    inc a
    dec b
    jnz a -2
    call abc
    abc:'''
    # print(simple_assembler(code.splitlines()), {'a': 0, 'b': -20})

    program = '''
    ; My first program
    mov  a, 5
    inc  a
    call function
    msg  '(5+1)/2 = ', a    ; output message
    end

    function:
        div  a, 2
        ret
    '''
    # print(assembler_interpreter(program))

    program = '''
        mov	a	8
        mov	b	0
        mov	c	0
        mov	d	0
        mov	e	1
        call	proc_fib
        call	print
        end
        proc_fib:
        cmp	c	2
        jl	func_0
        mov	b	d
        add	b	e
        mov	d	e
        mov	e	b
        inc	c
        cmp	c	a
        jle	proc_fib
        ret
        func_0:
        mov	b	c
        inc	c
        jmp	proc_fib
        print:
        msg	'Term '	a	' of Fibonacci series is: '	b
        ret'''
    print(assembler_interpreter(program))
