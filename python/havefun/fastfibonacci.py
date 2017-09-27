#


class FibonacciMachine(object):
    """
    f(n)    = f(n-2) + f(n-1)
    f(n+m)  = f(n)*f(m-1) + f(n+1)*f(m)
    f(2n)   = f(n) * (f(n-1) + f(n+1))
    f(2n-1) = f(n)*f(n-2) + f(n+1)*f(n-1)
    """

    @staticmethod
    def decompose(num):
        change16 = num & 0x0F
        num -= change16
        result = [change16]
        mask = 1 << 3
        while num > 0:
            mask <<= 1
            component = num & mask
            num -= component
            if component:
                result.append(component)
        return result

    @staticmethod
    def f2n(fn_m1, fn, fn_p1):
        """
        f(2n-1) = f(n-2)*f(n) + f(n-1)*f(n+1)
        f(2n)   = f(n) * (f(n-1) + f(n+1))
        :return: f(2n-1), f(2n), f(2n+1)
        """
        fn_m2 = fn - fn_m1
        f2n_m1 = fn_m2 * fn + fn_m1 * fn_p1
        f2n = fn * (fn_m1 + fn_p1)
        return f2n_m1, f2n, f2n + f2n_m1

    def __init__(self):
        self._changes = [0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597]
        self._map = {16: self._changes[15:18]}  # f15, f16, f17
        self._level = 16
        pass

    def f_n_m(self, n, m):
        """
        f(n+m)   = f(n)*f(m-1) + f(n+1)*f(m)
        f(n+m+1) = f(n)*f(m) + f(n+1)*f(m+1)
        :param n: (f(n-1), f(n), f(n+1))
        :param m: (f(m-1), f(m), f(m+1))
        :return: f(n+m-1), f(n+m), f(n+m+1)
        """
        f_nm = n[1] * m[0] + n[2] * m[1]
        f_nm_p1 = n[1] * m[1] + n[2] * m[2]

        return f_nm_p1 - f_nm, f_nm, f_nm_p1

    def change(self, n):
        return self._changes[n]

    def fetch(self, n):
        """
        :param n: power of 2, and >= 16
        :return: f(n-1), f(n), f(n+1)
        """
        while self._level < n:
            top = self._map[self._level]
            self._level <<= 1
            self._map[self._level] = self.f2n(*top)

        return self._map[n]

    def calculate(self, num):
        print('=' * 32)
        ns = self.decompose(num)
        # print '(%d) %s' % (num, str(ns))
        if len(ns) == 1:
            return self.change(ns[0])
        elif ns[0] == 1:
            trio, ns = list(self.fetch(ns[1])), ns[2:]
            trio = trio[1:] + [trio[-2] + trio[-1]]
        else:
            trio, ns = (self.change(ns[0]-1), self.change(ns[0]), self.change(ns[0]+1)), ns[1:]

        while ns:
            n, ns = ns[0], ns[1:]
            # print trio, n, ns
            trio = self.f_n_m(trio, self.fetch(n))
        # print trio
        return trio[1]


def fib(num):
    if num < 0:
        return -fib(-num) if num%2 == 0 else fib(-num)
    else:
        fm = FibonacciMachine()
        result = fm.calculate(num)
        # print(' ---- %s' % str(result))
        return result

# fib(7)
# fib(15)
# fib(17)
# fib(23)
# fib(100)
# fib(1000)
# fib(10000)
# fib(100000)
fib(1000000)
