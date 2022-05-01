#ifndef __CL_PARSER_H__
#define __CL_PARSER_H__

#include "puzzle.h"
#include <vector>
#include <string>

struct puzzle_pieces {
    int Rows;
    int Cols;
    std::vector<int> values;
};

class CLParser {

    private:
        std::string Rules = ""; // Copied from rules.txt
        std::string Rules_FileName = "rules.txt";

        // Regex pattern generated via https://regex-generator.olafneumann.org/
        std::string input_regex = "^(([+-]?(?=\\.\\d|\\d)(?:\\d+)?(?:\\.?\\d*))(?:[eE]([+-]?\\d+))?( ([+-]?(?=\\.\\d|\\d)(?:\\d+)?(?:\\.?\\d*))(?:[eE]([+-]?\\d+))?)+)\\|$";

    public:
    CLParser();
    //~CLParser();

    // Print to console | how to format string input through CL
    std::string getRules();

    // Read puzzle from CL
    const std::string readPuzzle(std::string Context, std::string __DEFAULT__);

    // Validate format of input puzzle string according to rules.txt
    int checkFormat(std::string InputString);

    // Parse puzzle
    puzzle_pieces parsePuzzle(const std::string InputString);

    // Parse and construct Puzzle object
    Puzzle* puzzleFactory(const std::string InputString);

};


#endif