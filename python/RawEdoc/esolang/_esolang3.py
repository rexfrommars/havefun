#


class PaintLuckMachine(object):
    def __init__(self, code, iterations, width, height):
        print('%dx%d @@ %d of %s' % (width, height, iterations, code))
        self._code = ''.join([c for c in code if c in 'nswe*[]'])
        self._code_len = len(self._code)
        self._cp = 0
        self._iterations = iterations
        self._w = width
        self._h = height
        self._data = [[False for _x in range(width)] for _y in range(height)]
        self._dx = 0
        self._dy = 0

    def _error(self): raise Exception('Something is wrong!')

    def n(self): self._dy = self._dy - 1 if self._dy > 0 else self._h - 1

    def s(self): self._dy = self._dy + 1 if self._dy < self._h - 1 else 0

    def w(self): self._dx = self._dx - 1 if self._dx > 0 else self._w - 1

    def e(self): self._dx = self._dx + 1 if self._dx < self._w - 1else 0

    def flip(self):
        print self._dx, self._dy
        self._data[self._dy][self._dx] = not self._data[self._dy][self._dx]

    def if0(self):
        if self._data[self._dy][self._dx] is False:
            p, c = self._cp, 1
            while p < self._code_len:
                p += 1
                if self._code[p] == ']':
                    c -= 1
                    if c == 0:
                        break
                elif self._code[p] == '[':
                    c += 1
            self._cp = p+1 if p < self._code_len else self._error()
        else:
            self._cp += 1

    def if1(self):
        if self._data[self._dy][self._dx] is True:
            p, c = self._cp, 1
            while p >= 0:
                p -= 1
                if self._code[p] == '[':
                    c -= 1
                    if c == 0:
                        break
                elif self._code[p] == ']':
                    c += 1
            self._cp = p+1 if p >= 0 else self._error()
        else:
            self._cp += 1

    def pace(self):
        cmd = self._code[self._cp]
        func = {
            'n': lambda: self.n(),
            's': lambda: self.s(),
            'w': lambda: self.w(),
            'e': lambda: self.e(),
            '*': lambda: self.flip(),
            '[': lambda: self.if0(),
            ']': lambda: self.if1(),
        }
        func[cmd]()
        if cmd not in '[]':
            self._cp += 1

    def execute(self):
        for _ in range(self._iterations):
            if self._cp < self._code_len:
                self.pace()

    def get_output(self):
        out = '\r\n'.join([''.join(['1' if x is True else '0' for x in line]) for line in self._data])
        # print('>> %s' % out)
        return out


def interpreter(code, iterations, width, height):
    machine = PaintLuckMachine(code, iterations, width, height)
    machine.execute()
    return machine.get_output()

if __name__ == '__main___':
    # print(interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 0, 6, 9))
    # print(interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 7, 6, 9))
    print(interpreter('eee*s*s*s*w*w*w*w*w*w*w*n*n*n*n*n*n*n*n*n*e*e*e*e*e*e*e*s*s*s*s*s*', 1000, 8, 10))
