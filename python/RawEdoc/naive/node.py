#


class Node(object):
    def __init__(self, data=None):
        self.data = data
        self.next = None

    def __repr__(self):
        return str(self.data) + ' -> ' + repr(self.next)


def build_list(elements):
    handle = Node(Node)
    tail = handle
    for element in elements:
        tail.next = Node(element)
        tail = tail.next
    return handle.next


def build_one_two_three():
    return build_list([1, 2, 3])


def mk_array(node):
    result = []
    while node is not None:
        result.append(node.data)
        node = node.next
    return result


def assert_linked_list_equals(l1, l2, message):
    a1, a2 = mk_array(l1), mk_array(l2)
    if a1 != a2:
        print('\n', a1, a2)
        raise AssertionError(message)

