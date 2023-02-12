// clang-format off
#include <gtest/gtest.h>
// clang-format on
#include "../lib/move/generator/MoveGenerator.hpp"
#include <algorithm>
#include <vector>

//
// pawn
//

TEST(MoveGeneratorTest, whitePawnMovesWithoutCapture) {
  Board boardTwoMoves = Board(true);
  boardTwoMoves(D, 4) = new Pawn(WHITE);
  std::vector<Move> twoMoves =
      MoveGenerator::getPieceMoves(boardTwoMoves, D, 4);
  ASSERT_EQ(twoMoves.size(), 2);
  ASSERT_EQ(std::find(twoMoves.begin(), twoMoves.end(), Move("D4C5")) !=
                twoMoves.end(),
            true);
  ASSERT_EQ(std::find(twoMoves.begin(), twoMoves.end(), Move("D4E5")) !=
                twoMoves.end(),
            true);

  Board boardOneMove = Board(true);
  boardOneMove(D, 4) = new Pawn(WHITE);
  boardOneMove(C, 5) = new Pawn(WHITE);
  std::vector<Move> oneMove = MoveGenerator::getPieceMoves(boardOneMove, D, 4);
  ASSERT_EQ(oneMove.size(), 1);
  ASSERT_EQ(std::find(oneMove.begin(), oneMove.end(), Move("D4E5")) !=
                oneMove.end(),
            true);

  Board boardZeroMoves = Board(true);
  boardZeroMoves(D, 4) = new Pawn(WHITE);
  boardZeroMoves(C, 5) = new Pawn(WHITE);
  boardZeroMoves(E, 5) = new Pawn(WHITE);
  std::vector<Move> zeroMoves =
      MoveGenerator::getPieceMoves(boardZeroMoves, D, 4);
  ASSERT_EQ(zeroMoves.size(), 0);

  Board boardMovesWithAnOutOfBounds = Board(true);
  boardMovesWithAnOutOfBounds(A, 1) = new Pawn(WHITE);
  std::vector<Move> oneOutOfBoundsMove =
      MoveGenerator::getPieceMoves(boardMovesWithAnOutOfBounds, A, 1);
  ASSERT_EQ(oneOutOfBoundsMove.size(), 1);
  ASSERT_EQ(std::find(oneOutOfBoundsMove.begin(), oneOutOfBoundsMove.end(),
                      Move("A1B2")) != oneOutOfBoundsMove.end(),
            true);

  Board boardMovesWithAllOutOfBounds = Board(true);
  boardMovesWithAllOutOfBounds(A, 8) = new Pawn(WHITE);
  std::vector<Move> allOutOfBoundsMoves =
      MoveGenerator::getPieceMoves(boardMovesWithAllOutOfBounds, A, 8);
  ASSERT_EQ(allOutOfBoundsMoves.size(), 0);
}

TEST(MoveGeneratorTest, blackPawnMovesWithoutCapture) {
  Board boardTwoMoves = Board(true);
  boardTwoMoves(D, 4) = new Pawn(BLACK);
  std::vector<Move> twoMoves =
      MoveGenerator::getPieceMoves(boardTwoMoves, D, 4);
  ASSERT_EQ(twoMoves.size(), 2);
  ASSERT_EQ(std::find(twoMoves.begin(), twoMoves.end(), Move("D4C3")) !=
                twoMoves.end(),
            true);
  ASSERT_EQ(std::find(twoMoves.begin(), twoMoves.end(), Move("D4E3")) !=
                twoMoves.end(),
            true);

  Board boardOneMove = Board(true);
  boardOneMove(D, 4) = new Pawn(BLACK);
  boardOneMove(C, 3) = new Pawn(BLACK);
  std::vector<Move> oneMove = MoveGenerator::getPieceMoves(boardOneMove, D, 4);
  ASSERT_EQ(oneMove.size(), 1);
  ASSERT_EQ(std::find(oneMove.begin(), oneMove.end(), Move("D4E3")) !=
                oneMove.end(),
            true);

  Board boardZeroMoves = Board(true);
  boardZeroMoves(D, 4) = new Pawn(BLACK);
  boardZeroMoves(C, 3) = new Pawn(BLACK);
  boardZeroMoves(E, 3) = new Pawn(BLACK);
  std::vector<Move> zeroMoves =
      MoveGenerator::getPieceMoves(boardZeroMoves, D, 4);
  ASSERT_EQ(zeroMoves.size(), 0);

  Board boardMovesWithAnOutOfBounds = Board(true);
  boardMovesWithAnOutOfBounds(A, 8) = new Pawn(BLACK);
  std::vector<Move> oneOutOfBoundsMove =
      MoveGenerator::getPieceMoves(boardMovesWithAnOutOfBounds, A, 8);
  ASSERT_EQ(oneOutOfBoundsMove.size(), 1);
  ASSERT_EQ(std::find(oneOutOfBoundsMove.begin(), oneOutOfBoundsMove.end(),
                      Move("A8B7")) != oneOutOfBoundsMove.end(),
            true);

  Board boardMovesWithAllOutOfBounds = Board(true);
  boardMovesWithAllOutOfBounds(A, 1) = new Pawn(BLACK);
  std::vector<Move> allOutOfBoundsMoves =
      MoveGenerator::getPieceMoves(boardMovesWithAllOutOfBounds, A, 1);
  ASSERT_EQ(allOutOfBoundsMoves.size(), 0);
}

TEST(MoveGeneratorTest, whitePawnMovesWithCapture) {
  Board boardOneLeftCaptureMove = Board(true);
  boardOneLeftCaptureMove(D, 4) = new Pawn(WHITE);
  boardOneLeftCaptureMove(C, 5) = new Pawn(BLACK);
  boardOneLeftCaptureMove(E, 5) = new Pawn(WHITE);
  Move oneLeftCaptureMoveResult = Move("D4B6");
  oneLeftCaptureMoveResult.addCapture(PieceLocation{C, 5});
  std::vector<Move> oneLeftCaptureMoves =
      MoveGenerator::getPieceMoves(boardOneLeftCaptureMove, D, 4);
  ASSERT_EQ(oneLeftCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneLeftCaptureMoves.begin(), oneLeftCaptureMoves.end(),
                      oneLeftCaptureMoveResult) != oneLeftCaptureMoves.end(),
            true);

  Board boardTwoLeftCaptureMove = Board(true);
  boardTwoLeftCaptureMove(E, 2) = new Pawn(WHITE);
  boardTwoLeftCaptureMove(D, 3) = new Pawn(BLACK);
  boardTwoLeftCaptureMove(F, 3) = new Pawn(WHITE);
  boardTwoLeftCaptureMove(B, 5) = new Pawn(BLACK);
  Move twoLeftCaptureMoveResult = Move("E2A6");
  twoLeftCaptureMoveResult.addCapture(PieceLocation{D, 3});
  twoLeftCaptureMoveResult.addCapture(PieceLocation{B, 5});
  std::vector<Move> twoLeftCaptureMoves =
      MoveGenerator::getPieceMoves(boardTwoLeftCaptureMove, E, 2);
  ASSERT_EQ(twoLeftCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(twoLeftCaptureMoves.begin(), twoLeftCaptureMoves.end(),
                      twoLeftCaptureMoveResult) != twoLeftCaptureMoves.end(),
            true);

  Board boardOneRightCaptureMove = Board(true);
  boardOneRightCaptureMove(D, 4) = new Pawn(WHITE);
  boardOneRightCaptureMove(C, 5) = new Pawn(WHITE);
  boardOneRightCaptureMove(E, 5) = new Pawn(BLACK);
  Move oneRightCaptureMoveResult = Move("D4F6");
  oneRightCaptureMoveResult.addCapture(PieceLocation{E, 5});
  std::vector<Move> oneRightCaptureMoves =
      MoveGenerator::getPieceMoves(boardOneRightCaptureMove, D, 4);
  ASSERT_EQ(oneRightCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneRightCaptureMoves.begin(), oneRightCaptureMoves.end(),
                      oneRightCaptureMoveResult) != oneRightCaptureMoves.end(),
            true);

  Board boardTwoRightCaptureMove = Board(true);
  boardTwoRightCaptureMove(B, 2) = new Pawn(WHITE);
  boardTwoRightCaptureMove(A, 3) = new Pawn(WHITE);
  boardTwoRightCaptureMove(C, 3) = new Pawn(BLACK);
  boardTwoRightCaptureMove(E, 5) = new Pawn(BLACK);
  Move twoRightCaptureMoveResult = Move("B2F6");
  twoRightCaptureMoveResult.addCapture(PieceLocation{C, 3});
  twoRightCaptureMoveResult.addCapture(PieceLocation{E, 5});
  std::vector<Move> twoRightCaptureMoves =
      MoveGenerator::getPieceMoves(boardTwoRightCaptureMove, B, 2);
  ASSERT_EQ(twoRightCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(twoRightCaptureMoves.begin(), twoRightCaptureMoves.end(),
                      twoRightCaptureMoveResult) != twoRightCaptureMoves.end(),
            true);

  Board boardOneLeftOneRightCaptureMove = Board(true);
  boardOneLeftOneRightCaptureMove(D, 2) = new Pawn(WHITE);
  boardOneLeftOneRightCaptureMove(C, 3) = new Pawn(BLACK);
  boardOneLeftOneRightCaptureMove(E, 3) = new Pawn(WHITE);
  boardOneLeftOneRightCaptureMove(C, 5) = new Pawn(BLACK);
  Move oneLeftOneRightCaptureMoveResult = Move("D2D6");
  oneLeftOneRightCaptureMoveResult.addCapture(PieceLocation{C, 3});
  oneLeftOneRightCaptureMoveResult.addCapture(PieceLocation{C, 5});
  std::vector<Move> oneLeftOneRightCaptureMoves =
      MoveGenerator::getPieceMoves(boardOneLeftOneRightCaptureMove, D, 2);
  ASSERT_EQ(oneLeftOneRightCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneLeftOneRightCaptureMoves.begin(),
                      oneLeftOneRightCaptureMoves.end(),
                      oneLeftOneRightCaptureMoveResult) !=
                oneLeftOneRightCaptureMoves.end(),
            true);

  Board boardOneRightOneLeftCaptureMove = Board(true);
  boardOneRightOneLeftCaptureMove(D, 2) = new Pawn(WHITE);
  boardOneRightOneLeftCaptureMove(C, 3) = new Pawn(WHITE);
  boardOneRightOneLeftCaptureMove(E, 3) = new Pawn(BLACK);
  boardOneRightOneLeftCaptureMove(E, 5) = new Pawn(BLACK);
  Move oneRightOneLeftCaptureMoveResult = Move("D2D6");
  oneRightOneLeftCaptureMoveResult.addCapture(PieceLocation{E, 3});
  oneRightOneLeftCaptureMoveResult.addCapture(PieceLocation{E, 5});
  std::vector<Move> oneRightOneLeftCaptureMoves =
      MoveGenerator::getPieceMoves(boardOneRightOneLeftCaptureMove, D, 2);
  ASSERT_EQ(oneRightOneLeftCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneRightOneLeftCaptureMoves.begin(),
                      oneRightOneLeftCaptureMoves.end(),
                      oneRightOneLeftCaptureMoveResult) !=
                oneRightOneLeftCaptureMoves.end(),
            true);
}

TEST(MoveGeneratorTest, blackPawnMovesWithCapture) {
  Board boardOneLeftCaptureMove = Board(true);
  boardOneLeftCaptureMove(D, 6) = new Pawn(BLACK);
  boardOneLeftCaptureMove(C, 5) = new Pawn(WHITE);
  boardOneLeftCaptureMove(E, 5) = new Pawn(BLACK);
  Move oneLeftCaptureMoveResult = Move("D6B4");
  oneLeftCaptureMoveResult.addCapture(PieceLocation{C, 5});
  std::vector<Move> oneLeftCaptureMoves =
      MoveGenerator::getPieceMoves(boardOneLeftCaptureMove, D, 6);
  ASSERT_EQ(oneLeftCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneLeftCaptureMoves.begin(), oneLeftCaptureMoves.end(),
                      oneLeftCaptureMoveResult) != oneLeftCaptureMoves.end(),
            true);

  Board boardTwoLeftCaptureMove = Board(true);
  boardTwoLeftCaptureMove(E, 8) = new Pawn(BLACK);
  boardTwoLeftCaptureMove(D, 7) = new Pawn(WHITE);
  boardTwoLeftCaptureMove(F, 7) = new Pawn(BLACK);
  boardTwoLeftCaptureMove(B, 5) = new Pawn(WHITE);
  Move twoLeftCaptureMoveResult = Move("E8A4");
  twoLeftCaptureMoveResult.addCapture(PieceLocation{D, 7});
  twoLeftCaptureMoveResult.addCapture(PieceLocation{B, 5});
  std::vector<Move> twoLeftCaptureMoves =
      MoveGenerator::getPieceMoves(boardTwoLeftCaptureMove, E, 8);
  ASSERT_EQ(twoLeftCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(twoLeftCaptureMoves.begin(), twoLeftCaptureMoves.end(),
                      twoLeftCaptureMoveResult) != twoLeftCaptureMoves.end(),
            true);

  Board boardOneRightCaptureMove = Board(true);
  boardOneRightCaptureMove(D, 6) = new Pawn(BLACK);
  boardOneRightCaptureMove(C, 5) = new Pawn(BLACK);
  boardOneRightCaptureMove(E, 5) = new Pawn(WHITE);
  Move oneRightCaptureMoveResult = Move("D6F4");
  oneRightCaptureMoveResult.addCapture(PieceLocation{E, 5});
  std::vector<Move> oneRightCaptureMoves =
      MoveGenerator::getPieceMoves(boardOneRightCaptureMove, D, 6);
  ASSERT_EQ(oneRightCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneRightCaptureMoves.begin(), oneRightCaptureMoves.end(),
                      oneRightCaptureMoveResult) != oneRightCaptureMoves.end(),
            true);

  Board boardTwoRightCaptureMove = Board(true);
  boardTwoRightCaptureMove(B, 8) = new Pawn(BLACK);
  boardTwoRightCaptureMove(A, 7) = new Pawn(BLACK);
  boardTwoRightCaptureMove(C, 7) = new Pawn(WHITE);
  boardTwoRightCaptureMove(E, 5) = new Pawn(WHITE);
  Move twoRightCaptureMoveResult = Move("B8F4");
  twoRightCaptureMoveResult.addCapture(PieceLocation{C, 7});
  twoRightCaptureMoveResult.addCapture(PieceLocation{E, 5});
  std::vector<Move> twoRightCaptureMoves =
      MoveGenerator::getPieceMoves(boardTwoRightCaptureMove, B, 8);
  ASSERT_EQ(twoRightCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(twoRightCaptureMoves.begin(), twoRightCaptureMoves.end(),
                      twoRightCaptureMoveResult) != twoRightCaptureMoves.end(),
            true);

  Board boardOneLeftOneRightCaptureMove = Board(true);
  boardOneLeftOneRightCaptureMove(D, 8) = new Pawn(BLACK);
  boardOneLeftOneRightCaptureMove(C, 7) = new Pawn(WHITE);
  boardOneLeftOneRightCaptureMove(E, 7) = new Pawn(BLACK);
  boardOneLeftOneRightCaptureMove(C, 5) = new Pawn(WHITE);
  Move oneLeftOneRightCaptureMoveResult = Move("D8D4");
  oneLeftOneRightCaptureMoveResult.addCapture(PieceLocation{C, 7});
  oneLeftOneRightCaptureMoveResult.addCapture(PieceLocation{C, 5});
  std::vector<Move> oneLeftOneRightCaptureMoves =
      MoveGenerator::getPieceMoves(boardOneLeftOneRightCaptureMove, D, 8);
  ASSERT_EQ(oneLeftOneRightCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneLeftOneRightCaptureMoves.begin(),
                      oneLeftOneRightCaptureMoves.end(),
                      oneLeftOneRightCaptureMoveResult) !=
                oneLeftOneRightCaptureMoves.end(),
            true);

  Board boardOneRightOneLeftCaptureMove = Board(true);
  boardOneRightOneLeftCaptureMove(D, 8) = new Pawn(BLACK);
  boardOneRightOneLeftCaptureMove(C, 7) = new Pawn(BLACK);
  boardOneRightOneLeftCaptureMove(E, 7) = new Pawn(WHITE);
  boardOneRightOneLeftCaptureMove(E, 5) = new Pawn(WHITE);
  Move oneRightOneLeftCaptureMoveResult = Move("D8D4");
  oneRightOneLeftCaptureMoveResult.addCapture(PieceLocation{E, 7});
  oneRightOneLeftCaptureMoveResult.addCapture(PieceLocation{E, 5});
  std::vector<Move> oneRightOneLeftCaptureMoves =
      MoveGenerator::getPieceMoves(boardOneRightOneLeftCaptureMove, D, 8);
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

TEST(MoveGeneratorTest, whiteQueenMovesWithoutCapture) {
  Board boardFourMoves = Board(true);
  boardFourMoves(D, 4) = new Queen(WHITE);
  std::vector<Move> fourMoves =
      MoveGenerator::getPieceMoves(boardFourMoves, D, 4);
  ASSERT_EQ(fourMoves.size(), 4);
  ASSERT_EQ(std::find(fourMoves.begin(), fourMoves.end(), Move("D4C5")) !=
                fourMoves.end(),
            true);
  ASSERT_EQ(std::find(fourMoves.begin(), fourMoves.end(), Move("D4E5")) !=
                fourMoves.end(),
            true);
  ASSERT_EQ(std::find(fourMoves.begin(), fourMoves.end(), Move("D4C3")) !=
                fourMoves.end(),
            true);
  ASSERT_EQ(std::find(fourMoves.begin(), fourMoves.end(), Move("D4E3")) !=
                fourMoves.end(),
            true);

  Board boardThreeMove = Board(true);
  boardThreeMove(D, 4) = new Queen(WHITE);
  boardThreeMove(C, 5) = new Pawn(WHITE);
  std::vector<Move> threeMoves =
      MoveGenerator::getPieceMoves(boardThreeMove, D, 4);
  ASSERT_EQ(threeMoves.size(), 3);
  ASSERT_EQ(std::find(threeMoves.begin(), threeMoves.end(), Move("D4E5")) !=
                threeMoves.end(),
            true);
  ASSERT_EQ(std::find(threeMoves.begin(), threeMoves.end(), Move("D4E3")) !=
                threeMoves.end(),
            true);
  ASSERT_EQ(std::find(threeMoves.begin(), threeMoves.end(), Move("D4C3")) !=
                threeMoves.end(),
            true);

  Board boardZeroMoves = Board(true);
  boardZeroMoves(D, 4) = new Queen(WHITE);
  boardZeroMoves(C, 5) = new Pawn(WHITE);
  boardZeroMoves(E, 5) = new Pawn(WHITE);
  boardZeroMoves(C, 3) = new Pawn(WHITE);
  boardZeroMoves(E, 3) = new Pawn(WHITE);
  std::vector<Move> zeroMoves =
      MoveGenerator::getPieceMoves(boardZeroMoves, D, 4);
  ASSERT_EQ(zeroMoves.size(), 0);

  Board boardMovesWithOutOfBounds = Board(true);
  boardMovesWithOutOfBounds(A, 1) = new Queen(WHITE);
  std::vector<Move> outOfBoundsMoves =
      MoveGenerator::getPieceMoves(boardMovesWithOutOfBounds, A, 1);
  ASSERT_EQ(outOfBoundsMoves.size(), 1);
  ASSERT_EQ(std::find(outOfBoundsMoves.begin(), outOfBoundsMoves.end(),
                      Move("A1B2")) != outOfBoundsMoves.end(),
            true);
}

TEST(MoveGeneratorTest, blackQueenMovesWithoutCapture) {
  Board boardFourMoves = Board(true);
  boardFourMoves(D, 4) = new Queen(BLACK);
  std::vector<Move> fourMoves =
      MoveGenerator::getPieceMoves(boardFourMoves, D, 4);
  ASSERT_EQ(fourMoves.size(), 4);
  ASSERT_EQ(std::find(fourMoves.begin(), fourMoves.end(), Move("D4C5")) !=
                fourMoves.end(),
            true);
  ASSERT_EQ(std::find(fourMoves.begin(), fourMoves.end(), Move("D4E5")) !=
                fourMoves.end(),
            true);
  ASSERT_EQ(std::find(fourMoves.begin(), fourMoves.end(), Move("D4C3")) !=
                fourMoves.end(),
            true);
  ASSERT_EQ(std::find(fourMoves.begin(), fourMoves.end(), Move("D4E3")) !=
                fourMoves.end(),
            true);

  Board boardThreeMoves = Board(true);
  boardThreeMoves(D, 4) = new Queen(BLACK);
  boardThreeMoves(C, 5) = new Pawn(BLACK);
  std::vector<Move> threeMoves =
      MoveGenerator::getPieceMoves(boardThreeMoves, D, 4);
  ASSERT_EQ(threeMoves.size(), 3);
  ASSERT_EQ(std::find(threeMoves.begin(), threeMoves.end(), Move("D4E5")) !=
                threeMoves.end(),
            true);
  ASSERT_EQ(std::find(threeMoves.begin(), threeMoves.end(), Move("D4E3")) !=
                threeMoves.end(),
            true);
  ASSERT_EQ(std::find(threeMoves.begin(), threeMoves.end(), Move("D4C3")) !=
                threeMoves.end(),
            true);

  Board boardZeroMoves = Board(true);
  boardZeroMoves(D, 4) = new Queen(BLACK);
  boardZeroMoves(C, 5) = new Pawn(BLACK);
  boardZeroMoves(E, 5) = new Pawn(BLACK);
  boardZeroMoves(C, 3) = new Pawn(BLACK);
  boardZeroMoves(E, 3) = new Pawn(BLACK);
  std::vector<Move> zeroMoves =
      MoveGenerator::getPieceMoves(boardZeroMoves, D, 4);
  ASSERT_EQ(zeroMoves.size(), 0);

  Board boardMovesWithOutOfBounds = Board(true);
  boardMovesWithOutOfBounds(A, 1) = new Queen(BLACK);
  std::vector<Move> outOfBoundsMoves =
      MoveGenerator::getPieceMoves(boardMovesWithOutOfBounds, A, 1);
  ASSERT_EQ(outOfBoundsMoves.size(), 1);
  ASSERT_EQ(std::find(outOfBoundsMoves.begin(), outOfBoundsMoves.end(),
                      Move("A1B2")) != outOfBoundsMoves.end(),
            true);
}

TEST(MoveGeneratorTest, whiteQueenMovesWithCapture) {
  Board boardOneLeftForwardCaptureMove = Board(true);
  boardOneLeftForwardCaptureMove(D, 4) = new Queen(WHITE);
  boardOneLeftForwardCaptureMove(C, 5) = new Pawn(BLACK);
  boardOneLeftForwardCaptureMove(E, 5) = new Pawn(WHITE);
  boardOneLeftForwardCaptureMove(E, 3) = new Pawn(WHITE);
  boardOneLeftForwardCaptureMove(C, 3) = new Pawn(WHITE);
  Move oneLeftForwardCaptureMoveResult = Move("D4B6");
  oneLeftForwardCaptureMoveResult.addCapture(PieceLocation{C, 5});
  std::vector<Move> oneLeftForwardCaptureMoves =
      MoveGenerator::getPieceMoves(boardOneLeftForwardCaptureMove, D, 4);
  ASSERT_EQ(oneLeftForwardCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneLeftForwardCaptureMoves.begin(),
                      oneLeftForwardCaptureMoves.end(),
                      oneLeftForwardCaptureMoveResult) !=
                oneLeftForwardCaptureMoves.end(),
            true);

  Board boardOneLeftBackCaptureMove = Board(true);
  boardOneLeftBackCaptureMove(D, 6) = new Queen(WHITE);
  boardOneLeftBackCaptureMove(C, 5) = new Pawn(BLACK);
  boardOneLeftBackCaptureMove(E, 5) = new Pawn(WHITE);
  boardOneLeftBackCaptureMove(E, 7) = new Pawn(WHITE);
  boardOneLeftBackCaptureMove(C, 7) = new Pawn(WHITE);
  Move oneLeftBackCaptureMoveResult = Move("D6B4");
  oneLeftBackCaptureMoveResult.addCapture(PieceLocation{C, 5});
  std::vector<Move> oneLeftBackCaptureMoves =
      MoveGenerator::getPieceMoves(boardOneLeftBackCaptureMove, D, 6);
  ASSERT_EQ(oneLeftBackCaptureMoves.size(), 1);
  ASSERT_EQ(
      std::find(oneLeftBackCaptureMoves.begin(), oneLeftBackCaptureMoves.end(),
                oneLeftBackCaptureMoveResult) != oneLeftBackCaptureMoves.end(),
      true);

  Board boardTwoLeftForwardCaptureMove = Board(true);
  boardTwoLeftForwardCaptureMove(E, 2) = new Queen(WHITE);
  boardTwoLeftForwardCaptureMove(D, 3) = new Pawn(BLACK);
  boardTwoLeftForwardCaptureMove(F, 3) = new Pawn(WHITE);
  boardTwoLeftForwardCaptureMove(B, 5) = new Pawn(BLACK);
  boardTwoLeftForwardCaptureMove(D, 1) = new Pawn(WHITE);
  boardTwoLeftForwardCaptureMove(F, 1) = new Pawn(WHITE);
  Move twoLeftForwardCaptureMoveResult = Move("E2A6");
  twoLeftForwardCaptureMoveResult.addCapture(PieceLocation{D, 3});
  twoLeftForwardCaptureMoveResult.addCapture(PieceLocation{B, 5});
  std::vector<Move> twoLeftForwardCaptureMoves =
      MoveGenerator::getPieceMoves(boardTwoLeftForwardCaptureMove, E, 2);
  ASSERT_EQ(twoLeftForwardCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(twoLeftForwardCaptureMoves.begin(),
                      twoLeftForwardCaptureMoves.end(),
                      twoLeftForwardCaptureMoveResult) !=
                twoLeftForwardCaptureMoves.end(),
            true);

  Board boardTwoLeftBackCaptureMove = Board(true);
  boardTwoLeftBackCaptureMove(E, 8) = new Queen(WHITE);
  boardTwoLeftBackCaptureMove(D, 7) = new Pawn(BLACK);
  boardTwoLeftBackCaptureMove(F, 7) = new Pawn(WHITE);
  boardTwoLeftBackCaptureMove(B, 5) = new Pawn(BLACK);
  Move twoLeftBackCaptureMoveResult = Move("E8A4");
  twoLeftBackCaptureMoveResult.addCapture(PieceLocation{D, 7});
  twoLeftBackCaptureMoveResult.addCapture(PieceLocation{B, 5});
  std::vector<Move> twoLeftBackCaptureMoves =
      MoveGenerator::getPieceMoves(boardTwoLeftBackCaptureMove, E, 8);
  ASSERT_EQ(twoLeftBackCaptureMoves.size(), 1);
  ASSERT_EQ(
      std::find(twoLeftBackCaptureMoves.begin(), twoLeftBackCaptureMoves.end(),
                twoLeftBackCaptureMoveResult) != twoLeftBackCaptureMoves.end(),
      true);

  Board boardOneRightForwardCaptureMove = Board(true);
  boardOneRightForwardCaptureMove(D, 4) = new Queen(WHITE);
  boardOneRightForwardCaptureMove(C, 5) = new Pawn(WHITE);
  boardOneRightForwardCaptureMove(E, 5) = new Pawn(BLACK);
  boardOneRightForwardCaptureMove(C, 3) = new Pawn(WHITE);
  boardOneRightForwardCaptureMove(E, 3) = new Pawn(WHITE);
  Move oneRightForwardCaptureMoveResult = Move("D4F6");
  oneRightForwardCaptureMoveResult.addCapture(PieceLocation{E, 5});
  std::vector<Move> oneRightForwardCaptureMoves =
      MoveGenerator::getPieceMoves(boardOneRightForwardCaptureMove, D, 4);
  ASSERT_EQ(oneRightForwardCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneRightForwardCaptureMoves.begin(),
                      oneRightForwardCaptureMoves.end(),
                      oneRightForwardCaptureMoveResult) !=
                oneRightForwardCaptureMoves.end(),
            true);

  Board boardOneRightBackCaptureMove = Board(true);
  boardOneRightBackCaptureMove(D, 6) = new Queen(WHITE);
  boardOneRightBackCaptureMove(C, 5) = new Pawn(WHITE);
  boardOneRightBackCaptureMove(E, 5) = new Pawn(BLACK);
  boardOneRightBackCaptureMove(C, 7) = new Pawn(WHITE);
  boardOneRightBackCaptureMove(E, 7) = new Pawn(WHITE);
  Move oneRightBackCaptureMoveResult = Move("D6F4");
  oneRightBackCaptureMoveResult.addCapture(PieceLocation{E, 5});
  std::vector<Move> oneRightBackCaptureMoves =
      MoveGenerator::getPieceMoves(boardOneRightBackCaptureMove, D, 6);
  ASSERT_EQ(oneRightBackCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneRightBackCaptureMoves.begin(),
                      oneRightBackCaptureMoves.end(),
                      oneRightBackCaptureMoveResult) !=
                oneRightBackCaptureMoves.end(),
            true);

  Board boardTwoRightBackCaptureMove = Board(true);
  boardTwoRightBackCaptureMove(B, 8) = new Queen(WHITE);
  boardTwoRightBackCaptureMove(A, 7) = new Pawn(WHITE);
  boardTwoRightBackCaptureMove(C, 7) = new Pawn(BLACK);
  boardTwoRightBackCaptureMove(E, 5) = new Pawn(BLACK);
  Move twoRightBackCaptureMoveResult = Move("B8F4");
  twoRightBackCaptureMoveResult.addCapture(PieceLocation{C, 7});
  twoRightBackCaptureMoveResult.addCapture(PieceLocation{E, 5});
  std::vector<Move> twoRightBackCaptureMoves =
      MoveGenerator::getPieceMoves(boardTwoRightBackCaptureMove, B, 8);
  ASSERT_EQ(twoRightBackCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(twoRightBackCaptureMoves.begin(),
                      twoRightBackCaptureMoves.end(),
                      twoRightBackCaptureMoveResult) !=
                twoRightBackCaptureMoves.end(),
            true);

  Board boardOneLeftOneRightForwardCaptureMove = Board(true);
  boardOneLeftOneRightForwardCaptureMove(D, 2) = new Queen(WHITE);
  boardOneLeftOneRightForwardCaptureMove(C, 3) = new Pawn(BLACK);
  boardOneLeftOneRightForwardCaptureMove(E, 3) = new Pawn(WHITE);
  boardOneLeftOneRightForwardCaptureMove(C, 5) = new Pawn(BLACK);
  boardOneLeftOneRightForwardCaptureMove(E, 1) = new Pawn(WHITE);
  boardOneLeftOneRightForwardCaptureMove(C, 1) = new Pawn(WHITE);
  Move oneLeftOneRightForwardCaptureMoveResult = Move("D2D6");
  oneLeftOneRightForwardCaptureMoveResult.addCapture(PieceLocation{C, 3});
  oneLeftOneRightForwardCaptureMoveResult.addCapture(PieceLocation{C, 5});
  std::vector<Move> oneLeftOneRightForwardCaptureMoves =
      MoveGenerator::getPieceMoves(boardOneLeftOneRightForwardCaptureMove, D,
                                   2);
  ASSERT_EQ(oneLeftOneRightForwardCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneLeftOneRightForwardCaptureMoves.begin(),
                      oneLeftOneRightForwardCaptureMoves.end(),
                      oneLeftOneRightForwardCaptureMoveResult) !=
                oneLeftOneRightForwardCaptureMoves.end(),
            true);

  Board boardOneRightOneLeftForwardCaptureMove = Board(true);
  boardOneRightOneLeftForwardCaptureMove(D, 2) = new Queen(WHITE);
  boardOneRightOneLeftForwardCaptureMove(C, 3) = new Pawn(WHITE);
  boardOneRightOneLeftForwardCaptureMove(E, 3) = new Pawn(BLACK);
  boardOneRightOneLeftForwardCaptureMove(E, 5) = new Pawn(BLACK);
  boardOneRightOneLeftForwardCaptureMove(C, 1) = new Pawn(WHITE);
  boardOneRightOneLeftForwardCaptureMove(E, 1) = new Pawn(WHITE);
  Move oneRightOneLeftForwardCaptureMoveResult = Move("D2D6");
  oneRightOneLeftForwardCaptureMoveResult.addCapture(PieceLocation{E, 3});
  oneRightOneLeftForwardCaptureMoveResult.addCapture(PieceLocation{E, 5});
  std::vector<Move> oneRightOneLeftForwardCaptureMoves =
      MoveGenerator::getPieceMoves(boardOneRightOneLeftForwardCaptureMove, D,
                                   2);
  ASSERT_EQ(oneRightOneLeftForwardCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneRightOneLeftForwardCaptureMoves.begin(),
                      oneRightOneLeftForwardCaptureMoves.end(),
                      oneRightOneLeftForwardCaptureMoveResult) !=
                oneRightOneLeftForwardCaptureMoves.end(),
            true);

  Board boardOneLeftOneRightBackCaptureMove = Board(true);
  boardOneLeftOneRightBackCaptureMove(D, 8) = new Queen(WHITE);
  boardOneLeftOneRightBackCaptureMove(C, 7) = new Pawn(BLACK);
  boardOneLeftOneRightBackCaptureMove(E, 7) = new Pawn(WHITE);
  boardOneLeftOneRightBackCaptureMove(C, 5) = new Pawn(BLACK);
  Move oneLeftOneRightBackCaptureMoveResult = Move("D8D4");
  oneLeftOneRightBackCaptureMoveResult.addCapture(PieceLocation{C, 7});
  oneLeftOneRightBackCaptureMoveResult.addCapture(PieceLocation{C, 5});
  std::vector<Move> oneLeftOneRightBackCaptureMoves =
      MoveGenerator::getPieceMoves(boardOneLeftOneRightBackCaptureMove, D, 8);
  ASSERT_EQ(oneLeftOneRightBackCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneLeftOneRightBackCaptureMoves.begin(),
                      oneLeftOneRightBackCaptureMoves.end(),
                      oneLeftOneRightBackCaptureMoveResult) !=
                oneLeftOneRightBackCaptureMoves.end(),
            true);

  Board boardOneRightOneLeftBackCaptureMove = Board(true);
  boardOneRightOneLeftBackCaptureMove(D, 8) = new Queen(WHITE);
  boardOneRightOneLeftBackCaptureMove(C, 7) = new Pawn(WHITE);
  boardOneRightOneLeftBackCaptureMove(E, 7) = new Pawn(BLACK);
  boardOneRightOneLeftBackCaptureMove(E, 5) = new Pawn(BLACK);
  Move oneRightOneLeftBackCaptureMoveResult = Move("D8D4");
  oneRightOneLeftBackCaptureMoveResult.addCapture(PieceLocation{E, 7});
  oneRightOneLeftBackCaptureMoveResult.addCapture(PieceLocation{E, 5});
  std::vector<Move> oneRightOneLeftBackCaptureMoves =
      MoveGenerator::getPieceMoves(boardOneRightOneLeftBackCaptureMove, D, 8);
  ASSERT_EQ(oneRightOneLeftBackCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneRightOneLeftBackCaptureMoves.begin(),
                      oneRightOneLeftBackCaptureMoves.end(),
                      oneRightOneLeftBackCaptureMoveResult) !=
                oneRightOneLeftBackCaptureMoves.end(),
            true);
}

TEST(MoveGeneratorTest, blackQueenMovesWithCapture) {
  Board boardOneLeftForwardCaptureMove = Board(true);
  boardOneLeftForwardCaptureMove(D, 4) = new Queen(BLACK);
  boardOneLeftForwardCaptureMove(C, 5) = new Pawn(WHITE);
  boardOneLeftForwardCaptureMove(E, 5) = new Pawn(BLACK);
  boardOneLeftForwardCaptureMove(E, 3) = new Pawn(BLACK);
  boardOneLeftForwardCaptureMove(C, 3) = new Pawn(BLACK);
  Move oneLeftForwardCaptureMoveResult = Move("D4B6");
  oneLeftForwardCaptureMoveResult.addCapture(PieceLocation{C, 5});
  std::vector<Move> oneLeftForwardCaptureMoves =
      MoveGenerator::getPieceMoves(boardOneLeftForwardCaptureMove, D, 4);
  ASSERT_EQ(oneLeftForwardCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneLeftForwardCaptureMoves.begin(),
                      oneLeftForwardCaptureMoves.end(),
                      oneLeftForwardCaptureMoveResult) !=
                oneLeftForwardCaptureMoves.end(),
            true);

  Board boardOneLeftBackCaptureMove = Board(true);
  boardOneLeftBackCaptureMove(D, 6) = new Queen(BLACK);
  boardOneLeftBackCaptureMove(C, 5) = new Pawn(WHITE);
  boardOneLeftBackCaptureMove(E, 5) = new Pawn(BLACK);
  boardOneLeftBackCaptureMove(E, 7) = new Pawn(BLACK);
  boardOneLeftBackCaptureMove(C, 7) = new Pawn(BLACK);
  Move oneLeftBackCaptureMoveResult = Move("D6B4");
  oneLeftBackCaptureMoveResult.addCapture(PieceLocation{C, 5});
  std::vector<Move> oneLeftBackCaptureMoves =
      MoveGenerator::getPieceMoves(boardOneLeftBackCaptureMove, D, 6);
  ASSERT_EQ(oneLeftBackCaptureMoves.size(), 1);
  ASSERT_EQ(
      std::find(oneLeftBackCaptureMoves.begin(), oneLeftBackCaptureMoves.end(),
                oneLeftBackCaptureMoveResult) != oneLeftBackCaptureMoves.end(),
      true);

  Board boardTwoLeftForwardCaptureMove = Board(true);
  boardTwoLeftForwardCaptureMove(E, 2) = new Queen(BLACK);
  boardTwoLeftForwardCaptureMove(D, 3) = new Pawn(WHITE);
  boardTwoLeftForwardCaptureMove(F, 3) = new Pawn(BLACK);
  boardTwoLeftForwardCaptureMove(B, 5) = new Pawn(WHITE);
  boardTwoLeftForwardCaptureMove(D, 1) = new Pawn(BLACK);
  boardTwoLeftForwardCaptureMove(F, 1) = new Pawn(BLACK);
  Move twoLeftForwardCaptureMoveResult = Move("E2A6");
  twoLeftForwardCaptureMoveResult.addCapture(PieceLocation{D, 3});
  twoLeftForwardCaptureMoveResult.addCapture(PieceLocation{B, 5});
  std::vector<Move> twoLeftForwardCaptureMoves =
      MoveGenerator::getPieceMoves(boardTwoLeftForwardCaptureMove, E, 2);
  ASSERT_EQ(twoLeftForwardCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(twoLeftForwardCaptureMoves.begin(),
                      twoLeftForwardCaptureMoves.end(),
                      twoLeftForwardCaptureMoveResult) !=
                twoLeftForwardCaptureMoves.end(),
            true);

  Board boardTwoLeftBackCaptureMove = Board(true);
  boardTwoLeftBackCaptureMove(E, 8) = new Queen(BLACK);
  boardTwoLeftBackCaptureMove(D, 7) = new Pawn(WHITE);
  boardTwoLeftBackCaptureMove(F, 7) = new Pawn(BLACK);
  boardTwoLeftBackCaptureMove(B, 5) = new Pawn(WHITE);
  Move twoLeftBackCaptureMoveResult = Move("E8A4");
  twoLeftBackCaptureMoveResult.addCapture(PieceLocation{D, 7});
  twoLeftBackCaptureMoveResult.addCapture(PieceLocation{B, 5});
  std::vector<Move> twoLeftBackCaptureMoves =
      MoveGenerator::getPieceMoves(boardTwoLeftBackCaptureMove, E, 8);
  ASSERT_EQ(twoLeftBackCaptureMoves.size(), 1);
  ASSERT_EQ(
      std::find(twoLeftBackCaptureMoves.begin(), twoLeftBackCaptureMoves.end(),
                twoLeftBackCaptureMoveResult) != twoLeftBackCaptureMoves.end(),
      true);

  Board boardOneRightForwardCaptureMove = Board(true);
  boardOneRightForwardCaptureMove(D, 4) = new Queen(BLACK);
  boardOneRightForwardCaptureMove(C, 5) = new Pawn(BLACK);
  boardOneRightForwardCaptureMove(E, 5) = new Pawn(WHITE);
  boardOneRightForwardCaptureMove(C, 3) = new Pawn(BLACK);
  boardOneRightForwardCaptureMove(E, 3) = new Pawn(BLACK);
  Move oneRightForwardCaptureMoveResult = Move("D4F6");
  oneRightForwardCaptureMoveResult.addCapture(PieceLocation{E, 5});
  std::vector<Move> oneRightForwardCaptureMoves =
      MoveGenerator::getPieceMoves(boardOneRightForwardCaptureMove, D, 4);
  ASSERT_EQ(oneRightForwardCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneRightForwardCaptureMoves.begin(),
                      oneRightForwardCaptureMoves.end(),
                      oneRightForwardCaptureMoveResult) !=
                oneRightForwardCaptureMoves.end(),
            true);

  Board boardOneRightBackCaptureMove = Board(true);
  boardOneRightBackCaptureMove(D, 6) = new Queen(BLACK);
  boardOneRightBackCaptureMove(C, 5) = new Pawn(BLACK);
  boardOneRightBackCaptureMove(E, 5) = new Pawn(WHITE);
  boardOneRightBackCaptureMove(C, 7) = new Pawn(BLACK);
  boardOneRightBackCaptureMove(E, 7) = new Pawn(BLACK);
  Move oneRightBackCaptureMoveResult = Move("D6F4");
  oneRightBackCaptureMoveResult.addCapture(PieceLocation{E, 5});
  std::vector<Move> oneRightBackCaptureMoves =
      MoveGenerator::getPieceMoves(boardOneRightBackCaptureMove, D, 6);
  ASSERT_EQ(oneRightBackCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneRightBackCaptureMoves.begin(),
                      oneRightBackCaptureMoves.end(),
                      oneRightBackCaptureMoveResult) !=
                oneRightBackCaptureMoves.end(),
            true);

  Board boardTwoRightBackCaptureMove = Board(true);
  boardTwoRightBackCaptureMove(B, 8) = new Queen(BLACK);
  boardTwoRightBackCaptureMove(A, 7) = new Pawn(BLACK);
  boardTwoRightBackCaptureMove(C, 7) = new Pawn(WHITE);
  boardTwoRightBackCaptureMove(E, 5) = new Pawn(WHITE);
  Move twoRightBackCaptureMoveResult = Move("B8F4");
  twoRightBackCaptureMoveResult.addCapture(PieceLocation{C, 7});
  twoRightBackCaptureMoveResult.addCapture(PieceLocation{E, 5});
  std::vector<Move> twoRightBackCaptureMoves =
      MoveGenerator::getPieceMoves(boardTwoRightBackCaptureMove, B, 8);
  ASSERT_EQ(twoRightBackCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(twoRightBackCaptureMoves.begin(),
                      twoRightBackCaptureMoves.end(),
                      twoRightBackCaptureMoveResult) !=
                twoRightBackCaptureMoves.end(),
            true);

  Board boardOneLeftOneRightForwardCaptureMove = Board(true);
  boardOneLeftOneRightForwardCaptureMove(D, 2) = new Queen(BLACK);
  boardOneLeftOneRightForwardCaptureMove(C, 3) = new Pawn(WHITE);
  boardOneLeftOneRightForwardCaptureMove(E, 3) = new Pawn(BLACK);
  boardOneLeftOneRightForwardCaptureMove(C, 5) = new Pawn(WHITE);
  boardOneLeftOneRightForwardCaptureMove(E, 1) = new Pawn(BLACK);
  boardOneLeftOneRightForwardCaptureMove(C, 1) = new Pawn(BLACK);
  Move oneLeftOneRightForwardCaptureMoveResult = Move("D2D6");
  oneLeftOneRightForwardCaptureMoveResult.addCapture(PieceLocation{C, 3});
  oneLeftOneRightForwardCaptureMoveResult.addCapture(PieceLocation{C, 5});
  std::vector<Move> oneLeftOneRightForwardCaptureMoves =
      MoveGenerator::getPieceMoves(boardOneLeftOneRightForwardCaptureMove, D,
                                   2);
  ASSERT_EQ(oneLeftOneRightForwardCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneLeftOneRightForwardCaptureMoves.begin(),
                      oneLeftOneRightForwardCaptureMoves.end(),
                      oneLeftOneRightForwardCaptureMoveResult) !=
                oneLeftOneRightForwardCaptureMoves.end(),
            true);

  Board boardOneRightOneLeftForwardCaptureMove = Board(true);
  boardOneRightOneLeftForwardCaptureMove(D, 2) = new Queen(BLACK);
  boardOneRightOneLeftForwardCaptureMove(C, 3) = new Pawn(BLACK);
  boardOneRightOneLeftForwardCaptureMove(E, 3) = new Pawn(WHITE);
  boardOneRightOneLeftForwardCaptureMove(E, 5) = new Pawn(WHITE);
  boardOneRightOneLeftForwardCaptureMove(C, 1) = new Pawn(BLACK);
  boardOneRightOneLeftForwardCaptureMove(E, 1) = new Pawn(BLACK);
  Move oneRightOneLeftForwardCaptureMoveResult = Move("D2D6");
  oneRightOneLeftForwardCaptureMoveResult.addCapture(PieceLocation{E, 3});
  oneRightOneLeftForwardCaptureMoveResult.addCapture(PieceLocation{E, 5});
  std::vector<Move> oneRightOneLeftForwardCaptureMoves =
      MoveGenerator::getPieceMoves(boardOneRightOneLeftForwardCaptureMove, D,
                                   2);
  ASSERT_EQ(oneRightOneLeftForwardCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneRightOneLeftForwardCaptureMoves.begin(),
                      oneRightOneLeftForwardCaptureMoves.end(),
                      oneRightOneLeftForwardCaptureMoveResult) !=
                oneRightOneLeftForwardCaptureMoves.end(),
            true);

  Board boardOneLeftOneRightBackCaptureMove = Board(true);
  boardOneLeftOneRightBackCaptureMove(D, 8) = new Queen(BLACK);
  boardOneLeftOneRightBackCaptureMove(C, 7) = new Pawn(WHITE);
  boardOneLeftOneRightBackCaptureMove(E, 7) = new Pawn(BLACK);
  boardOneLeftOneRightBackCaptureMove(C, 5) = new Pawn(WHITE);
  Move oneLeftOneRightBackCaptureMoveResult = Move("D8D4");
  oneLeftOneRightBackCaptureMoveResult.addCapture(PieceLocation{C, 7});
  oneLeftOneRightBackCaptureMoveResult.addCapture(PieceLocation{C, 5});
  std::vector<Move> oneLeftOneRightBackCaptureMoves =
      MoveGenerator::getPieceMoves(boardOneLeftOneRightBackCaptureMove, D, 8);
  ASSERT_EQ(oneLeftOneRightBackCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneLeftOneRightBackCaptureMoves.begin(),
                      oneLeftOneRightBackCaptureMoves.end(),
                      oneLeftOneRightBackCaptureMoveResult) !=
                oneLeftOneRightBackCaptureMoves.end(),
            true);

  Board boardOneRightOneLeftBackCaptureMove = Board(true);
  boardOneRightOneLeftBackCaptureMove(D, 8) = new Queen(BLACK);
  boardOneRightOneLeftBackCaptureMove(C, 7) = new Pawn(BLACK);
  boardOneRightOneLeftBackCaptureMove(E, 7) = new Pawn(WHITE);
  boardOneRightOneLeftBackCaptureMove(E, 5) = new Pawn(WHITE);
  Move oneRightOneLeftBackCaptureMoveResult = Move("D8D4");
  oneRightOneLeftBackCaptureMoveResult.addCapture(PieceLocation{E, 7});
  oneRightOneLeftBackCaptureMoveResult.addCapture(PieceLocation{E, 5});
  std::vector<Move> oneRightOneLeftBackCaptureMoves =
      MoveGenerator::getPieceMoves(boardOneRightOneLeftBackCaptureMove, D, 8);
  ASSERT_EQ(oneRightOneLeftBackCaptureMoves.size(), 1);
  ASSERT_EQ(std::find(oneRightOneLeftBackCaptureMoves.begin(),
                      oneRightOneLeftBackCaptureMoves.end(),
                      oneRightOneLeftBackCaptureMoveResult) !=
                oneRightOneLeftBackCaptureMoves.end(),
            true);
}
