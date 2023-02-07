#include "include/Move.hpp"
#include "include/Game.hpp"
#include "include/Piece.hpp"
#include <algorithm>
#include <iterator>
#include <stdexcept>

Move::Move(uint8_t originFile,uint8_t originRank,uint8_t destinationFile,uint8_t destinationRank) : originFile(originFile), originRank(originRank), destinationFile(destinationFile), destinationRank(destinationRank), captures(std::vector<PieceLocation>()){}

Move::Move(std::string moveString) {
    const char *origFile = std::find(std::begin(FILES_REPRESENTATION), std::end(FILES_REPRESENTATION), moveString[0]);
    const char *origRank = std::find(std::begin(RANKS_REPRESENTATION), std::end(RANKS_REPRESENTATION), moveString[1]);
    const char *destFile = std::find(std::begin(FILES_REPRESENTATION), std::end(FILES_REPRESENTATION), moveString[2]);
    const char *destRank = std::find(std::begin(RANKS_REPRESENTATION), std::end(RANKS_REPRESENTATION), moveString[3]);

    if(moveString.size() != 4 || origFile == std::end(FILES_REPRESENTATION) || origRank == std::end(RANKS_REPRESENTATION) || destFile == std::end(FILES_REPRESENTATION) || destRank == std::end(RANKS_REPRESENTATION)) {
        throw std::runtime_error("Illegal move string");
    }

    originFile = std::distance(FILES_REPRESENTATION, origFile);
    originRank = std::distance(RANKS_REPRESENTATION, origRank);
    destinationFile = std::distance(FILES_REPRESENTATION, destFile);
    destinationRank = std::distance(RANKS_REPRESENTATION, destRank);
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

std::string Move::repr() const {
    std::string moveString = {FILES_REPRESENTATION[getOriginFile()], RANKS_REPRESENTATION[getOriginRank()], FILES_REPRESENTATION[getDestinationFile()], RANKS_REPRESENTATION[getDestinationRank()]};

    return moveString;
}

std::ostream& operator<<(std::ostream& os, const Move& m){
    os << m.repr();
    return os;
}
