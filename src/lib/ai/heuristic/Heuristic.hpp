#pragma once
#include "../../board/Board.hpp"

// TODO: implement heuristics
class Heuristic {
private:
    static int gameOverH(const Board &);
public:
    static int h(const Board &);
};
