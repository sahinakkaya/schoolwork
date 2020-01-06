#include "node.h"
Node::Node(colors c = red) {
    color = c;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    size = 1;
}

int Node::key() const{
    return data.get_size();
}