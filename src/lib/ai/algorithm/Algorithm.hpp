#pragma once
#include "../../board/Board.hpp"

// TODO: implement algorithm
class Algorithm {
private:
    int maxDepth;
public:
    Algorithm(int);
    Board &minmaxAlphaBeta(const Board&, bool);
};
