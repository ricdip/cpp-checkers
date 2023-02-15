// clang-format off
#include <gtest/gtest.h>
// clang-format on
#include "../lib/ai/algorithm/Algorithm.hpp"
#include "../lib/ai/heuristic/Heuristic.hpp"
#include "../lib/game/Game.hpp"

TEST(AITest, heuristics) {
  Board board1 = Board(true);
  board1(A, 2) = new Pawn(WHITE);
  board1(C, 5) = new Queen(WHITE);
  board1(D, 6) = new Pawn(BLACK);

  ASSERT_EQ(Heuristic::gameOverH(board1), 0);
  ASSERT_EQ(Heuristic::boardPieceValuesH(board1), 100);
  ASSERT_EQ(Heuristic::Htot(board1), 100);

  board1.makeMove(Move("C5E7"));

  ASSERT_EQ(Heuristic::gameOverH(board1), INT32_MAX);
  ASSERT_EQ(Heuristic::boardPieceValuesH(board1), 110);
  ASSERT_EQ(Heuristic::Htot(board1), INT32_MAX);

  Board board2 = Board(BLACK, true);
  board2(A, 2) = new Pawn(BLACK);
  board2(C, 5) = new Queen(BLACK);
  board2(D, 6) = new Pawn(WHITE);

  ASSERT_EQ(Heuristic::gameOverH(board2), 0);
  ASSERT_EQ(Heuristic::boardPieceValuesH(board2), -100);
  ASSERT_EQ(Heuristic::Htot(board2), -100);

  board2.makeMove(Move("C5E7"));

  ASSERT_EQ(Heuristic::gameOverH(board2), INT32_MIN);
  ASSERT_EQ(Heuristic::boardPieceValuesH(board2), -110);
  ASSERT_EQ(Heuristic::Htot(board2), INT32_MIN);
}

TEST(AITest, algorithm) {
  Board initState = Board(true);
  initState(A, 2) = new Pawn(WHITE);
  initState(C, 5) = new Queen(WHITE);
  initState(D, 6) = new Pawn(BLACK);
  initState(G, 4) = new Pawn(WHITE);
  initState(F, 5) = new Pawn(BLACK);

  uint32_t maxDepth = 5;
  Algorithm ai = Algorithm(maxDepth);
  Board stateMove1 = ai.minmaxAlphaBeta(initState, initState.getTurn());

  ASSERT_EQ(stateMove1(A, 2).isEmpty(), false);
  ASSERT_EQ(stateMove1(C, 5).isEmpty(), true);
  ASSERT_EQ(stateMove1(D, 6).isEmpty(), true);
  ASSERT_EQ(stateMove1(E, 7).isEmpty(), false);
  ASSERT_EQ(stateMove1(G, 4).isEmpty(), false);
  ASSERT_EQ(stateMove1(F, 5).isEmpty(), false);

  Board stateMove2 = ai.minmaxAlphaBeta(stateMove1, stateMove1.getTurn());

  ASSERT_EQ(stateMove2(A, 2).isEmpty(), false);
  ASSERT_EQ(stateMove2(E, 7).isEmpty(), false);
  ASSERT_EQ(stateMove2(G, 4).isEmpty(), true);
  ASSERT_EQ(stateMove2(F, 5).isEmpty(), true);
  ASSERT_EQ(stateMove2(H, 3).isEmpty(), false);
}
