#ifndef __NODE_CPP__
#define __NODE_CPP__

#include "node.h"

Node::Node(Node *prev, int priority, int tile_x, int tile_y, int x_move, int y_move) : priority(priority), depth(depth)
{
    this->depth = prev->getDepth() + 1;

    this->state = prev->getState();
    int check = this->state.moveTile(tile_x, tile_y, x_move, y_move);

    prev->getNext().push_back(this);

    this->appendPath(prev->getPath());
}
Node::~Node()
{
    delete this->prev;
}

int Node::getDepth() const
{
    return this->depth;
}

Node *Node::getPrev() const
{
    return this->prev;
}

std::vector<Node *>& Node::getNext()
{
    return this->next;
}

Puzzle Node::getState()
{
    return this->state;
}

void Node::setPriority(int input)
{
    this->priority = input;
}

const int Node::getPriority() const
{
    return this->priority;
}

bool Node::operator<(const Node &b)
{
    return this->getPriority() < b.getPriority();
}

#endif