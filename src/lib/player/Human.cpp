#include "Human.hpp"
#include <iostream>

Human::Human(bool color) : Player(color) {}

Board Human::getMove(const Board &board) {
  std::string moveStr;
  std::cout << "- enter move: ";
  std::cin >> moveStr;

  Board newboard = *board.clone();

  newboard.makeMove(Move(moveStr));

  return newboard;
}
