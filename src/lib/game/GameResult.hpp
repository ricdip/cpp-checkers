#pragma once
#include <sstream>

class GameResult {
private:
  bool gameOn;
  bool winnerPlayer;
  bool threeFoldRepetitionDraw;
  GameResult();

public:
  static GameResult winner(bool);
  static GameResult threeFoldRepetition();
  static GameResult gameNotOver();
  std::string repr() const;
  bool operator==(const GameResult &) const;
  bool operator!=(const GameResult &) const;
  friend std::ostream &operator<<(std::ostream &, const GameResult &);
};
