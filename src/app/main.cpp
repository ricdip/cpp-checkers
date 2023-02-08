#include "../lib/include/Game.hpp"
#include <iostream>
#include <vector>

int main() {
  Board a = Board();
  std::cout << a << std::endl;

  Game g = Game();
  std::vector<Move> moves = g.getPieceMoves(a, C, 6);
  for(auto it = moves.begin(); it != moves.end(); it++) {
      std::cout << *it << " ";
  }
  std::cout << std::endl;

  std::cout << "Hello World!" << std::endl;
  return 0;
}
