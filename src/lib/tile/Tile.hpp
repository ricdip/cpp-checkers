#pragma once
#include "../piece/Piece.hpp"
#include <memory>

class Tile {
  std::shared_ptr<Piece> occupant;

public:
  // constructors
  Tile();
  Tile(Piece *);
  // destructor
  ~Tile();
  // getters
  Piece &getPiece() const;
  bool isEmpty() const;
  // clean
  void reset();
  // representation
  char repr() const;
  // operator << overload
  friend std::ostream &operator<<(std::ostream &, const Tile &);
  // operator = overload
  Tile &operator=(Piece *);
};
