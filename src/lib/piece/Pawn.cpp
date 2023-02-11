#include "Pawn.hpp"
#include "../game/Game.hpp"

Pawn::Pawn(bool color) : Piece(color) { type = PieceType::PAWN; }

char Pawn::repr() const { return (getColor() == WHITE) ? WPAWN : BPAWN; }
