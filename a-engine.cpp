#ifndef __A_ENGINE_CPP__
#define __A_ENGINE_CPP__

#include "a-engine.h"
#include <cmath>
#include <queue>
#include <vector>

bool contains(std::vector<Node *> set, Node *input)
{
    for (int i = 0; i < set.size(); i++)
    {
        if (set[i]->getState().getPuzzle() == input->getState().getPuzzle())
            return true;
    }
    return false;
}

Node *AlgorithmEngine::a_star_search(Puzzle *init_state, Puzzle *goal_state)
{
    this->selectHeuristic();

    std::priority_queue<Node *, std::vector<Node*>, std::greater<Node*>> frontier;

    std::vector<Node *> explored_set, solution_set, f_set;

    Node *head = new Node(*init_state, this->heuristic(*init_state, *goal_state), 0);

    frontier.push(head);
    f_set.push_back(head);

    int minDepth = INT_MAX;

    bool DEBUG = 0;

    std::cout << "Initial State: " << std::endl;
    init_state->print();

    std::cout << "Goal State: " << std::endl;
    goal_state->print();

    system("pause");

    if (DEBUG)
        std::cout << "Algorithm Initialized. Loop will begin." << std::endl;

    do
    {
        std::cout << "\rComputing";

        for(int i = 0; i < frontier.size()%5; i++) std::cout << ".";

        if (frontier.empty())
        {
            if (DEBUG)
                std::cout << "Frontier is empty, failed." << std::endl;
            return nullptr;
        }

        //std::cout << "Frontier Size: " << frontier.size() << " | " << solution_set.size() << std::endl;
        

        Node *leaf = frontier.top();
        frontier.pop();
        
        for(int i = 0; i < f_set.size(); i++) {
            if(f_set[i]->getState().getPuzzle() == leaf->getState().getPuzzle())
                f_set.erase(f_set.begin()+i);
        }

        if (DEBUG)
            std::cout << "Frontier popped." << std::endl;

        if (leaf->getState().eq(*goal_state))
        {
            solution_set.push_back(leaf);
            if(leaf->getDepth() <= minDepth) minDepth = leaf->getDepth();
            if (DEBUG)
                std::cout << "Goal state found." << std::endl;
        }
        explored_set.push_back(leaf);

        // Expand Node and add new nodes to frontier

        // Find coordinates of empty square
        Puzzle temp = leaf->getState();
        if (DEBUG)
            temp.print();
        int x, y;

        for (int i = 0; i < temp.getPuzzle().size(); i++)
        {
            for (int j = 0; j < temp.getPuzzle()[0].size(); j++)
            {
                if (temp.getPuzzle()[i][j] == -1)
                {
                    x = j;
                    y = i;
                    if (DEBUG)
                        std::cout << "* located at (" << x << ", " << y << ")" << std::endl;
                    break;
                }
            }
        }

        if (temp.isValidMove(x, y, -1, 0)) // MOVE RIGHT (MOVE STAR LEFT)
        {
            int p = heuristic(leaf->getState(), *goal_state);
            Node *t = new Node(leaf, p + leaf->getDepth() + 1, x, y, -1, 0);

            if (!contains(explored_set, t) && !contains(f_set, t) && leaf->getDepth() <= minDepth)
            {
                frontier.push(t);
                t->appendPath("<, ");
                if (DEBUG)
                    std::cout << "MOVE RIGHT." << std::endl;
            }
        }

        if (temp.isValidMove(x, y, 1, 0)) // MOVE LEFT (MOVE STAR RIGHT)
        {
            int p = heuristic(leaf->getState(), *goal_state);
            Node *t = new Node(leaf, p + leaf->getDepth() + 1, x, y, 1, 0);

            if (!contains(explored_set, t) && !contains(f_set, t) && leaf->getDepth() <= minDepth)
            {
                frontier.push(t);
                t->appendPath(">, ");
                if (DEBUG)
                    std::cout << "MOVE LEFT." << std::endl;
            }
        }

        if (temp.isValidMove(x, y, 0, 1)) // MOVE UP (MOVE STAR DOWN)
        {
            int p = heuristic(leaf->getState(), *goal_state);
            Node *t = new Node(leaf, p + leaf->getDepth() + 1, x, y, 0, 1);

            if (!contains(explored_set, t) && !contains(f_set, t) && leaf->getDepth() <= minDepth)
            {
                frontier.push(t);
                t->appendPath("v, ");
                if (DEBUG)
                    std::cout << "MOVE UP." << std::endl;
            }
        }

        if (temp.isValidMove(x, y, 0, -1)) // MOVE DOWN (MOVE STAR UP)
        {
            int p = heuristic(leaf->getState(), *goal_state);
            Node *t = new Node(leaf, p + leaf->getDepth() + 1, x, y, 0, -1);

            if (!contains(explored_set, t) && !contains(f_set, t) && leaf->getDepth() <= minDepth)
            {
                frontier.push(t);
                t->appendPath("^, ");
                if (DEBUG)
                    std::cout << "MOVE DOWN." << std::endl;
            }
        }

        if (DEBUG)
            std::cout << leaf->getNext().size() << " nodes expanded." << std::endl;

    } while (!frontier.empty());

    system("CLS");

    if (DEBUG)
        std::cout << "Loop terminated." << std::endl;

    if (solution_set.empty())
    {
        if (DEBUG)
            std::cout << "No solution located. Failure." << std::endl;
        return nullptr;
    }

    Node *minNode = solution_set[0];
    int minD = solution_set[0]->getDepth();

    for (int i = 1; i < solution_set.size(); i++)
    {
        if (solution_set[i]->getDepth() < minD)
        {
            minD = solution_set[i]->getDepth();
            minNode = solution_set[i];
        }
    }
    if (DEBUG)
        std::cout << "Solution located, returning..." << std::endl;

    return minNode;
}

int UCS(Puzzle a, Puzzle b)
{
    return 0;
}

int MTH(Puzzle a, Puzzle b)
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

int EDH(Puzzle a, Puzzle b)
{
    int run_sum = 0;

    for (int i = 0; i < a.getPuzzle().size(); i++)
    {
        for (int j = 0; j < a.getPuzzle()[0].size(); j++)
        {
            for (int _i = 0; _i < b.getPuzzle().size(); _i++)
            {
                for (int _j = 0; _j < b.getPuzzle()[0].size(); _j++)
                {
                    if (a.getPuzzle()[i][j] == b.getPuzzle()[_i][_j])
                        run_sum += std::pow(_i - i, 2) + std::pow(_j - j, 2);
                }
            }
        }
    }

    return std::sqrt(run_sum);
}

void AlgorithmEngine::selectHeuristic()
{
    std::string input = "";
    unsigned int invalid_format = 0;

    do
    {
        system("CLS");
        std::cout << this->getMenu() << std::endl;

        if (invalid_format)
            std::cout << "(" << invalid_format << ") "
                      << "ERROR: Invalid Format. \n";

        std::cout << "-> ";
        std::cin.clear();
        std::cin >> input;

        invalid_format += 1;
    } while (!this->checkFormat(input));

    switch (std::stoi(input))
    {
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

void AlgorithmEngine::printPath(Node *tail)
{
}

#endif