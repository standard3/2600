from abc import ABC, abstractmethod
import math

class Vehicule:
    def __init__(self, porte: int = 2):
        self.porte = porte

class Animal(Deplacement):
    def __init__(self, patte: int = 4, queue: bool = False):
        self.patte = patte
        self.queue = queue

class Deplacement(ABC):
    @property
    @abstractmethod
    def x(self):
        ...

    @property
    @abstractmethod
    def y(self):
        ...

    @property
    @abstractmethod
    def z(self):
        ...

    @x.setter
    def x(self, x: float):
        self.x = x

    @y.setter
    def y(self, y: float):
        self.y = y

    @z.setter
    def z(self, y: float):
        self.z = z

    @abstractmethod
    def move_to(x: float, y: float, z: float, zone: str):
        ...

class Volant(Deplacement):
    def __init__(self):
        self.x, self.y, self.z = 0.0, 0.0, 0.0

    def move_to(self, x: float, y: float, z: float, zone: str):
        if z < 0: raise ValueError
        self.x, self.y, self.z = x, y, z
        return f"se déplace vers {x}, {y}, {z} en volant"

class Courant(Deplacement):
    def __init__(self):
        self.x, self.y, self.z = 0.0, 0.0, 0.0

    def move_to(self, x: float, y: float, z: float, zone: str):
        if z != 0 or not zone == 'terre': 
            raise ValueError
        
        self.x, self.y, self.z = x, y, z

        return f"se déplace vers {x}, {z} en courant"

class Roulant(Deplacement):
    def __init__(self):
        self.x, self.y, self.z = 0.0, 0.0, 0.0

    def move_to(self, x: float, y: float, z: float, zone: str):
        if z != 0 or not zone == 'terre': 
            raise ValueError
        
        self.x, self.y, self.z = x, y, z

        return f"se déplace vers {x}, {z} en roulant"

class Marchant(Deplacement):
    def __init__(self):
        self.x, self.y, self.z = 0.0, 0.0, 0.0

    def move_to(self, x: float, y: float, z: float, zone: str):
        if z != 0 or not zone == 'terre': 
            raise Exception
        
        self.x, self.y, self.z = x, y, z

        return f"se déplace vers {x}, {z} en marchant"

class Flottant(Deplacement):
    def __init__(self):
        self.x, self.y, self.z = 0.0, 0.0, 0.0

    def move_to(self, x: float, y: float, z: float, zone: str):
        if z != 0 or not zone == 'mer': 
            raise Exception
        
        self.x, self.y, self.z = x, y, z

        return f"se déplace vers {x}, {z} en flottant"

class Nageant(Deplacement):
    def __init__(self):
        self.x, self.y, self.z = 0.0, 0.0, 0.0

    def move_to(self, x: float, y: float, z: float, zone: str):
        if z >= 0 or not zone == 'mer': 
            raise Exception
        
        self.x, self.y, self.z = x, y, z

        return f"se déplace vers {x}, {y}, {z} en nageant"

class Humain(Animal, Courant, Marchant, Flottant, Nageant):
    def __init__(self):
        Animal.__init__(self, patte=2, queue=False)
        self.x, self.y, self.z = 0.0, 0.0, 0.0
        
    def move_to(self, x: float, y: float, z: float, zone: str):
        dist = math.dist((self.x, self.y, self.z), (x, y, z))

        if zone == "terre":
            if dist >= 2.0 and dist <= 10.0:
                Courant.move_to(self, x, y, z, zone=zone)
            else:            
                Marchant.move_to(self, x, y, z, zone=zone)
        elif zone == "mer":
            Flottant.move_to(self, x, y, z, zone=zone)
            # todo: gérer nageant

class VoitureSansPermis(Vehicule, Roulant):
    def __init__(self):
        Vehicule.__init__(self, porte=2)
        self.x, self.y, self.z = 0.0, 0.0, 0.0

    def move_to(self, x: float, y: float, z: float, zone: str):
        Roulant.move_to(self, x, y, z, zone=zone)

class Berline(Vehicule, Roulant):
    def __init__(self):
        Vehicule.__init__(self, porte=4)
        self.x, self.y, self.z = 0.0, 0.0, 0.0

    def move_to(self, x: float, y: float, z: float, zone: str):
        Roulant.move_to(self, x, y, z, zone=zone)

class Moto(Vehicule, Roulant):
    def __init__(self):
        Vehicule.__init__(self, porte=0)
        self.x, self.y, self.z = 0.0, 0.0, 0.0

    def move_to(self, x: float, y: float, z: float, zone: str):
        Roulant.move_to(self, x, y, z, zone=zone)

class Hors_Bord(Vehicule, Flottant):
    def __init__(self):
        Vehicule.__init__(self, porte=0)
        self.x, self.y, self.z = 0.0, 0.0, 0.0

    def move_to(self, x: float, y: float, z: float, zone: str):
        Flottant.move_to(self, x, y, z, zone=zone)

class Spitfire(Vehicule, Volant, Flottant):
    def __init__(self):
        Vehicule.__init__(self, porte=0)
        self.x, self.y, self.z = 0.0, 0.0, 0.0

    def move_to(self, x: float, y: float, z: float, zone: str):
        if zone == "mer":
            Flottant.move_to(self, x, y, z, zone=zone)
        else:
            Volant.move_to(self, x, y, z, zone=zone)

class Cygne(Animal, Volant, Flottant, Nageant):
    def __init__(self):
        Animal.__init__(self, patte=2, queue=True)
        self.x, self.y, self.z = 0.0, 0.0, 0.0

    def move_to(self, x: float, y: float, z: float, zone: str):
        if zone == "mer":
            if y == 0:
                Flottant.move_to(self, x, y, z, zone=zone)
            else:
                Nageant.move_to(self, x, y, z, zone=zone)
        else:
            Volant.move_to(self, x, y, z, zone=zone)

class Canard(Animal, Volant, Flottant, Nageant, Marchant):
    def __init__(self):
        Animal.__init__(self, patte=2, queue=True)
        self.x, self.y, self.z = 0.0, 0.0, 0.0

    def move_to(self, x: float, y: float, z: float, zone: str):
        if zone == "mer":
            if y == 0:
                Flottant.move_to(self, x, y, z, zone=zone)
            else:
                Nageant.move_to(self, x, y, z, zone=zone)
        elif zone == "terre":
            Marchant.move_to(self, x, y, z, zone=zone)
        else:
            Volant.move_to(self, x, y, z, zone=zone)

class Poisson(Animal, Nageant):
    def __init__(self):
        Animal.__init__(self, patte=0, queue=True)
        self.x, self.y, self.z = 0.0, 0.0, 0.0

    def move_to(self, x: float, y: float, z: float, zone: str):
        Nageant.move_to(self, x, y, z, zone=zone)