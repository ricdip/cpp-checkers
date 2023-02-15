#include "../lib/ai/algorithm/Algorithm.hpp"
#include "../lib/board/Board.hpp"

int main() {
  Board state = Board();
  Algorithm ai = Algorithm(3);

  std::cout << state << "\n\n";

  while (!state.isGameOver()) {
    state = ai.minmaxAlphaBeta(state, state.getTurn());
    std::cout << state << "\n\n";
  }

  std::cout << "winner: " << ((state.getWinner()) ? "white" : "black")
            << "\n\n";

  return 0;
}
