#ifndef __NODE_H__
#define __NODE_H__

#include "puzzle.cpp"
#include <vector>

class Node
{
private:
    Puzzle state;
    Node *prev;
    std::vector<Node *> next;

    int depth;

public:
    Node(Node *prev, int tile_x, int tile_y, int x_move, int y_move)
    {
        this->depth = prev->getDepth() + 1;

        this->state = prev->getState();
        this->state.moveTile(tile_x, tile_y, x_move, y_move);
    }
    ~Node() {
        delete this->prev;
    }

    int getDepth() const
    {
        return this->depth;
    }

    Node *getPrev() const
    {
        return this->prev;
    }

    std::vector<Node *> getNext()
    {
        return this->next;
    }

    Puzzle getState()
    {
        return this->state;
    }
};

#endif