#ifndef __MAIN_CPP__
#define __MAIN_CPP__

#include <string>
#include <iostream>
#include "cl-parser.cpp"
#include "puzzle.cpp"
#include <regex>

int main(int argc, char **argv) {

    CLParser* parser = new CLParser();

    Puzzle* puzzle = parser->puzzleFactory(parser->readPuzzle());

    std::cout << std::endl << "Puzzle: " << std::endl;
    puzzle->print();

    std::cout << "\n \n \n \n";
    std::cin.clear();
    system("pause");

    delete puzzle;
    delete parser;

    return 0;
}

#endif