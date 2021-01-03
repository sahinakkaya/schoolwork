import numpy as np
def chunks(l, n):
    """Yield successive n-sized chunks from lst."""
    n = max(1, n)
    return (l[i:i+n] for i in range(0, len(l), n))


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
        with open(file_name) as f:
            grid = [list(map(int, line.strip().split())) for line in f]

        grid = np.array(grid)
        turn = 'MAX'
        return State(grid, turn)

    def successors(self, state):
        """
        Returns a dictionary of (coordinate, available_numbers) pairs
        """
        empty_positions = np.argwhere(state.grid == 0)
        return {(i, j): self._get_available_numbers(state.grid, i, j)
                for i, j in empty_positions}

    def is_terminal(self, state):
        """Returns True if the current state is terminal, False otherwise"""
        available_actions = self.successors(state)
        return not any(available_actions.values())

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
    game = Game(sys.argv[1])
    print(game.initial_state)
