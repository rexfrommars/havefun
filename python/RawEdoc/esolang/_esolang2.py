#


class SmallLuckMachine(object):
    def __init__(self, code, tape):
        # TODO filter code '<>*[]'
        self._code = code
        self._code_len = len(code)
        self._tape = [False if c == '0' else True for c in list(tape)]
        self._tape_len = len(tape)
        self._cp = 0
        self._tp = 0

    def _error(self): raise Exception('Something is wrong!')

    def inc_p(self): self._tp += 1

    def dec_p(self): self._tp -= 1

    def flip(self): self._tape[self._tp] = not self._tape[self._tp]

    def if0(self):
        if self._tape[self._tp] is False:
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
        if self._tape[self._tp] is True:
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
            '>': lambda: self.inc_p(),
            '<': lambda: self.dec_p(),
            '*': lambda: self.flip(),
            '[': lambda: self.if0(),
            ']': lambda: self.if1(),
        }
        func[cmd]()
        if cmd not in '[]':
            self._cp += 1

    def execute(self):
        while self._cp < self._code_len and 0 <= self._tp < self._tape_len:
            self.pace()

    def get_output(self):
        return ''.join(['1' if x is True else '0' for x in self._tape])


def interpreter(code, tape):
    machine = SmallLuckMachine(code, tape)
    machine.execute()
    return machine.get_output()


if __name__ == '__main___':
    # print(interpreter("*", "00101100") == "10101100")
    print(interpreter('[[]*>*>*>]', '000'))
