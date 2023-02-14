#include "Heuristic.hpp"

// TODO: implement heuristics
int32_t Heuristic::h(const Board &board) { return gameOverH(board); }

int32_t Heuristic::gameOverH(const Board &) { return 0; }
