#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "../lib/include/Game.hpp"

// TODO: missing tests
TEST(GameTest, whitePawnMovesWithoutCapture) {
    Game game = Game();

    Board boardTwoMoves = Board(true);
    boardTwoMoves(D, 5) = new Pawn(WHITE);
    std::vector<Move> twoMoves = game.getPieceMoves(boardTwoMoves, D, 5);
    ASSERT_EQ(twoMoves.size(), 2);
    ASSERT_EQ(std::find(twoMoves.begin(), twoMoves.end(), Move("D5C4")) != twoMoves.end(), true);
    ASSERT_EQ(std::find(twoMoves.begin(), twoMoves.end(), Move("D5E4")) != twoMoves.end(), true);

    Board boardOneMove = Board(true);
    boardOneMove(D, 5) = new Pawn(WHITE);
    boardOneMove(C, 4) = new Pawn(WHITE);
    std::vector<Move> oneMove = game.getPieceMoves(boardOneMove, D, 5);
    ASSERT_EQ(oneMove.size(), 1);
    ASSERT_EQ(std::find(oneMove.begin(), oneMove.end(), Move("D5E4")) != oneMove.end(), true);

    Board boardZeroMoves = Board(true);
    boardZeroMoves(D, 5) = new Pawn(WHITE);
    boardZeroMoves(C, 4) = new Pawn(WHITE);
    boardZeroMoves(E, 4) = new Pawn(WHITE);
    std::vector<Move> zeroMoves = game.getPieceMoves(boardZeroMoves, D, 5);
    ASSERT_EQ(zeroMoves.size(), 0);

    Board boardMovesWithAnOutOfBounds = Board(true);
    boardMovesWithAnOutOfBounds(A, 8) = new Pawn(WHITE);
    std::vector<Move> oneOutOfBoundsMove = game.getPieceMoves(boardMovesWithAnOutOfBounds, A, 8);
    ASSERT_EQ(oneOutOfBoundsMove.size(), 1);
    ASSERT_EQ(std::find(oneOutOfBoundsMove.begin(), oneOutOfBoundsMove.end(), Move("A8B7")) != oneOutOfBoundsMove.end(), true);

    Board boardMovesWithAllOutOfBounds = Board(true);
    boardMovesWithAllOutOfBounds(A, 1) = new Pawn(WHITE);
    std::vector<Move> allOutOfBoundsMoves = game.getPieceMoves(boardMovesWithAllOutOfBounds, A, 1);
    ASSERT_EQ(allOutOfBoundsMoves.size(), 0);
}

TEST(GameTest, whitePawnMovesWithCapture) {
    Game game = Game();

    Board boardOneLeftCaptureMove = Board(true);
    boardOneLeftCaptureMove(D, 5) = new Pawn(WHITE);
    boardOneLeftCaptureMove(C, 4) = new Pawn(BLACK);
    boardOneLeftCaptureMove(E, 4) = new Pawn(WHITE);
    Move oneLeftCaptureMoveResult = Move("D5B3");
    oneLeftCaptureMoveResult.addCapture(PieceLocation{C, 4});
    std::vector<Move> oneLeftCaptureMoves = game.getPieceMoves(boardOneLeftCaptureMove, D, 5);
    ASSERT_EQ(oneLeftCaptureMoves.size(), 1);
    ASSERT_EQ(std::find(oneLeftCaptureMoves.begin(), oneLeftCaptureMoves.end(), oneLeftCaptureMoveResult) != oneLeftCaptureMoves.end(), true);

    Board boardTwoLeftCaptureMove = Board(true);
    boardTwoLeftCaptureMove(E, 7) = new Pawn(WHITE);
    boardTwoLeftCaptureMove(D, 6) = new Pawn(BLACK);
    boardTwoLeftCaptureMove(F, 6) = new Pawn(WHITE);
    boardTwoLeftCaptureMove(B, 4) = new Pawn(BLACK);
    Move twoLeftCaptureMoveResult = Move("E7A3");
    twoLeftCaptureMoveResult.addCapture(PieceLocation{D, 6});
    twoLeftCaptureMoveResult.addCapture(PieceLocation{B, 4});
    std::vector<Move> twoLeftCaptureMoves = game.getPieceMoves(boardTwoLeftCaptureMove, E, 7);
    ASSERT_EQ(twoLeftCaptureMoves.size(), 1);
    ASSERT_EQ(std::find(twoLeftCaptureMoves.begin(), twoLeftCaptureMoves.end(), twoLeftCaptureMoveResult) != twoLeftCaptureMoves.end(), true);

    Board boardOneRightCaptureMove = Board(true);
    boardOneRightCaptureMove(D, 5) = new Pawn(WHITE);
    boardOneRightCaptureMove(C, 4) = new Pawn(WHITE);
    boardOneRightCaptureMove(E, 4) = new Pawn(BLACK);
    Move oneRightCaptureMoveResult = Move("D5F3");
    oneRightCaptureMoveResult.addCapture(PieceLocation{E, 4});
    std::vector<Move> oneRightCaptureMoves = game.getPieceMoves(boardOneRightCaptureMove, D, 5);
    ASSERT_EQ(oneRightCaptureMoves.size(), 1);
    ASSERT_EQ(std::find(oneRightCaptureMoves.begin(), oneRightCaptureMoves.end(), oneRightCaptureMoveResult) != oneRightCaptureMoves.end(), true);

    Board boardTwoRightCaptureMove = Board(true);
    boardTwoRightCaptureMove(B, 7) = new Pawn(WHITE);
    boardTwoRightCaptureMove(A, 6) = new Pawn(WHITE);
    boardTwoRightCaptureMove(C, 6) = new Pawn(BLACK);
    boardTwoRightCaptureMove(E, 4) = new Pawn(BLACK);
    Move twoRightCaptureMoveResult = Move("B7F3");
    twoRightCaptureMoveResult.addCapture(PieceLocation{C, 6});
    twoRightCaptureMoveResult.addCapture(PieceLocation{E, 4});
    std::vector<Move> twoRightCaptureMoves = game.getPieceMoves(boardTwoRightCaptureMove, B, 7);
    ASSERT_EQ(twoRightCaptureMoves.size(), 1);
    ASSERT_EQ(std::find(twoRightCaptureMoves.begin(), twoRightCaptureMoves.end(), twoRightCaptureMoveResult) != twoRightCaptureMoves.end(), true);

    Board boardOneLeftOneRightCaptureMove = Board(true);
    boardOneLeftOneRightCaptureMove(D, 7) = new Pawn(WHITE);
    boardOneLeftOneRightCaptureMove(C, 6) = new Pawn(BLACK);
    boardOneLeftOneRightCaptureMove(E, 6) = new Pawn(WHITE);
    boardOneLeftOneRightCaptureMove(C, 4) = new Pawn(BLACK);
    Move oneLeftOneRightCaptureMoveResult = Move("D7D3");
    oneLeftOneRightCaptureMoveResult.addCapture(PieceLocation{C, 6});
    oneLeftOneRightCaptureMoveResult.addCapture(PieceLocation{C, 4});
    std::vector<Move> oneLeftOneRightCaptureMoves = game.getPieceMoves(boardOneLeftOneRightCaptureMove, D, 7);
    ASSERT_EQ(oneLeftOneRightCaptureMoves.size(), 1);
    ASSERT_EQ(std::find(oneLeftOneRightCaptureMoves.begin(), oneLeftOneRightCaptureMoves.end(), oneLeftOneRightCaptureMoveResult) != oneLeftOneRightCaptureMoves.end(), true);

    Board boardOneRightOneLeftCaptureMove = Board(true);
    boardOneRightOneLeftCaptureMove(D, 7) = new Pawn(WHITE);
    boardOneRightOneLeftCaptureMove(C, 6) = new Pawn(WHITE);
    boardOneRightOneLeftCaptureMove(E, 6) = new Pawn(BLACK);
    boardOneRightOneLeftCaptureMove(E, 4) = new Pawn(BLACK);
    Move oneRightOneLeftCaptureMoveResult = Move("D7D3");
    oneRightOneLeftCaptureMoveResult.addCapture(PieceLocation{E, 6});
    oneRightOneLeftCaptureMoveResult.addCapture(PieceLocation{E, 4});
    std::vector<Move> oneRightOneLeftCaptureMoves = game.getPieceMoves(boardOneRightOneLeftCaptureMove, D, 7);
    ASSERT_EQ(oneRightOneLeftCaptureMoves.size(), 1);
    ASSERT_EQ(std::find(oneRightOneLeftCaptureMoves.begin(), oneRightOneLeftCaptureMoves.end(), oneRightOneLeftCaptureMoveResult) != oneRightOneLeftCaptureMoves.end(), true);
}

TEST(GameTest, blackPawnMovesWithoutCapture) {
    Game game = Game();

    Board boardTwoMoves = Board(true);
    boardTwoMoves(D, 5) = new Pawn(BLACK);
    std::vector<Move> twoMoves = game.getPieceMoves(boardTwoMoves, D, 5);
    ASSERT_EQ(twoMoves.size(), 2);
    ASSERT_EQ(std::find(twoMoves.begin(), twoMoves.end(), Move("D5C6")) != twoMoves.end(), true);
    ASSERT_EQ(std::find(twoMoves.begin(), twoMoves.end(), Move("D5E6")) != twoMoves.end(), true);

    Board boardOneMove = Board(true);
    boardOneMove(D, 5) = new Pawn(BLACK);
    boardOneMove(C, 6) = new Pawn(BLACK);
    std::vector<Move> oneMove = game.getPieceMoves(boardOneMove, D, 5);
    ASSERT_EQ(oneMove.size(), 1);
    ASSERT_EQ(std::find(oneMove.begin(), oneMove.end(), Move("D5E6")) != oneMove.end(), true);

    Board boardZeroMoves = Board(true);
    boardZeroMoves(D, 5) = new Pawn(BLACK);
    boardZeroMoves(C, 6) = new Pawn(BLACK);
    boardZeroMoves(E, 6) = new Pawn(BLACK);
    std::vector<Move> zeroMoves = game.getPieceMoves(boardZeroMoves, D, 5);
    ASSERT_EQ(zeroMoves.size(), 0);

    Board boardMovesWithAnOutOfBounds = Board(true);
    boardMovesWithAnOutOfBounds(A, 1) = new Pawn(BLACK);
    std::vector<Move> oneOutOfBoundsMove = game.getPieceMoves(boardMovesWithAnOutOfBounds, A, 1);
    ASSERT_EQ(oneOutOfBoundsMove.size(), 1);
    ASSERT_EQ(std::find(oneOutOfBoundsMove.begin(), oneOutOfBoundsMove.end(), Move("A1B2")) != oneOutOfBoundsMove.end(), true);

    Board boardMovesWithAllOutOfBounds = Board(true);
    boardMovesWithAllOutOfBounds(A, 8) = new Pawn(BLACK);
    std::vector<Move> allOutOfBoundsMoves = game.getPieceMoves(boardMovesWithAllOutOfBounds, A, 8);
    ASSERT_EQ(allOutOfBoundsMoves.size(), 0);
}
