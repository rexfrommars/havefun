#


def mini_bit_move(code, array):
    array = [_ for _ in array]
    cursor = 0
    try:
        while cursor < len(array):
            for c in code:
                if c == '1':
                    array[cursor] = '1' if array[cursor] == '0' else '0'
                elif c == '0':
                    cursor += 1
        return ''.join(array)
    except IndexError:
        pass

if __name__ == '__main__':
    print(mini_bit_move('10', '1100101'), '0011010')
