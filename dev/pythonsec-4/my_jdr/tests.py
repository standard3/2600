from my_jdr import *

p1 = D6() + d6 + 1
print(repr(p1))
# D6 + D6 + 1

p2 = d6 * 4 + 12 + 4 * d8
print(repr(p2))
# 4D6 + 12 + 4D8

AbstractResult.seed(12345)
print(f"p1 throw = {p1.throw()}") # 8
print(f"p2 throw = {p2.throw()}") # 42

print(f"p1 show = {p1.show()}")   # 6, 1, 1
print(f"p2 show = {p2.show()}")   # 1, 6, 3, 2, 12, 4, 1, 5, 8

if type(p1.roll()).__name__ != 'generator':
    raise TypeError("La méthode roll doit retourner un générater")

for t in (D6() + D4() + 1).roll():
    print(t)

proba = (D6() * 6).success(lambda x: sum(x) >= 30)
print("=> check %s%%" % proba)

proba = (D10() * 5).success(Pool.darkness)
print("=> check %s%%" % proba)