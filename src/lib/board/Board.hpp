#pragma once
#include "../tile/Tile.hpp"
#include <cstdint>

#define COLS 8
#define ROWS 8

#define A 1
#define B 2
#define C 3
#define D 4
#define E 5
#define F 6
#define G 7
#define H 8

class Board {
private:
  Tile tiles[ROWS][COLS];
  void initBoard();

public:
  Board(bool = false);
  // (rows, colums) = (rank, file) = (1, A)
  bool checkPositionInBound(uint8_t, uint8_t) const;
  uint8_t countPiecesByColor(bool color);

  Tile &operator()(uint8_t, uint8_t);
  const Tile &operator()(uint8_t, uint8_t) const;
  friend std::ostream &operator<<(std::ostream &, const Board &);
};
