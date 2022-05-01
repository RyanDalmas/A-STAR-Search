#ifndef __CL_PARSER_H__
#define __CL_PARSER_H__

#include "puzzle.h"
#include <vector>
#include <string>

class CLParser {

    private:
        std::string Rules; // Copied from rules.txt

    public:
    CLParser();
    ~CLParser();

    // Print to console | how to format string input through CL
    void displayRules();

    // Read puzzle from CL
    const std::vector<int> readPuzzle();

    // Parse and construct Puzzle object
    Puzzle puzzleFactory(int Rows, int Cols, std::vector<int> oVals);

};


#endif