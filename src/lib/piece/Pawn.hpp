#pragma once
#include "Piece.hpp"

class Pawn : public Piece {
public:
  Pawn(bool);
  char repr() const;
};
