// clang-format off
#include <gtest/gtest.h>
// clang-format on
#include "../lib/game/Game.hpp"

TEST(TileTest, methods) {
  Tile t1 = Tile(new Pawn(WHITE));
  Tile t2 = Tile(new Queen(BLACK));

  EXPECT_EQ(t1.isEmpty(), false);
  EXPECT_EQ(t2.isEmpty(), false);
  EXPECT_EQ(t1.getPiece().getColor(), WHITE);
  EXPECT_EQ(t1.getPiece().getType(), PieceType::PAWN);
  EXPECT_EQ(t2.getPiece().getColor(), BLACK);
  EXPECT_EQ(t2.getPiece().getType(), PieceType::QUEEN);

  t1.reset();
  t2.reset();

  EXPECT_EQ(t1.isEmpty(), true);
  EXPECT_EQ(t2.isEmpty(), true);

  EXPECT_EQ(Tile().isEmpty(), true);
  EXPECT_EQ(Tile(new Pawn(WHITE)).isEmpty(), false);
  EXPECT_EQ(Tile(new Pawn(BLACK)).isEmpty(), false);
  EXPECT_EQ(Tile(new Queen(WHITE)).isEmpty(), false);
  EXPECT_EQ(Tile(new Queen(BLACK)).isEmpty(), false);
}

TEST(TileTest, operators) {
  Tile t1 = Tile(new Pawn(WHITE));
  Tile t2 = Tile(new Queen(BLACK));

  EXPECT_EQ(t1.isEmpty(), false);
  EXPECT_EQ(t2.isEmpty(), false);
  EXPECT_EQ(t1.getPiece().getColor(), WHITE);
  EXPECT_EQ(t1.getPiece().getType(), PieceType::PAWN);
  EXPECT_EQ(t2.getPiece().getColor(), BLACK);
  EXPECT_EQ(t2.getPiece().getType(), PieceType::QUEEN);

  t1 = std::move(t2);

  EXPECT_EQ(t1.isEmpty(), false);
  EXPECT_EQ(t2.isEmpty(), false);
  EXPECT_EQ(t1.getPiece().getColor(), BLACK);
  EXPECT_EQ(t1.getPiece().getType(), PieceType::QUEEN);
  EXPECT_EQ(t2.getPiece().getColor(), BLACK);
  EXPECT_EQ(t2.getPiece().getType(), PieceType::QUEEN);

  t2.reset();

  EXPECT_EQ(t1.isEmpty(), false);
  EXPECT_EQ(t2.isEmpty(), true);
  EXPECT_EQ(t1.getPiece().getColor(), BLACK);
  EXPECT_EQ(t1.getPiece().getType(), PieceType::QUEEN);

  t2 = new Pawn(WHITE);

  EXPECT_EQ(t1.isEmpty(), false);
  EXPECT_EQ(t2.isEmpty(), false);
  EXPECT_EQ(t1.getPiece().getColor(), BLACK);
  EXPECT_EQ(t1.getPiece().getType(), PieceType::QUEEN);
  EXPECT_EQ(t2.getPiece().getColor(), WHITE);
  EXPECT_EQ(t2.getPiece().getType(), PieceType::PAWN);
}

TEST(TileTest, representations) {
  EXPECT_EQ(Tile().repr(), ' ');
  EXPECT_EQ(Tile(new Pawn(WHITE)).repr(), 'w');
  EXPECT_EQ(Tile(new Pawn(BLACK)).repr(), 'b');
  EXPECT_EQ(Tile(new Queen(WHITE)).repr(), 'W');
  EXPECT_EQ(Tile(new Queen(BLACK)).repr(), 'B');
}
