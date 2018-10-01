#!/usr/bin/env python3

import math


def grow(table, begin):
    result = []

    entry = table[begin]
    result.append(entry[0])
    entry[1] = True
    options = entry[2]
    print("options:", entry[0], options)

    while True:
        entry = table[options[0]]
        result.append(entry[0])
        entry[1] = True
        options = list(filter(lambda i: table[i][1] is False, entry[2]))
        print("options:", entry[0], options)
        if len(options) != 1:
            break

    return result


def sq_sum_1(table, head):
    raise NotImplementedError


def sq_sum_2(table, head, tail):
    table = [[i, True, v] for i, v in table]
    print(table)

    head_list = [head]
    table[head][1] = False

    tail_list = [tail]
    table[tail][1] = False

    while True:
        grow(table, head_list)
        grow(table, tail_list)

    return []


def sq_sum(n):
    sqs = [x * x for x in range(1, int(math.sqrt(n * 2)) + 1)]
    sqs.reverse()

    print(sqs)

    table = [(x, list(filter(lambda i: 0 < i <= n and i != x, [y - x for y in sqs]))) for x in range(n + 1)]
    print(table)

    begins = list(filter(lambda i: len(i[1]) == 1, table))
    print(begins)

    if len(begins) > 2:
        return []
    elif len(begins) == 2:
        if begins[0][1][0] == begins[1][0]:
            return []
        else:
            return sq_sum_2(table, begins[0][0], begins[1][0])
    else:
        return sq_sum_1(table, begins[0])


def test():
    print(sq_sum(15))


if __name__ == '__main__':
    test()
