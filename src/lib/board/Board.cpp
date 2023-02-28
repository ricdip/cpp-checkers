#include "Board.hpp"
#include "../game/Game.hpp"
#include "../move/generator/MoveGenerator.hpp"
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>

Board::Board(bool emptyBoard) : turn(true), threeFoldRepetition(false) {
  if (!emptyBoard) {
    initBoard();
  }
  madeMoves = std::vector<Move>();
}

Board::Board(bool turn, bool emptyBoard)
    : turn(turn), threeFoldRepetition(false) {
  if (!emptyBoard) {
    initBoard();
  }
  madeMoves = std::vector<Move>();
}

Board::Board(bool turn, bool emptyBoard, std::vector<Move> madeMoves)
    : turn(turn), madeMoves(madeMoves), threeFoldRepetition(false) {
  if (!emptyBoard) {
    initBoard();
  }
}

std::shared_ptr<Board> Board::clone() const {
  std::shared_ptr<Board> board = std::make_shared<Board>(turn, true, madeMoves);
  board->threeFoldRepetition = threeFoldRepetition;
  for (uint8_t rank = ROWS; rank >= 1; rank--) {
    for (uint8_t file = 1; file <= COLS; file++) {
      if (!(*this)(file, rank).isEmpty()) {
        Piece *p = &(*this)(file, rank).getPiece();
        if (p->getType() == PieceType::PAWN) {
          (*board)(file, rank) = new Pawn(p->getColor());
        } else if (p->getType() == PieceType::QUEEN) {
          (*board)(file, rank) = new Queen(p->getColor());
        } else {
          throw std::runtime_error(
              "Error during board copy: illegal piece type");
        }
      }
    }
  }
  return board;
}

void Board::initBoard() {
  // black
  // Board::operator() = new Pawn()
  (*this)(B, 8) = new Pawn(BLACK);
  (*this)(D, 8) = new Pawn(BLACK);
  (*this)(F, 8) = new Pawn(BLACK);
  (*this)(H, 8) = new Pawn(BLACK);

  (*this)(A, 7) = new Pawn(BLACK);
  (*this)(C, 7) = new Pawn(BLACK);
  (*this)(E, 7) = new Pawn(BLACK);
  (*this)(G, 7) = new Pawn(BLACK);

  (*this)(B, 6) = new Pawn(BLACK);
  (*this)(D, 6) = new Pawn(BLACK);
  (*this)(F, 6) = new Pawn(BLACK);
  (*this)(H, 6) = new Pawn(BLACK);
  // white
  (*this)(A, 3) = new Pawn(WHITE);
  (*this)(C, 3) = new Pawn(WHITE);
  (*this)(E, 3) = new Pawn(WHITE);
  (*this)(G, 3) = new Pawn(WHITE);

  (*this)(B, 2) = new Pawn(WHITE);
  (*this)(D, 2) = new Pawn(WHITE);
  (*this)(F, 2) = new Pawn(WHITE);
  (*this)(H, 2) = new Pawn(WHITE);

  (*this)(A, 1) = new Pawn(WHITE);
  (*this)(C, 1) = new Pawn(WHITE);
  (*this)(E, 1) = new Pawn(WHITE);
  (*this)(G, 1) = new Pawn(WHITE);
}

bool Board::checkPositionInBound(uint8_t file, uint8_t rank) const {
  return !((file - 1) >= COLS || (rank - 1) >= ROWS || (file - 1) < 0 ||
           (rank - 1) < 0);
}

uint8_t Board::countPiecesByColor(bool color) const {
  uint8_t count = 0;
  for (uint8_t rank = ROWS; rank >= 1; rank--) {
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

  if (threeFoldRepetition) {
    return legalMoves;
  }

  for (uint8_t rank = ROWS; rank >= 1; rank--) {
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

std::vector<Move> Board::getMadeMoves() const { return madeMoves; }

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

  // pawn promotion
  Piece &p =
      (*this)(move.getDestinationFile(), move.getDestinationRank()).getPiece();
  if (p.getType() == PieceType::PAWN && p.getColor() == WHITE &&
      move.getDestinationRank() == 8) {
    (*this)(move.getDestinationFile(), move.getDestinationRank()) =
        new Queen(WHITE);
  } else if (p.getType() == PieceType::PAWN && p.getColor() == BLACK &&
             move.getDestinationRank() == 1) {
    (*this)(move.getDestinationFile(), move.getDestinationRank()) =
        new Queen(BLACK);
  }

  // delete captured pieces
  for (auto it = captures.begin(); it != captures.end(); it++) {
    (*this)(it->file, it->rank).reset();
  }

  turn = !turn;

  // save made move
  madeMoves.push_back(move);

  // check threefold repetition
  uint32_t count = 0;
  for (auto it = madeMoves.begin(); it != madeMoves.end(); it++) {
    if (move == *it) {
      count++;
    }
  }
  if (count >= 3) {
    threeFoldRepetition = true;
  }
}

// a player wins when the opponent cannot make a move (all opponent pieces are
// captured or the opponent is blocked from moving) -> game over = no current
// moves available for current player or we have a threefold repetition
bool Board::isGameOver() const { return getMoves().empty(); }

// a player wins when the opponent cannot make a move (all opponent pieces are
// captured or the opponent is blocked from moving) -> in case of game over
// (with no threefold repetition), we don't have moves available, so winner =
// previous player
GameResult Board::getGameResult() const {
  // game not over case
  if (!isGameOver()) {
    return GameResult::gameNotOver();
  }
  // draw case
  if (threeFoldRepetition) {
    return GameResult::threeFoldRepetition();
  }
  // winner case
  return GameResult::winner(!turn);
}

std::string Board::repr() const {
  std::string boardStr = "";
  for (uint8_t rank = ROWS; rank >= 1; rank--) {
    for (uint8_t file = 1; file <= COLS; file++) {
      if ((*this)(file, rank).isEmpty()) {
        boardStr += ".";
      } else {
        boardStr += (*this)(file, rank).getPiece().repr();
      }
    }
  }
  boardStr += '/';
  boardStr += ((turn) ? "W" : "B");
  return boardStr;
}

// (file, rank) = (A, 1)
Tile &Board::operator()(uint8_t file, uint8_t rank) {
  if (!checkPositionInBound(file, rank)) {
    std::string errString = "Out of range access on Board: (";
    errString += std::to_string(+file);
    errString += ", ";
    errString += std::to_string(+rank);
    errString += ")";
    throw std::runtime_error(errString);
  }
  return tiles[8 - rank][file - 1];
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
  return tiles[8 - rank][file - 1];
}

std::ostream &operator<<(std::ostream &os, const Board &board) {
  os << '\n'
     << "   "
     << "A B C D E F G H"
     << "\n\n";
  for (uint8_t rank = ROWS; rank >= 1; rank--) {
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
  int32_t madeMovesSize = board.madeMoves.size();
  os << '\n'
     << "- last move: "
     << ((madeMovesSize > 0) ? board.madeMoves[madeMovesSize - 1].repr()
                             : "None")
     << '\n';
  os << "- turn: " << ((board.turn) ? "WHITE" : "BLACK") << '\n';
  return os;
}
