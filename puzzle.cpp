#ifndef __PUZZLE_CPP__
#define __PUZZLE_CPP__

#include "puzzle.h";

Puzzle::Puzzle(int Rows, int Cols)
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

Puzzle::Puzzle(int Rows, int Cols, std::vector<int> oVals)
{

    unsigned int Counter = 0;

    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            this->setTile(i, j, oVals[Counter++]);
        }
    }
}

Puzzle::~Puzzle()
{
    
}

int Puzzle::getTile(int tile_x, int tile_y) const
{
    if (tile_x >= 0 && tile_x < this->cols)
    {
        if (tile_y >= 0 && tile_y < this->rows)
        {
            return this->puzzle[tile_x][tile_y];
        }
    }

    return -2; // Out of bounds
}


int Puzzle::isValidMove(int tile_x, int tile_y, int move_x, int move_y) const
{
    int tile_value = this->getTile(tile_x, tile_y);
    int tile_dest_value = this->getTile(tile_x + move_x, tile_y + move_y);

    return (tile_value != -2) && (tile_dest_value == -1);
}

int Puzzle::moveTile(int tile_x, int tile_y, int move_x, int move_y)
{
    if(!this->isValidMove(tile_x, tile_y, move_x, move_y)) return 0;

    // Swap tiles
    this->puzzle[tile_x + move_x][tile_y + move_y] = this->puzzle[tile_x][tile_y]; 
    this->puzzle[tile_x][tile_y] = -1;

    return 1;
}

#endif