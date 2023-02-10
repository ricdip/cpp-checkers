// clang-format off
#include <gtest/gtest.h>
// clang-format on
#include "../lib/include/Game.hpp"
#include <algorithm>
#include <vector>

//
// pawn
//

TEST(GameTest, whitePawnMovesWithoutCapture) {
  Game game = Game();

  Board boardTwoMoves = Board(true);
  boardTwoMoves(D, 5) = new Pawn(WHITE);
  std::vector<Move> twoMoves = game.getPieceMoves(boardTwoMoves, D, 5);
  ASSERT_EQ(twoMoves.size(), 2);
  ASSERT_EQ(std::find(twoMoves.begin(), twoMoves.end(), Move("D5C4")) !=
                twoMoves.end(),
            true);
  ASSERT_EQ(std::find(twoMoves.begin(), twoMoves.end(), Move("D5E4")) !=
                twoMoves.end(),
            true);

  Board boardOneMove = Board(true);
  boardOneMove(D, 5) = new Pawn(WHITE);
  boardOneMove(C, 4) = new Pawn(WHITE);
  std::vector<Move> oneMove = game.getPieceMoves(boardOneMove, D, 5);
  ASSERT_EQ(oneMove.size(), 1);
  ASSERT_EQ(std::find(oneMove.begin(), oneMove.end(), Move("D5E4")) !=
                oneMove.end(),
            true);

  Board boardZeroMoves = Board(true);
  boardZeroMoves(D, 5) = new Pawn(WHITE);
  boardZeroMoves(C, 4) = new Pawn(WHITE);
  boardZeroMoves(E, 4) = new Pawn(WHITE);
  std::vector<Move> zeroMoves = game.getPieceMoves(boardZeroMoves, D, 5);
  ASSERT_EQ(zeroMoves.size(), 0);

  Board boardMovesWithAnOutOfBounds = Board(true);
  boardMovesWithAnOutOfBounds(A, 8) = new Pawn(WHITE);
  std::vector<Move> oneOutOfBoundsMove =
      game.getPieceMoves(boardMovesWithAnOutOfBounds, A, 8);
  ASSERT_EQ(oneOutOfBoundsMove.size(), 1);
  ASSERT_EQ(std::find(oneOutOfBoundsMove.begin(), oneOutOfBoundsMove.end(),
                      Move("A8B7")) != oneOutOfBoundsMove.end(),
            true);

  Board boardMovesWithAllOutOfBounds = Board(true);
  boardMovesWithAllOutOfBounds(A, 1) = new Pawn(WHITE);
  std::vector<Move> allOutOfBoundsMoves =
      game.getPieceMoves(boardMovesWithAllOutOfBounds, A, 1);
  ASSERT_EQ(allOutOfBoundsMoves.size(), 0);
}

TEST(GameTest, blackPawnMovesWithoutCapture) {
  Game game = Game();

  Board boardTwoMoves = Board(true);
  boardTwoMoves(D, 5) = new Pawn(BLACK);
  std::vector<Move> twoMoves = game.getPieceMoves(boardTwoMoves, D, 5);
  ASSERT_EQ(twoMoves.size(), 2);
  ASSERT_EQ(std::find(twoMoves.begin(), twoMoves.end(), Move("D5C6")) !=
                twoMoves.end(),
            true);
  ASSERT_EQ(std::find(twoMoves.begin(), twoMoves.end(), Move("D5E6")) !=
                twoMoves.end(),
            true);

  Board boardOneMove = Board(true);
  boardOneMove(D, 5) = new Pawn(BLACK);
  boardOneMove(C, 6) = new Pawn(BLACK);
  std::vector<Move> oneMove = game.getPieceMoves(boardOneMove, D, 5);
  ASSERT_EQ(oneMove.size(), 1);
  ASSERT_EQ(std::find(oneMove.begin(), oneMove.end(), Move("D5E6")) !=
                oneMove.end(),
            true);

  Board boardZeroMoves = Board(true);
  boardZeroMoves(D, 5) = new Pawn(BLACK);
  boardZeroMoves(C, 6) = new Pawn(BLACK);
  boardZeroMoves(E, 6) = new Pawn(BLACK);
  std::vector<Move> zeroMoves = game.getPieceMoves(boardZeroMoves, D, 5);
  ASSERT_EQ(zeroMoves.size(), 0);

  Board boardMovesWithAnOutOfBounds = Board(true);
  boardMovesWithAnOutOfBounds(A, 1) = new Pawn(BLACK);
  std::vector<Move> oneOutOfBoundsMove =
      game.getPieceMoves(boardMovesWithAnOutOfBounds, A, 1);
  ASSERT_EQ(oneOutOfBoundsMove.size(), 1);
  ASSERT_EQ(std::find(oneOutOfBoundsMove.begin(), oneOutOfBoundsMove.end(),
                      Move("A1B2")) != oneOutOfBoundsMove.end(),
            true);

  Board boardMovesWithAllOutOfBounds = Board(true);
  boardMovesWithAllOutOfBounds(A, 8) = new Pawn(BLACK);
  std::vector<Move> allOutOfBoundsMoves =
      game.getPieceMoves(boardMovesWithAllOutOfBounds, A, 8);
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
  std::vector<Move> oneLeftCaptureMoves =
      game.getPieceMoves(boardOneLeftCaptureMove, D, 5);
  ASSERT_EQ(oneLeftCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneLeftCaptureMoves.begin(), oneLeftCaptureMoves.end(),
                      oneLeftCaptureMoveResult) != oneLeftCaptureMoves.end(),
            true);

  Board boardTwoLeftCaptureMove = Board(true);
  boardTwoLeftCaptureMove(E, 7) = new Pawn(WHITE);
  boardTwoLeftCaptureMove(D, 6) = new Pawn(BLACK);
  boardTwoLeftCaptureMove(F, 6) = new Pawn(WHITE);
  boardTwoLeftCaptureMove(B, 4) = new Pawn(BLACK);
  Move twoLeftCaptureMoveResult = Move("E7A3");
  twoLeftCaptureMoveResult.addCapture(PieceLocation{D, 6});
  twoLeftCaptureMoveResult.addCapture(PieceLocation{B, 4});
  std::vector<Move> twoLeftCaptureMoves =
      game.getPieceMoves(boardTwoLeftCaptureMove, E, 7);
  ASSERT_EQ(twoLeftCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(twoLeftCaptureMoves.begin(), twoLeftCaptureMoves.end(),
                      twoLeftCaptureMoveResult) != twoLeftCaptureMoves.end(),
            true);

  Board boardOneRightCaptureMove = Board(true);
  boardOneRightCaptureMove(D, 5) = new Pawn(WHITE);
  boardOneRightCaptureMove(C, 4) = new Pawn(WHITE);
  boardOneRightCaptureMove(E, 4) = new Pawn(BLACK);
  Move oneRightCaptureMoveResult = Move("D5F3");
  oneRightCaptureMoveResult.addCapture(PieceLocation{E, 4});
  std::vector<Move> oneRightCaptureMoves =
      game.getPieceMoves(boardOneRightCaptureMove, D, 5);
  ASSERT_EQ(oneRightCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneRightCaptureMoves.begin(), oneRightCaptureMoves.end(),
                      oneRightCaptureMoveResult) != oneRightCaptureMoves.end(),
            true);

  Board boardTwoRightCaptureMove = Board(true);
  boardTwoRightCaptureMove(B, 7) = new Pawn(WHITE);
  boardTwoRightCaptureMove(A, 6) = new Pawn(WHITE);
  boardTwoRightCaptureMove(C, 6) = new Pawn(BLACK);
  boardTwoRightCaptureMove(E, 4) = new Pawn(BLACK);
  Move twoRightCaptureMoveResult = Move("B7F3");
  twoRightCaptureMoveResult.addCapture(PieceLocation{C, 6});
  twoRightCaptureMoveResult.addCapture(PieceLocation{E, 4});
  std::vector<Move> twoRightCaptureMoves =
      game.getPieceMoves(boardTwoRightCaptureMove, B, 7);
  ASSERT_EQ(twoRightCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(twoRightCaptureMoves.begin(), twoRightCaptureMoves.end(),
                      twoRightCaptureMoveResult) != twoRightCaptureMoves.end(),
            true);

  Board boardOneLeftOneRightCaptureMove = Board(true);
  boardOneLeftOneRightCaptureMove(D, 7) = new Pawn(WHITE);
  boardOneLeftOneRightCaptureMove(C, 6) = new Pawn(BLACK);
  boardOneLeftOneRightCaptureMove(E, 6) = new Pawn(WHITE);
  boardOneLeftOneRightCaptureMove(C, 4) = new Pawn(BLACK);
  Move oneLeftOneRightCaptureMoveResult = Move("D7D3");
  oneLeftOneRightCaptureMoveResult.addCapture(PieceLocation{C, 6});
  oneLeftOneRightCaptureMoveResult.addCapture(PieceLocation{C, 4});
  std::vector<Move> oneLeftOneRightCaptureMoves =
      game.getPieceMoves(boardOneLeftOneRightCaptureMove, D, 7);
  ASSERT_EQ(oneLeftOneRightCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneLeftOneRightCaptureMoves.begin(),
                      oneLeftOneRightCaptureMoves.end(),
                      oneLeftOneRightCaptureMoveResult) !=
                oneLeftOneRightCaptureMoves.end(),
            true);

  Board boardOneRightOneLeftCaptureMove = Board(true);
  boardOneRightOneLeftCaptureMove(D, 7) = new Pawn(WHITE);
  boardOneRightOneLeftCaptureMove(C, 6) = new Pawn(WHITE);
  boardOneRightOneLeftCaptureMove(E, 6) = new Pawn(BLACK);
  boardOneRightOneLeftCaptureMove(E, 4) = new Pawn(BLACK);
  Move oneRightOneLeftCaptureMoveResult = Move("D7D3");
  oneRightOneLeftCaptureMoveResult.addCapture(PieceLocation{E, 6});
  oneRightOneLeftCaptureMoveResult.addCapture(PieceLocation{E, 4});
  std::vector<Move> oneRightOneLeftCaptureMoves =
      game.getPieceMoves(boardOneRightOneLeftCaptureMove, D, 7);
  ASSERT_EQ(oneRightOneLeftCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneRightOneLeftCaptureMoves.begin(),
                      oneRightOneLeftCaptureMoves.end(),
                      oneRightOneLeftCaptureMoveResult) !=
                oneRightOneLeftCaptureMoves.end(),
            true);
}

TEST(GameTest, blackPawnMovesWithCapture) {
  Game game = Game();

  Board boardOneLeftCaptureMove = Board(true);
  boardOneLeftCaptureMove(D, 3) = new Pawn(BLACK);
  boardOneLeftCaptureMove(C, 4) = new Pawn(WHITE);
  boardOneLeftCaptureMove(E, 4) = new Pawn(BLACK);
  Move oneLeftCaptureMoveResult = Move("D3B5");
  oneLeftCaptureMoveResult.addCapture(PieceLocation{C, 4});
  std::vector<Move> oneLeftCaptureMoves =
      game.getPieceMoves(boardOneLeftCaptureMove, D, 3);
  ASSERT_EQ(oneLeftCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneLeftCaptureMoves.begin(), oneLeftCaptureMoves.end(),
                      oneLeftCaptureMoveResult) != oneLeftCaptureMoves.end(),
            true);

  Board boardTwoLeftCaptureMove = Board(true);
  boardTwoLeftCaptureMove(E, 1) = new Pawn(BLACK);
  boardTwoLeftCaptureMove(D, 2) = new Pawn(WHITE);
  boardTwoLeftCaptureMove(F, 2) = new Pawn(BLACK);
  boardTwoLeftCaptureMove(B, 4) = new Pawn(WHITE);
  Move twoLeftCaptureMoveResult = Move("E1A5");
  twoLeftCaptureMoveResult.addCapture(PieceLocation{D, 2});
  twoLeftCaptureMoveResult.addCapture(PieceLocation{B, 4});
  std::vector<Move> twoLeftCaptureMoves =
      game.getPieceMoves(boardTwoLeftCaptureMove, E, 1);
  ASSERT_EQ(twoLeftCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(twoLeftCaptureMoves.begin(), twoLeftCaptureMoves.end(),
                      twoLeftCaptureMoveResult) != twoLeftCaptureMoves.end(),
            true);

  Board boardOneRightCaptureMove = Board(true);
  boardOneRightCaptureMove(D, 3) = new Pawn(BLACK);
  boardOneRightCaptureMove(C, 4) = new Pawn(BLACK);
  boardOneRightCaptureMove(E, 4) = new Pawn(WHITE);
  Move oneRightCaptureMoveResult = Move("D3F5");
  oneRightCaptureMoveResult.addCapture(PieceLocation{E, 4});
  std::vector<Move> oneRightCaptureMoves =
      game.getPieceMoves(boardOneRightCaptureMove, D, 3);
  ASSERT_EQ(oneRightCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneRightCaptureMoves.begin(), oneRightCaptureMoves.end(),
                      oneRightCaptureMoveResult) != oneRightCaptureMoves.end(),
            true);

  Board boardTwoRightCaptureMove = Board(true);
  boardTwoRightCaptureMove(B, 1) = new Pawn(BLACK);
  boardTwoRightCaptureMove(A, 2) = new Pawn(BLACK);
  boardTwoRightCaptureMove(C, 2) = new Pawn(WHITE);
  boardTwoRightCaptureMove(E, 4) = new Pawn(WHITE);
  Move twoRightCaptureMoveResult = Move("B1F5");
  twoRightCaptureMoveResult.addCapture(PieceLocation{C, 2});
  twoRightCaptureMoveResult.addCapture(PieceLocation{E, 4});
  std::vector<Move> twoRightCaptureMoves =
      game.getPieceMoves(boardTwoRightCaptureMove, B, 1);
  ASSERT_EQ(twoRightCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(twoRightCaptureMoves.begin(), twoRightCaptureMoves.end(),
                      twoRightCaptureMoveResult) != twoRightCaptureMoves.end(),
            true);

  Board boardOneLeftOneRightCaptureMove = Board(true);
  boardOneLeftOneRightCaptureMove(D, 1) = new Pawn(BLACK);
  boardOneLeftOneRightCaptureMove(C, 2) = new Pawn(WHITE);
  boardOneLeftOneRightCaptureMove(E, 2) = new Pawn(BLACK);
  boardOneLeftOneRightCaptureMove(C, 4) = new Pawn(WHITE);
  Move oneLeftOneRightCaptureMoveResult = Move("D1D5");
  oneLeftOneRightCaptureMoveResult.addCapture(PieceLocation{C, 2});
  oneLeftOneRightCaptureMoveResult.addCapture(PieceLocation{C, 4});
  std::vector<Move> oneLeftOneRightCaptureMoves =
      game.getPieceMoves(boardOneLeftOneRightCaptureMove, D, 1);
  ASSERT_EQ(oneLeftOneRightCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneLeftOneRightCaptureMoves.begin(),
                      oneLeftOneRightCaptureMoves.end(),
                      oneLeftOneRightCaptureMoveResult) !=
                oneLeftOneRightCaptureMoves.end(),
            true);

  Board boardOneRightOneLeftCaptureMove = Board(true);
  boardOneRightOneLeftCaptureMove(D, 1) = new Pawn(BLACK);
  boardOneRightOneLeftCaptureMove(C, 2) = new Pawn(BLACK);
  boardOneRightOneLeftCaptureMove(E, 2) = new Pawn(WHITE);
  boardOneRightOneLeftCaptureMove(E, 4) = new Pawn(WHITE);
  Move oneRightOneLeftCaptureMoveResult = Move("D1D5");
  oneRightOneLeftCaptureMoveResult.addCapture(PieceLocation{E, 2});
  oneRightOneLeftCaptureMoveResult.addCapture(PieceLocation{E, 4});
  std::vector<Move> oneRightOneLeftCaptureMoves =
      game.getPieceMoves(boardOneRightOneLeftCaptureMove, D, 1);
  ASSERT_EQ(oneRightOneLeftCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneRightOneLeftCaptureMoves.begin(),
                      oneRightOneLeftCaptureMoves.end(),
                      oneRightOneLeftCaptureMoveResult) !=
                oneRightOneLeftCaptureMoves.end(),
            true);
}

//
// queens
//

TEST(GameTest, whiteQueenMovesWithoutCapture) {
  Game game = Game();

  Board boardFourMoves = Board(true);
  boardFourMoves(D, 5) = new Queen(WHITE);
  std::vector<Move> fourMoves = game.getPieceMoves(boardFourMoves, D, 5);
  ASSERT_EQ(fourMoves.size(), 4);
  ASSERT_EQ(std::find(fourMoves.begin(), fourMoves.end(), Move("D5C4")) !=
                fourMoves.end(),
            true);
  ASSERT_EQ(std::find(fourMoves.begin(), fourMoves.end(), Move("D5E4")) !=
                fourMoves.end(),
            true);
  ASSERT_EQ(std::find(fourMoves.begin(), fourMoves.end(), Move("D5C6")) !=
                fourMoves.end(),
            true);
  ASSERT_EQ(std::find(fourMoves.begin(), fourMoves.end(), Move("D5E6")) !=
                fourMoves.end(),
            true);

  Board boardThreeMove = Board(true);
  boardThreeMove(D, 5) = new Queen(WHITE);
  boardThreeMove(C, 4) = new Pawn(WHITE);
  std::vector<Move> threeMoves = game.getPieceMoves(boardThreeMove, D, 5);
  ASSERT_EQ(threeMoves.size(), 3);
  ASSERT_EQ(std::find(threeMoves.begin(), threeMoves.end(), Move("D5E4")) !=
                threeMoves.end(),
            true);
  ASSERT_EQ(std::find(threeMoves.begin(), threeMoves.end(), Move("D5E6")) !=
                threeMoves.end(),
            true);
  ASSERT_EQ(std::find(threeMoves.begin(), threeMoves.end(), Move("D5C6")) !=
                threeMoves.end(),
            true);

  Board boardZeroMoves = Board(true);
  boardZeroMoves(D, 5) = new Queen(WHITE);
  boardZeroMoves(C, 4) = new Pawn(WHITE);
  boardZeroMoves(E, 4) = new Pawn(WHITE);
  boardZeroMoves(C, 6) = new Pawn(WHITE);
  boardZeroMoves(E, 6) = new Pawn(WHITE);
  std::vector<Move> zeroMoves = game.getPieceMoves(boardZeroMoves, D, 5);
  ASSERT_EQ(zeroMoves.size(), 0);

  Board boardMovesWithOutOfBounds = Board(true);
  boardMovesWithOutOfBounds(A, 8) = new Queen(WHITE);
  std::vector<Move> outOfBoundsMoves =
      game.getPieceMoves(boardMovesWithOutOfBounds, A, 8);
  ASSERT_EQ(outOfBoundsMoves.size(), 1);
  ASSERT_EQ(std::find(outOfBoundsMoves.begin(), outOfBoundsMoves.end(),
                      Move("A8B7")) != outOfBoundsMoves.end(),
            true);
}

TEST(GameTest, blackQueenMovesWithoutCapture) {
  Game game = Game();

  Board boardFourMoves = Board(true);
  boardFourMoves(D, 5) = new Queen(BLACK);
  std::vector<Move> fourMoves = game.getPieceMoves(boardFourMoves, D, 5);
  ASSERT_EQ(fourMoves.size(), 4);
  ASSERT_EQ(std::find(fourMoves.begin(), fourMoves.end(), Move("D5C4")) !=
                fourMoves.end(),
            true);
  ASSERT_EQ(std::find(fourMoves.begin(), fourMoves.end(), Move("D5E4")) !=
                fourMoves.end(),
            true);
  ASSERT_EQ(std::find(fourMoves.begin(), fourMoves.end(), Move("D5C6")) !=
                fourMoves.end(),
            true);
  ASSERT_EQ(std::find(fourMoves.begin(), fourMoves.end(), Move("D5E6")) !=
                fourMoves.end(),
            true);

  Board boardThreeMoves = Board(true);
  boardThreeMoves(D, 5) = new Queen(BLACK);
  boardThreeMoves(C, 4) = new Pawn(BLACK);
  std::vector<Move> threeMoves = game.getPieceMoves(boardThreeMoves, D, 5);
  ASSERT_EQ(threeMoves.size(), 3);
  ASSERT_EQ(std::find(threeMoves.begin(), threeMoves.end(), Move("D5E4")) !=
                threeMoves.end(),
            true);
  ASSERT_EQ(std::find(threeMoves.begin(), threeMoves.end(), Move("D5E6")) !=
                threeMoves.end(),
            true);
  ASSERT_EQ(std::find(threeMoves.begin(), threeMoves.end(), Move("D5C6")) !=
                threeMoves.end(),
            true);

  Board boardZeroMoves = Board(true);
  boardZeroMoves(D, 5) = new Queen(BLACK);
  boardZeroMoves(C, 4) = new Pawn(BLACK);
  boardZeroMoves(E, 4) = new Pawn(BLACK);
  boardZeroMoves(C, 6) = new Pawn(BLACK);
  boardZeroMoves(E, 6) = new Pawn(BLACK);
  std::vector<Move> zeroMoves = game.getPieceMoves(boardZeroMoves, D, 5);
  ASSERT_EQ(zeroMoves.size(), 0);

  Board boardMovesWithOutOfBounds = Board(true);
  boardMovesWithOutOfBounds(A, 8) = new Queen(BLACK);
  std::vector<Move> outOfBoundsMoves =
      game.getPieceMoves(boardMovesWithOutOfBounds, A, 8);
  ASSERT_EQ(outOfBoundsMoves.size(), 1);
  ASSERT_EQ(std::find(outOfBoundsMoves.begin(), outOfBoundsMoves.end(),
                      Move("A8B7")) != outOfBoundsMoves.end(),
            true);
}

TEST(GameTest, whiteQueenMovesWithCapture) {
  Game game = Game();

  Board boardOneLeftForwardCaptureMove = Board(true);
  boardOneLeftForwardCaptureMove(D, 5) = new Queen(WHITE);
  boardOneLeftForwardCaptureMove(C, 4) = new Pawn(BLACK);
  boardOneLeftForwardCaptureMove(E, 4) = new Pawn(WHITE);
  boardOneLeftForwardCaptureMove(E, 6) = new Pawn(WHITE);
  boardOneLeftForwardCaptureMove(C, 6) = new Pawn(WHITE);
  Move oneLeftForwardCaptureMoveResult = Move("D5B3");
  oneLeftForwardCaptureMoveResult.addCapture(PieceLocation{C, 4});
  std::vector<Move> oneLeftForwardCaptureMoves =
      game.getPieceMoves(boardOneLeftForwardCaptureMove, D, 5);
  ASSERT_EQ(oneLeftForwardCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneLeftForwardCaptureMoves.begin(),
                      oneLeftForwardCaptureMoves.end(),
                      oneLeftForwardCaptureMoveResult) !=
                oneLeftForwardCaptureMoves.end(),
            true);

  Board boardOneLeftBackCaptureMove = Board(true);
  boardOneLeftBackCaptureMove(D, 3) = new Queen(WHITE);
  boardOneLeftBackCaptureMove(C, 4) = new Pawn(BLACK);
  boardOneLeftBackCaptureMove(E, 4) = new Pawn(WHITE);
  boardOneLeftBackCaptureMove(E, 2) = new Pawn(WHITE);
  boardOneLeftBackCaptureMove(C, 2) = new Pawn(WHITE);
  Move oneLeftBackCaptureMoveResult = Move("D3B5");
  oneLeftBackCaptureMoveResult.addCapture(PieceLocation{C, 4});
  std::vector<Move> oneLeftBackCaptureMoves =
      game.getPieceMoves(boardOneLeftBackCaptureMove, D, 3);
  ASSERT_EQ(oneLeftBackCaptureMoves.size(), 1);
  ASSERT_EQ(
      std::find(oneLeftBackCaptureMoves.begin(), oneLeftBackCaptureMoves.end(),
                oneLeftBackCaptureMoveResult) != oneLeftBackCaptureMoves.end(),
      true);

  Board boardTwoLeftForwardCaptureMove = Board(true);
  boardTwoLeftForwardCaptureMove(E, 7) = new Queen(WHITE);
  boardTwoLeftForwardCaptureMove(D, 6) = new Pawn(BLACK);
  boardTwoLeftForwardCaptureMove(F, 6) = new Pawn(WHITE);
  boardTwoLeftForwardCaptureMove(B, 4) = new Pawn(BLACK);
  boardTwoLeftForwardCaptureMove(D, 8) = new Pawn(WHITE);
  boardTwoLeftForwardCaptureMove(F, 8) = new Pawn(WHITE);
  Move twoLeftForwardCaptureMoveResult = Move("E7A3");
  twoLeftForwardCaptureMoveResult.addCapture(PieceLocation{D, 6});
  twoLeftForwardCaptureMoveResult.addCapture(PieceLocation{B, 4});
  std::vector<Move> twoLeftForwardCaptureMoves =
      game.getPieceMoves(boardTwoLeftForwardCaptureMove, E, 7);
  ASSERT_EQ(twoLeftForwardCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(twoLeftForwardCaptureMoves.begin(),
                      twoLeftForwardCaptureMoves.end(),
                      twoLeftForwardCaptureMoveResult) !=
                twoLeftForwardCaptureMoves.end(),
            true);

  Board boardTwoLeftBackCaptureMove = Board(true);
  boardTwoLeftBackCaptureMove(E, 1) = new Queen(WHITE);
  boardTwoLeftBackCaptureMove(D, 2) = new Pawn(BLACK);
  boardTwoLeftBackCaptureMove(F, 2) = new Pawn(WHITE);
  boardTwoLeftBackCaptureMove(B, 4) = new Pawn(BLACK);
  Move twoLeftBackCaptureMoveResult = Move("E1A5");
  twoLeftBackCaptureMoveResult.addCapture(PieceLocation{D, 2});
  twoLeftBackCaptureMoveResult.addCapture(PieceLocation{B, 4});
  std::vector<Move> twoLeftBackCaptureMoves =
      game.getPieceMoves(boardTwoLeftBackCaptureMove, E, 1);
  ASSERT_EQ(twoLeftBackCaptureMoves.size(), 1);
  ASSERT_EQ(
      std::find(twoLeftBackCaptureMoves.begin(), twoLeftBackCaptureMoves.end(),
                twoLeftBackCaptureMoveResult) != twoLeftBackCaptureMoves.end(),
      true);

  Board boardOneRightForwardCaptureMove = Board(true);
  boardOneRightForwardCaptureMove(D, 5) = new Queen(WHITE);
  boardOneRightForwardCaptureMove(C, 4) = new Pawn(WHITE);
  boardOneRightForwardCaptureMove(E, 4) = new Pawn(BLACK);
  boardOneRightForwardCaptureMove(C, 6) = new Pawn(WHITE);
  boardOneRightForwardCaptureMove(E, 6) = new Pawn(WHITE);
  Move oneRightForwardCaptureMoveResult = Move("D5F3");
  oneRightForwardCaptureMoveResult.addCapture(PieceLocation{E, 4});
  std::vector<Move> oneRightForwardCaptureMoves =
      game.getPieceMoves(boardOneRightForwardCaptureMove, D, 5);
  ASSERT_EQ(oneRightForwardCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneRightForwardCaptureMoves.begin(),
                      oneRightForwardCaptureMoves.end(),
                      oneRightForwardCaptureMoveResult) !=
                oneRightForwardCaptureMoves.end(),
            true);

  Board boardOneRightBackCaptureMove = Board(true);
  boardOneRightBackCaptureMove(D, 3) = new Queen(WHITE);
  boardOneRightBackCaptureMove(C, 4) = new Pawn(WHITE);
  boardOneRightBackCaptureMove(E, 4) = new Pawn(BLACK);
  boardOneRightBackCaptureMove(C, 2) = new Pawn(WHITE);
  boardOneRightBackCaptureMove(E, 2) = new Pawn(WHITE);
  Move oneRightBackCaptureMoveResult = Move("D3F5");
  oneRightBackCaptureMoveResult.addCapture(PieceLocation{E, 4});
  std::vector<Move> oneRightBackCaptureMoves =
      game.getPieceMoves(boardOneRightBackCaptureMove, D, 3);
  ASSERT_EQ(oneRightBackCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneRightBackCaptureMoves.begin(),
                      oneRightBackCaptureMoves.end(),
                      oneRightBackCaptureMoveResult) !=
                oneRightBackCaptureMoves.end(),
            true);

  Board boardTwoRightBackCaptureMove = Board(true);
  boardTwoRightBackCaptureMove(B, 1) = new Queen(WHITE);
  boardTwoRightBackCaptureMove(A, 2) = new Pawn(WHITE);
  boardTwoRightBackCaptureMove(C, 2) = new Pawn(BLACK);
  boardTwoRightBackCaptureMove(E, 4) = new Pawn(BLACK);
  Move twoRightBackCaptureMoveResult = Move("B1F5");
  twoRightBackCaptureMoveResult.addCapture(PieceLocation{C, 2});
  twoRightBackCaptureMoveResult.addCapture(PieceLocation{E, 4});
  std::vector<Move> twoRightBackCaptureMoves =
      game.getPieceMoves(boardTwoRightBackCaptureMove, B, 1);
  ASSERT_EQ(twoRightBackCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(twoRightBackCaptureMoves.begin(),
                      twoRightBackCaptureMoves.end(),
                      twoRightBackCaptureMoveResult) !=
                twoRightBackCaptureMoves.end(),
            true);

  Board boardOneLeftOneRightForwardCaptureMove = Board(true);
  boardOneLeftOneRightForwardCaptureMove(D, 7) = new Queen(WHITE);
  boardOneLeftOneRightForwardCaptureMove(C, 6) = new Pawn(BLACK);
  boardOneLeftOneRightForwardCaptureMove(E, 6) = new Pawn(WHITE);
  boardOneLeftOneRightForwardCaptureMove(C, 4) = new Pawn(BLACK);
  boardOneLeftOneRightForwardCaptureMove(E, 8) = new Pawn(WHITE);
  boardOneLeftOneRightForwardCaptureMove(C, 8) = new Pawn(WHITE);
  Move oneLeftOneRightForwardCaptureMoveResult = Move("D7D3");
  oneLeftOneRightForwardCaptureMoveResult.addCapture(PieceLocation{C, 6});
  oneLeftOneRightForwardCaptureMoveResult.addCapture(PieceLocation{C, 4});
  std::vector<Move> oneLeftOneRightForwardCaptureMoves =
      game.getPieceMoves(boardOneLeftOneRightForwardCaptureMove, D, 7);
  ASSERT_EQ(oneLeftOneRightForwardCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneLeftOneRightForwardCaptureMoves.begin(),
                      oneLeftOneRightForwardCaptureMoves.end(),
                      oneLeftOneRightForwardCaptureMoveResult) !=
                oneLeftOneRightForwardCaptureMoves.end(),
            true);

  Board boardOneRightOneLeftForwardCaptureMove = Board(true);
  boardOneRightOneLeftForwardCaptureMove(D, 7) = new Queen(WHITE);
  boardOneRightOneLeftForwardCaptureMove(C, 6) = new Pawn(WHITE);
  boardOneRightOneLeftForwardCaptureMove(E, 6) = new Pawn(BLACK);
  boardOneRightOneLeftForwardCaptureMove(E, 4) = new Pawn(BLACK);
  boardOneRightOneLeftForwardCaptureMove(C, 8) = new Pawn(WHITE);
  boardOneRightOneLeftForwardCaptureMove(E, 8) = new Pawn(WHITE);
  Move oneRightOneLeftForwardCaptureMoveResult = Move("D7D3");
  oneRightOneLeftForwardCaptureMoveResult.addCapture(PieceLocation{E, 6});
  oneRightOneLeftForwardCaptureMoveResult.addCapture(PieceLocation{E, 4});
  std::vector<Move> oneRightOneLeftForwardCaptureMoves =
      game.getPieceMoves(boardOneRightOneLeftForwardCaptureMove, D, 7);
  ASSERT_EQ(oneRightOneLeftForwardCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneRightOneLeftForwardCaptureMoves.begin(),
                      oneRightOneLeftForwardCaptureMoves.end(),
                      oneRightOneLeftForwardCaptureMoveResult) !=
                oneRightOneLeftForwardCaptureMoves.end(),
            true);

  Board boardOneLeftOneRightBackCaptureMove = Board(true);
  boardOneLeftOneRightBackCaptureMove(D, 1) = new Queen(WHITE);
  boardOneLeftOneRightBackCaptureMove(C, 2) = new Pawn(BLACK);
  boardOneLeftOneRightBackCaptureMove(E, 2) = new Pawn(WHITE);
  boardOneLeftOneRightBackCaptureMove(C, 4) = new Pawn(BLACK);
  Move oneLeftOneRightBackCaptureMoveResult = Move("D1D5");
  oneLeftOneRightBackCaptureMoveResult.addCapture(PieceLocation{C, 2});
  oneLeftOneRightBackCaptureMoveResult.addCapture(PieceLocation{C, 4});
  std::vector<Move> oneLeftOneRightBackCaptureMoves =
      game.getPieceMoves(boardOneLeftOneRightBackCaptureMove, D, 1);
  ASSERT_EQ(oneLeftOneRightBackCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneLeftOneRightBackCaptureMoves.begin(),
                      oneLeftOneRightBackCaptureMoves.end(),
                      oneLeftOneRightBackCaptureMoveResult) !=
                oneLeftOneRightBackCaptureMoves.end(),
            true);

  Board boardOneRightOneLeftBackCaptureMove = Board(true);
  boardOneRightOneLeftBackCaptureMove(D, 1) = new Queen(WHITE);
  boardOneRightOneLeftBackCaptureMove(C, 2) = new Pawn(WHITE);
  boardOneRightOneLeftBackCaptureMove(E, 2) = new Pawn(BLACK);
  boardOneRightOneLeftBackCaptureMove(E, 4) = new Pawn(BLACK);
  Move oneRightOneLeftBackCaptureMoveResult = Move("D1D5");
  oneRightOneLeftBackCaptureMoveResult.addCapture(PieceLocation{E, 2});
  oneRightOneLeftBackCaptureMoveResult.addCapture(PieceLocation{E, 4});
  std::vector<Move> oneRightOneLeftBackCaptureMoves =
      game.getPieceMoves(boardOneRightOneLeftBackCaptureMove, D, 1);
  ASSERT_EQ(oneRightOneLeftBackCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneRightOneLeftBackCaptureMoves.begin(),
                      oneRightOneLeftBackCaptureMoves.end(),
                      oneRightOneLeftBackCaptureMoveResult) !=
                oneRightOneLeftBackCaptureMoves.end(),
            true);
}

TEST(GameTest, blackQueenMovesWithCapture) {
  Game game = Game();

  Board boardOneLeftForwardCaptureMove = Board(true);
  boardOneLeftForwardCaptureMove(D, 5) = new Queen(BLACK);
  boardOneLeftForwardCaptureMove(C, 4) = new Pawn(WHITE);
  boardOneLeftForwardCaptureMove(E, 4) = new Pawn(BLACK);
  boardOneLeftForwardCaptureMove(E, 6) = new Pawn(BLACK);
  boardOneLeftForwardCaptureMove(C, 6) = new Pawn(BLACK);
  Move oneLeftForwardCaptureMoveResult = Move("D5B3");
  oneLeftForwardCaptureMoveResult.addCapture(PieceLocation{C, 4});
  std::vector<Move> oneLeftForwardCaptureMoves =
      game.getPieceMoves(boardOneLeftForwardCaptureMove, D, 5);
  ASSERT_EQ(oneLeftForwardCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneLeftForwardCaptureMoves.begin(),
                      oneLeftForwardCaptureMoves.end(),
                      oneLeftForwardCaptureMoveResult) !=
                oneLeftForwardCaptureMoves.end(),
            true);

  Board boardOneLeftBackCaptureMove = Board(true);
  boardOneLeftBackCaptureMove(D, 3) = new Queen(BLACK);
  boardOneLeftBackCaptureMove(C, 4) = new Pawn(WHITE);
  boardOneLeftBackCaptureMove(E, 4) = new Pawn(BLACK);
  boardOneLeftBackCaptureMove(E, 2) = new Pawn(BLACK);
  boardOneLeftBackCaptureMove(C, 2) = new Pawn(BLACK);
  Move oneLeftBackCaptureMoveResult = Move("D3B5");
  oneLeftBackCaptureMoveResult.addCapture(PieceLocation{C, 4});
  std::vector<Move> oneLeftBackCaptureMoves =
      game.getPieceMoves(boardOneLeftBackCaptureMove, D, 3);
  ASSERT_EQ(oneLeftBackCaptureMoves.size(), 1);
  ASSERT_EQ(
      std::find(oneLeftBackCaptureMoves.begin(), oneLeftBackCaptureMoves.end(),
                oneLeftBackCaptureMoveResult) != oneLeftBackCaptureMoves.end(),
      true);

  Board boardTwoLeftForwardCaptureMove = Board(true);
  boardTwoLeftForwardCaptureMove(E, 7) = new Queen(BLACK);
  boardTwoLeftForwardCaptureMove(D, 6) = new Pawn(WHITE);
  boardTwoLeftForwardCaptureMove(F, 6) = new Pawn(BLACK);
  boardTwoLeftForwardCaptureMove(B, 4) = new Pawn(WHITE);
  boardTwoLeftForwardCaptureMove(D, 8) = new Pawn(BLACK);
  boardTwoLeftForwardCaptureMove(F, 8) = new Pawn(BLACK);
  Move twoLeftForwardCaptureMoveResult = Move("E7A3");
  twoLeftForwardCaptureMoveResult.addCapture(PieceLocation{D, 6});
  twoLeftForwardCaptureMoveResult.addCapture(PieceLocation{B, 4});
  std::vector<Move> twoLeftForwardCaptureMoves =
      game.getPieceMoves(boardTwoLeftForwardCaptureMove, E, 7);
  ASSERT_EQ(twoLeftForwardCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(twoLeftForwardCaptureMoves.begin(),
                      twoLeftForwardCaptureMoves.end(),
                      twoLeftForwardCaptureMoveResult) !=
                twoLeftForwardCaptureMoves.end(),
            true);

  Board boardTwoLeftBackCaptureMove = Board(true);
  boardTwoLeftBackCaptureMove(E, 1) = new Queen(BLACK);
  boardTwoLeftBackCaptureMove(D, 2) = new Pawn(WHITE);
  boardTwoLeftBackCaptureMove(F, 2) = new Pawn(BLACK);
  boardTwoLeftBackCaptureMove(B, 4) = new Pawn(WHITE);
  Move twoLeftBackCaptureMoveResult = Move("E1A5");
  twoLeftBackCaptureMoveResult.addCapture(PieceLocation{D, 2});
  twoLeftBackCaptureMoveResult.addCapture(PieceLocation{B, 4});
  std::vector<Move> twoLeftBackCaptureMoves =
      game.getPieceMoves(boardTwoLeftBackCaptureMove, E, 1);
  ASSERT_EQ(twoLeftBackCaptureMoves.size(), 1);
  ASSERT_EQ(
      std::find(twoLeftBackCaptureMoves.begin(), twoLeftBackCaptureMoves.end(),
                twoLeftBackCaptureMoveResult) != twoLeftBackCaptureMoves.end(),
      true);

  Board boardOneRightForwardCaptureMove = Board(true);
  boardOneRightForwardCaptureMove(D, 5) = new Queen(BLACK);
  boardOneRightForwardCaptureMove(C, 4) = new Pawn(BLACK);
  boardOneRightForwardCaptureMove(E, 4) = new Pawn(WHITE);
  boardOneRightForwardCaptureMove(C, 6) = new Pawn(BLACK);
  boardOneRightForwardCaptureMove(E, 6) = new Pawn(BLACK);
  Move oneRightForwardCaptureMoveResult = Move("D5F3");
  oneRightForwardCaptureMoveResult.addCapture(PieceLocation{E, 4});
  std::vector<Move> oneRightForwardCaptureMoves =
      game.getPieceMoves(boardOneRightForwardCaptureMove, D, 5);
  ASSERT_EQ(oneRightForwardCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneRightForwardCaptureMoves.begin(),
                      oneRightForwardCaptureMoves.end(),
                      oneRightForwardCaptureMoveResult) !=
                oneRightForwardCaptureMoves.end(),
            true);

  Board boardOneRightBackCaptureMove = Board(true);
  boardOneRightBackCaptureMove(D, 3) = new Queen(BLACK);
  boardOneRightBackCaptureMove(C, 4) = new Pawn(BLACK);
  boardOneRightBackCaptureMove(E, 4) = new Pawn(WHITE);
  boardOneRightBackCaptureMove(C, 2) = new Pawn(BLACK);
  boardOneRightBackCaptureMove(E, 2) = new Pawn(BLACK);
  Move oneRightBackCaptureMoveResult = Move("D3F5");
  oneRightBackCaptureMoveResult.addCapture(PieceLocation{E, 4});
  std::vector<Move> oneRightBackCaptureMoves =
      game.getPieceMoves(boardOneRightBackCaptureMove, D, 3);
  ASSERT_EQ(oneRightBackCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneRightBackCaptureMoves.begin(),
                      oneRightBackCaptureMoves.end(),
                      oneRightBackCaptureMoveResult) !=
                oneRightBackCaptureMoves.end(),
            true);

  Board boardTwoRightBackCaptureMove = Board(true);
  boardTwoRightBackCaptureMove(B, 1) = new Queen(BLACK);
  boardTwoRightBackCaptureMove(A, 2) = new Pawn(BLACK);
  boardTwoRightBackCaptureMove(C, 2) = new Pawn(WHITE);
  boardTwoRightBackCaptureMove(E, 4) = new Pawn(WHITE);
  Move twoRightBackCaptureMoveResult = Move("B1F5");
  twoRightBackCaptureMoveResult.addCapture(PieceLocation{C, 2});
  twoRightBackCaptureMoveResult.addCapture(PieceLocation{E, 4});
  std::vector<Move> twoRightBackCaptureMoves =
      game.getPieceMoves(boardTwoRightBackCaptureMove, B, 1);
  ASSERT_EQ(twoRightBackCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(twoRightBackCaptureMoves.begin(),
                      twoRightBackCaptureMoves.end(),
                      twoRightBackCaptureMoveResult) !=
                twoRightBackCaptureMoves.end(),
            true);

  Board boardOneLeftOneRightForwardCaptureMove = Board(true);
  boardOneLeftOneRightForwardCaptureMove(D, 7) = new Queen(BLACK);
  boardOneLeftOneRightForwardCaptureMove(C, 6) = new Pawn(WHITE);
  boardOneLeftOneRightForwardCaptureMove(E, 6) = new Pawn(BLACK);
  boardOneLeftOneRightForwardCaptureMove(C, 4) = new Pawn(WHITE);
  boardOneLeftOneRightForwardCaptureMove(E, 8) = new Pawn(BLACK);
  boardOneLeftOneRightForwardCaptureMove(C, 8) = new Pawn(BLACK);
  Move oneLeftOneRightForwardCaptureMoveResult = Move("D7D3");
  oneLeftOneRightForwardCaptureMoveResult.addCapture(PieceLocation{C, 6});
  oneLeftOneRightForwardCaptureMoveResult.addCapture(PieceLocation{C, 4});
  std::vector<Move> oneLeftOneRightForwardCaptureMoves =
      game.getPieceMoves(boardOneLeftOneRightForwardCaptureMove, D, 7);
  ASSERT_EQ(oneLeftOneRightForwardCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneLeftOneRightForwardCaptureMoves.begin(),
                      oneLeftOneRightForwardCaptureMoves.end(),
                      oneLeftOneRightForwardCaptureMoveResult) !=
                oneLeftOneRightForwardCaptureMoves.end(),
            true);

  Board boardOneRightOneLeftForwardCaptureMove = Board(true);
  boardOneRightOneLeftForwardCaptureMove(D, 7) = new Queen(BLACK);
  boardOneRightOneLeftForwardCaptureMove(C, 6) = new Pawn(BLACK);
  boardOneRightOneLeftForwardCaptureMove(E, 6) = new Pawn(WHITE);
  boardOneRightOneLeftForwardCaptureMove(E, 4) = new Pawn(WHITE);
  boardOneRightOneLeftForwardCaptureMove(C, 8) = new Pawn(BLACK);
  boardOneRightOneLeftForwardCaptureMove(E, 8) = new Pawn(BLACK);
  Move oneRightOneLeftForwardCaptureMoveResult = Move("D7D3");
  oneRightOneLeftForwardCaptureMoveResult.addCapture(PieceLocation{E, 6});
  oneRightOneLeftForwardCaptureMoveResult.addCapture(PieceLocation{E, 4});
  std::vector<Move> oneRightOneLeftForwardCaptureMoves =
      game.getPieceMoves(boardOneRightOneLeftForwardCaptureMove, D, 7);
  ASSERT_EQ(oneRightOneLeftForwardCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneRightOneLeftForwardCaptureMoves.begin(),
                      oneRightOneLeftForwardCaptureMoves.end(),
                      oneRightOneLeftForwardCaptureMoveResult) !=
                oneRightOneLeftForwardCaptureMoves.end(),
            true);

  Board boardOneLeftOneRightBackCaptureMove = Board(true);
  boardOneLeftOneRightBackCaptureMove(D, 1) = new Queen(BLACK);
  boardOneLeftOneRightBackCaptureMove(C, 2) = new Pawn(WHITE);
  boardOneLeftOneRightBackCaptureMove(E, 2) = new Pawn(BLACK);
  boardOneLeftOneRightBackCaptureMove(C, 4) = new Pawn(WHITE);
  Move oneLeftOneRightBackCaptureMoveResult = Move("D1D5");
  oneLeftOneRightBackCaptureMoveResult.addCapture(PieceLocation{C, 2});
  oneLeftOneRightBackCaptureMoveResult.addCapture(PieceLocation{C, 4});
  std::vector<Move> oneLeftOneRightBackCaptureMoves =
      game.getPieceMoves(boardOneLeftOneRightBackCaptureMove, D, 1);
  ASSERT_EQ(oneLeftOneRightBackCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneLeftOneRightBackCaptureMoves.begin(),
                      oneLeftOneRightBackCaptureMoves.end(),
                      oneLeftOneRightBackCaptureMoveResult) !=
                oneLeftOneRightBackCaptureMoves.end(),
            true);

  Board boardOneRightOneLeftBackCaptureMove = Board(true);
  boardOneRightOneLeftBackCaptureMove(D, 1) = new Queen(BLACK);
  boardOneRightOneLeftBackCaptureMove(C, 2) = new Pawn(BLACK);
  boardOneRightOneLeftBackCaptureMove(E, 2) = new Pawn(WHITE);
  boardOneRightOneLeftBackCaptureMove(E, 4) = new Pawn(WHITE);
  Move oneRightOneLeftBackCaptureMoveResult = Move("D1D5");
  oneRightOneLeftBackCaptureMoveResult.addCapture(PieceLocation{E, 2});
  oneRightOneLeftBackCaptureMoveResult.addCapture(PieceLocation{E, 4});
  std::vector<Move> oneRightOneLeftBackCaptureMoves =
      game.getPieceMoves(boardOneRightOneLeftBackCaptureMove, D, 1);
  ASSERT_EQ(oneRightOneLeftBackCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneRightOneLeftBackCaptureMoves.begin(),
                      oneRightOneLeftBackCaptureMoves.end(),
                      oneRightOneLeftBackCaptureMoveResult) !=
                oneRightOneLeftBackCaptureMoves.end(),
            true);
}
