#include "AI.hpp"

AI::AI(bool color, uint32_t maxDepth) : Player(color), algorithm(maxDepth) {}

Board AI::getMove(const Board &board) {
  return algorithm.minmaxAlphaBeta(board, getColor());
}
