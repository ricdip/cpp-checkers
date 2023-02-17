#include "GameResult.hpp"

// TODO: test
GameResult::GameResult()
    : gameOn(false), winnerPlayer(false), threeFoldRepetitionDraw(false) {}

GameResult GameResult::winner(bool winner) {
  GameResult gameResult = GameResult();
  gameResult.winnerPlayer = winner;
  return gameResult;
}

GameResult GameResult::threeFoldRepetition() {
  GameResult gameResult = GameResult();
  gameResult.threeFoldRepetitionDraw = true;
  return gameResult;
}

GameResult GameResult::gameNotOver() {
  GameResult gameResult = GameResult();
  gameResult.gameOn = true;
  return gameResult;
}

std::string GameResult::repr() const {
  if (gameOn) {
    return "Game not over yet";
  } else if (threeFoldRepetitionDraw) {
    return "Winner: None, draw caused by threefold repetition";
  }

  if (winnerPlayer) {
    return "Winner: WHITE";
  } else {
    return "Winner: BLACK";
  }
}

bool GameResult::operator==(const GameResult &gameResult) const {
  return gameOn == gameResult.gameOn &&
         winnerPlayer == gameResult.winnerPlayer &&
         threeFoldRepetitionDraw == gameResult.threeFoldRepetitionDraw;
}

bool GameResult::operator!=(const GameResult &gameResult) const {
  return !(*this == gameResult);
}

std::ostream &operator<<(std::ostream &os, const GameResult &gameResult) {
  os << gameResult.repr();
  return os;
}
