#!/usr/bin/env python3

from my_checktype import *

#####
print(1)
try:
    @checktypes
    def f(a, b, c):
        print("cool %r" % locals())

    f(1, 2, 3)
except Exception as e:
    print(e.args[0])

# cool {'a': 1, 'c': 3, 'b': 2}

#####
print(2)
try:
    @checktypes
    def f(a: str, b, c):
        print("cool %r" % locals())

    f(1, 2, 3)
except Exception as e:
    print(e.args[0])

# wrong type of 'a' argument, 'str' expected, got 'int'

#####
print(3)
try:
    @checktypes
    def f(a: str, b: float, c):
        print("cool %r" % locals())

    f(1, 2, 3)
except Exception as e:
    print(e.args[0])

# wrong type of 'a' argument, 'str' expected, got 'int'

#####
print(4)
try:
    @checktypes
    def f(a, b: float, c):
        print("cool %r" % locals())

    f(1, 2, 3)
except Exception as e:
    print(e.args[0])

# f: wrong type of 'b' argument, 'float' expected, got 'int'

#####
print(5)
try:
    @checktypes
    def f(a, b: float, c) -> str:
        print("cool %r" % locals())
        return 1

    f(1, 2.1, 3)
except Exception as e:
    print(e.args[0])

# cool {'a': 1, 'c': 3, 'b': 2.1}$
# f: wrong return type, 'str' expected, got 'int'$

#####
print(6)
try:
    @checktypes
    def f(a, b, c) -> str:
        print("cool %r" % locals())
        return 1

    f(1, 2, 3)
except Exception as e:
    print(e.args[0])

# 6$
# cool {'a': 1, 'c': 3, 'b': 2}$
# f: wrong return type, 'str' expected, got 'int'$

#####
print(7)
try:
    @checktypes
    def f(a, b, c) -> str:
        print("cool %r  " % locals())
        return "yes"

    f(1, 2, 3)
except Exception as e:
    print(e.args[0])

# 7$
# cool {'a': 1, 'c': 3, 'b': 2}$

#####
print(8)
class Pouet:
    def __init__(self, *a):
        self.__dict__.update({'_' + str(i): v for i, v in zip(range(len(a)), a)})

    def __repr__(self):
        return repr(vars(self))

try:
    @checktypes
    def f(a: int, b: float, c: Pouet) -> str:
        print("cool %r" % locals())
        return "yes"

    f(1, 2.2, 12)
except Exception as e:
    print(e.args[0])

# 8$
# f: wrong type of 'c' argument, 'Pouet' expected, got 'int'$

#####
print(9)
try:
    @checktypes
    def f(a: int, b: float, c: Pouet) -> str:
        print("cool %r" % locals())
        return "yes"

    f(1, 2.2, Pouet('cool', 42))
except Exception as e:
    print(e.args[0])

# 9$
# cool {'a': 1, 'c': {'_0': 'cool', '_1': 42}, 'b': 2.2}
