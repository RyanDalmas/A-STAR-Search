#ifndef __A_ENGINE_CPP__
#define __A_ENGINE_CPP__

#include "a-engine.h"

Node *AlgorithmEngine::a_star_search(Puzzle init_state, Puzzle goal_state)
{

}

void AlgorithmEngine::selectHeuristic(int input)
{
    switch(input) {
        default:
        case 1:
            this->heuristic = &UCS;
            break;
        case 2:
            this->heuristic = &MTH;
            break;
        case 3:
            this->heuristic = &EDH;
    }
}

int AlgorithmEngine::UCS(Puzzle a, Puzzle b)
{
    return 0;
}

int AlgorithmEngine::MTH(Puzzle a, Puzzle b)
{
    int misplaced_count = 0;

    // Assuming both puzzles are the same size (they should be)
    for (int i = 0; i < a.getPuzzle().size(); i++)
    {
        for (int j = 0; j < a.getPuzzle()[0].size(); j++)
        {
            if (a.getPuzzle()[i][j] != b.getPuzzle()[i][j])
                misplaced_count++;
        }
    }

    return misplaced_count;
}

int AlgorithmEngine::EDH(Puzzle a, Puzzle b)
{
}

void AlgorithmEngine::printPath(Node *head)
{
}

#endif