#include "include/Queen.hpp"
#include "include/Game.hpp"

Queen::Queen(bool color) : Piece(color) {
    type = PieceType::QUEEN;
}

char Queen::repr() const {
    return (getColor() == WHITE) ? WQUEEN : BQUEEN;
}
