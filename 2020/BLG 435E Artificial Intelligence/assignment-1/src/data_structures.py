import heapq
from collections import deque


class Queue(deque):
    def pop(self, index=-1):
        return self.popleft()


class Stack(list):
    pass


class PriorityQueue:
    def __init__(self, f):
        self.heap = []
        self.f = f

    def append(self, node):
        heapq.heappush(self.heap, (self.f(node), node))

    def pop(self):
        return heapq.heappop(self.heap)[1]

    def __len__(self):
        return len(self.heap)
