#pragma once
#include "../game/GameResult.hpp"
#include "../move/Move.hpp"
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
  bool turn;
  std::vector<Move> madeMoves;
  bool threeFoldRepetition;
  void initBoard();

public:
  Board(bool = false);
  Board(bool, bool);
  Board(bool, bool, std::vector<Move>);
  std::shared_ptr<Board> clone() const;
  bool checkPositionInBound(uint8_t, uint8_t) const;
  uint8_t countPiecesByColor(bool) const;
  std::vector<Move> getMoves() const;
  std::vector<Move> getMadeMoves() const;
  bool getTurn() const;
  void makeMove(Move);
  bool isGameOver() const;
  GameResult getGameResult() const;

  Tile &operator()(uint8_t, uint8_t);
  const Tile &operator()(uint8_t, uint8_t) const;
  friend std::ostream &operator<<(std::ostream &, const Board &);
};
