#

import re
from decimal import Decimal


def tokenize(expression):
    if expression == "":
        return []

    regex = re.compile("\s*(=>|[-+*\/\%=\(\)]|[A-Za-z_][A-Za-z0-9_]*|[0-9]*\.?[0-9]+)\s*")
    tokens = regex.findall(expression)
    return [s for s in tokens if not s.isspace()]


class IllFormedExpression(Exception):
    pass


class InvalidIdentifier(Exception):
    def __init__(self, var):
        self.var = var
        super(self.__class__, self).__init__(self)


class NameConflict(Exception):
    def __init__(self, name):
        self.name = name
        super(self.__class__, self).__init__(self)


class InsufficientParameter(Exception):
    pass


class Interpreter:

    def __init__(self, parent=None):
        self.parent = parent
        self.vars = {}
        self.funcs = {}
        self.operators = {
            '+': lambda a, b: a + b,
            '-': lambda a, b: a - b,
            '*': lambda a, b: a * b,
            '/': lambda a, b: a / b,
            '%': lambda a, b: a % b,
        }
        self.history = []

    def __repr__(self):
        return str(self.parent) + '|| %s \n' % str(self.vars) + '\n'.join(['--> ' + e for e in self.history])

    @staticmethod
    def _ill_formed(message):
        raise IllFormedExpression(message)

    def call_func(self, func_name, args):
        # print('@@@@ call func "%s" with args: %s' % (func_name, args))
        call_ctx = Interpreter()
        for var, value in zip(self.funcs[func_name][0], args):
            print(var, value)
            call_ctx.input('%s = %s' % (var, value))
        result = call_ctx.input(self.funcs[func_name][1])
        # print('#### %s' % str(result))
        return result

    def calculate(self, tokens):
        def _v(duo):
            try:
                return duo[1] if duo[0] == t_num else self.vars[duo[1]]
            except KeyError:
                raise InvalidIdentifier(duo[1])
        t_var, t_assign, t_num, t_op0, t_op1, t_bracket = 0, 1, 2, 10, 11, 20  # op0: +1; op1:*/%
        stack = []  # (t, name)
        call_stack = []
        for token in tokens:
            print('%s #### %s' % (token, str([str(_1) for _0, _1 in stack])))
            if call_stack:
                if token == '=':
                    raise NameConflict(call[0])
                elif token in self.vars:
                    call_stack[-1][1].append(self.vars[token])
                elif token not in self.funcs:
                    call_stack[-1][1].append(token)
                else:
                    call_stack.append((token, []))

                while call_stack and len(call_stack[-1][1]) == len(self.funcs[call_stack[-1][0]][0]):
                    call = call_stack.pop()
                    print(call)
                    result = self.call_func(*call)
                    if call_stack:
                        call_stack[-1][1].append(result)
                    else:
                        stack.append((t_num, result))
            elif token in self.funcs:
                if not self.funcs[token][0]:
                    stack.append((t_num, self.call_func(token, [])))
                else:
                    call_stack.append((token, []))
            elif token.isdigit():
                if len(stack) >= 2 and stack[-1][0] is t_op1:
                    op, a = stack.pop(), _v(stack.pop())
                    stack.append((t_num, self.operators[op[1]](a, Decimal(token))))
                else:
                    stack.append((t_num, Decimal(token)))
            elif token in '+-':  # op0
                l = len(stack)

                if l >= 3 and stack[-1][0] == t_num and stack[-2][0] == t_op0 and stack[-3][0] == t_num:
                    b, op, a = stack.pop(), stack.pop(), stack.pop()
                    stack.append((t_num, self.operators[op[1]](a[1], b[1])))

                if len(stack) and stack[-1][0] in (t_var, t_num):
                    stack.append((t_op0, token))
                else:
                    self._ill_formed('The symbol "%s" appears in wrong place.' % token)
            elif token in '*/%':  # op1
                stack.append((t_op1, token))
            elif token == '(':
                stack.append((t_bracket, token))
            elif token == ')':
                l, v = len(stack), None
                if l >= 4 and stack[-4][0] == t_bracket and stack[-2][0] == t_op0:
                    b, op, a, _ = _v(stack.pop()), stack.pop(), _v(stack.pop()), stack.pop()
                    v = self.operators[op[1]](a, b)
                elif l >= 4 and [t for t, v in stack[-4:-1]] == [t_bracket, t_var, t_assign]:
                    b, _, a, _ = _v(stack.pop()), stack.pop(), stack.pop(), stack.pop()
                    if a[1] in self.funcs:
                        raise NameConflict(a[1])
                    self.vars[a[1]], v = b, b
                elif l >= 2 and stack[-1][0] == t_num and stack[-2][0] == t_bracket:
                    (_, v), _ = stack.pop(), stack.pop()
                else:
                    self._ill_formed(stack)

                if len(stack) >= 2 and stack[-1][0] is t_op1:
                    op, a = stack.pop(), stack.pop()
                    v = self.operators[op[1]](a[1], Decimal(v))
                stack.append((t_num, Decimal(v)))

            elif token == '=':
                if not stack or stack[-1][0] != t_var:
                    self._ill_formed('The symbol "=" appears in wrong place.')
                stack.append((t_assign, token))
            else:  # it should be an identifier
                if stack and stack[-1][0] in (t_num, t_var):
                    self._ill_formed('whatever')
                else:
                    stack.append((t_var, token))

        if call_stack:
            raise InsufficientParameter("Insufficient parameters for function call.")

        print(stack)
        while len(stack) >= 3:
            if stack[-2][0] == t_op0:
                b, op, a = _v(stack.pop()), stack.pop(), _v(stack.pop())
                stack.append((t_num, self.operators[op[1]](a, b)))
            elif stack[-2][0] == t_assign:
                b, op, a = _v(stack.pop()), stack.pop(), stack.pop()
                if a[1] in self.funcs:
                    raise NameConflict(a[1])
                self.vars[a[1]] = b
                stack.append((t_num, b))

            else:  # elif stack[-2][0] == assign:
                break

        if len(stack) == 1:
            return _v(stack[0])
        elif len(stack) == 0:
            return ''
        self._ill_formed(stack)

    def input(self, expression):
        print('::::::::', expression)
        self.history.append(expression)
        tokens = tokenize(expression)
        if tokens and tokens[0] == 'fn':
            name = tokens[1]
            args = tokens[2:tokens.index('=>')]
            for arg in args:
                if arg[0].isdigit():
                    self._ill_formed("invalid variable name: %s" % arg)
            if len(set(args)) < len(args):
                self._ill_formed("Declearation of the function with duplicate parameter name")
            for token in tokens[tokens.index('=>') + 1:]:
                if token[0].isalpha() or token[0] == '_':
                    if token not in args:
                        self._ill_formed("Expression of the function contains invalid variable name.")

            body = expression[expression.find('=>') + 2:]
            if name not in self.vars:
                self.funcs[name] = (args, body.strip())
                return ''
            else:
                raise NameConflict(name)
        else:
            return self.calculate(tokens)


def test():
    interpreter = Interpreter()
    # print '>>', interpreter.input('1 + 1')
    # print '>>', interpreter.input('2 - 1')
    # print '>>', interpreter.input('2 * 3')
    # print '>>', interpreter.input('8 / 4')
    # print '>>', interpreter.input('7 % 4')
    # #
    # print '>>', interpreter.input('x = 1')
    # print '>>', interpreter.input('x * 1')
    # print '>>', interpreter.input('x / 1')
    # print '>>', interpreter.input('x')
    # print '>>', interpreter.input('x + 3')
    # print '>>', interpreter.input('y')
    # #
    # print '>>', interpreter.input('(4 + 2) * 3')
    # print '>>', interpreter.input('(4 + 2) / 3')
    # #
    # print '>>', interpreter.input('(7 + 3) / (2 * 2 + 1)')
    # print '>>', interpreter.input('(10 / (8 - (4 + 2))) * 3')
    # #
    print '>>', interpreter.input('x = 7')
    print '>>', interpreter.input('y = x + 5')
    # print '>>', interpreter.input('z = x + y')
    # print '>>', interpreter.input('1 + 11')
    # print '>>', interpreter.input('(1 + 11)')

    # print '>>', interpreter.input('x = 7')
    # print '>>', interpreter.input('x = y = 7')
    # print '>>', interpreter.input('x = 13 + (y = 3)')
    # print '>>', interpreter.input('x')
    # print '>>', interpreter.input('y')
    # print '>>', interpreter.input('x + y')
    # print '>>', interpreter.input('(x + y)')
    # print '>>', interpreter.input('(x + y)/2')

    # print '>>', interpreter.input('two = 2')
    # print '>>', interpreter.input('1two')
    # print '>>', interpreter.input('avg = 3')

    # print '>>', interpreter.input('fn two => 1+1')
    # print '>>', interpreter.input('two')
    #
    print '>>', interpreter.input('fn echo x => x')
    # print '>>', interpreter.input('echo 39')
    # print '>>', interpreter.input('x = echo')

    # print '>>', interpreter.input('x = 3')
    # print '>>', interpreter.input('y = 4')
    # print '>>', interpreter.input('(x + y) / 2')

    print '>>', interpreter.input('fn avg x y => (x + y) / 2')
    # print '>>', interpreter.input('avg 7')
    # print '>>', interpreter.input('avg = 3')
    print '>>', interpreter.input('avg 3 4')
    print '>>', interpreter.input('avg x y')
    # print '>>', interpreter.input('avg echo 2 echo 4')

    # print '>>', interpreter.input('fn add x y => x + y')
    # print '>>', interpreter.input('add 3 4')
    # print '>>', interpreter.input('fn inc a => a+1')
    # print '>>', interpreter.input('inc 3')

    # print '>>', interpreter.input('x = 1')
    # print '>>', interpreter.input('x')
    # print '>>', interpreter.input('fn x => 0')

    print interpreter
