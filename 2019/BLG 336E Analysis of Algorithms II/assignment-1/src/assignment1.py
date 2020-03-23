# /usr/bin/python3.8


class Attack:
    """A class to represent an attack"""

    def __init__(self, name: str, cost: str,
                 accuracy: str, damage: str, first_usage: str):
        """
        :param name: name of the attack
        :param cost: the integer that will be decreased from attacker's pp
        :param accuracy: the probability that the attack will succeed
        :param damage: the integer that will be decreased from defender's hp
                       if the attack is succeeded
        :param first_usage: the first round where the attack may be used
        """
        self.name = name
        self.cost = int(cost)
        self.accuracy = int(accuracy)
        self.damage = int(damage)
        self.first_usage = int(first_usage)

    def __repr__(self):
        return f"{self.name}, {self.cost}, {self.accuracy}, " \
               f"{self.damage}, {self.first_usage}"


class Pokemon:
    """A class to represent pokemons"""
    ATTACKS = {"pikachu": [], "blastoise": []}

    def __init__(self, name: str, health_points: int, power_points: int):
        """
        :param name: name of the pokemon, either 'pikachu' or 'blastoise'
        :param health_points: the integer that holds the initial HP of pokemon
        :param power_points: the integer that holds the initial PP of pokemon
        """
        self.health_points = health_points
        self.power_points = power_points
        self.is_pikachu = name == "pikachu"
        assert name in ("pikachu", "blastoise"), \
            "name of the pokemon should be 'pikachu' or 'blastoise'"
        if not self.ATTACKS[name]:
            self.ATTACKS[name].extend(self.__read_attacks_file(name))

    @staticmethod
    def __read_attacks_file(name):
        """
        Reads attacks file for pokemon specified by name and returns
        list of attacks that the pokemon can do
        """
        with open(name + ".txt") as f:
            f.readline()
            return [Attack(*line.split(",")) for line in f.readlines()]

    @property
    def __attacks(self):
        """Returns list of all attacks that the pokemon can do"""
        name = "pikachu" if self.is_pikachu else "blastoise"
        return self.ATTACKS[name]

    def get_attacks(self, level: int):
        """
        Takes an integer, level, and returns possible attacks for
        that level
        """
        return [attack for attack in self.__attacks
                if attack.first_usage <= level]


class Node:
    """A class to represent a state in the game"""

    def __init__(self, pikachu: Pokemon, blastoise: Pokemon, turn: str,
                 probability: float, level: int, is_leaf: bool = True):
        """

        :param pikachu: a Pokemon instance that holds the values for pikachu
                        in this state
        :param blastoise: a Pokemon instance that holds the values for
                        blastoise in this state
        :param turn: the initial of the pokemon who will play next
        :param probability: the probability of encountering this state in the
                            game
        :param level: an integer that shows the level of this state
        :param is_leaf: a boolean that tells if this state is end of game
        """
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
