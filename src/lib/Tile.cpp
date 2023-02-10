#include "include/Tile.hpp"

// make_shared creates an empty shared pointer
Tile::Tile() : occupant(nullptr) {}

// make_shared creates a shared pointer storing a piece
Tile::Tile(Piece *p) : occupant(p) {}

Tile::Tile(const Tile &t) {
  // increments the shared pointer use_count
  occupant = t.occupant;
}

Tile::~Tile() {
  // if shared_ptr.unique is true, this will delete the managed object
  occupant.reset();
}

Piece &Tile::getPiece() const { return *occupant; }

bool Tile::isEmpty() const {
  // shared_ptr.get() returns the stored pointer
  return occupant.get() == nullptr;
}

char Tile::repr() const {
  return (occupant == nullptr) ? ' ' : occupant->repr();
}

std::ostream &operator<<(std::ostream &os, const Tile &t) {
  os << t.repr();
  return os;
}

Tile &Tile::operator=(Piece *t) {
  occupant.reset(t);
  return *this;
}
