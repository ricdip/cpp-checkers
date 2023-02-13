#include "Heuristic.hpp"

// TODO: implement heuristics
int Heuristic::h(const Board &board) {
    return gameOverH(board);
}

int Heuristic::gameOverH(const Board &) {
    return 0;
}
