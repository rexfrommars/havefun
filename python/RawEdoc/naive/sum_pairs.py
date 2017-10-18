#


def sum_pairs_brutal_force(ints, s):
    a, b = len(ints), len(ints)
    for cursor in range(len(ints) - 1):
        if cursor == b - 1:
            break
        base = ints[cursor]
        for i, v in enumerate(ints[cursor + 1:]):
            print cursor, i
            if cursor + 1 + i >= b:
                break
            if base + v == s:
                a, b = cursor, cursor + 1 + i
                print '-', a, b

    print '=', a, b
    return None if a == len(ints) else [ints[a], ints[b]]


def sum_pairs(ints, s):
    d = {}
    for i, v in enumerate(ints):
        if s - v in d:
            return v, s - v
        elif v not in d:
            d[v] = i
    return None


def test():
    pass


if __name__ == '__main__':
    test()
