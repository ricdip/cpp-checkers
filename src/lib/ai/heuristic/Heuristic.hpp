#pragma once
#include "../../board/Board.hpp"

class Heuristic {
private:
  static int32_t gameOverH(const Board &);

public:
  static int32_t h(const Board &);
};
