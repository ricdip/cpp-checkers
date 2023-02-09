#pragma once
#include "Pawn.hpp"
#include "Queen.hpp"
#include "Board.hpp"
#include "Move.hpp"
#define WHITE true
#define BLACK false

const char FILES_REPRESENTATION[] = {'A','B','C','D','E','F','G','H'};
const char RANKS_REPRESENTATION[] = {'1','2','3','4','5','6','7','8'};

class Game {
    private:
        std::vector<Move> getPawnMoves(const Board&, const Pawn&, const uint8_t, const uint8_t) const;
        std::vector<Move> getQueenMoves(const Board&, const Queen&, const uint8_t, const uint8_t) const;

        void appendForwardMoves(const Board&, const bool, const uint8_t, const uint8_t, std::vector<Move>&) const;
        void appendBackMoves(const Board&, const bool, const uint8_t, const uint8_t, std::vector<Move>&) const;
        PieceLocation forwardCaptures(const Board&, const bool, const uint8_t, const uint8_t, std::vector<PieceLocation>&) const;
        PieceLocation backCaptures(const Board&, const bool, const uint8_t, const uint8_t, std::vector<PieceLocation>&) const;
    public:
        std::vector<Move> getPieceMoves(const Board&, const uint8_t, const uint8_t) const;
};
