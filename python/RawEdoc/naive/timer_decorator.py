import time
from time import sleep
from functools import wraps


def timer(limit):
    def wrap(func):
        @wraps(func)
        def wf(*args):
            begin = time.time()
            func(*args)
            end = time.time()
            return end - begin < limit
        return wf
    return wrap


def test():
    @timer(1)
    def foo():
        sleep(0.1)

    @timer(1)
    def bar():
        sleep(1.1)

    assert foo() is True
    assert bar() is False
