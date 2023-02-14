#pragma once
#include "../../board/Board.hpp"

class Algorithm {
private:
  int32_t maxDepth;
  int32_t minmaxAlphaBetaAux(const Board &, int32_t, int32_t, int32_t, bool);

public:
  Algorithm(int32_t);
  Board &minmaxAlphaBeta(const Board &, bool);
};
