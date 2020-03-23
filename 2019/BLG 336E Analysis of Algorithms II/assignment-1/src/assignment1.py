# /usr/bin/python3.8
from typing import List, Set, Dict, Tuple, Optional


class Attack:
    """A class to represent an attack"""

    def __init__(self, name: str, cost: str,
                 accuracy: str, damage: str, first_usage: str):
        """
        :param name: name of the attack
        :param cost: the integer that will be decreased from attacker's pp
        :param accuracy: the probability that the attack will succeed (0-100)
        :param damage: the integer that will be decreased from defender's hp
                       if the attack is succeeded
        :param first_usage: the first round where the attack may be used
        """
        self.name = name
        self.cost = -int(cost)
        self.accuracy = int(accuracy) / 100
        self.inaccuracy = 1 - self.accuracy
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
                if attack.first_usage <= level and attack.cost <= self.power_points]

    def copy(self):
        d = self.__dict__.copy()
        d["name"] = "pikachu" if self.is_pikachu else "blastoise"
        d.pop("is_pikachu")
        return Pokemon(**d)

    def attack(self, opponent: 'Pokemon', attack: Attack, effective: bool):
        """
        Attacks to the opponent with specified attack and do damage
        if effective is True
        """
        self.power_points -= attack.cost
        if effective:
            opponent.health_points -= attack.damage
            if opponent.health_points < 0:
                opponent.health_points = 0

    def __repr__(self):
        name = "pikachu" if self.is_pikachu else "blastoise"
        return f"Pokemon('{name}', {self.health_points}, {self.power_points})"

    def __str__(self):
        i = "P" if self.is_pikachu else "B"
        return f"{i}_HP:{self.health_points} {i}_PP:{self.power_points}"


class Node:
    """A class to represent a state in the game"""
    MAX_LEVEL = -1

    def __init__(self, pokemons: Tuple[Pokemon, Pokemon],
                 probability: float, level: int, is_leaf: bool = True):
        """
        :param pokemons: a pair of Pokemon instances where the next attacker comes
                        first
        :param probability: the probability of encountering this state in the
                            game
        :param level: an integer that shows the level of this state
        :param is_leaf: a boolean that tells if this state is end of game
        """
        self.pokemons = pokemons
        self.attacker, self.defender = pokemons
        self.probability = probability
        self.level = level
        self.is_leaf = is_leaf
        self.children = []

    def create_children(self, verbose=True):
        """Creates children and calls itself recursively on children"""
        if self.level >= Node.MAX_LEVEL:
            if verbose:
                print(self)
            return
        children = []
        if self.attacker.health_points > 0:
            possible_attacks = self.attacker.get_attacks(self.level)
            num_attacks = len(possible_attacks)
            for attack in possible_attacks:
                attacker, defender = self.attacker.copy(), self.defender.copy()
                # Effective
                attacker.attack(defender, attack, effective=True)
                probability = self.probability / num_attacks * attack.accuracy
                node = Node((defender, attacker), probability, self.level + 1)
                children.append(node)

                if attack.accuracy != 1:
                    # Not effective
                    attacker, defender = self.attacker.copy(), self.defender.copy()
                    attacker.attack(defender, attack, effective=False)
                    probability = self.probability / num_attacks * attack.inaccuracy
                    node = Node((defender, attacker), probability, self.level + 1)
                    children.append(node)

        if len(children) > 0:
            self.is_leaf = False
            self.children.extend(children)
            for child in children:
                child.create_children(verbose)

    @staticmethod
    def breadth_first_search(root_node, verbose=False):
        """
        Performs a level order traversal on tree that has root 'root_node' and
        returns number of nodes
        """
        if root_node is None:
            return 0
        node_count = 0
        queue = [root_node]
        while len(queue) > 0:
            node_count += 1
            node = queue.pop(0)
            if verbose:
                print(node)
            queue.extend(node.children)

        return node_count

    @staticmethod
    def depth_first_search(root_node, verbose=False):
        """
        Performs pre order traversal on tree that has root 'root_node' and
        returns number of nodes
        """
        if root_node is None:
            return 0
        node_count = 0
        stack = [root_node]
        while len(stack) > 0:
            node_count += 1
            node = stack.pop()
            if verbose:
                print(node)
            stack.extend(reversed(node.children))
        return node_count

    def __str__(self):
        pikachu_index = 0 if self.pokemons[0].is_pikachu else 1
        blastoise_index = (pikachu_index + 1) % 2
        return " ".join(map(str, (self.pokemons[pikachu_index],
                                  self.pokemons[blastoise_index],
                                  f"PROB:{self.probability:.3f}")))


def main():
    import sys
    import time
    start = time.perf_counter()
    pikachu = Pokemon("pikachu", 273, 100)
    blastoise = Pokemon("blastoise", 361, 100)
    # a = pikachu.copy()
    # print(a == pikachu)
    # print(a.__dict__)
    # print(pikachu.__dict__)
    # print(a.get_attacks(3))
    # print(*pikachu.get_attacks(3), sep="\n")
    # print(*blastoise.get_attacks(0), sep="\n")
    n = Node((pikachu, blastoise), 1.0, 0)
    Node.MAX_LEVEL = int(sys.argv[2])
    # Node.MAX_LEVEL = 3
    if sys.argv[1] == "part1":
        n.create_children()
        # print(n)
    elif sys.argv[1] == "part2":
        n.create_children(verbose=False)

        if sys.argv[3] == "bfs":
            node_count = Node.breadth_first_search(n)
        elif sys.argv[3] == "dfs":
            node_count = Node.depth_first_search(n)
        else:
            raise Exception

        print(f"node count is: {node_count}")
    total = time.perf_counter() - start
    print(f"Took {total:.2f} seconds to execute")


if __name__ == '__main__':
    main()
