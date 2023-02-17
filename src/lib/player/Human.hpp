#pragma once
#include "Player.hpp"

class Human : public Player {
public:
  Human(bool);
  Board getMove(const Board &);
};
