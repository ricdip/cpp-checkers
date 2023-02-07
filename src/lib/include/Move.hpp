#pragma once
#include <cstdint>
#include <string>

class Move {
    private:
        uint8_t originFile, originRank;
        uint8_t destinationFile, destinationRank;
    public:
        Move(uint8_t,uint8_t,uint8_t,uint8_t);
        Move(std::string);
        uint8_t getOriginFile() const;
        uint8_t getOriginRank() const;
        uint8_t getDestinationFile() const;
        uint8_t getDestinationRank() const;

        std::string repr() const;

        friend std::ostream& operator<<(std::ostream&, const Move&);
};
