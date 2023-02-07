#pragma once
#include "Tile.hpp"
#include <cstdint>

#define COLS 8
#define ROWS 8

#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7

class Board {
    private:
        Tile tiles[ROWS][COLS];
        void initBoard();
    public:
        Board();
        // (rows, colums) = (rank, file) = (1, A)
        bool checkPositionInBound(uint8_t, uint8_t) const;
        Tile& operator()(uint8_t, uint8_t);
        const Tile& operator()(uint8_t, uint8_t) const;
        friend std::ostream& operator<<(std::ostream&, const Board&);
};
