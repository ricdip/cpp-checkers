// clang-format off
#include <gtest/gtest.h>
#include <algorithm>
// clang-format on
#include "../lib/game/Game.hpp"

TEST(BoardTest, baseMethods) {
  Board board1 = Board();
  Board board2 = Board(BLACK, true);

  ASSERT_EQ(board1.getTurn(), WHITE);
  ASSERT_EQ(board1.countPiecesByColor(WHITE), 12);
  ASSERT_EQ(board1.countPiecesByColor(BLACK), 12);

  ASSERT_EQ(board2.getTurn(), BLACK);
  ASSERT_EQ(board2.countPiecesByColor(WHITE), 0);
  ASSERT_EQ(board2.countPiecesByColor(BLACK), 0);
}

TEST(BoardTest, operators) {
  Board board = Board();

  EXPECT_NO_THROW(board(A, 1));
  EXPECT_NO_THROW(board(H, 8));
  EXPECT_THROW(board(A, 9), std::runtime_error);
  EXPECT_THROW(board(A, 10), std::runtime_error);
  EXPECT_THROW(board(A, 0), std::runtime_error);
  EXPECT_THROW(board(9, 1), std::runtime_error);
  EXPECT_THROW(board(10, 10), std::runtime_error);
  EXPECT_THROW(board(0, 0), std::runtime_error);
}

TEST(BoardTest, representations) {
  Board board = Board();

  ASSERT_EQ(board(A, 1).repr(), ' ');
  ASSERT_EQ(board(B, 1).repr(), 'p');
  ASSERT_EQ(board(G, 7).repr(), ' ');
  ASSERT_EQ(board(H, 7).repr(), 'P');
}

TEST(BoardTest, bounds) {
  Board board = Board();

  ASSERT_EQ(board.checkPositionInBound(A, 1), true);
  ASSERT_EQ(board.checkPositionInBound(B, 1), true);
  ASSERT_EQ(board.checkPositionInBound(G, 7), true);
  ASSERT_EQ(board.checkPositionInBound(H, 7), true);
  ASSERT_EQ(board.checkPositionInBound(E, 8), true);
  ASSERT_EQ(board.checkPositionInBound(F, 8), true);
  ASSERT_EQ(board.checkPositionInBound(H, 8), true);

  ASSERT_EQ(board.checkPositionInBound(A, 0), false);
  ASSERT_EQ(board.checkPositionInBound(A, 9), false);
  ASSERT_EQ(board.checkPositionInBound(9, 2), false);
  ASSERT_EQ(board.checkPositionInBound(9, 9), false);
  ASSERT_EQ(board.checkPositionInBound(10, 0), false);
  ASSERT_EQ(board.checkPositionInBound(10, 10), false);
  ASSERT_EQ(board.checkPositionInBound(0, 0), false);
}

TEST(BoardTest, countPiecesInBoard) {
  Board board = Board();
  ASSERT_EQ(board.countPiecesByColor(WHITE), 12);
  ASSERT_EQ(board.countPiecesByColor(BLACK), 12);

  Board board_2_whites = Board(true);
  board_2_whites(G, 3) = new Pawn(WHITE);
  board_2_whites(H, 5) = new Queen(WHITE);
  ASSERT_EQ(board_2_whites.countPiecesByColor(WHITE), 2);
  ASSERT_EQ(board_2_whites.countPiecesByColor(BLACK), 0);

  Board board_2_blacks = Board(true);
  board_2_blacks(G, 3) = new Pawn(BLACK);
  board_2_blacks(H, 5) = new Queen(BLACK);
  ASSERT_EQ(board_2_blacks.countPiecesByColor(WHITE), 0);
  ASSERT_EQ(board_2_blacks.countPiecesByColor(BLACK), 2);
}

TEST(BoardTest, customBoards) {
  Board board = Board();
  Board customBoard = Board(true);
  customBoard(G, 3) = new Pawn(WHITE);
  customBoard(H, 5) = new Queen(WHITE);
  customBoard(H, 1) = new Queen(BLACK);

  ASSERT_EQ(board.countPiecesByColor(WHITE), 12);
  ASSERT_EQ(board.countPiecesByColor(BLACK), 12);

  ASSERT_EQ(customBoard.countPiecesByColor(WHITE), 2);
  ASSERT_EQ(customBoard.countPiecesByColor(BLACK), 1);
}

TEST(BoardTest, boardMoves) {
  Board board1 = Board();

  std::vector<Move> board1Moves = board1.getMoves();

  ASSERT_EQ(board1Moves.size(), 7);
  ASSERT_EQ(std::find(board1Moves.begin(), board1Moves.end(), Move("A6B5")) !=
                board1Moves.end(),
            true);
  ASSERT_EQ(std::find(board1Moves.begin(), board1Moves.end(), Move("C6B5")) !=
                board1Moves.end(),
            true);
  ASSERT_EQ(std::find(board1Moves.begin(), board1Moves.end(), Move("C6D5")) !=
                board1Moves.end(),
            true);
  ASSERT_EQ(std::find(board1Moves.begin(), board1Moves.end(), Move("E6D5")) !=
                board1Moves.end(),
            true);
  ASSERT_EQ(std::find(board1Moves.begin(), board1Moves.end(), Move("E6F5")) !=
                board1Moves.end(),
            true);
  ASSERT_EQ(std::find(board1Moves.begin(), board1Moves.end(), Move("G6F5")) !=
                board1Moves.end(),
            true);
  ASSERT_EQ(std::find(board1Moves.begin(), board1Moves.end(), Move("G6H5")) !=
                board1Moves.end(),
            true);

  Board board2 = Board(BLACK, true);
  board2(C, 6) = new Queen(BLACK);
  board2(D, 5) = new Pawn(WHITE);

  std::vector<Move> board2Moves = board2.getMoves();

  Move moveCapturedPawn = Move("C6E4");
  moveCapturedPawn.addCapture(PieceLocation{D, 5});

  ASSERT_EQ(board2Moves.size(), 4);
  ASSERT_EQ(std::find(board2Moves.begin(), board2Moves.end(), Move("C6B5")) !=
                board2Moves.end(),
            true);
  ASSERT_EQ(std::find(board2Moves.begin(), board2Moves.end(),
                      moveCapturedPawn) != board2Moves.end(),
            true);
  ASSERT_EQ(std::find(board2Moves.begin(), board2Moves.end(), Move("C6B7")) !=
                board2Moves.end(),
            true);
  ASSERT_EQ(std::find(board2Moves.begin(), board2Moves.end(), Move("C6D7")) !=
                board2Moves.end(),
            true);
}

TEST(BoardTest, makeIllegalMove) {
  Board board = Board();
  EXPECT_THROW(board.makeMove(Move("G4E5")), std::runtime_error);
  EXPECT_THROW(board.makeMove(Move("H7H6")), std::runtime_error);
  EXPECT_THROW(board.makeMove(Move("G4E5")), std::runtime_error);
  EXPECT_THROW(board.makeMove(Move("B34C")), std::runtime_error);
}

TEST(BoardTest, makeMovesNoCapture) {
  Board board = Board(true);
  board(D, 5) = new Pawn(WHITE);
  board(A, 5) = new Pawn(BLACK);

  EXPECT_EQ(board.getTurn(), WHITE);
  EXPECT_NO_THROW(board.makeMove(Move("D5E4")));
  EXPECT_EQ(board.getTurn(), BLACK);
  EXPECT_EQ(board(D, 5).isEmpty(), true);
  EXPECT_EQ(board(E, 4).isEmpty(), false);
  EXPECT_EQ(board(E, 4).getPiece().getColor(), WHITE);
  EXPECT_EQ(board(E, 4).getPiece().getType(), PieceType::PAWN);

  EXPECT_EQ(board.getTurn(), BLACK);
  EXPECT_NO_THROW(board.makeMove(Move("A5B6")));
  EXPECT_EQ(board.getTurn(), WHITE);
  EXPECT_EQ(board(A, 5).isEmpty(), true);
  EXPECT_EQ(board(B, 6).isEmpty(), false);
  EXPECT_EQ(board(B, 6).getPiece().getColor(), BLACK);
  EXPECT_EQ(board(B, 6).getPiece().getType(), PieceType::PAWN);
}

TEST(BoardTest, makeMovesOneCapture) {
  Board board = Board(true);
  board(D, 5) = new Pawn(WHITE);
  board(E, 4) = new Pawn(BLACK);
  board(A, 5) = new Pawn(BLACK);
  board(B, 6) = new Pawn(WHITE);

  EXPECT_EQ(board.getTurn(), WHITE);
  EXPECT_NO_THROW(board.makeMove(Move("D5F3")));
  EXPECT_EQ(board.getTurn(), BLACK);
  EXPECT_EQ(board(D, 5).isEmpty(), true);
  EXPECT_EQ(board(E, 4).isEmpty(), true);
  EXPECT_EQ(board(F, 3).isEmpty(), false);
  EXPECT_EQ(board(F, 3).getPiece().getColor(), WHITE);
  EXPECT_EQ(board(F, 3).getPiece().getType(), PieceType::PAWN);

  EXPECT_EQ(board.getTurn(), BLACK);
  EXPECT_NO_THROW(board.makeMove(Move("A5C7")));
  EXPECT_EQ(board.getTurn(), WHITE);
  EXPECT_EQ(board(A, 5).isEmpty(), true);
  EXPECT_EQ(board(B, 6).isEmpty(), true);
  EXPECT_EQ(board(C, 7).isEmpty(), false);
  EXPECT_EQ(board(C, 7).getPiece().getColor(), BLACK);
  EXPECT_EQ(board(C, 7).getPiece().getType(), PieceType::PAWN);
}

TEST(BoardTest, makeMovesMultiCaptures) {
  Board board = Board(true);
  board(D, 5) = new Pawn(WHITE);
  board(E, 4) = new Pawn(BLACK);
  board(E, 2) = new Pawn(BLACK);

  board(A, 4) = new Pawn(BLACK);
  board(B, 5) = new Pawn(WHITE);
  board(B, 7) = new Pawn(WHITE);

  EXPECT_EQ(board.getTurn(), WHITE);
  EXPECT_NO_THROW(board.makeMove(Move("D5D1")));
  EXPECT_EQ(board.getTurn(), BLACK);
  EXPECT_EQ(board(D, 5).isEmpty(), true);
  EXPECT_EQ(board(E, 4).isEmpty(), true);
  EXPECT_EQ(board(E, 2).isEmpty(), true);
  EXPECT_EQ(board(D, 1).isEmpty(), false);
  EXPECT_EQ(board(D, 1).getPiece().getColor(), WHITE);
  EXPECT_EQ(board(D, 1).getPiece().getType(), PieceType::PAWN);

  EXPECT_EQ(board.getTurn(), BLACK);
  EXPECT_NO_THROW(board.makeMove(Move("A4A8")));
  EXPECT_EQ(board.getTurn(), WHITE);
  EXPECT_EQ(board(A, 4).isEmpty(), true);
  EXPECT_EQ(board(B, 5).isEmpty(), true);
  EXPECT_EQ(board(B, 7).isEmpty(), true);
  EXPECT_EQ(board(A, 8).isEmpty(), false);
  EXPECT_EQ(board(A, 8).getPiece().getColor(), BLACK);
  EXPECT_EQ(board(A, 8).getPiece().getType(), PieceType::PAWN);
}
