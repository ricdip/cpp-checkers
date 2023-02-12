#include "Tile.hpp"
#include "../piece/pawn/Pawn.hpp"
#include "../piece/queen/Queen.hpp"

Tile::Tile() : occupant(NULL) {}

Tile::Tile(Piece *p) { occupant.reset(p); }

Tile::~Tile() { occupant.reset(); }

Piece &Tile::getPiece() const { return *occupant; }

bool Tile::isEmpty() const {
  return occupant == NULL || occupant.get() == NULL;
}

void Tile::reset() { occupant.reset(); }

char Tile::repr() const { return (!isEmpty()) ? occupant->repr() : ' '; }

std::ostream &operator<<(std::ostream &os, const Tile &t) {
  os << t.repr();
  return os;
}

Tile &Tile::operator=(Piece *p) {
  occupant.reset(p);
  return *this;
}
