#include "Game.hpp"

std::vector<Board> Game::neighbors(const Board &board) {
  std::vector<Board> states = std::vector<Board>();

  std::vector<Move> moves = board.getMoves();
  for (auto it = moves.begin(); it != moves.end(); it++) {
    Board newState = *board.clone();
    newState.makeMove(*it);
    states.push_back(newState);
  }

  return states;
}
