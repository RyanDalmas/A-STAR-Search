#ifndef __CL_PARSER_CPP__
#define __CL_PARSER_CPP__

#include "cl-parser.h"
#include "puzzle.cpp"
#include <fstream>
#include <iostream>
#include <regex>

CLParser::CLParser()
{
    std::fstream rules_file;
    rules_file.open(this->Rules_FileName, std::ios::in);
    if (rules_file.is_open())
    {
        std::string temp;
        while (std::getline(rules_file, temp))
        {
            this->Rules += temp + "\n";
        }
    }
    rules_file.close();
}

std::string CLParser::getRules()
{
    return this->Rules;
}

int CLParser::checkFormat(std::string InputString)
{

    int regex_check = std::regex_match(InputString, std::regex(this->input_regex));

    if (!regex_check)
        return false;

    puzzle_pieces check_size = this->parsePuzzle(InputString);

    return (check_size.values.size() == (check_size.Cols * check_size.Rows));
}

const std::string CLParser::readPuzzle()
{
    std::string InputString;
    unsigned int invalid_format = 0;

    do
    {
        system("CLS");
        std::cout << this->getRules() << std::endl;

        if (invalid_format)
            std::cout << "(" << invalid_format << ") "
                      << "ERROR: Invalid Format. \n";

        std::cout << "-> ";
        std::cin.clear();
        InputString = "";
        std::getline(std::cin, InputString);

        invalid_format += 1;
    } while (!this->checkFormat(InputString));

    return InputString;
}

puzzle_pieces CLParser::parsePuzzle(const std::string InputString)
{
    puzzle_pieces p;

    // Parse out the following strings
    std::string M, N, oVals;

    std::string c_str = (std::string)InputString;

    // Format already verfied by readPuzzle()

    int first_space = c_str.find(" ");

    M = c_str.substr(0, first_space);
    c_str = c_str.substr(first_space + 1);

    int second_space = c_str.find(" ");

    N = c_str.substr(0, second_space);
    c_str = c_str.substr(second_space + 1);

    oVals = c_str;

    // Cast and build Puzzle object

    p.Cols = std::stoi(M);
    p.Rows = std::stoi(N);

    std::string temp_num = "";

    for (auto i : oVals)
    {
        switch (i)
        {
        case ' ':
        case '|':
            p.values.push_back(std::stoi(temp_num));
            temp_num = "";
            break;
        default:
            temp_num += i;
            break;
        }
    }

    return p;
}

// int Rows, int Cols, std::vector<int> oVals
// input format: "M N [#,#,#,...]"
Puzzle *CLParser::puzzleFactory(const std::string InputString)
{
    puzzle_pieces p = this->parsePuzzle(InputString);

    Puzzle* p_temp = new Puzzle(p.Cols, p.Rows, p.values);
    return p_temp;
}

#endif