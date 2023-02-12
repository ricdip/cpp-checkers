#pragma once
#include "../../game/Game.hpp"

class MoveGenerator {
private:
  static std::vector<Move> getPawnMoves(const Board &, const Pawn &,
                                        const uint8_t, const uint8_t);
  static std::vector<Move> getQueenMoves(const Board &, const Queen &,
                                         const uint8_t, const uint8_t);

  static void appendForwardMoves(const Board &, const bool, const uint8_t,
                                 const uint8_t, std::vector<Move> &);
  static void appendBackMoves(const Board &, const bool, const uint8_t,
                              const uint8_t, std::vector<Move> &);
  static PieceLocation forwardCaptures(const Board &, const bool, const uint8_t,
                                       const uint8_t,
                                       std::vector<PieceLocation> &);
  static PieceLocation backCaptures(const Board &, const bool, const uint8_t,
                                    const uint8_t,
                                    std::vector<PieceLocation> &);

public:
  static std::vector<Move> getPieceMoves(const Board &, const uint8_t,
                                         const uint8_t);
};
