class Node:
    def __init__(self, state, parent=None, action=None):
        self.state = state
        self.parent = parent
        self.action = action
        self.depth = 0
        if parent:
            self.depth = parent.depth + 1

    @property
    def path_cost(self):
        return self.depth

    def g(self):
        return self.path_cost

    def __repr__(self):
        return "Node <{}>".format(' - '.join(str(i) for i in self.state.agent_positions))

    def __eq__(self, other):
        return self.state == other.state

    def __lt__(self, other):
        return True


def solution(node):
    path = [node.state]
    while node.parent:
        path.append(node.parent.state)
        node = node.parent
    return list(reversed(path))


def child_node(problem, node, action):
    return Node(problem.result(node.state, action), node, action)
