#include "include/Move.hpp"
#include "include/Game.hpp"
#include <algorithm>

Move::Move(uint8_t originFile,uint8_t originRank,uint8_t destinationFile,uint8_t destinationRank) : originFile(originFile), originRank(originRank), destinationFile(destinationFile), destinationRank(destinationRank), captures(std::vector<PieceLocation>()){}

Move::Move(std::string moveString) {
    const char *origFile = std::find(std::begin(FILES_REPRESENTATION), std::end(FILES_REPRESENTATION), moveString[0]);
    const char *origRank = std::find(std::begin(RANKS_REPRESENTATION), std::end(RANKS_REPRESENTATION), moveString[1]);
    const char *destFile = std::find(std::begin(FILES_REPRESENTATION), std::end(FILES_REPRESENTATION), moveString[2]);
    const char *destRank = std::find(std::begin(RANKS_REPRESENTATION), std::end(RANKS_REPRESENTATION), moveString[3]);

    if(moveString.size() != 4 || origFile == std::end(FILES_REPRESENTATION) || origRank == std::end(RANKS_REPRESENTATION) || destFile == std::end(FILES_REPRESENTATION) || destRank == std::end(RANKS_REPRESENTATION)) {
        std::string errString = "Illegal move string: (";
        errString += moveString;
        errString += ")";
        throw std::runtime_error(errString);
    }

    originFile = std::distance(FILES_REPRESENTATION, origFile) + 1;
    originRank = std::distance(RANKS_REPRESENTATION, origRank) + 1;
    destinationFile = std::distance(FILES_REPRESENTATION, destFile) + 1;
    destinationRank = std::distance(RANKS_REPRESENTATION, destRank) + 1;
    captures = std::vector<PieceLocation>();
}

uint8_t Move::getOriginFile() const{
    return originFile;
}

uint8_t Move::getOriginRank() const{
    return originRank;
}

uint8_t Move::getDestinationFile() const{
    return destinationFile;
}

uint8_t Move::getDestinationRank() const{
    return destinationRank;
}


std::vector<PieceLocation> Move::getCaptures() {
    return captures;
}

void Move::addCapture(PieceLocation pieceLocation) {
    captures.push_back(pieceLocation);
}

void Move::addCaptures(std::vector<PieceLocation> pieceLocations) {
    captures = pieceLocations;
}

std::string Move::repr() const {
    std::string moveString = {FILES_REPRESENTATION[getOriginFile() - 1], RANKS_REPRESENTATION[getOriginRank() - 1], FILES_REPRESENTATION[getDestinationFile() - 1], RANKS_REPRESENTATION[getDestinationRank() - 1]};

    return moveString;
}

std::ostream& operator<<(std::ostream& os, const Move& m){
    os << m.repr();
    return os;
}


bool Move::operator==(const Move& m) const {
    return (originFile == m.originFile) &&
    (originRank == m.originRank) &&
    (destinationFile == m.destinationFile) &&
    (destinationRank == m.destinationRank) &&
    (captures == m.captures);
}

bool Move::operator!=(const Move& m) const {
    return !(*this == m);
}
