#ifndef __A_ENGINE_H__
#define __A_ENGINE_H__

#include "puzzle.cpp"
#include "Node.cpp"
#include <string>
#include <fstream>

class AlgorithmEngine
{

private:
    int (AlgorithmEngine::*heuristic)(Puzzle a, Puzzle b);
    std::string selectMenu = "";
    std::string menu_filename = "algorithm_menu.txt";

public:
    AlgorithmEngine()
    {
        this->selectHeuristic(0);

        std::fstream menu_file;
        menu_file.open(this->menu_filename, std::ios::in);
        if (menu_file.is_open())
        {
            std::string temp;
            while (std::getline(menu_file, temp))
            {
                this->selectMenu += temp + "\n";
            }
        }
        menu_file.close();
    }
    ~AlgorithmEngine();

    Node *a_star_search(Puzzle init_state, Puzzle goal_state);
    void selectHeuristic(int input);

    // Uniform cost search heuristic
    int UCS(Puzzle a, Puzzle b);

    // Misplaced tile heuristic
    int MTH(Puzzle a, Puzzle b);

    // Euclidean distance heuristic
    int EDH(Puzzle a, Puzzle b);

    // Print path
    void printPath(Node *head);
};

#endif