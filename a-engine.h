#ifndef __A_ENGINE_H__
#define __A_ENGINE_H__

#include "puzzle.cpp"
#include "Node.cpp"
#include <string>
#include <fstream>
#include <regex>

class AlgorithmEngine
{

private:
    int (*heuristic)(Puzzle a, Puzzle b);

    std::string selectMenu = "";
    std::string menu_filename = "algorithm_menu.txt";
    std::string input_regex = "^\\d$";

public:
    AlgorithmEngine()
    {

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
    ~AlgorithmEngine() {}

    std::string getMenu()
    {
        return this->selectMenu;
    }

    int checkFormat(std::string input_string) {
        if(!std::regex_match(input_string, std::regex(this->input_regex))) return false;

        return input_string == "1" || input_string == "2" || input_string == "3";
    }

    Node * a_star_search(Puzzle* init_state, Puzzle* goal_state);
    void selectHeuristic();

    // Uniform cost search heuristic
    friend int UCS(Puzzle a, Puzzle b);

    // Misplaced tile heuristic
    friend int MTH(Puzzle a, Puzzle b);

    // Euclidean distance heuristic
    friend int EDH(Puzzle a, Puzzle b);

    friend bool contains(std::vector<Node*> set, Node* input);

    // Print path
    void printPath(Node *head);
};

#endif