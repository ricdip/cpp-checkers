#include "../lib/ai/algorithm/Algorithm.hpp"
#include "../lib/board/Board.hpp"

int main() {
  Board state;
  uint32_t maxDepth = 4;
  // uint32_t maxDepth = 6;
  Algorithm ai(maxDepth);

  std::cout << state << std::endl;

  while (!state.isGameOver()) {
    state = ai.minmaxAlphaBeta(state, state.getTurn());
    std::cout << state << std::endl;
  }

  std::cout << state.getGameResult() << std::endl;

  return 0;
}
