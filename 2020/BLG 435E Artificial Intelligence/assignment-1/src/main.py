import sys
import os
import textwrap
import numpy as np

from collections import defaultdict
from enum import Enum
from functools import partial
from itertools import count, combinations, product
from search_algorithms import bfs, dfs, a_star, heuristic
from visualize import Visualizer


class Action(Enum):
    """An enumeration for all the possible actions"""

    DOWN = (1, 0)
    RIGHT = (0, 1)
    UP = (-1, 0)
    LEFT = (0, -1)
    PASS = (0, 0)

    def __call__(self, x, y):
        """
        Apply action to the arguments
        Action.RIGHT(3, 7) returns (3, 8)
        """
        return x + self.value[0], y + self.value[1]


class Problem:
    """A class to represent the problem"""

    def __init__(self, initial_state, maze, agent_goals):
        self.initial_state = initial_state
        self.maze = maze
        self.agent_goals = agent_goals

    def __str__(self):
        visualizer = Visualizer(self.maze, self.agent_goals)
        return visualizer.prettify_state(self.initial_state)

    def actions(self, state):
        """
        Generate actions that can be performed from the current state
        :param state: the current state
        :return: list of actions (i.e. [((1, 0), (-1, 0)), ((0, 1), (0, 0))])
        """
        agent_positions = state.agent_positions
        possible_positions = [self._get_possible_positions(agent)
                              for agent in agent_positions]
        possible_states = product(*possible_positions)
        actual_states = []
        for ps in possible_states:
            if len(ps) != len(set(ps)):  # if any two agents ends up in the same position
                continue  # discard the state
            elif any(self.walk_through_each_other(a1, a2, ps) 
                     for a1, a2 in combinations(agent_positions, 2)):
                continue  # if any two agents walk through each other, discard the state
            else:
                actual_states.append(ps)
        state_actions = np.array(actual_states) - agent_positions
        return state_actions

    def _get_possible_positions(self, agent_pos):
        """Helper method to get the list of possible positions for an agent"""
        possible_positions = []
        for action in Action:
            x, y = action(*agent_pos)
            if self.maze[x][y] != 'W':
                possible_positions.append((x, y))
        return possible_positions

    @staticmethod
    def walk_through_each_other(a1, a2, l):
        """
        Helper method to check if two agents are walking through each other
        :param a1: agent 1's  position
        :param a2: agent 2's  position
        :param l: a list which holds the positions of the agents after they move
        :return: True if they walk through each other False otherwise
        """
        (x1, y1), (x2, y2) = a1, a2
        if a1 not in l or a2 not in l or abs(x1 - x2)+abs(y1 - y2) != 1:
            return False
        i = l.index(a1)
        j = l.index(a2)
        return j < i

    def result(self, state, action):
        """
        Perform an action on the current state to generate the next state
        :param state: current state
        :param action: action to perform
        :return: a new State object which holds the new positions of the agents
        """
        old_positions = np.array(state.agent_positions)
        action = np.array(action)
        new_positions = old_positions + action
        new_positions = [tuple(item) for item in new_positions.tolist()]
        return State(new_positions)

    def goal_test(self, state):
        """Check if current state is goal state"""
        return self.agent_goals == state.agent_positions

    @staticmethod
    def generate_moves(solution):
        """
        Generate moves from the solution
        :param solution: an iterable that contains all the states of the solution
        :return: an list that contains the moves (i.e. ['DD', 'LR', ...])
        """
        moves = []
        for curr_state, prev_state in zip(solution[1:], solution):
            curr_agent_pos = np.array(curr_state.agent_positions)
            prev_agent_pos = np.array(prev_state.agent_positions)
            action = [tuple(i) 
                      for i in (curr_agent_pos - prev_agent_pos).tolist()]
            moves.append(''.join([Action(i).name[0] for i in action]))

        return moves

    @staticmethod
    def prettify(solution):
        """Print the solution in desired format"""
        moves = Problem.generate_moves(solution)
        num_of_moves = len(moves)
        num_of_agents = len(moves[0])
        r = f'{num_of_moves} {num_of_agents}\n'
        r += '\n'.join(moves)
        return r


class State:
    """A class that represents a state in the problem"""
    def __init__(self, agent_positions):
        self.agent_positions = agent_positions

    def __repr__(self):
        return str(dict(zip(count(1), self.agent_positions)))

    def __eq__(self, other):
        return repr(self) == repr(other)


def formulate_maze_problem(file):
    """Formulate the problem from the input file"""
    maze = parse_file(file)

    agent_positions, agent_goals = get_agent_positions_and_goals(maze)
    if not agent_positions or len(agent_positions) != len(agent_goals):
        return None

    problem = Problem(State(agent_positions), maze, agent_goals)
    return problem


def parse_file(file):
    """Parse the file to create the maze as list of lists"""
    with open(file) as f:
        f.readline()  # skip the first line, we don't need these informations
        maze = []
        for line in f:
            maze.append(line.strip().split('\t'))
        return maze


def get_agent_positions_and_goals(maze):
    agents = defaultdict(dict)
    for i, row in enumerate(maze):
        for j, cell in enumerate(row):
            if cell not in ('W', 'E'):
                char, num = cell
                location = 'pos' if char == 'A' else 'goal'
                agents[num][location] = i, j
                maze[i][j] = 'E'
    positions = []
    goals = []
    # we need to make sure that first agent (A1) comes first
    # dicts have order since python3.7
    agents = dict(sorted(agents.items()))
    for agent_num, agent_info in agents.items():
        positions.append(agent_info['pos'])
        goals.append(agent_info['goal'])
    return positions, goals


def print_possible_actions():
    template = """\
    Possible actions:
     - Perform [D]epth first search
     - Perform [B]readth first search
     - Perform [A]* search
    """
    print(textwrap.dedent(template))


if __name__ == '__main__':
    input_file_name, *rest = sys.argv[1:]
    if rest:
        output_file_name = rest[0]
    else:
        output_file_name = 'output.txt'

    algorithms = {'d': dfs, 'b': bfs, 'a': partial(a_star, h=heuristic)}

    problem = formulate_maze_problem(input_file_name)
    visualizer = Visualizer(problem)
    if problem:
        os.system('clear')
        visualizer.visualize_state(problem.initial_state)
        print_possible_actions()
        option = input('Enter an option: ').lower()
        algorithm = algorithms.get(option) 
        if not algorithm:
            print('Press only the first letter of the algorithm')
            sys.exit(1)
        os.system('clear')
        solution = algorithm(problem)
        if solution:
            visualizer.visualize(solution)
            output = problem.prettify(solution)
            with open(output_file_name, 'w') as f:
                print(output, file=f)
            print(output)
            print(f'Output is written to file {output_file_name}!')

    else:
        print('There is a "problem" with the problem :)')
        sys.exit(1)



