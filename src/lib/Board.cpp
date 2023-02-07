#include "include/Board.hpp"
#include "include/Game.hpp"
#include "include/Pawn.hpp"
#include <cstdint>
#include <stdexcept>

Board::Board() {
    initBoard();
}

void Board::initBoard() {
    // white
    // Board::operator() = new Pawn()
    (*this)(B,1) = new Pawn(WHITE);
    (*this)(D,1) = new Pawn(WHITE);
    (*this)(F,1) = new Pawn(WHITE);
    (*this)(H,1) = new Pawn(WHITE);
             
    (*this)(A,2) = new Pawn(WHITE);
    (*this)(C,2) = new Pawn(WHITE);
    (*this)(E,2) = new Pawn(WHITE);
    (*this)(G,2) = new Pawn(WHITE);
               
    (*this)(B,3) = new Pawn(WHITE);
    (*this)(D,3) = new Pawn(WHITE);
    (*this)(F,3) = new Pawn(WHITE);
    (*this)(H,3) = new Pawn(WHITE);
    // black
    (*this)(A,6) = new Pawn(BLACK);
    (*this)(C,6) = new Pawn(BLACK);
    (*this)(E,6) = new Pawn(BLACK);
    (*this)(G,6) = new Pawn(BLACK);
            
    (*this)(B,7) = new Pawn(BLACK);
    (*this)(D,7) = new Pawn(BLACK);
    (*this)(F,7) = new Pawn(BLACK);
    (*this)(H,7) = new Pawn(BLACK);
                
    (*this)(A,8) = new Pawn(BLACK);
    (*this)(C,8) = new Pawn(BLACK);
    (*this)(E,8) = new Pawn(BLACK);
    (*this)(G,8) = new Pawn(BLACK);
}

bool Board::checkPositionInBound(uint8_t file, uint8_t rank) const {
    return !(file >= COLS || (rank-1) >= ROWS || (rank-1) < 0);
}

// (rows, colums) = (file, rank) = (A, 1)
Tile& Board::operator()(uint8_t file, uint8_t rank) {
    if(!checkPositionInBound(file, rank)) {
        throw std::runtime_error("Out of range access on Board");
    }
    return tiles[rank - 1][file];
}

const Tile& Board::operator()(uint8_t file, uint8_t rank) const {
    if(!checkPositionInBound(file, rank)) {
        throw std::runtime_error("Out of range access on Board");
    }
    return tiles[rank - 1][file];
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
    os << '\n' << "   " << "A B C D E F G H" << "\n\n";
    for(uint8_t rank = 1; rank <= ROWS; rank++) {
        for(uint8_t file = 0; file < COLS; file++) {
            if(file == 0) {
                os << +rank << "  ";
            }
            os << board(file, rank) << ' ';

            if(file == COLS - 1) {
                os << "  " << +rank;
            }
        }
        os << '\n';
    }
    os << '\n' << "   " << "A B C D E F G H" << '\n';
    return os;
}
