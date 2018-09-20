#!/usr/bin/env python3

# TODO a non-recursive implement


def _p(x, left):
    for index in range(len(x)):
        if x[index][1] and left > 1:
            x[index][1] -= 1
            for item in _p(x, left - 1):
                yield [x[index][0]] + item
            x[index][1] += 1
        elif x[index][1]:
            yield [x[index][0]]
            break


def permutations(s):
        x = [[c, s.count(c)] for c in sorted(set(s))]
        for p in _p(x, len(s)):
            yield ''.join(p)


def test(s):
    print('=' * 32)
    print(' >> %s' % s)
    for p in permutations(s):
        print(' -- %s' % (p,) )


if __name__ == '__main__':
    test('')
    test('a')
    test('ab')
    test('abc')

