#include <gtest/gtest.h>
#include "../lib/include/Pawn.hpp"
#include "../lib/include/Queen.hpp"
#include "../lib/include/Game.hpp"
#include "../lib/include/Tile.hpp"

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
