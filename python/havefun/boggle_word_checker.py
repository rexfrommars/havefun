def find_word(boggle, word):
    def find(c0):
        for ri, row in enumerate(boggle):
            for ci, c in enumerate(row):
                if c == c0:
                    yield ri, ci

    def find_nbs(_c, x0, y0):
        for _x, _y in [(_x, _y) for _x in {x0-1, x0, x0+1} for _y in {y0-1, y0, y0+1}
                       if 0 <= _x < len(boggle) and 0 <= _y < len(boggle[0]) and (_x != x0 or _y != y0)]:
            if (_x, _y) not in p and boggle[_x][_y] == _c:
                yield _x, _y

    l, s, p = len(word), [find(word[0])], [(-1, -1)]  # word_len, stack, path

    while len(s):
        try:
            p.append(next(s[-1]))
            if len(s) < l:
                s.append(find_nbs(word[len(s)], *p[-1]))
            else:
                return True
        except StopIteration:
            s.pop(), p.pop()

    return False


board = [
  ["E", "A", "R", "A"],
  ["N", "L", "E", "C"],
  ["I", "A", "I", "S"],
  ["B", "Y", "O", "R"]
]

# print find_word(board, 'CEREAL')

print find_word(board, 'C')
print find_word(board, 'EAR')
print find_word(board, 'EARS')
print find_word(board, 'BAILER')
print find_word(board, 'RSCAREIOYBAILNEA')
print find_word(board, 'CEREAL')
print find_word(board, 'ROBES')

