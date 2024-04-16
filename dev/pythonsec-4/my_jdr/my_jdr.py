import random
import itertools

###

class AddExpr:
    def __init__(self, lhs, rhs):
        self.lhs = lhs
        self.rhs = rhs
        self.result = 0

    def __repr__(self) -> str:
        return repr(self.lhs) + ' + ' + repr(self.rhs)

    def throw(self) -> int:
        if self.result == 0:
            a = self.lhs.throw()
            b = self.rhs.throw()
            self.result = a + b
        return self.result

    def show(self):
        if self.result == 0:
            self.throw()

        return ", ".join(str(i) for i in self.lhs.show()) + ", ".join(str(i) for i in self.rhs.show())

class RAddExpr(AddExpr):
    def __repr__(self) -> str:
        return repr(self.rhs) + repr(self.lhs)

class SubExpr:
    def __init__(self, lhs, rhs):
        self.lhs = lhs
        self.rhs = rhs
        self.result = 0

    def __repr__(self) -> str:
        return repr(self.lhs) + ' - ' + repr(self.rhs)

    def throw(self) -> int:
        if self.result == 0:
            a = self.lhs.throw()
            b = self.rhs.throw()
            self.result = a - b
        return self.result

    def show(self):
        if self.result == 0:
            self.throw()

        return ", ".join(str(i) for i in self.lhs.show()) + ", ".join(str(i) for i in self.rhs.show())

class RSubExpr(SubExpr):
    def __repr__(self) -> str:
        return repr(self.rhs) + repr(self.lhs)

class MulExpr:
    def __init__(self, lhs, rhs):
        self.lhs = lhs
        self.rhs = rhs
        self.result = 0

    def __repr__(self) -> str:
        return repr(self.rhs) + repr(self.lhs)

    def throw(self) -> int:
        if self.result == 0:
            a = self.lhs.throw()
            b = self.rhs.throw()
            self.result = a * b
        return self.result

    def show(self):
        if self.result == 0:
            self.throw()

        return ", ".join(str(i) for i in self.lhs.show()) + ", ".join(str(i) for i in self.rhs.show())

class RMulExpr(MulExpr):
    def __repr__(self) -> str:
        return repr(self.lhs) + repr(self.rhs)

class Pool:

    # Dans le système “World Of Darkness”, on compte le nombre de fois qu’un D10 dépasse
    # (dans une poignée de dés) une certaine valeur par dés. Si le nombre de dés ainsi calculé
    # dépasses un certain objectif c’est un succès. Cette lambda compte le nombre de dés ≥ 5
    # et si le nombre total de dés remplissant ce contrat est ≥ 4 alors c’est un succès.
    darkness = lambda t: sum(1 for i in t if i >= 5) >= 4

    def __init__(self, op):
        self.op = op

    def throw(self):
        return self.op.throw()

    def roll(self):
        if hasattr(self, 'op'):
            if (isinstance(self.op, MulExpr)
            and isinstance(self.op.rhs, FrozenDice)):
                yield from itertools.product(
                    self.op.lhs.roll(),
                    repeat=self.op.rhs.throw()
                )
            else:
                l1, l2 = self.op.lhs.roll(), self.op.rhs.roll()

                for result_lhs, result_rhs in itertools.product(l1, l2):
                    yield ((result_lhs,) if isinstance(result_lhs, int) else result_lhs) + \
                          ((result_rhs,) if isinstance(result_rhs, int) else result_rhs)
        else:
            yield from range(self.min, self.max + 1)

    def success(self, lamb) -> float:
        """
        Calcule la probabilité de chance qu'un trow() soit un succès. La lambda
        lamb définit ce qui est succès. La lambda reçoit en unique paramètre un
        tuple représentant un jet de dés (chaque élément du tuple donne la valeur
        de chaque dés). La lambda sera évidement appelé par success pour toutes
        les solutions possibles pour ce jet de dés. Par exemple, dans le RPG “Star Wars”
        un succès c'est quand avec la somme d'un certain nombre de D6 ont dépasse
        un seuil. 6D6 étant une valeur de compétence correct, et un niveau de
        difficulté de 30 un acte héroïque...
        """
        total, success = 0, 0
        for t in self.roll():
            total += 1
            if lamb(t):
                success += 1
        return (success / total) * 100

    def __add__(self, rhs):
        if type(rhs) is int:
            rhs = FrozenDice(rhs)
        return Pool(AddExpr(self, rhs))

    def __radd__(self, lhs):
        if type(lhs) is int:
            lhs = FrozenDice(lhs)
        return Pool(RAddExpr(lhs, self))

    def __sub__(self, rhs):
        if type(rhs) is int:
            rhs = FrozenDice(rhs)
        return Pool(SubExpr(self, rhs))

    def __rsub__(self, lhs):
        if type(lhs) is int:
            lhs = FrozenDice(lhs)
        return Pool(RSubExpr(lhs, self))

    def __mul__(self, rhs):
        if type(rhs) is int:
            rhs = FrozenDice(rhs)
        return Pool(MulExpr(self, rhs))

    def __rmul__(self, lhs):
        if type(lhs) is int:
            lhs = FrozenDice(lhs)
        return Pool(RMulExpr(lhs, self))

    def __repr__(self) -> str:
        return repr(self.op)

    def show(self):
        if hasattr(self, 'op'):
            results = []
            for _ in range(AbstractResult.min, AbstractResult.max + 1):
                results.append(str(next(self.roll())))
            return ', '.join(results)
        else:
            return str(self.throw())

class AbstractResult(Pool):
    min = 1
    max = 1

    def __init__(self):
        self.result = 0

    def __repr__(self):
        return type(self).__name__

    def throw(self):
        if self.result == 0:
            self.result = random.randint(type(self).min, type(self).max)
        return self.result

    def seed(s):
        random.seed(s)

class FrozenDice(AbstractResult):
    def __init__(self, v):
        self.result = v
        self.min = v
        self.max = v

    def __repr__(self):
        return str(self.result)

    def throw(self):
        return self.result

####

dices = [4, 6, 8, 10, 12, 20]

for dice in dices:
    name = 'D' + str(dice)

    # Create a new dice class
    globals()[name] = type(
        name,
        (AbstractResult,),
        {'min': 1, 'max': dice}
    )

    # Create a new dice object
    globals()[name.lower()] = globals()[name]()

