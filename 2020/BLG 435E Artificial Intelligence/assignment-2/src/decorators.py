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
    def wrapper(self, *args, **kwargs):
        result = f(self, *args, **kwargs)
        nodes_evaluated = self.nodes_evaluated
        template = f'''\
        {f.__name__:-^30}
        Number of nodes evaluated: {nodes_evaluated:,}'''
        print(textwrap.dedent(template))
        return result
    return wrapper
