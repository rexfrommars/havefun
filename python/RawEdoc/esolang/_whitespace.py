#


# to help with debugging
def dye(code):
    return code.replace(' ', 's').replace('\t', 't').replace('\n', 'n')


def bleach(code):
    return code.replace('s', ' ').replace('t', '\t').replace('n', '\n')


class _Meta(type):
    def __new__(mcs, cls_name, bases, dict_):
        _S, _T, _N = ' ', '\t', '\n'
        _DISPATCH = {}
        for k, v in dict_.items():
            if k.startswith('_CMD_'):
                nv = {}
                print v[0]
                for _k, _f, _e in v:
                    n_k = _k.replace('s', _S).replace('t', _T).replace('n', _N)
                    if _f is None:
                        _DISPATCH[n_k] = nv
                        print(n_k, nv)
                    else:
                        nv[n_k] = (_f, _e)
        dict_['_DISPATCH'] = _DISPATCH
        return super(mcs, mcs).__new__(mcs, cls_name, bases, dict_)


class WhiteSpaceMachine(object):  # , metaclass=Meta):  # metaclass: Python3 style
    __metaclass__ = _Meta  # Python2 style

    class Cmd(object):
        def __init__(self, func, extra):
            self.func = func
            self.extra = extra
            self.next = None

    def __init__(self, code, input_):
        self._code = ''.join([c for c in code if c in ' \t\n'])
        self._code_repr = dye(code)
        self._cursor = 0
        self._raw_input = input_
        self._input = input_
        self._cmd_list = self.Cmd('__head__', None)
        self._cmd_count = 0
        self._cmd = None
        self._label_register = {}
        self._call_stack = []
        self._output = []
        self._stack = []
        self._heap = {}
        self._run = True

        print('@@ %s' % self._code_repr)
        print('$$ %s' % self._raw_input)

    def _exception(self, message):
        raise Exception(message)

    def code(self):
        return self._code_repr

    def output(self):
        return ''.join(self._output)

    def _parse_number(self, cursor):
        code = self._code[cursor:]
        if code[0] == self._N:
            return self._exception('(%d) no sign for a number' % self._cursor)
        sign = -1 if code[0] == '\t' else 1  # ' '
        c = code.find(self._N)
        if c < 0:
            return self._exception('(%d) no sign for a number' % self._cursor)
        num = code[1:c]
        num = int(num.replace(self._S, '0').replace(self._T, '1'), 2) * sign if len(num) else 0
        return num, cursor + c + 1

    def _parse_label(self, cursor):
        code = self._code[cursor:]
        c = code.find(self._N)
        if c < 0:
            return self._exception('(%d) nonterminated label' % self._cursor)
        label = code[:c]
        # print('zzzzzz _%s_' % label.replace(self._S, 's').replace(self._N, 'n'))
        return label, cursor + c + 1

    # Stack Manipulation
    _CMD_STACK = [
        ['s',   None, None],
        ['ss',  '_stack_push', 'N'],
        ['sts', '_stack_dup_nth', 'N'],
        ['stn', '_stack_discard_top_n', 'N'],
        ['sns', '_stack_dup_top', None],
        ['snt', '_stack_swap_top2', None],
        ['snn', '_discard_top', None],
    ]

    def _stack_push(self, num):
        self._stack.append(num)
        print('_stack_push %d' % num)
        return None

    def _stack_dup_nth(self, num):
        if 0 <= num < len(self._stack):
            num = self._stack[-num-1]
            self._stack.append(num)
            print('_stack_dup_nth %d' % num)
            return None
        else:
            return self._exception('dup-nth out of index! %d' % num)

    def _stack_discard_top_n(self, num):
        if num <= 0 or num >= len(self._stack):
            self._stack = [self._stack[-1]]
        else:
            self._stack = self._stack[:len(self._stack) - num - 1] + [self._stack[-1]]
        return None

    def _stack_dup_top(self, _):
        self._stack.append(self._stack[-1])
        return None

    def _stack_swap_top2(self, _):
        a, b = self._stack.pop(), self._stack.pop()
        self._stack += [a, b]
        return None

    def _discard_top(self, _):
        self._stack.pop()
        return None

    # Arithmetic
    _CMD_ARITHMETIC = [
        ['ts', None, None],
        ['tsss', '_arith_add', None],
        ['tsst', '_arith_minus', None],
        ['tssn', '_arith_muliply', None],
        ['tsts', '_arith_floor_div', None],
        ['tstt', '_arith_mode', None],
    ]

    def _arith_add(self, _):
        a, b = self._stack.pop(), self._stack.pop()
        self._stack.append(b + a)
        return None

    def _arith_minus(self, _):
        a, b = self._stack.pop(), self._stack.pop()
        self._stack.append(b - a)
        return None

    def _arith_muliply(self, _):
        a, b = self._stack.pop(), self._stack.pop()
        self._stack.append(b * a)
        return None

    def _arith_floor_div(self, _):
        a, b = self._stack.pop(), self._stack.pop()
        self._stack.append(int(b / a))
        return None

    def _arith_mode(self, _):
        a, b = self._stack.pop(), self._stack.pop()
        self._stack.append(b % a)
        return None

    # Heap
    _CMD_HEAP = [
        ['tt', None, None],
        ['tts', '_heap_put', None],
        ['ttt', '_heap_get', None],
    ]

    def _heap_put(self, _):
        value, addr = self._stack.pop(), self._stack.pop()
        self._heap[addr] = value
        return None

    def _heap_get(self, _):
        addr = self._stack.pop()
        self._stack.append(self._heap[addr])
        return None

    # IO
    _CMD_IO = [
        ['tn', None, None],
        ['tnss', '_io_o_c', None],
        ['tnst', '_io_o_i', None],
        ['tnts', '_io_i_c', None],
        ['tntt', '_io_i_i', None],
    ]

    def _io_o_c(self, _):
        num = self._stack.pop()
        self._output.append('%s' % chr(num))
        print('_io_o_i %s' % self._output[-1])
        return None

    def _io_o_i(self, _):
        num = self._stack.pop()
        self._output.append('%d' % num)
        print('_io_o_i %s' % self._output[-1])
        return None

    def _io_i_c(self, _):
        v, self._input = self._input[0], self._input[1:]
        addr = self._stack.pop()
        self._heap[addr] = ord(v)
        return None

    def _io_i_i(self, _):
        a = self._input.find('\n')
        if a >= 0:
            num, self._input = self._input[:a], self._input[a+1:]
        else:
            num, self._input = self._input, ''
        num = int(num)
        addr = self._stack.pop()
        self._heap[addr] = num
        return None

    # FLOW CONTROL
    _CMD_FC = [
        ['n', None, None],
        ['nss', '_fc_label', 'L'],
        ['nst', '_fc_call', 'L'],
        ['nsn', '_fc_jump', 'L'],
        ['nts', '_fc_if_zero', 'L'],
        ['ntt', '_fc_if_neg', 'L'],
        ['ntn', '_fc_return', None],
        ['nnn', '_fc_exit', None],
    ]

    def _fc_label(self, label):
        return None

    def _fc_call(self, label):
        self._call_stack.append(self._cmd.next)
        return self._label_register[label].next

    def _fc_jump(self, label):
        return self._label_register[label].next

    def _fc_if_zero(self, label):
        return self._label_register[label].next if self._stack.pop() is 0 else None

    def _fc_if_neg(self, label):
        return self._label_register[label].next if self._stack.pop() < 0 else None

    def _fc_return(self, _):
        return self._call_stack.pop()

    def _fc_exit(self, _):
        self._run = False
        return None

    #
    _S, _T, _N = ' ', '\t', '\n'
    _DISPATCH = {}

    _FUNC_MAP = {}

    def next_cmd(self):
        code = self._code[self._cursor:]
        print('--' * 16)
        print('>> %s' % self._code_repr[self._cursor:])
        for imp in self._DISPATCH.keys():
            if code.startswith(imp):
                for serial, (func, extra) in self._DISPATCH[imp].items():
                    if code.startswith(serial):
                        print('--> ', func, extra)
                        self._cursor += len(serial)
                        if extra is None:
                            return func, None
                        elif extra == 'N':
                            num, self._cursor = self._parse_number(self._cursor)
                            return func, num
                        elif extra == 'L':
                            label, self._cursor = self._parse_label(self._cursor)
                            return func, label
                        else:
                            return self._exception('unknown extra instruction: %s' % extra)
        self._exception('(%d) unknown command' % self._cursor)

    def parse(self):
        tail = self._cmd_list
        while self._cursor < len(self._code):
            func, extra = self.next_cmd()
            tail.next = self.Cmd(func, extra)
            tail = tail.next
            self._cmd_count += 1
            if func == '_fc_label':
                if extra in self._label_register:
                    self._exception('redundant label: %s' % extra)
                self._label_register[extra] = tail
            print(func, extra)

        print('cmd-count: %d' % self._cmd_count)

    def pace(self, cmd):
        print(cmd.func, cmd.extra)
        jump = self.__getattribute__(cmd.func)(cmd.extra)
        return cmd.next if jump is None else jump

    def execute(self):
        self._cmd = self._cmd_list.next
        while self._run:
            self._cmd = self.pace(self._cmd)


def whitespace(code, inp=''):
    machine = WhiteSpaceMachine(code, inp)
    machine.parse()
    machine.execute()
    return machine.output()


# ===============================================

if __name__ == '__main__':
    code_list = [
        '   \t\n\t\n \t\n\n\n',     # 1
        '   \t \n\t\n \t\n\n\n',    # 2
        '   \t\t\n\t\n \t\n\n\n',   # 3
        '    \n\t\n \t\n\n\n',      # 0

        '  \t\t\n\t\n \t\n\n\n',    # -1
        '  \t\t \n\t\n \t\n\n\n',   # -2
        '  \t\t\t\n\t\n \t\n\n\n',  # -3

        '   \t     \t\n\t\n  \n\n\n',   # 'A'
        '   \t    \t \n\t\n  \n\n\n',   # 'B'
        '   \t    \t\t\n\t\n  \n\n\n'   # 'C'
    ]

    code = code_list[1]

    # code = trans('sssttnsssttntnsttnstnnn')
    # code = trans('ssstnssstsnsssttnstsstsntnstnnn')

    # s = 'sssttnssstsnssstnssstssnsssttsnssststnssstttnsntstnsttntnsttnsttnsttnstnnn'
    # s = 'sstntnstnnn'
    # s = 'ssstnttttnstnnn'
    # s = 'ssstnssstsnsssttnststtntnstnnn'

    # s = 'ssstntnttssstsntnttsssttntnttsssttntttssstsntttssstnttttnsttnsttnstnnn'
    # inp = '1\n2\n3\n'
    #
    # s = 'ssstnssstsnsssttnstsstsntnstnnn'
    #
    # s = 'ssstntntsssstsntntssssttntntsssstssntntsssststntntsssststntt' \
    #     'tssstssntttsssttntttssstsntttssstnttttnsstnsstnsstnsstnssnnn'
    # inp = '12345'

    # fc
    s = 'ssstnsssttnsssnssstsnsssnssstnnssntnstntsnnnn'
    inp = ''

    s = 'ssttnsssnssstnssstsnsssttnnssntnstsnsnttsnnsnnnsssnnnn'

    code = bleach(s)
    result = whitespace(code, inp)
    print('*' * 32)
    print result
