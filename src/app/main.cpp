#include "../lib/ai/algorithm/Algorithm.hpp"
#include "../lib/game/Game.hpp"
#include "../lib/player/AI.hpp"
#include "../lib/player/Human.hpp"
#include <cstdint>
#include <iostream>

void run(Player &p1, Player &p2) {
  Player *players[2] = {&p1, &p2};
  Board state;

  std::cout << state << std::endl;

  while (!state.isGameOver()) {
    state = players[!state.getTurn()]->getMove(state);
    std::cout << state << std::endl;
  }

  std::cout << state.getGameResult() << std::endl;
}

void AivsAI(uint32_t maxDepthAI1, uint32_t maxDepthAI2) {
  AI white(WHITE, maxDepthAI1);
  AI black(BLACK, maxDepthAI2);

  run(white, black);
}

void HumanvsAI(uint32_t maxDepthAI) {
  Human white(WHITE);
  AI black(BLACK, maxDepthAI);

  run(white, black);
}

int main() {
  AivsAI(6, 3);
  // HumanvsAI(3);

  return 0;
}
