#pragma once
#include "../../board/Board.hpp"

namespace Heuristic {
int32_t Htot(const Board &);
int32_t gameOverH(const GameResult &);
int32_t boardPieceValuesH(const Board &);
}; // namespace Heuristic
