import numpy as np


def chunks(lst, n):
    """Yield successive n-sized chunks from lst."""
    for i in range(0, len(lst), n):
        yield lst[i:i + n]


class NotTerminalError(Exception):
    pass


class State:
    def __init__(self, grid, turn):
        self.grid = grid
        self.turn = turn

    def __str__(self):
        r = []
        row = 0
        r.append('   0 1 2   3 4 5   6 7 8')
        for three_lines in chunks(self.grid, 3):
            r.append('   ' + '-'*22)
            for line in three_lines:
                x = []
                for chunk in chunks(line, 3):
                    x.append(' '.join(' ' if i == 0 else str(i)
                                      for i in chunk))
                r.append(str(row) + ' |' + ' | '.join(x) + '|')
                row += 1
        r.append('   ' + '-'*22)
        return '\n'.join(r)


class Game:
    def __init__(self, file_name):
        self.initial_state = self.initalize_game(file_name)

    def initalize_game(self, file_name):
        """
        Initializes the game with given file and returns the initial
        state
        """
        with open(file_name) as f:
            grid = [list(map(int, line.strip().split())) for line in f]

        grid = np.array(grid)
        turn = 'MAX'
        return State(grid, turn)

    def actions(self, grid):
        """
        Returns a dictionary of (coordinate, available_numbers) pairs
        """
        empty_positions = np.argwhere(grid == 0)
        return {(i, j): self._get_available_numbers(grid, i, j)
                for i, j in empty_positions}

    def successors(self, state):
        """
        Yields (action, state) pairs that are reachable from `state`
        """
        available_actions = self.actions(state.grid)
        turn = "MAX" if state.turn == "MIN" else "MIN"
        for (i, j), available_numbers in available_actions.items():
            for num in available_numbers:
                new_grid = np.copy(state.grid)
                new_grid[i][j] = num
                yield ((i, j), num), State(new_grid, turn)

    def is_terminal(self, state):
        """Returns True if the current state is terminal, False otherwise"""
        available_actions = self.actions(state.grid)
        return not any(available_actions.values())

    def utility(self, state):
        """Returns the utility of the state: 1 or -1. Raises  NotTerminalError
        if the state is not terminal state"""
        if not self.is_terminal(state):
            raise NotTerminalError("non terminal state doesn't have any utility")
        return -1 if state.turn == 'MAX' else 1

    @staticmethod
    def _get_box_numbers(grid, i, j):
        """
        Returns available numbers for given position considering only the 3x3
        box around the position
        """
        top, left = i - i % 3, j - j % 3
        available_numbers = set(range(1, 10))
        for i in range(3):
            for j in range(3):
                current_num = grid[top+i][left+j]
                if current_num != 0:
                    available_numbers.remove(current_num)
        return available_numbers

    @staticmethod
    def _get_row_numbers(grid, row_index):
        """
        Returns available numbers for given position considering only the row
        of the position
        """
        return set(range(1, 10)).difference(grid[row_index])

    @staticmethod
    def _get_col_numbers(grid, col_index):
        """
        Returns available numbers for given position considering only the
        column of the position
        """
        return set(range(1, 10)).difference(grid[:, col_index])

    def _get_available_numbers(self, grid, row_index, col_index):
        """ Returns available numbers for given position """
        box = self._get_box_numbers(grid, row_index, col_index)
        row = self._get_row_numbers(grid, row_index)
        col = self._get_col_numbers(grid, col_index)
        return box.intersection(row).intersection(col)


if __name__ == '__main__':
    import sys
    from agents import MiniMax, AlphaBeta

    game = Game(sys.argv[1])
    if len(sys.argv) > 2 and sys.argv[2] == 'm':
        agent = MiniMax(game)
    else:
        agent = AlphaBeta(game)

    print(agent.solve())
