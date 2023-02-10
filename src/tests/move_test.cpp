#include "../lib/include/Board.hpp"
#include "../lib/include/Move.hpp"
#include <gtest/gtest.h>

TEST(MoveTest, attributes) {
  Move m1 = Move(A, 1, B, 2);
  Move m2 = Move(C, 4, D, 5);
  Move m3 = Move("D3E4");
  Move m4 = Move("G5H6");

  ASSERT_EQ(m1.getOriginFile(), A);
  ASSERT_EQ(m1.getOriginRank(), 1);
  ASSERT_EQ(m1.getDestinationFile(), B);
  ASSERT_EQ(m1.getDestinationRank(), 2);

  ASSERT_EQ(m2.getOriginFile(), C);
  ASSERT_EQ(m2.getOriginRank(), 4);
  ASSERT_EQ(m2.getDestinationFile(), D);
  ASSERT_EQ(m2.getDestinationRank(), 5);

  ASSERT_EQ(m3.getOriginFile(), D);
  ASSERT_EQ(m3.getOriginRank(), 3);
  ASSERT_EQ(m3.getDestinationFile(), E);
  ASSERT_EQ(m3.getDestinationRank(), 4);

  ASSERT_EQ(m4.getOriginFile(), G);
  ASSERT_EQ(m4.getOriginRank(), 5);
  ASSERT_EQ(m4.getDestinationFile(), H);
  ASSERT_EQ(m4.getDestinationRank(), 6);

  m1.addCapture(PieceLocation{A, 1});
  m1.addCapture(PieceLocation{B, 3});
  m1.addCapture(PieceLocation{D, 5});

  m2.addCapture(PieceLocation{H, 8});

  std::vector<PieceLocation> m1PieceLocations = m1.getCaptures();
  std::vector<PieceLocation> m2PieceLocations = m2.getCaptures();

  ASSERT_EQ(m1PieceLocations[0].file, A);
  ASSERT_EQ(m1PieceLocations[0].rank, 1);

  ASSERT_EQ(m1PieceLocations[1].file, B);
  ASSERT_EQ(m1PieceLocations[1].rank, 3);

  ASSERT_EQ(m1PieceLocations[2].file, D);
  ASSERT_EQ(m1PieceLocations[2].rank, 5);

  ASSERT_EQ(m2PieceLocations[0].file, H);
  ASSERT_EQ(m2PieceLocations[0].rank, 8);

  ASSERT_EQ(m3.getCaptures().size(), 0);
}

TEST(MoveTest, representations) {
  Move m1 = Move(A, 1, B, 2);
  Move m2 = Move(C, 4, D, 5);
  Move m3 = Move("D3E4");
  Move m4 = Move("G5H6");

  ASSERT_STREQ(m1.repr().c_str(), "A1B2");
  ASSERT_STREQ(m2.repr().c_str(), "C4D5");

  ASSERT_STREQ(m3.repr().c_str(), "D3E4");
  ASSERT_STREQ(m4.repr().c_str(), "G5H6");
}

TEST(MoveTest, operations) {
  Move m1 = Move(A, 1, B, 2);
  Move m2 = Move(C, 4, D, 5);
  Move m3 = Move("A1B2");
  Move m4 = Move("C4D5");
  Move m5 = Move("D3E4");
  Move m6 = Move("G5H6");
  Move m7 = Move("D3E4");
  Move m8 = Move(H, 3, D, 5);

  ASSERT_EQ(m1, m3);
  ASSERT_EQ(m2, m4);
  ASSERT_EQ(m5, m7);

  ASSERT_NE(m1, m2);
  ASSERT_NE(m6, m8);
  ASSERT_NE(m1, m5);
}
