#include "../lib/game/Game.hpp"
#include "../lib/player/AI.hpp"
#include "../lib/player/Human.hpp"
#include <chrono>
#include <iostream>
#include <thread>

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

  std::cout << white << '\n';
  std::cout << black << '\n';
  std::cout << "start in 5 seconds..." << '\n';

  std::this_thread::sleep_for(std::chrono::milliseconds(5000));

  run(white, black);
}

void HumanvsAI(uint32_t maxDepthAI) {
  Human white(WHITE);
  AI black(BLACK, maxDepthAI);

  std::cout << white << '\n';
  std::cout << black << '\n';
  std::cout << "start in 5 seconds..." << '\n';

  std::this_thread::sleep_for(std::chrono::milliseconds(5000));

  run(white, black);
}

int main() {
  int32_t choice;
  std::cout << '\n';
  std::cout << "AIvsAI or HumanvsAI? [1,2]: ";
  std::cin >> choice;
  std::cout << '\n';

  if (choice == 1) {
    int32_t AI1MaxDepth;
    int32_t AI2MaxDepth;
    std::cout << "AI 1 (WHITE) max depth: ";
    std::cin >> AI1MaxDepth;
    std::cout << "AI 2 (BLACK) max depth: ";
    std::cin >> AI2MaxDepth;
    std::cout << '\n';
    AivsAI(AI1MaxDepth, AI2MaxDepth);

  } else if (choice == 2) {
    int32_t AIMaxDepth;
    std::cout << "AI (BLACK) max depth: ";
    std::cin >> AIMaxDepth;
    std::cout << '\n';
    HumanvsAI(AIMaxDepth);

  } else {
    throw std::runtime_error("Illegal choice");
  }

  return 0;
}
