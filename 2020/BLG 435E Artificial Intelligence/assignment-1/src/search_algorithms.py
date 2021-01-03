from data_structures import PriorityQueue, Stack, Queue
from decorators import report_node_info, time_this, set_human_readable_name
from node import Node, child_node, solution


@time_this
@report_node_info
@set_human_readable_name('Breadth first search')
def bfs(problem):
    return uninformed_search(problem, frontier=Queue)


@time_this
@report_node_info
@set_human_readable_name('Depth first search')
def dfs(problem):
    return uninformed_search(problem, frontier=Stack)


@time_this
@report_node_info
@set_human_readable_name('A*')
def a_star(problem, h):
    def f(node):
        return node.g() + h(node, problem.agent_goals)
    return best_first_search(problem, f)


def uninformed_search(problem, frontier):
    nodes_generated = max_nodes_in_memory = 1
    nodes_expanded = 0
    node = Node(problem.initial_state)

    if problem.goal_test(node.state):
        nodes_info = [nodes_generated, nodes_expanded, max_nodes_in_memory]
        return solution(node), nodes_info
    frontier = frontier([node])
    explored = set()

    while frontier:
        node = frontier.pop()
        explored.add(repr(node.state))
        nodes_expanded += 1
        for action in problem.actions(node.state):
            child = child_node(problem, node, action)
            nodes_generated += 1
            if repr(child.state) not in explored:
                explored.add(repr(child.state))
                if problem.goal_test(child.state):
                    nodes_info = [nodes_generated, nodes_expanded, max_nodes_in_memory]
                    return solution(child), nodes_info
                frontier.append(child)
        # print(*frontier, sep='\n')
        # input()
        nodes_in_memory = len(frontier) + len(explored)
        if nodes_in_memory > max_nodes_in_memory:
            max_nodes_in_memory = nodes_in_memory
    nodes_info = [nodes_generated, nodes_expanded, max_nodes_in_memory]
    return None, nodes_info  # we couldn't find a solution


def best_first_search(problem, f):
    node = Node(problem.initial_state)
    frontier = PriorityQueue(f)
    explored = set()
    frontier.append(node)
    nodes_generated = max_nodes_in_memory = 1
    nodes_expanded = 0
    while frontier:
        node = frontier.pop()
        nodes_expanded += 1
        if problem.goal_test(node.state):
            nodes_info = [nodes_generated, nodes_expanded, max_nodes_in_memory]
            return solution(node), nodes_info
        else:
            for action in problem.actions(node.state):
                nodes_generated += 1
                child = child_node(problem, node, action)
                if repr(child.state) not in explored:
                    explored.add(repr(child.state))
                    frontier.append(child)
        nodes_in_memory = len(frontier) + len(explored)
        if nodes_in_memory > max_nodes_in_memory:
            max_nodes_in_memory = nodes_in_memory
    nodes_info = [nodes_generated, nodes_expanded, max_nodes_in_memory]
    return None, nodes_info  # we couldn't find a solution


def heuristic(node, agent_goals):
    """
    Calculate the manhattan distance from agent locations to 
    their goal and return the max of them
    """
    distances = []
    for agent_pos, agent_goal in zip(node.state.agent_positions, agent_goals):
        (x1, y1), (x2, y2) = agent_pos, agent_goal
        dist = abs(x1-x2) + abs(y1 - y2)
        distances.append(dist)
    return max(distances)
