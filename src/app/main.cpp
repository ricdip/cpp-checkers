#include "../lib/include/Board.hpp"
#include "../lib/include/Game.hpp"
#include "../lib/include/Piece.hpp"
#include "../lib/include/Move.hpp"
#include <iostream>

int main() {
  Board a = Board();
  std::cout << a << std::endl;
  //Move m = Move(A, 1, C, 1);

  std::cout << a(A, 8) << std::endl;

  std::cout << "Hello World!" << std::endl;
  return 0;
}
