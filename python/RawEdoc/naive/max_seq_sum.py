#


def smart(arr):
    result, curr = 0, 0
    for i in arr:
        curr = curr + i if curr + i > 0 else 0
        result = result if result > curr else curr
    return result


def stupid(arr):
    if not arr:
        return 0

    xacc, acc = arr[:], 0
    for i in range(len(arr)):
        acc += arr[i]
        xacc[i] = acc
    yacc, acc = arr[:], 0
    for i in range(len(arr)):
        a = -1-i
        acc += arr[a]
        yacc[a] = acc

    result = [(0, min(yacc))]
    for c in range(1, len(arr)):
        result.append((xacc[c - 1], min(yacc[c:])))
    result.append((min(xacc), 0))
    result = min([sum(duo) for duo in result])
    return sum(arr) - result

max_seq_sum = stupid


def test():
    assert max_seq_sum([-2, 1, -3, 4, -1, 2, 1, -5, 4]) == 6

    arr = [27, -20, 42, -4, 24, -11, 14, -30, 3, -39, 49, -46, 57,
           -2, 1, -16, 44, -95, 51, -95, 1, -5, 25, -46, 23, -20, 19]
    assert max_seq_sum(arr) == 93
