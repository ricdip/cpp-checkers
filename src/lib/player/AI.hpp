#pragma once
#include "../ai/algorithm/Algorithm.hpp"
#include "Player.hpp"

class AI : public Player {
private:
  uint32_t maxDepth;
  Algorithm algorithm;

public:
  AI(bool, uint32_t);
  Board getMove(const Board &);
  std::string repr() const;
};
