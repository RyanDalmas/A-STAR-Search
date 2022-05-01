#ifndef __NODE_H__
#define __NODE_H__

#include "puzzle.cpp"
#include <vector>

class Node
{
private:
    Puzzle state;
    int priority;
    int depth;

    Node *prev;
    std::vector<Node *> next;
    std::string Steps = "";

public:
    Node();
    Node(Puzzle state, int priority, int depth) : state(state), priority(priority), depth(depth) {}
    Node(Node *prev, int priority, int tile_x, int tile_y, int x_move, int y_move);
    ~Node();

    int getDepth() const;

    Node *getPrev() const;

    std::vector<Node *>& getNext();

    Puzzle getState();

    void appendPath(std::string input) {
        Steps += input;
    }

    std::string getPath() {
        return this->Steps;
    }

    void setPriority(int input);

    const int getPriority() const;

    bool operator<(const Node& b);
 
};

#endif