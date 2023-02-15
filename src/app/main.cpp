#include "../lib/ai/algorithm/Algorithm.hpp"
#include "../lib/board/Board.hpp"

int main() {
  Board state = Board();
  Algorithm ai = Algorithm(3);

  std::cout << state << std::endl;
  std::cout << "turn: " << ((state.getTurn()) ? "white" : "black") << "\n";

  while (!state.isGameOver()) {
    state = ai.minmaxAlphaBeta(state, state.getTurn());
    std::cout << state << std::endl;
    std::cout << "turn: " << ((state.getTurn()) ? "white" : "black") << "\n";
  }

  std::cout << "winner: " << ((state.getWinner()) ? "white" : "black")
            << std::endl;

  return 0;
}
