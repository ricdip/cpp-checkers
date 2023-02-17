#include "AI.hpp"

AI::AI(bool color, uint32_t maxDepth)
    : Player(color), maxDepth(maxDepth), algorithm(maxDepth) {}

Board AI::getMove(const Board &board) {
  return algorithm.minmaxAlphaBeta(board, getColor());
}

std::string AI::repr() const {
  std::string reprStr = "AI(";
  reprStr += "color: ";
  reprStr += ((getColor()) ? "WHITE" : "BLACK");
  reprStr += ", maxDepth: ";
  reprStr += (std::to_string(maxDepth));
  reprStr += ")";

  return reprStr;
}
