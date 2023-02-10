#include "../lib/include/Game.hpp"
#include <gtest/gtest.h>

TEST(BoardTest, operators) {
  Board board = Board();

  ASSERT_EQ(board(A, 1).repr(), ' ');
  ASSERT_EQ(board(B, 1).repr(), 'p');
  ASSERT_EQ(board(G, 7).repr(), ' ');
  ASSERT_EQ(board(H, 7).repr(), 'P');

  EXPECT_NO_THROW(board(A, 1));
  EXPECT_NO_THROW(board(H, 8));
  EXPECT_THROW(board(A, 9), std::runtime_error);
  EXPECT_THROW(board(A, 10), std::runtime_error);
  EXPECT_THROW(board(A, 0), std::runtime_error);
  EXPECT_THROW(board(9, 1), std::runtime_error);
  EXPECT_THROW(board(10, 10), std::runtime_error);
  EXPECT_THROW(board(0, 0), std::runtime_error);
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
