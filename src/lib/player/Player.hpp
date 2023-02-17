#pragma once
#include "../board/Board.hpp"

class Player {
private:
  bool color;

public:
  Player(bool);
  bool getColor() const;
  virtual Board getMove(const Board &) = 0;
};
