// clang-format off
#include <gtest/gtest.h>
// clang-format on
#include "../lib/include/Game.hpp"

TEST(PieceTest, attributes) {
  Pawn P = Pawn(WHITE);
  Queen Q = Queen(WHITE);
  Pawn p = Pawn(BLACK);
  Queen q = Queen(BLACK);

  EXPECT_EQ(P.getColor(), WHITE);
  EXPECT_EQ(P.getType(), PieceType::PAWN);

  EXPECT_EQ(Q.getColor(), WHITE);
  EXPECT_EQ(Q.getType(), PieceType::QUEEN);

  EXPECT_EQ(p.getColor(), BLACK);
  EXPECT_EQ(p.getType(), PieceType::PAWN);

  EXPECT_EQ(q.getColor(), BLACK);
  EXPECT_EQ(q.getType(), PieceType::QUEEN);
}

TEST(PieceTest, representations) {
  EXPECT_EQ(Pawn(WHITE).repr(), WPAWN);
  EXPECT_EQ(Queen(WHITE).repr(), WQUEEN);
  EXPECT_EQ(Pawn(BLACK).repr(), BPAWN);
  EXPECT_EQ(Queen(BLACK).repr(), BQUEEN);
}

TEST(PieceTest, PieceLocation) {
  PieceLocation p1 = PieceLocation{A, 1};
  PieceLocation p2 = PieceLocation{B, 3};
  PieceLocation p3 = PieceLocation{D, 5};

  EXPECT_EQ(p1.file, A);
  EXPECT_EQ(p1.rank, 1);

  EXPECT_EQ(p2.file, B);
  EXPECT_EQ(p2.rank, 3);

  EXPECT_EQ(p3.file, D);
  EXPECT_EQ(p3.rank, 5);
}
