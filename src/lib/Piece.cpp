#include "include/Piece.hpp"

Piece::Piece(bool c) : color(c) {}

bool Piece::getColor() const { return color; }

PieceType Piece::getType() const { return type; }

std::ostream &operator<<(std::ostream &os, const Piece &p) {
  os << p.repr();
  return os;
}

bool PieceLocation::operator==(const PieceLocation &pieceLocation) const {
  return (file == pieceLocation.file) && (rank == pieceLocation.rank);
}

bool PieceLocation::operator!=(const PieceLocation &pieceLocation) const {
  return !(*this == pieceLocation);
}
