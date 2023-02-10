// clang-format off
#include <gtest/gtest.h>
// clang-format on
#include "../lib/include/Game.hpp"

TEST(TileTest, attributes) {
  EXPECT_EQ(Tile().isEmpty(), true);
  EXPECT_EQ(Tile(new Pawn(WHITE)).isEmpty(), false);
  EXPECT_EQ(Tile(new Pawn(BLACK)).isEmpty(), false);
  EXPECT_EQ(Tile(new Queen(WHITE)).isEmpty(), false);
  EXPECT_EQ(Tile(new Queen(BLACK)).isEmpty(), false);
}

TEST(TileTest, representations) {
  EXPECT_EQ(Tile().repr(), ' ');
  EXPECT_EQ(Tile(new Pawn(WHITE)).repr(), 'P');
  EXPECT_EQ(Tile(new Pawn(BLACK)).repr(), 'p');
  EXPECT_EQ(Tile(new Queen(WHITE)).repr(), 'Q');
  EXPECT_EQ(Tile(new Queen(BLACK)).repr(), 'q');
}
