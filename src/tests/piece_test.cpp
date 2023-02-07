#include <gtest/gtest.h>
#include "../lib/include/Piece.hpp"
#include "../lib/include/Pawn.hpp"
#include "../lib/include/Queen.hpp"
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
