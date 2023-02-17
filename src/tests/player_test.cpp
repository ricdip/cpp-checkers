// clang-format off
#include <gtest/gtest.h>
// clang-format on
#include "../lib/game/Game.hpp"
#include "../lib/player/AI.hpp"
#include "../lib/player/Human.hpp"

TEST(PlayerTest, AIPlayer) {
  AI p(WHITE, 3);

  ASSERT_EQ(p.getColor(), WHITE);
  ASSERT_EQ(p.repr(), "AI(color: WHITE, maxDepth: 3)");
}

TEST(PlayerTest, HumanPlayer) {
  Human p(WHITE);

  ASSERT_EQ(p.getColor(), WHITE);
  ASSERT_EQ(p.repr(), "Human(color: WHITE)");
}
