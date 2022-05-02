#ifndef __MAIN_CPP__
#define __MAIN_CPP__

#include <string>
#include <iostream>
#include "cl-parser.cpp"
#include "puzzle.cpp"
#include <regex>
#include "a-engine.cpp"

int main(int argc, char **argv)
{

    CLParser *parser = new CLParser();

    Puzzle *initial_state = parser->puzzleFactory(parser->readPuzzle("Initial", "3 3 1 2 3 4 8 -1 7 6 5|"));

    Puzzle *goal_state = parser->puzzleFactory(parser->readPuzzle("Goal", "3 3 1 2 3 4 5 6 7 8 -1|"));

    AlgorithmEngine engine = AlgorithmEngine();

    while (true)
    {
        Node *path = engine.a_star_search(initial_state, goal_state);

        std::cout << "SOLUTION:" << std::endl;

        initial_state->print();
        std::cout << "- - - - -" << std::endl;
        goal_state->print();

        std::cout << "PATH: " << path->getPath() << std::endl;
        std::cout << "Depth: " << path->getDepth() << std::endl;
        std::cout << "Max Queue: " << path->getMaxQ() << std::endl;
        std::cout << "Nodes Expanded: " << path->getNodeCount() << std::endl;

        system("pause");
    }

    return 0;
}

#endif