#pragma once
#include "../../board/Board.hpp"

class Algorithm {
private:
  uint32_t maxDepth;
  int32_t minmaxAlphaBetaAux(const Board &, uint32_t, int32_t, int32_t, bool);

public:
  Algorithm(uint32_t);
  Board minmaxAlphaBeta(const Board &, bool);
};
