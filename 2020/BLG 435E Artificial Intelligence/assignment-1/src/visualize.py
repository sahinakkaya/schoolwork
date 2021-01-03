from copy import deepcopy
import os
from termcolor import colored


class Visualizer:
    def __init__(self, problem):
        self.maze = deepcopy(problem.maze)
        self.goals = problem.agent_goals

        self.colors = [
                'green', 'red', 'yellow', 'blue',
                'magenta', 'cyan', 'grey', 'white', 'green'
            ]
        for goal_num, position in enumerate(self.goals):
            x, y = position
            self.maze[x][y] = f'G{goal_num+1}'

        for i in range(len(self.maze)):
            for j in range(len(self.maze[0])):
                if i == 0:
                    self.maze[i][j] = str(j)
                elif j == 0:
                    self.maze[i][j] = str(i)

    def prettify_state(self, state):
        current_maze = deepcopy(self.maze)
        for agent_num, position in enumerate(state.agent_positions):
            x, y = position
            if self.goals[agent_num] == (x, y):
                current_maze[x][y] = colored(f'A{agent_num+1}', 'white',
                                             f'on_{self.colors[agent_num]}')
            else:
                current_maze[x][y] = colored(f'A{agent_num+1}',
                                             f'{self.colors[agent_num]}')
        r = []
        for line in current_maze:
            r.append('  '.join((item if item != 'E' else ' ').center(2)
                               for item in line))

        return '\n'.join(r)

    def visualize_state(self, state):
        os.system('clear')
        print(self.prettify_state(state))

    def visualize(self, solution):
        s = input('Press any key to start visualization, press s for skip: ')
        if s.lower() == 's':
            return
        os.system('clear')
        states = []
        for state in solution:
            states.append(self.prettify_state(state))

        i = 0
        warn = False
        while True:
            if i < 0:
                i = 0
                warn = True
            try:
                current_maze = states[i]
            except IndexError:
                break
            print(f'State: {i}/{len(states)-1}')
            print(states[i])

            if warn:
                print("Already at the oldest state!")
            warn = False
            if input('Prev / [N]ext: ').lower() == 'p':
                i -= 1
            else:
                i += 1
            os.system('clear')
