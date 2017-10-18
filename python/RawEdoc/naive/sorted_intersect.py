from node import Node, build_list, assert_linked_list_equals


def sorted_intersect(first, second):
    handle = Node(None)
    tail = handle
    while first is not None and second is not None:
        if first.data == second.data:
            tail.next, first = first, first.next
            tail = tail.next
            tail.next, data = None, tail.data
            data = tail.data
        else:
            data = min(first.data, second.data)
        while first and first.data == data:
            first = first.next
        while second and second.data == data:
            second = second.next
    return handle.next


def test():
    # assert_linked_list_equals(sorted_intersect(Node(1), None), None, "result should be None.")
    # assert_linked_list_equals(sorted_intersect(None, Node(1)), None, "result should be None.")
    #
    # assert_linked_list_equals(sorted_intersect(Node(23), Node(44)), None, "result should be None.")
    # assert_linked_list_equals(sorted_intersect(Node(44), Node(23)), None, "result should be None.")
    # assert_linked_list_equals(sorted_intersect(Node(12), Node(12)), Node(12), "result should be 12 -> None.")
    #
    # assert_linked_list_equals(sorted_intersect(build_list([1, 3]), build_list([2, 4])), None, "result should be None.")
    # assert_linked_list_equals(sorted_intersect(build_list([3]), build_list([2, 4])), None, "result should be None.")
    # assert_linked_list_equals(sorted_intersect(build_list([3, 4, 5]), build_list([2, 9])), None,
    #                           "result should be None.")
    # assert_linked_list_equals(sorted_intersect(build_list([4, 5]), build_list([1])), None, "result should be None.")
    # assert_linked_list_equals(sorted_intersect(build_list([4, 5]), build_list([4, 5])), build_list([4, 5]),
    #                           "result should be 4 -> 5 -> None.")
    assert_linked_list_equals(sorted_intersect(build_list([4, 5]), build_list([1, 2, 3, 4, 5])), build_list([4, 5]),
                              "result should be 4 -> 5 -> None.")
    assert_linked_list_equals(sorted_intersect(build_list([1, 2, 2, 2, 2, 2, 5]), build_list([1, 5])),
                              build_list([1, 5]), "result should be 1 -> 5 -> None.")


if __name__ == '__main__':
    test()
