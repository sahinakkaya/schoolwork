# /usr/bin/python3.8


class Attack:
    def __init__(self, name, cost, accuracy, damage, first_usage):
        self.name = name
        self.cost = int(cost)
        self.accuracy = int(accuracy)
        self.damage = int(damage)
        self.first_usage = int(first_usage)

    def __repr__(self):
        return f"{self.name}, {self.cost}, {self.accuracy}, " \
               f"{self.damage}, {self.first_usage}"


class Pokemon:
    ATTACKS = {"pikachu": [], "blastoise": []}

    def __init__(self, name, health_points, power_points):
        self.health_points = health_points
        self.power_points = power_points
        self.is_pikachu = name == "pikachu"
        if not self.ATTACKS[name]:
            self.ATTACKS[name].extend(self.read_attacks_file(name))

    @staticmethod
    def read_attacks_file(name):
        attacks = []
        with open(name + ".txt") as f:
            f.readline()
            for line in f.readlines():
                attacks.append(Attack(*line.split(",")))
        return attacks

    @property
    def __attacks(self):
        name = "pikachu" if self.is_pikachu else "blastoise"
        return self.ATTACKS[name]

    def get_attacks(self, level):
        return [attack for attack in self.__attacks
                if attack.first_usage <= level]


class Node:
    def __init__(self, pikachu, blastoise, turn,
                 probability, level, is_leaf=True):
        self.pokemons = {"p": pikachu, "b": blastoise}
        self.turn = turn
        self.probability = probability
        self.level = level
        self.is_leaf = is_leaf
        self.children = None


def main():
    pikachu = Pokemon("pikachu", 273, 100)
    blastoise = Pokemon("blastoise", 361, 100)

    print(*pikachu.get_attacks(3), sep="\n")
    print(*blastoise.get_attacks(0), sep="\n")


if __name__ == '__main__':
    main()
