from node import Node, build_list, assert_linked_list_equals


def sorted_merge(first, second):
    if first is None and second is None:
        return None
    handle = Node()
    tail = handle
    while first is not None and second is not None:
        if first.data <= second.data:
            tail.next, first, tail.next.next = first, first.next, None
        else:
            tail.next, second, tail.next.next = second, second.next, None
        tail.next.next, tail = None, tail.next
    tail.next = first if first is not None else second
    return handle.next


def test():
    assert_linked_list_equals(sorted_merge(Node(1), None), build_list([1]), "result should be 1 -> None.")
    assert_linked_list_equals(sorted_merge(None, Node(1)), build_list([1]), "result should be 1 -> None.")
    assert_linked_list_equals(sorted_merge(Node(23), Node(44)), build_list([23, 44]), "result should be 23 -> 44 -> None.")
    assert_linked_list_equals(sorted_merge(Node(44), Node(23)), build_list([23, 44]), "result should be 23 -> 44 -> None.")


if __name__ == '__main__':
    test()
