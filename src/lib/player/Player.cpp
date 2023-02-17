#include "Player.hpp"

Player::Player(bool color) : color(color) {}

bool Player::getColor() const { return color; }

std::ostream &operator<<(std::ostream &os, const Player &player) {
  os << player.repr();
  return os;
}
