// clang-format off
#include <gtest/gtest.h>
// clang-format on
#include "../lib/game/Game.hpp"
#include "../lib/game/GameResult.hpp"
#include <vector>

TEST(GameTest, neighbors) {
  Board board = Board(true);
  board(D, 5) = new Pawn(WHITE);
  board(E, 6) = new Pawn(BLACK);

  std::vector<Board> states = Game::neighbors(board);
  ASSERT_EQ(states.size(), 2);
  ASSERT_EQ(states[0](D, 5).isEmpty(), true);
  ASSERT_EQ(states[0](C, 6).isEmpty(), false);
  ASSERT_EQ(states[0](E, 6).isEmpty(), false);
  ASSERT_EQ(states[0](F, 7).isEmpty(), true);

  ASSERT_EQ(states[1](D, 5).isEmpty(), true);
  ASSERT_EQ(states[1](C, 6).isEmpty(), true);
  ASSERT_EQ(states[1](E, 6).isEmpty(), true);
  ASSERT_EQ(states[1](F, 7).isEmpty(), false);
}

TEST(GameResultTest, methods) {
  ASSERT_EQ(GameResult::winner(WHITE), GameResult::winner(WHITE));
  ASSERT_EQ(GameResult::winner(BLACK), GameResult::winner(BLACK));
  ASSERT_EQ(GameResult::gameNotOver(), GameResult::gameNotOver());
  ASSERT_EQ(GameResult::threeFoldRepetition(),
            GameResult::threeFoldRepetition());
}
