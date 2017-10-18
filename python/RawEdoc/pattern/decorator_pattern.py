#
# https://www.codewars.com/kata/patterncraft-decorator/train/python

# TODO getattr

class Marine:
    def __init__(self, damage, armor):
        self.damage = damage
        self.armor = armor

    def __getattr__(self, name):
        if name in self.__dict__:
            return self.__dict__[name]
        else:
            raise AttributeError(name)


class MarineWeaponUpgrade:
    def __init__(self, marine):
        self._marine = marine

    def __getattr__(self, name):
        if name == 'damage':
            return self._marine.damage + 1
        else:
            return self._marine.__getattr__(name)


class MarineArmorUpgrade:
    def __init__(self, marine):
        self._marine = marine

    def __getattr__(self, name):
        if name == 'armor':
            print(self, self._marine, self._marine.armor)
            return self._marine.armor + 1
        else:
            return self._marine.__getattr__(name)

