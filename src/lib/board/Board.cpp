#include "Board.hpp"
#include "../game/Game.hpp"
#include "../move/generator/MoveGenerator.hpp"
#include <cstdint>
#include <stdexcept>
#include <string>

Board::Board(bool emptyBoard) : turn(true) {
  if (!emptyBoard) {
    initBoard();
  }
}

Board::Board(bool turn, bool emptyBoard) : turn(turn) {
  if (!emptyBoard) {
    initBoard();
  }
}

void Board::initBoard() {
  // black
  // Board::operator() = new Pawn()
  (*this)(B, 1) = new Pawn(BLACK);
  (*this)(D, 1) = new Pawn(BLACK);
  (*this)(F, 1) = new Pawn(BLACK);
  (*this)(H, 1) = new Pawn(BLACK);

  (*this)(A, 2) = new Pawn(BLACK);
  (*this)(C, 2) = new Pawn(BLACK);
  (*this)(E, 2) = new Pawn(BLACK);
  (*this)(G, 2) = new Pawn(BLACK);

  (*this)(B, 3) = new Pawn(BLACK);
  (*this)(D, 3) = new Pawn(BLACK);
  (*this)(F, 3) = new Pawn(BLACK);
  (*this)(H, 3) = new Pawn(BLACK);
  // white
  (*this)(A, 6) = new Pawn(WHITE);
  (*this)(C, 6) = new Pawn(WHITE);
  (*this)(E, 6) = new Pawn(WHITE);
  (*this)(G, 6) = new Pawn(WHITE);

  (*this)(B, 7) = new Pawn(WHITE);
  (*this)(D, 7) = new Pawn(WHITE);
  (*this)(F, 7) = new Pawn(WHITE);
  (*this)(H, 7) = new Pawn(WHITE);

  (*this)(A, 8) = new Pawn(WHITE);
  (*this)(C, 8) = new Pawn(WHITE);
  (*this)(E, 8) = new Pawn(WHITE);
  (*this)(G, 8) = new Pawn(WHITE);
}

bool Board::checkPositionInBound(uint8_t file, uint8_t rank) const {
  return !((file - 1) >= COLS || (rank - 1) >= ROWS || (file - 1) < 0 ||
           (rank - 1) < 0);
}

uint8_t Board::countPiecesByColor(bool color) const {
  uint8_t count = 0;
  for (uint8_t rank = 1; rank <= ROWS; rank++) {
    for (uint8_t file = 1; file <= COLS; file++) {
      if ((!(*this)(file, rank).isEmpty()) &&
          ((*this)(file, rank).getPiece().getColor() == color)) {
        count++;
      }
    }
  }
  return count;
}

std::vector<Move> Board::getMoves() const {
  std::vector<Move> legalMoves = std::vector<Move>();
  for (uint8_t rank = 1; rank <= ROWS; rank++) {
    for (uint8_t file = 1; file <= COLS; file++) {
      if ((!(*this)(file, rank).isEmpty()) &&
          ((*this)(file, rank).getPiece().getColor() == turn)) {
        std::vector<Move> newMoves =
            MoveGenerator::getPieceMoves(*this, file, rank);
        legalMoves.insert(legalMoves.end(), newMoves.begin(), newMoves.end());
      }
    }
  }
  return legalMoves;
}

bool Board::getTurn() const { return turn; }

void Board::makeMove(Move move) {
  std::vector<Move> legalMoves = getMoves();
  std::vector<PieceLocation> captures = std::vector<PieceLocation>();

  bool isLegal = false;
  for (auto it = legalMoves.begin(); it != legalMoves.end(); it++) {
    if (it->getOriginFile() == move.getOriginFile() &&
        it->getOriginRank() == move.getOriginRank() &&
        it->getDestinationFile() == move.getDestinationFile() &&
        it->getDestinationRank() == move.getDestinationRank()) {
      isLegal = true;
      captures = it->getCaptures();
      break;
    }
  }

  if (!isLegal) {
    std::string errString = "Attempt to make an illegal move: (";
    errString += move.repr();
    errString += ")";
    throw std::runtime_error(errString);
  }

  (*this)(move.getDestinationFile(), move.getDestinationRank()) =
      std::move((*this)(move.getOriginFile(), move.getOriginRank()));

  (*this)(move.getOriginFile(), move.getOriginRank()).reset();

  for (auto it = captures.begin(); it != captures.end(); it++) {
    (*this)(it->file, it->rank).reset();
  }

  turn = !turn;
}

// (rows, colums) = (file, rank) = (A, 1)
Tile &Board::operator()(uint8_t file, uint8_t rank) {
  if (!checkPositionInBound(file, rank)) {
    std::string errString = "Out of range access on Board: (";
    errString += std::to_string(+file);
    errString += ", ";
    errString += std::to_string(+rank);
    errString += ")";
    throw std::runtime_error(errString);
  }
  return tiles[rank - 1][file - 1];
}

const Tile &Board::operator()(uint8_t file, uint8_t rank) const {
  if (!checkPositionInBound(file, rank)) {
    std::string errString = "Out of range access on Board: (";
    errString += std::to_string(+file);
    errString += ", ";
    errString += std::to_string(+rank);
    errString += ")";
    throw std::runtime_error(errString);
  }
  return tiles[rank - 1][file - 1];
}

std::ostream &operator<<(std::ostream &os, const Board &board) {
  os << '\n'
     << "   "
     << "A B C D E F G H"
     << "\n\n";
  for (uint8_t rank = 1; rank <= ROWS; rank++) {
    for (uint8_t file = 1; file <= COLS; file++) {
      if (file == 1) {
        os << +rank << "  ";
      }
      os << board(file, rank) << ' ';

      if (file == COLS) {
        os << "  " << +rank;
      }
    }
    os << '\n';
  }
  os << '\n'
     << "   "
     << "A B C D E F G H" << '\n';
  return os;
}
