#pragma once
#include "PieceType.hpp"
#include <sstream>

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
  Piece(bool);
  bool getColor() const;
  PieceType getType() const;
  virtual char repr() const = 0;
  friend std::ostream &operator<<(std::ostream &, const Piece &);
};

struct PieceLocation {
  uint8_t file;
  uint8_t rank;

  bool operator==(const PieceLocation &) const;
  bool operator!=(const PieceLocation &) const;
};
