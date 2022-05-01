#ifndef __PUZZLE_CPP__
#define __PUZZLE_CPP__

#include "puzzle.h"
#include <iostream>

Puzzle::Puzzle(int Rows, int Cols) : rows(Rows), cols(Cols)
{
    for (int i = 0; i < this->rows; i++)
    {
        std::vector<int> _temp;

        for (int i = 0; i < this->cols; i++)
        {
            _temp.push_back(-1);
        }

        this->puzzle.push_back(_temp);
    }
}

Puzzle::Puzzle(int Rows, int Cols, std::vector<int> oVals) : rows(Rows), cols(Cols)
{

    for (int i = 0; i < this->rows; i++)
    {
        std::vector<int> _temp;

        for (int i = 0; i < this->cols; i++)
        {
            _temp.push_back(-1);
        }

        this->puzzle.push_back(_temp);
    }

    unsigned int Counter = 0;

    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            if(Counter < oVals.size()) this->setTile(j, i, oVals[Counter++]);
        }
    }
}

const std::vector<std::vector<int>> Puzzle::getPuzzle() const {
    return this->puzzle;
}

int Puzzle::getTile(int tile_x, int tile_y) const
{
    if (tile_x >= 0 && tile_x < this->cols)
    {
        if (tile_y >= 0 && tile_y < this->rows)
        {
            return this->puzzle[tile_y][tile_x];
        }
    }

    return -2; // Out of bounds
}

int Puzzle::setTile(int tile_x, int tile_y, int tile_value)
{
    if (this->getTile(tile_x, tile_y) != -2)
    {
        this->puzzle[tile_y][tile_x] = tile_value;
        return 1;
    }

    return -2;
}

int Puzzle::isValidMove(int tile_x, int tile_y, int move_x, int move_y) const
{
    int tile_value = this->getTile(tile_x, tile_y);
    int tile_dest_value = this->getTile(tile_x + move_x, tile_y + move_y);

    return ((tile_value != -2) && (tile_dest_value != -2)) && ((tile_value == -1) || (tile_dest_value == -1));
}

int Puzzle::moveTile(int tile_x, int tile_y, int move_x, int move_y)
{
    if (!this->isValidMove(tile_x, tile_y, move_x, move_y))
        return 0;

    // Swap tiles
    int temp = this->puzzle[tile_y + move_y][tile_x + move_x];
    this->puzzle[tile_y + move_y][tile_x + move_x] = this->puzzle[tile_y][tile_x];
    this->puzzle[tile_y][tile_x] = temp;

    return 1;
}

void Puzzle::print()
{

    const std::vector<std::vector<int>> p = this->getPuzzle();

    unsigned int max_width = 0;

    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            if(std::to_string(p[i][j]).length() > max_width) max_width = std::to_string(p[i][j]).length();
        }
    }

    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            int curr = p[i][j];

            int buffer = max_width - std::to_string((curr == -1) ? 0 : curr).length();

            for(int k = 0; k < buffer; k++) std::cout << " ";

            (curr == -1) ? std::cout << '*' : std::cout << curr;
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

#endif