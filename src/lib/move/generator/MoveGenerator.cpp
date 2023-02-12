#include "MoveGenerator.hpp"

std::vector<Move> MoveGenerator::getPieceMoves(const Board &board,
                                               const uint8_t file,
                                               const uint8_t rank) {
  if (board(file, rank).isEmpty()) {
    return std::vector<Move>();
  }

  Piece &piece = board(file, rank).getPiece();
  if (piece.getType() == PieceType::PAWN) {
    return getPawnMoves(board, dynamic_cast<Pawn &>(piece), file, rank);
  } else if (piece.getType() == PieceType::QUEEN) {
    return getQueenMoves(board, dynamic_cast<Queen &>(piece), file, rank);
  } else {
    std::string errString = "Illegal piece: (";
    errString += std::to_string(+file);
    errString += ", ";
    errString += std::to_string(+rank);
    errString += ")";
    throw std::runtime_error(errString);
  }
}

std::vector<Move> MoveGenerator::getPawnMoves(const Board &board,
                                              const Pawn &pawn,
                                              const uint8_t file,
                                              const uint8_t rank) {
  std::vector<Move> moves = std::vector<Move>();

  if (pawn.getColor() == WHITE) {
    // append white legal moves to moves vector
    MoveGenerator::appendForwardMoves(board, WHITE, file, rank, moves);
  } else {
    // append black legal moves to moves vector
    MoveGenerator::appendBackMoves(board, BLACK, file, rank, moves);
  }

  return moves;
}

std::vector<Move> MoveGenerator::getQueenMoves(const Board &board,
                                               const Queen &queen,
                                               const uint8_t file,
                                               const uint8_t rank) {
  std::vector<Move> moves = std::vector<Move>();

  if (queen.getColor() == WHITE) {
    // append white legal moves to moves vector
    MoveGenerator::appendForwardMoves(board, WHITE, file, rank, moves);
    MoveGenerator::appendBackMoves(board, WHITE, file, rank, moves);
  } else {
    // append black legal moves to moves vector
    MoveGenerator::appendForwardMoves(board, BLACK, file, rank, moves);
    MoveGenerator::appendBackMoves(board, BLACK, file, rank, moves);
  }

  return moves;
}

void MoveGenerator::appendForwardMoves(const Board &board,
                                       const bool pieceColor,
                                       const uint8_t file, const uint8_t rank,
                                       std::vector<Move> &moves) {
  // move to up-left
  uint8_t upLeftFile = file - 1;
  uint8_t upLeftRank = rank + 1;
  if (board.checkPositionInBound(upLeftFile, upLeftRank) &&
      board(upLeftFile, upLeftRank).isEmpty()) {
    // empty space, can move
    moves.push_back(Move(file, rank, upLeftFile, upLeftRank));
  }

  // move to up-right
  uint8_t upRightFile = file + 1;
  uint8_t upRightRank = rank + 1;
  if (board.checkPositionInBound(upRightFile, upRightRank) &&
      board(upRightFile, upRightRank).isEmpty()) {
    // empty space, can move
    moves.push_back(Move(file, rank, upRightFile, upRightRank));
  }

  // can capture up-left
  uint8_t upLeftAfterStepFile = file - 2;
  uint8_t upLeftAfterStepRank = rank + 2;
  if (board.checkPositionInBound(upLeftFile, upLeftRank) &&
      (!board(upLeftFile, upLeftRank).isEmpty()) &&
      (board(upLeftFile, upLeftRank).getPiece().getColor() == !pieceColor) &&
      board.checkPositionInBound(upLeftAfterStepFile, upLeftAfterStepRank) &&
      board(upLeftAfterStepFile, upLeftAfterStepRank).isEmpty()) {
    std::vector<PieceLocation> captures = std::vector<PieceLocation>();
    PieceLocation finalLocation =
        MoveGenerator::forwardCaptures(board, pieceColor, file, rank, captures);
    Move move = Move(file, rank, finalLocation.file, finalLocation.rank);
    move.addCaptures(captures);
    moves.push_back(move);
  }

  // can capture up-right
  uint8_t upRightAfterStepFile = file + 2;
  uint8_t upRightAfterStepRank = rank + 2;
  if (board.checkPositionInBound(upRightFile, upRightRank) &&
      (!board(upRightFile, upRightRank).isEmpty()) &&
      (board(upRightFile, upRightRank).getPiece().getColor() == !pieceColor) &&
      board.checkPositionInBound(upRightAfterStepFile, upRightAfterStepRank) &&
      board(upRightAfterStepFile, upRightAfterStepRank).isEmpty()) {
    std::vector<PieceLocation> captures = std::vector<PieceLocation>();
    PieceLocation finalLocation =
        MoveGenerator::forwardCaptures(board, pieceColor, file, rank, captures);
    Move move = Move(file, rank, finalLocation.file, finalLocation.rank);
    move.addCaptures(captures);
    moves.push_back(move);
  }
}

void MoveGenerator::appendBackMoves(const Board &board, const bool pieceColor,
                                    const uint8_t file, const uint8_t rank,
                                    std::vector<Move> &moves) {
  // move to down-left
  uint8_t downLeftFile = file - 1;
  uint8_t downLeftRank = rank - 1;
  if (board.checkPositionInBound(downLeftFile, downLeftRank) &&
      board(downLeftFile, downLeftRank).isEmpty()) {
    // empty space, can move
    moves.push_back(Move(file, rank, downLeftFile, downLeftRank));
  }

  // move to down-right
  uint8_t downRightFile = file + 1;
  uint8_t downRightRank = rank - 1;
  if (board.checkPositionInBound(downRightFile, downRightRank) &&
      board(downRightFile, downRightRank).isEmpty()) {
    // empty space, can move
    moves.push_back(Move(file, rank, downRightFile, downRightRank));
  }

  // can capture down-left
  uint8_t downLeftAfterStepFile = file - 2;
  uint8_t downLeftAfterStepRank = rank - 2;
  if (board.checkPositionInBound(downLeftFile, downLeftRank) &&
      (!board(downLeftFile, downLeftRank).isEmpty()) &&
      (board(downLeftFile, downLeftRank).getPiece().getColor() ==
       !pieceColor) &&
      board.checkPositionInBound(downLeftAfterStepFile,
                                 downLeftAfterStepRank) &&
      board(downLeftAfterStepFile, downLeftAfterStepRank).isEmpty()) {
    std::vector<PieceLocation> captures = std::vector<PieceLocation>();
    PieceLocation finalLocation =
        MoveGenerator::backCaptures(board, pieceColor, file, rank, captures);
    Move move = Move(file, rank, finalLocation.file, finalLocation.rank);
    move.addCaptures(captures);
    moves.push_back(move);
  }

  // can capture down-right
  uint8_t downRightAfterStepFile = file + 2;
  uint8_t downRightAfterStepRank = rank - 2;
  if (board.checkPositionInBound(downRightFile, downRightRank) &&
      (!board(downRightFile, downRightRank).isEmpty()) &&
      (board(downRightFile, downRightRank).getPiece().getColor() ==
       !pieceColor) &&
      board.checkPositionInBound(downRightAfterStepFile,
                                 downRightAfterStepRank) &&
      board(downRightAfterStepFile, downRightAfterStepRank).isEmpty()) {
    std::vector<PieceLocation> captures = std::vector<PieceLocation>();
    PieceLocation finalLocation =
        MoveGenerator::backCaptures(board, pieceColor, file, rank, captures);
    Move move = Move(file, rank, finalLocation.file, finalLocation.rank);
    move.addCaptures(captures);
    moves.push_back(move);
  }
}

PieceLocation
MoveGenerator::forwardCaptures(const Board &board, const bool pieceColor,
                               const uint8_t file, const uint8_t rank,
                               std::vector<PieceLocation> &capturesLocations) {
  uint8_t upLeftFile = file - 1;
  uint8_t upLeftRank = rank + 1;
  uint8_t upRightFile = file + 1;
  uint8_t upRightRank = rank + 1;
  uint8_t upLeftAfterStepFile = file - 2;
  uint8_t upLeftAfterStepRank = rank + 2;
  uint8_t upRightAfterStepFile = file + 2;
  uint8_t upRightAfterStepRank = rank + 2;
  if (board.checkPositionInBound(upLeftFile, upLeftRank) &&
      (!board(upLeftFile, upLeftRank).isEmpty()) &&
      (board(upLeftFile, upLeftRank).getPiece().getColor() == !pieceColor) &&
      board.checkPositionInBound(upLeftAfterStepFile, upLeftAfterStepRank) &&
      board(upLeftAfterStepFile, upLeftAfterStepRank).isEmpty()) {
    // can capture up-left
    capturesLocations.push_back(PieceLocation{upLeftFile, upLeftRank});
    return MoveGenerator::forwardCaptures(
        board, pieceColor, upLeftAfterStepFile, upLeftAfterStepRank,
        capturesLocations);

  } else if (board.checkPositionInBound(upRightFile, upRightRank) &&
             (!board(upRightFile, upRightRank).isEmpty()) &&
             (board(upRightFile, upRightRank).getPiece().getColor() ==
              !pieceColor) &&
             board.checkPositionInBound(upRightAfterStepFile,
                                        upRightAfterStepRank) &&
             board(upRightAfterStepFile, upRightAfterStepRank).isEmpty()) {
    // can capture up-right
    capturesLocations.push_back(PieceLocation{upRightFile, upRightRank});
    return MoveGenerator::forwardCaptures(
        board, pieceColor, upRightAfterStepFile, upRightAfterStepRank,
        capturesLocations);

  } else {
    // no captures left
    return PieceLocation{file, rank};
  }
}

PieceLocation
MoveGenerator::backCaptures(const Board &board, const bool pieceColor,
                            const uint8_t file, const uint8_t rank,
                            std::vector<PieceLocation> &capturesLocations) {
  uint8_t downLeftFile = file - 1;
  uint8_t downLeftRank = rank - 1;
  uint8_t downRightFile = file + 1;
  uint8_t downRightRank = rank - 1;
  uint8_t downLeftAfterStepFile = file - 2;
  uint8_t downLeftAfterStepRank = rank - 2;
  uint8_t downRightAfterStepFile = file + 2;
  uint8_t downRightAfterStepRank = rank - 2;
  if (board.checkPositionInBound(downLeftFile, downLeftRank) &&
      (!board(downLeftFile, downLeftRank).isEmpty()) &&
      (board(downLeftFile, downLeftRank).getPiece().getColor() ==
       !pieceColor) &&
      board.checkPositionInBound(downLeftAfterStepFile,
                                 downLeftAfterStepRank) &&
      board(downLeftAfterStepFile, downLeftAfterStepRank).isEmpty()) {
    // can capture down-left
    capturesLocations.push_back(PieceLocation{downLeftFile, downLeftRank});
    return MoveGenerator::backCaptures(board, pieceColor, downLeftAfterStepFile,
                                       downLeftAfterStepRank,
                                       capturesLocations);

  } else if (board.checkPositionInBound(downRightFile, downRightRank) &&
             (!board(downRightFile, downRightRank).isEmpty()) &&
             (board(downRightFile, downRightRank).getPiece().getColor() ==
              !pieceColor) &&
             board.checkPositionInBound(downRightAfterStepFile,
                                        downRightAfterStepRank) &&
             board(downRightAfterStepFile, downRightAfterStepRank).isEmpty()) {
    // can capture down-right
    capturesLocations.push_back(PieceLocation{downRightFile, downRightRank});
    return MoveGenerator::backCaptures(
        board, pieceColor, downRightAfterStepFile, downRightAfterStepRank,
        capturesLocations);

  } else {
    // no captures left
    return PieceLocation{file, rank};
  }
}
