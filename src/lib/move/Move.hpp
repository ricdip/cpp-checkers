#pragma once
#include "../piece/Piece.hpp"
#include <vector>

class Move {
private:
  uint8_t originFile, originRank;
  uint8_t destinationFile, destinationRank;
  std::vector<PieceLocation> captures;

public:
  Move(uint8_t, uint8_t, uint8_t, uint8_t);
  Move(std::string);
  uint8_t getOriginFile() const;
  uint8_t getOriginRank() const;
  uint8_t getDestinationFile() const;
  uint8_t getDestinationRank() const;

  std::vector<PieceLocation> getCaptures();
  void addCapture(PieceLocation);
  void addCaptures(std::vector<PieceLocation>);

  std::string repr() const;

  friend std::ostream &operator<<(std::ostream &, const Move &);
  bool operator==(const Move &) const;
  bool operator!=(const Move &) const;
};
