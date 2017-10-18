class Node(object):
    def __init__(self, data=None):
        self.data = data
        self.next = None

    def __repr__(self):
        return str(self.data) + ' -> ' + repr(self.next)


def _reverse(head):
    if head.next is not None:
        node, head = head, head.next
        node.next = None
        head, tail = _reverse(head)
        tail.next = node
        return head, tail.next
    else:
        return head, head


def recersive_reverse(head):
    if head is None or head.next is None:
        return head
    head, _ = _reverse(head)
    return head


def test(ia):
    if not ia:
        assert recersive_reverse(None) is None
    else:
        print(':: ' + str(ia))
        head = Node(ia[0])
        tail = head
        for i in ia[1:]:
            tail.next = Node(i)
            tail = tail.next
        print head
        head = recersive_reverse(head)
        print head
        result = []
        while head:
            result.append(head.data)
            head = head.next
        print ia, result
        assert result == list(reversed(ia))


if __name__ == '__main__':
    test(None)
    test([1])
    test([1, 2])
    test([1, 2, 3])
