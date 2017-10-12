#

from random import randint


class _BefungeExit(Exception):
    pass


class BefungeMachine(object):

    _R, _L, _D, _U = (0, 1), (0, -1), (1, 0), (-1, 0)

    def _noop(self, _): pass

    def _nimp(self, op): raise NotImplementedError('op: %s' % op)

    def _num(self, n): self._stack.append(int(n))

    def _add(self, _):
        x = self._stack.pop()
        self._stack[-1] += x

    def _minus(self, _):
        x = self._stack.pop()
        self._stack[-1] -= x

    def _mul(self, _):
        x = self._stack.pop()
        self._stack[-1] *= x

    def _div(self, _):
        x = self._stack.pop()
        self._stack[-1] = self._stack[-1] // x

    def _mod(self, _):
        x = self._stack.pop()
        self._stack[-1] %= x

    def _not(self, _):
        self._stack[-1] = 1 if self._stack[-1] == 0 else 0

    def _gt(self, _):
        x = self._stack.pop()
        self._stack[-1] = 1 if self._stack[-1] > x else 0

    def _dir_right(self, _): self._direct, self._d= '>', self._R

    def _dir_left(self, _): self._direct, self._d = '<', self._L

    def _dir_down(self, _): self._direct, self._d = 'v', self._D

    def _dir_up(self, _): self._direct, self._d = '^', self._U

    def _dir_rand(self, _): self._l[ord('<>^v'[randint(0, 3)])](self, None)

    def _if_horizontal(self, _): self._dir_right(_) if self._stack.pop() is 0 else self._dir_left(_)

    def _if_vertical(self, _): self._dir_down(_) if self._stack.pop() is 0 else self._dir_up(_)

    def _str_mode(self, _): self._str_mode = True

    def _dup_top(self, _): self._stack.append(self._stack[-1] if len(self._stack) else 0)

    def _swap_top2(self, _):
        l = len(self._stack)
        if l > 1:
            map(self._stack.append, [self._stack.pop(), self._stack.pop()])
        elif l > 0:
            self._stack.append(0)

    def _discard_top(self, _): self._stack.pop()

    def _o_int(self, op): self._output.append(str(self._stack.pop()))

    def _o_char(self, op):
        self._output.append(chr(self._stack.pop()))

    def _skip_next(self, _):
        self._x += self._d[0]
        self._y += self._d[1]

    def _put(self, _):  # TODO 'the ASCII value' ?
        x, y, v = self._stack.pop(), self._stack.pop(), self._stack.pop()
        self._plane[x][y] = chr(v)
        print ''.join(['|' + ''.join(line) + '\n' for line in self._plane])

    def _get(self, _):  # TODO 'the ASCII value' ?
        x, y = self._stack.pop(), self._stack.pop()
        self._stack.append(ord(self._plane[x][y]))

    def _end(self, _): raise _BefungeExit()

    # 0123456789+-*/%!`><v^?_|":\\$.,#pg @
    _ = {
        '0': _num,
        '1': _num,
        '2': _num,
        '3': _num,
        '4': _num,
        '5': _num,
        '6': _num,
        '7': _num,
        '8': _num,
        '9': _num,
        '+': _add,
        '-': _minus,
        '*': _mul,
        '/': _div,
        '%': _mod,
        '!': _not,
        '`': _gt,
        '>': _dir_right,
        '<': _dir_left,
        'v': _dir_down,
        '^': _dir_up,
        '?': _dir_rand,
        '_': _if_horizontal,
        '|': _if_vertical,
        '"': _str_mode,
        ':': _dup_top,
        '\\': _swap_top2,
        '$': _discard_top,
        '.': _o_int,
        ',': _o_char,
        '#': _skip_next,
        'p': _put,
        'g': _get,
        ' ': _noop,
        '@': _end,
    }

    _l = [_nimp for i in range(256)]
    for _op, _func in _.items():
        _l[ord(_op)] = _func

    def __init__(self, programme):
        self._programme = programme
        self._plane = [list(row) for row in self._programme.split('\n')]
        self._stack = []
        self._direct = None
        self._d = self._R
        self._x = 0
        self._y = -1
        self._str_mode = False
        self._output = []
        print ''.join(['|' + ''.join(line) + '\n' for line in self._plane])

    def __repr__(self):
        return '(%d, %d) %s || %s' % (self._x, self. _y, self._stack, ''.join(self._output))

    def get_output(self):
        return ''.join(self._output)

    def _next_op(self):
        self._x += self._d[0]
        self._y += self._d[1]
        op = self._plane[self._x][self._y]
        print('%d,%d ----> %s' % (self._x, self._y, op))
        return op

    def execute(self):
        try:
            while True:
                op = self._next_op()
                if self._str_mode is False:
                    self._l[ord(op)](self, op)
                else:
                    if op != '"':
                        self._stack.append(ord(op))
                    else:
                        self._str_mode = False

                print op, self

        except _BefungeExit:
            print('Befunge programme exit.')
            pass

        except IndexError:
            print self
            raise


def interpret(code):
    bm = BefungeMachine(code)
    bm.execute()
    return bm.get_output()


if __name__ == '__main__':
    # program = '>987v>.v\n' \
    #           'v456<  :\n' \
    #           '>321 ^ _@'

    # program = '>25*"!dlroW olleH":v\n' \
    #           '                v:,_@\n' \
    #           '                >  ^'

    # program = '01->1# +# :# 0# g# ,# :# 5# 8# *# 4# +# -# _@'

    # program = '08>:1-:v v *_$.@\n' \
    #           '  ^    _$>\:^'

    # program = '"abc"34p         @\n' \
    #           'xxxxxxxxxxxxxxxxxx\n' \
    #           'xxxxxxxxxxxxxxxxxx\n' \
    #           'xxxxxxxxxxxxxxxxxx\n' \
    #           'xxxxxxxxxxxxxxxxxx\n' \
    #           'xxxxxxxxxxxxxxxxxx\n'

    program = '2>:3g" "-!v\  g30          <\n' \
              ' |!`"&":+1_:.:03p>03g+:"&"`|\n' \
              ' @               ^  p3\\" ":<\n' \
              '2 2345678901234567890123456789012345678'

    print interpret(program)

