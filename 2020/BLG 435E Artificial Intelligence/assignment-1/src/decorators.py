import textwrap
from timeit import default_timer
from functools import wraps


def time_this(f):
    @wraps(f)
    def wrapper(*args, **kwargs):
        t = default_timer()
        result = f(*args, **kwargs)
        t = default_timer() - t
        print(f'Took {t:.3f} seconds to complete\n')
        return result
    return wrapper


def set_human_readable_name(new_name):
    def decorator(f):
        f.__name__ = new_name
        return f
    return decorator


def report_node_info(f):
    @wraps(f)
    def wrapper(*args, **kwargs):
        result, nodes_info = f(*args, **kwargs)
        nodes_generated, nodes_expanded, max_nodes_in_memory = nodes_info
        solution = f"exists ({len(result) - 1} steps)" if result else "doesn't exist"
        template = f'''\
        {f.__name__:-^30}
        Solution: {solution}
        Nodes generated: {nodes_generated:,}
        Nodes expanded: {nodes_expanded:,}
        Max nodes in memory: {max_nodes_in_memory:,}'''
        print(textwrap.dedent(template))
        return result
    return wrapper
