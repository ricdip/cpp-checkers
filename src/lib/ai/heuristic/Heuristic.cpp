#include "Heuristic.hpp"
#include "../../game/Game.hpp"
#include "PieceValue.hpp"

int32_t Heuristic::Htot(const Board &board) {
  int32_t H1 = gameOverH(board);
  int32_t H2 = boardPieceValuesH(board);

  return (H1 != 0) ? H1 : H2;
}

int32_t Heuristic::boardPieceValuesH(const Board &board) {
  int32_t count = 0;
  for (uint8_t rank = ROWS; rank >= 1; rank--) {
    for (uint8_t file = 1; file <= COLS; file++) {
      if (!board(file, rank).isEmpty()) {
        Piece &p = board(file, rank).getPiece();
        if (p.getColor() == WHITE) {
          // white piece
          count +=
              ((p.getType() == PieceType::PAWN) ? PAWN_VALUE : QUEEN_VALUE);
        } else {
          // black piece
          count -=
              ((p.getType() == PieceType::PAWN) ? PAWN_VALUE : QUEEN_VALUE);
        }
      }
    }
  }
  return count;
}

int32_t Heuristic::gameOverH(const Board &board) {
  GameResult gameResult = board.getGameResult();
  if (gameResult == GameResult::gameNotOver()) {
    // game not over yet
    return 0;
  } else if (gameResult == GameResult::winner(WHITE)) {
    // max player is the winner
    return INT32_MAX;
  } else if (gameResult == GameResult::winner(BLACK)) {
    // min player is the winner
    return INT32_MIN;
  } else {
    // game draw
    return 0;
  }
}
