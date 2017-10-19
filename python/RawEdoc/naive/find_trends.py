#


def find_trends(arr):
    inc, dec = [], []
    c, l = 0, len(arr)
    while l - c > 2:
        cc = c
        while cc < l - 1 and arr[cc] < arr[cc + 1]:
            cc += 1
        if cc - c > 1:
            inc.append([c, cc + 1])
            c = cc
        else:
            c = cc

        cc = c
        while cc < l - 1 and arr[cc] > arr[cc + 1]:
            cc += 1
        if cc - c > 1:
            dec.append([c, cc + 1])
            c = cc
        else:
            c = cc

        cc = c
        while cc < l - 1 and arr[cc] == arr[cc + 1]:
            cc += 1
        c = cc

    return inc, dec


def test():
    # arr = [345, 32, 45, 12, 45, 47, 49, 55, 90, 104, 20, 30, 34]
    arr = [345, 288, 250, 215, 187, 156, 32, 32, 45, 12, 45, 47, 49, 55, 90, 104, 20, 30, 34]
    # arr = [234, 230, 229, 225, 318, 317, 312, 612, 620, 613, 30, 40, 10]
    inc, dec = find_trends(arr)
    print inc
    print dec
    inc = max(inc, key=lambda duo: duo[1] - duo[0]) if len(inc) else None
    dec = max(dec, key=lambda duo: duo[1] - duo[0]) if len(dec) else None
    print inc
    print dec


if __name__ == '__main__':
    test()
