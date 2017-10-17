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


class Interpreter:
    def __init__(self):
        self.vars = {}
        self.functions = {
            '+': lambda a, b: a + b,
            '-': lambda a, b: a - b,
            '*': lambda a, b: a * b,
            '/': lambda a, b: a / b,  # TODO ?
            '%': lambda a, b: a % b,
        }

    def _ill_formed(self, message):
        raise IllFormedExpression(message)

    def calculate(self, tokens):
        var, assign, num, op0, op1, bracket = 0, 1, 2, 10, 11, 20  # op0: +1; op1:*/%
        stack = []  # (t, name)
        for token in tokens:
            print('#### %s' % str([str(_1) for _0, _1 in stack]))
            if token.isdigit():
                if len(stack) >= 2 and stack[-1][0] is op1:
                    op, a = stack.pop(), stack.pop()
                    stack.append((num, self.functions[op[1]](a[1], Decimal(token))))
                else:
                    stack.append((num, Decimal(token)))
            elif token in '+-':  # op0
                l = len(stack)

                if l >= 3 and stack[-1][0] == num and stack[-2][0] == op0 and stack[-3][0] == num:
                    b, op, a = stack.pop(), stack.pop(), stack.pop()
                    stack.append((num, self.functions[op[1]](a[1], b[1])))

                if len(stack) and stack[-1][0] in (var, num):
                    stack.append((op0, token))
                else:
                    self._ill_formed('The symbol "%s" appears in wrong place.' % token)
            elif token in '*/%':  # op1
                # TODO more check
                stack.append((op1, token))
            elif token == '(':
                # TODO
                stack.append((bracket, token))
            elif token == ')':
                l, v = len(stack), None
                if l >= 4 and [t for t, v in stack[-4:]] == [bracket, num, op0, num]:
                    b, op, a, _ = stack.pop(), stack.pop(), stack.pop(), stack.pop()
                    v = self.functions[op[1]](a[1], b[1])
                elif l >= 2 and stack[-1][0] == num and stack[-2][0] == bracket:
                    (_, v), _ = stack.pop(), stack.pop()
                else:
                    self._ill_formed(stack)

                if len(stack) >= 2 and stack[-1][0] is op1:
                    op, a = stack.pop(), stack.pop()
                    v = self.functions[op[1]](a[1], Decimal(v))
                print v
                stack.append((num, Decimal(v)))

            elif token == '=':
                if len(stack) != 1 or stack[0][0] != var:
                    self._ill_formed('The symbol "=" appears in wrong place.')
                stack.append((assign, token))
            else:  # it should be an identifier
                if len(stack) == 0:
                    stack.append((var, token))
                elif stack[-1][0] == num:
                    self._ill_formed('whatever')
                elif token in self.vars:
                    stack.append((num, self.vars[token]))
                else:
                    raise InvalidIdentifier(var)

        print(stack)
        while len(stack) >= 3:
            if stack[-2][0] == op0:
                try:
                    b, op, a = stack.pop(), stack.pop(), stack.pop()
                    a = self.vars[a[1]] if a[0] == var else a[1]
                    stack.append((num, self.functions[op[1]](a, b[1])))
                except KeyError:
                    raise InvalidIdentifier(stack[0][1])
            else:  # elif stack[-2][0] == assign:
                break

        if len(stack) == 3:
            if stack[1][0] == assign:
                if stack[0][0] == var and stack[2][0] == num:
                    self.vars[stack[0][1]] = stack[2][1]
                    return stack[2][1]
        elif len(stack) == 1:
            try:
                return self.vars[stack[0][1]] if stack[0][0] == var else stack[0][1]
            except KeyError:
                self._ill_formed(stack)
        elif len(stack) == 0:
            return ''
        self._ill_formed(stack)

    def input(self, expression):
        tokens = tokenize(expression)
        try:
            result = self.calculate(tokens)
            return result
        except IllFormedExpression:
            # return 'ERROR: ill-formed expression.'
            # return 'input: %s' % expression
            # raise
            raise Exception('input: %s' % expression)
        except InvalidIdentifier as e:
            return '''ERROR: Invalid identifier. No variable with name '%s' was found.''' % e.var


interpreter = Interpreter()
# print '>>', interpreter.input('1 + 1')
# print '>>', interpreter.input('2 - 1')
# print '>>', interpreter.input('2 * 3')
# print '>>', interpreter.input('8 / 4')
# print '>>', interpreter.input('7 % 4')
#
# print '>>', interpreter.input('x = 1')
# print '>>', interpreter.input('x')
# print '>>', interpreter.input('x + 3')
# print '>>', interpreter.input('y')

# print '>>', interpreter.input('(4 + 2) * 3')
#
# print '>>', interpreter.input('(7 + 3) / (2 * 2 + 1)')
# print '>>', interpreter.input('(10 / (8 - (4 + 2))) * 3')

# print '>>', interpreter.input('x = 7')
# print '>>', interpreter.input('y = x + 5')
# print '>>', interpreter.input('1 + 11')
print '>>', interpreter.input('1two')

