#include "include/Game.hpp"
#include "include/Move.hpp"
#include "include/Piece.hpp"
#include <cstdint>
#include <utility>
#include <vector>

/*TODO: 
 * - remove unused parameter pawn
 * - missing tests
 * */
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

    if(pawn.getColor() == WHITE) {
        // append white legal moves to moves vector
        Game::appendForwardMoves(board, pawn, file, rank, moves);
    } else {
        // append black legal moves to moves vector
        Game::appendBackMoves(board, pawn, file, rank, moves);
    }

    return moves;
}

std::vector<Move> Game::getQueenMoves(const Board& board, const Queen& queen, const uint8_t file, const uint8_t rank) {
    std::vector<Move> moves = std::vector<Move>();

    board.checkPositionInBound(file, rank);
    std::cout << queen.repr() << std::endl;

    return moves;
}

void Game::appendForwardMoves(const Board& board, const Piece& piece, const uint8_t file, const uint8_t rank, std::vector<Move>& moves) {
    // move to up-left
    uint8_t upLeftFile = file - 1;
    uint8_t upLeftRank = rank - 1;
    if(board.checkPositionInBound(upLeftFile, upLeftRank) && board(upLeftFile, upLeftRank).isEmpty()) {
        // empty space, can move
        moves.push_back(Move(file, rank, upLeftFile, upLeftRank));
    } 

    // move to up-right
    uint8_t upRightFile = file + 1;
    uint8_t upRightRank = rank - 1;
    if(board.checkPositionInBound(upRightFile, upRightRank) && board(upRightFile, upRightRank).isEmpty()) {
        // empty space, can move
        moves.push_back(Move(file, rank, upRightFile, upRightRank));
    }

    // can capture up-left
    uint8_t upLeftAfterStepFile = file - 2;
    uint8_t upLeftAfterStepRank = rank - 2;
    if((!board(upLeftFile, upLeftRank).isEmpty()) && (board(upLeftFile, upLeftRank).getPiece().getColor() == !piece.getColor()) && board(upLeftAfterStepFile, upLeftAfterStepRank).isEmpty()) {
        std::vector<PieceLocation> captures = std::vector<PieceLocation>();
        PieceLocation finalLocation = Game::forwardCaptures(board, piece, file, rank, captures);
        Move move = Move(file, rank, finalLocation.file, finalLocation.rank);
        move.addCaptures(captures);
        moves.push_back(move);
    }

    // can capture up-right
    uint8_t upRightAfterStepFile = file + 2;
    uint8_t upRightAfterStepRank = rank - 2;
    if((!board(upRightFile, upRightRank).isEmpty()) && (board(upRightFile, upRightRank).getPiece().getColor() == !piece.getColor()) && board(upRightAfterStepFile, upRightAfterStepRank).isEmpty()) {
        std::vector<PieceLocation> captures = std::vector<PieceLocation>();
        PieceLocation finalLocation = Game::forwardCaptures(board, piece, file, rank, captures);
        Move move = Move(file, rank, finalLocation.file, finalLocation.rank);
        move.addCaptures(captures);
        moves.push_back(move);
    }
}

void Game::appendBackMoves(const Board& board, const Piece& piece, const uint8_t file, const uint8_t rank, std::vector<Move>& moves) {
    // move to down-left
    uint8_t downLeftFile = file - 1;
    uint8_t downLeftRank = rank + 1;
    if(board.checkPositionInBound(downLeftFile, downLeftRank) && board(downLeftFile, downLeftRank).isEmpty()) {
        // empty space, can move
        moves.push_back(Move(file, rank, downLeftFile, downLeftRank));
    } 

    // move to down-right
    uint8_t downRightFile = file + 1;
    uint8_t downRightRank = rank + 1;
    if(board.checkPositionInBound(downRightFile, downRightRank) && board(downRightFile, downRightRank).isEmpty()) {
        // empty space, can move
        moves.push_back(Move(file, rank, downRightFile, downRightRank));
    }

    // can capture down-left
    uint8_t downLeftAfterStepFile = file - 2;
    uint8_t downLeftAfterStepRank = rank + 2;
    if((!board(downLeftFile, downLeftRank).isEmpty()) && (board(downLeftFile, downLeftRank).getPiece().getColor() == !piece.getColor()) && board(downLeftAfterStepFile, downLeftAfterStepRank).isEmpty()) {
        std::vector<PieceLocation> captures = std::vector<PieceLocation>();
        PieceLocation finalLocation = Game::backCaptures(board, piece, file, rank, captures);
        Move move = Move(file, rank, finalLocation.file, finalLocation.rank);
        move.addCaptures(captures);
        moves.push_back(move);
    }

    // can capture down-right
    uint8_t downRightAfterStepFile = file + 2;
    uint8_t downRightAfterStepRank = rank + 2;
    if((!board(downRightFile, downRightRank).isEmpty()) && (board(downRightFile, downRightRank).getPiece().getColor() == !piece.getColor()) && board(downRightAfterStepFile, downRightAfterStepRank).isEmpty()) {
        std::vector<PieceLocation> captures = std::vector<PieceLocation>();
        PieceLocation finalLocation = Game::backCaptures(board, piece, file, rank, captures);
        Move move = Move(file, rank, finalLocation.file, finalLocation.rank);
        move.addCaptures(captures);
        moves.push_back(move);
    }
}

PieceLocation Game::forwardCaptures(const Board& board, const Piece& piece, const uint8_t file, const uint8_t rank, std::vector<PieceLocation>& capturesLocations) {
    uint8_t upLeftFile = file - 1;
    uint8_t upLeftRank = rank - 1;
    uint8_t upRightFile = file + 1;
    uint8_t upRightRank = rank - 1;
    uint8_t upLeftAfterStepFile = file - 2;
    uint8_t upLeftAfterStepRank = rank - 2;
    uint8_t upRightAfterStepFile = file + 2;
    uint8_t upRightAfterStepRank = rank - 2;
    if((!board(upLeftFile, upLeftRank).isEmpty()) && (board(upLeftFile, upLeftRank).getPiece().getColor() == !piece.getColor()) && board(upLeftAfterStepFile, upLeftAfterStepRank).isEmpty()) {
        // can capture up-left
        capturesLocations.push_back(PieceLocation{upLeftFile, upLeftRank});
        return Game::forwardCaptures(board, piece, upLeftAfterStepFile, upLeftAfterStepRank, capturesLocations);

    } else if((!board(upRightFile, upRightRank).isEmpty()) && (board(upRightFile, upRightRank).getPiece().getColor() == !piece.getColor()) && board(upRightAfterStepFile, upRightAfterStepRank).isEmpty()) {
        // can capture up-right
        capturesLocations.push_back(PieceLocation{upRightFile, upRightRank});
        return Game::forwardCaptures(board, piece, upRightAfterStepFile, upRightAfterStepRank, capturesLocations);

    } else {
        // no captures left
        return PieceLocation{file, rank};
    }
}

PieceLocation Game::backCaptures(const Board& board, const Piece& piece, const uint8_t file, const uint8_t rank, std::vector<PieceLocation>& capturesLocations) {
    uint8_t downLeftFile = file - 1;
    uint8_t downLeftRank = rank + 1;
    uint8_t downRightFile = file + 1;
    uint8_t downRightRank = rank + 1;
    uint8_t downLeftAfterStepFile = file - 2;
    uint8_t downLeftAfterStepRank = rank + 2;
    uint8_t downRightAfterStepFile = file + 2;
    uint8_t downRightAfterStepRank = rank + 2;
    if((!board(downLeftFile, downLeftRank).isEmpty()) && (board(downLeftFile, downLeftRank).getPiece().getColor() == !piece.getColor()) && board(downLeftAfterStepFile, downLeftAfterStepRank).isEmpty()) {
        // can capture down-left
        capturesLocations.push_back(PieceLocation{downLeftFile, downLeftRank});
        return Game::backCaptures(board, piece, downLeftAfterStepFile, downLeftAfterStepRank, capturesLocations);

    } else if((!board(downRightFile, downRightRank).isEmpty()) && (board(downRightFile, downRightRank).getPiece().getColor() == !piece.getColor()) && board(downRightAfterStepFile, downRightAfterStepRank).isEmpty()) {
        // can capture down-right
        capturesLocations.push_back(PieceLocation{downRightFile, downRightRank});
        return Game::backCaptures(board, piece, downRightAfterStepFile, downRightAfterStepRank, capturesLocations);

    } else {
        // no captures left
        return PieceLocation{file, rank};
    }
}
