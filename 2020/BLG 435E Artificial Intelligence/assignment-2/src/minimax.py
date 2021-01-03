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
        for three_lines in chunks(self.grid, 3):
            r.append('-'*21)
            for line in three_lines:
                x = []
                for chunk in chunks(line, 3):
                    x.append(' '.join(' ' if i == 0 else str(i)
                                      for i in chunk))
                r.append(' | '.join(x))
        r.append('-'*21)
        return '\n'.join(r)


class Game:
    def __init__(self, file_name):
        self.initial_state = self.initalize_game(file_name)

    def initalize_game(self, file_name):
        with open(file_name) as f:
            grid = [list(map(int, line.strip().split())) for line in f]

        turn = 'MAX'
        return State(grid, turn)


if __name__ == '__main__':
    import sys
    game = Game(sys.argv[1])
    print(game.initial_state)
