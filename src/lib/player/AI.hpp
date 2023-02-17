#pragma once
#include "../ai/algorithm/Algorithm.hpp"
#include "Player.hpp"

class AI : public Player {
private:
  Algorithm algorithm;

public:
  AI(bool, uint32_t);
  Board getMove(const Board &);
};
