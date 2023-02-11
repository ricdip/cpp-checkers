#pragma once
#include "../Piece.hpp"

class Queen : public Piece {
public:
  Queen(bool);
  char repr() const;
};
