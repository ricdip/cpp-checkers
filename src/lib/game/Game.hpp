#pragma once
#include "../board/Board.hpp"
#include "../move/Move.hpp"
#include "../piece/pawn/Pawn.hpp"
#include "../piece/queen/Queen.hpp"
#define WHITE true
#define BLACK false

const char FILES_REPRESENTATION[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
const char RANKS_REPRESENTATION[] = {'1', '2', '3', '4', '5', '6', '7', '8'};

class Game {
public:
  static std::vector<Board> neighbors(const Board &);
};
