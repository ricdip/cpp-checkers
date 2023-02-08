#include <gtest/gtest.h>
#include "../lib/include/Board.hpp"

TEST(BoardTest, operators) {
    Board board = Board();

    ASSERT_EQ(board(A, 1).repr(), ' ');
    ASSERT_EQ(board(B, 1).repr(), 'p');
    ASSERT_EQ(board(G, 7).repr(), ' ');
    ASSERT_EQ(board(H, 7).repr(), 'P');

    EXPECT_THROW(board(A, 9), std::runtime_error);
    EXPECT_THROW(board(A, 10), std::runtime_error);
    EXPECT_THROW(board(A, 0), std::runtime_error);
    EXPECT_THROW(board(8, 1), std::runtime_error);
    EXPECT_THROW(board(9, 1), std::runtime_error);
}

TEST(BoardTest, bounds) {
    Board board = Board();

    ASSERT_EQ(board.checkPositionInBound(A, 1), true);
    ASSERT_EQ(board.checkPositionInBound(B, 1), true);
    ASSERT_EQ(board.checkPositionInBound(G, 7), true);
    ASSERT_EQ(board.checkPositionInBound(H, 7), true);
    ASSERT_EQ(board.checkPositionInBound(E, 8), true);
    ASSERT_EQ(board.checkPositionInBound(F, 8), true);

    ASSERT_EQ(board.checkPositionInBound(A, 0), false);
    ASSERT_EQ(board.checkPositionInBound(A, 9), false);
    ASSERT_EQ(board.checkPositionInBound(8, 2), false);
    ASSERT_EQ(board.checkPositionInBound(9, 2), false);
    ASSERT_EQ(board.checkPositionInBound(10, 0), false);
    ASSERT_EQ(board.checkPositionInBound(10, 10), false);
}
