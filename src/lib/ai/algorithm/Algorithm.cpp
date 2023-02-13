#include "Algorithm.hpp"

Algorithm::Algorithm(int depth) : maxDepth(depth) {}

// TODO: implement algorithm
Board &Algorithm::minmaxAlphaBeta(const Board& board, bool turn) {
    return *board.clone();
}
