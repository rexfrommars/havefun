#!/usr/bin/env python3

def permutations(l:list):
    if len(l) > 1:
        for i in l:
            ao = l[:]
            ao.remove(i)
            for p in permutations(ao):
                yield (i, *p)
    else:
        yield tuple(l)


def test(l:list):
    print('=' * 32)
    print(' ~~ %s' % l)
    for p in permutations(l):
        print(' -- %s' % (p,))


if __name__ == '__main__':
    test([])
    test([1])
    test([1,2])
    test([1,2,3])

