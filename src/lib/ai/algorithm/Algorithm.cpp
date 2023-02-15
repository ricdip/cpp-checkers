#include "Algorithm.hpp"
#include "../../game/Game.hpp"
#include "../heuristic/Heuristic.hpp"

Algorithm::Algorithm(uint32_t depth) {
  if (depth == 0) {
    throw std::runtime_error("Illegal initial algorithm max depth");
  }
  maxDepth = depth;
}

// MinMax Alpha-Beta (fail-hard implementation)
int32_t Algorithm::minmaxAlphaBetaAux(const Board &board, uint32_t depth,
                                      int32_t alpha, int32_t beta, bool turn) {
  if (depth == 0 || board.isGameOver()) {
    return Heuristic::Htot(board);
  }
  if (turn) {
    // max player = WHITE
    int32_t value = INT32_MIN;
    std::vector<Board> children = Game::neighbors(board);
    for (auto child = children.begin(); child != children.end(); child++) {
      value = std::max(
          value, minmaxAlphaBetaAux(*child, depth - 1, alpha, beta, BLACK));
      if (value > beta) {
        // beta cutoff
        break;
      }
      alpha = std::max(alpha, value);
    }
    return value;
  } else {
    // min player = BLACK
    int32_t value = INT32_MAX;
    std::vector<Board> children = Game::neighbors(board);
    for (auto child = children.begin(); child != children.end(); child++) {
      value = std::min(
          value, minmaxAlphaBetaAux(*child, depth - 1, alpha, beta, WHITE));
      if (value < alpha) {
        // alpha cutoff
        break;
      }
      beta = std::min(beta, value);
    }
    return value;
  }
}

Board Algorithm::minmaxAlphaBeta(const Board &board, bool turn) {
  // always first call with alpha = -infty, beta = +infty
  int32_t alpha = INT32_MIN;
  int32_t beta = INT32_MAX;

  std::vector<Board> children = Game::neighbors(board);

  int32_t bestStateValue = (turn) ? INT32_MIN : INT32_MAX;
  Board &bestState = children[0];

  if (turn) {
    // max player = WHITE
    for (auto child = children.begin(); child != children.end(); child++) {
      int32_t value =
          minmaxAlphaBetaAux(*child, maxDepth - 1, alpha, beta, BLACK);
      if (value > bestStateValue) {
        bestStateValue = value;
        bestState = *child;
      }
      alpha = std::max(alpha, value);
    }
  } else {
    // min player = BLACK
    for (auto child = children.begin(); child != children.end(); child++) {
      int32_t value =
          minmaxAlphaBetaAux(*child, maxDepth - 1, alpha, beta, WHITE);
      if (value < bestStateValue) {
        bestStateValue = value;
        bestState = *child;
      }
      beta = std::min(beta, value);
    }
  }

  return bestState;
}
