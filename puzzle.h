#ifndef __PUZZLE_H__
#define __PUZZLE_H__

#include <vector>

class Puzzle {
    private:
        // Puzzle represented as 2D Vector
        int rows, cols;
        std::vector<std::vector<int>> puzzle;

    public:
        Puzzle() {}
        // Initialize a blank (all -1's) M x N puzzle
        Puzzle(int Rows, int Cols);
        // Initialize a specific puzzle
        Puzzle(int Rows, int Cols, std::vector<int> oVals);

        //~Puzzle();

        // Returns unchangeable copy of puzzle
        const std::vector<std::vector<int>> getPuzzle() const ;

        void print();

        // Returns value of tile via coordinates
        int getTile(int tile_x, int tile_y) const ;

        // If valid tile, set new value, return value (return -2 if invalid)
        int setTile(int tile_x, int tile_y, int tile_value);

        // Returns 1 (TRUE) if input move is legal, 0 (FALSE) if not
        int isValidMove(int tile_x, int tile_y, int move_x, int move_y) const ;

        // Checks fror valid move, if valid -> perform move
        int moveTile(int tile_x, int tile_y, int move_x, int move_y);

        bool eq(Puzzle& a) const {
            return this->getPuzzle() == a.getPuzzle();
        }
        
};

#endif