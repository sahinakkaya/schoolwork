import numpy as np

from decorators import time_this, set_human_readable_name, report_node_info


class MiniMax:
    def __init__(self, game):
        self.game = game
        self.nodes_evaluated = 0

    def solve(self):
        return self.minimax_decision(self.game.initial_state)

    # uncomment these lines to measure time and number of nodes evaluated
    # @time_this
    # @report_node_info
    # @set_human_readable_name('Standard Mini-Max')
    def minimax_decision(self, state):
        v = self.max_value(state)
        return 1 if v == 1 else 2

    def max_value(self, state):
        if self.game.is_terminal(state):
            return self.game.utility(state)

        v = -np.inf
        for action, state in self.game.successors(state):
            self.nodes_evaluated += 1
            v = max(v, self.min_value(state))
        return v

    def min_value(self, state):
        if self.game.is_terminal(state):
            return self.game.utility(state)

        v = np.inf
        for action, state in self.game.successors(state):
            self.nodes_evaluated += 1
            v = min(v, self.max_value(state))
        return v


class AlphaBeta:
    def __init__(self, game):
        self.game = game
        self.nodes_evaluated = 0

    def solve(self):
        return self.alpha_beta_decision(self.game.initial_state)

    # uncomment these lines to measure time and number of nodes evaluated
    # @time_this
    # @report_node_info
    # @set_human_readable_name('Alpha Beta Pruning')
    def alpha_beta_decision(self, state):
        v = self.max_value(state, -np.inf, np.inf)
        return 1 if v == 1 else 2

    def max_value(self, state, alpha, beta):
        if self.game.is_terminal(state):
            return self.game.utility(state)

        v = -np.inf
        for action, state in self.game.successors(state):
            self.nodes_evaluated += 1
            v = max(v, self.min_value(state, alpha, beta))
            if v >= beta:
                return v
            alpha = max(alpha, v)
        return v

    def min_value(self, state, alpha, beta):
        if self.game.is_terminal(state):
            return self.game.utility(state)

        v = np.inf
        for action, state in self.game.successors(state):
            self.nodes_evaluated += 1
            v = min(v, self.max_value(state, alpha, beta))
            if v <= alpha:
                return v
            beta = min(beta, v)
        return v
