from node import Node, build_list, assert_linked_list_equals


def front_back_split(source, front, back):
    if front is None or back is None or source is None or source.data is None or source.next is None:
        raise ValueError()
    front.next = source
    a, b = front, source
    while b is not None:
        a = a.next
        b = b.next
        if b is not None:
            b = b.next
    back.data, back.next, a.next = a.next.data, a.next.next, None
    front.data, front.next = source.data, source.next


def test():
    source = build_list([1,2])
    front, back = Node(), Node()
    front_back_split(source, front, back)
    assert_linked_list_equals(front, Node(1), "front should be 1 -> None.")
    assert_linked_list_equals(back, Node(2), "back should be 2 -> None.")


if __name__ == '__main__':
    test()
