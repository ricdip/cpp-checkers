#pragma once
#include "Piece.hpp"
#include <memory>

class Tile {
    private:
        // shared pointer: type of smart pointer that is designed for scenarios in which more that one owner might have to manage the lifetime of the object in memory
        std::shared_ptr<Piece> occupant;
    public:
        // constructors
        Tile();
        Tile(Piece*);
        // copy constructor: member function that initializes an object using another object of the same class
        Tile(const Tile&);
        // destructor
        ~Tile();
        // getters
        Piece& getPiece() const;
        bool isEmpty() const;
        // representation
        char repr() const;
        // operator << overload
        friend std::ostream& operator<<(std::ostream&, const Tile&);
        // operator = overload
        Tile& operator=(Piece*);
};
