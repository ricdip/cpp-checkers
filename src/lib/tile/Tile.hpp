#pragma once
#include "../piece/Piece.hpp"
#include <memory>

class Tile {
  std::shared_ptr<Piece> occupant;

public:
  Tile();
  Tile(Piece *);
  ~Tile();
  Piece &getPiece() const;
  bool isEmpty() const;
  void reset();
  char repr() const;
  friend std::ostream &operator<<(std::ostream &, const Tile &);
  Tile &operator=(Piece *);
};
