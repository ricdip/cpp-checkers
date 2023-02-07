#include "../lib/include/Game.hpp"
#include <iostream>

int main() {
  Board a = Board();
  std::cout << a << std::endl;
  //Move m = Move(A, 1, C, 1);

  std::cout << a(A, 8) << std::endl;

  Game g = Game();
  g.getPieceMoves(a, A, 8);

  std::cout << "Hello World!" << std::endl;
  return 0;
}
