#pragma once
#include "PieceType.hpp"
#include <iostream>

#define WPAWN 'w'
#define BPAWN 'b'
#define WQUEEN 'W'
#define BQUEEN 'B'

class Piece {
private:
  bool color;

protected:
  PieceType type;

public:
  // constructor
  Piece(bool);
  // getters
  bool getColor() const;
  PieceType getType() const;
  // representation
  virtual char repr() const = 0;
  // operator << overload
  friend std::ostream &operator<<(std::ostream &, const Piece &);
};

struct PieceLocation {
  uint8_t file;
  uint8_t rank;

  bool operator==(const PieceLocation &) const;
  bool operator!=(const PieceLocation &) const;
};
