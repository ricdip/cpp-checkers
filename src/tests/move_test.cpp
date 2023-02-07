#include <gtest/gtest.h>
#include "../lib/include/Move.hpp"
#include "../lib/include/Board.hpp"

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
