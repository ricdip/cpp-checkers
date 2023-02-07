#include "include/Game.hpp"

std::vector<Move> Game::getPieceMoves(const Board& board, const uint8_t file, const uint8_t rank) {
    Piece &piece = board(file, rank).getPiece();
    if(piece.getType() == PieceType::PAWN) {
            return getPawnMoves(board, dynamic_cast<Pawn*>(&piece), file, rank);
    } else if (piece.getType() == PieceType::QUEEN) {
        return getQueenMoves(board, dynamic_cast<Queen*>(&piece), file, rank);
    } else {
        throw std::runtime_error("Illegal piece");
    }
}

std::vector<Move> Game::getPawnMoves(const Board& board, const Pawn& pawn, const uint8_t file, const uint8_t rank) {
    std::vector<Move> moves = std::vector<Move>();

    board.checkPositionInBound(file, rank);
    std::cout << pawn.repr() << std::endl;

    return moves;
}

std::vector<Move> Game::getQueenMoves(const Board& board, const Queen& queen, const uint8_t file, const uint8_t rank) {
    std::vector<Move> moves = std::vector<Move>();

    board.checkPositionInBound(file, rank);
    std::cout << queen.repr() << std::endl;

    return moves;
}
