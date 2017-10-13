#


class BrainLuckMachine(object):
    def __init__(self, code, inp):
        self._code = code
        self._code_len = len(code)
        self._data = [0 for _ in range(256)]
        self._cp = 0
        self._dp = 0
        self._in = inp
        self._out = []

    def _error(self): raise Exception('Incorrect code!')

    def inc_dp(self):   self._dp += 1

    def dec_dp(self):   self._dp -= 1

    def inc_d(self):    self._data[self._dp] = (self._data[self._dp]+1) % 256

    def dec_d(self):    self._data[self._dp] = self._data[self._dp]-1 if self._data[self._dp]>0 else 255

    def out(self):      self._out.append(chr(self._data[self._dp]))

    def read(self):     self._data[self._dp], self._in = ord(self._in[0]), self._in[1:]

    def if_0(self):
        if self._data[self._dp] == 0:
            p, c = self._cp, 1
            while p < self._code_len:
                p += 1
                if self._code[p] == ']':
                    c -= 1
                    if c is 0:
                        break
                elif self._code[p] == '[':
                    c += 1
            self._cp = p+1 if p < self._code_len else self._error()
        else:
            self._cp += 1

    def if_1(self):
        if self._data[self._dp] != 0:
            p, c = self._cp, 1
            while p >= 0:
                p -= 1
                if self._code[p] == '[':
                    c -= 1
                    if c is 0:
                        break
                elif self._code[p] == ']':
                    c += 1
            self._cp = p+1 if p > 0 else self._error()
        else:
            self._cp += 1

    def pace(self):
        cmd = self._code[self._cp]
        {
            '>': lambda:self.inc_dp(),
            '<': lambda:self.dec_dp(),
            '+': lambda:self.inc_d(),
            '-': lambda:self.dec_d(),
            '.': lambda:self.out(),
            ',': lambda:self.read(),
            '[': lambda:self.if_0(),
            ']': lambda:self.if_1(),
        }[cmd]()
        if cmd not in '[]':
            self._cp += 1

    def execute(self):
        while self._cp < len(self._code):
            self.pace()

    def get_output(self):
        return ''.join(self._out)


def brain_luck(code, inp):
    machine = BrainLuckMachine(code, inp)
    machine.execute()
    return machine.get_output()


if __name__ == '__main__':
    print(brain_luck(',+[-.,+]', 'Codewars' + chr(255)))  # Codewars
    print(brain_luck(',[.[-],]', 'Codewars' + chr(0)))  # Codewars
    print(brain_luck(',>,<[>[->+>+<<]>>[-<<+>>]<<<-]>>.', chr(8) + chr(9)))  # chr(72)
    print(chr(72))
