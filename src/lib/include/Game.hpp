#pragma once
#include <cstdint>
#include <vector>
#include "Pawn.hpp"
#include "Queen.hpp"
#include "Board.hpp"
#include "Move.hpp"
#define WHITE true
#define BLACK false

const char FILES_REPRESENTATION[] = {'A','B','C','D','E','F','G','H'};
const char RANKS_REPRESENTATION[] = {'0','1','2','3','4','5','6','7'};

class Game {
    private:
        std::vector<Move> getPawnMoves(const Board&, const Pawn&, const uint8_t, const uint8_t);
        std::vector<Move> getQueenMoves(const Board&, const Queen&, const uint8_t, const uint8_t);
    public:
        std::vector<Move> getPieceMoves(const Board&, const uint8_t, const uint8_t);
};
