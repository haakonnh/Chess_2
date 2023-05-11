#include "Tile.h"

// Copy constructor
Tile::Tile(const Tile& other)
    : x(other.x), y(other.y), isPossibleMove(other.isPossibleMove)
{
    if (other.piece) {
        if (dynamic_cast<Knight*>(other.piece.get())) {
            piece = std::make_unique<Knight>(*dynamic_cast<Knight*>(other.piece.get()));
        } else if (dynamic_cast<Pawn*>(other.piece.get())) {
            piece = std::make_unique<Pawn>(*dynamic_cast<Pawn*>(other.piece.get()));
        } else if (dynamic_cast<Rook*>(other.piece.get())) {
            piece = std::make_unique<Rook>(*dynamic_cast<Rook*>(other.piece.get()));
        } else if (dynamic_cast<Bishop*>(other.piece.get())) {
            piece = std::make_unique<Bishop>(*dynamic_cast<Bishop*>(other.piece.get()));
        } else if (dynamic_cast<Queen*>(other.piece.get())) {
            piece = std::make_unique<Queen>(*dynamic_cast<Queen*>(other.piece.get()));
        } else if (dynamic_cast<King*>(other.piece.get())) {
            piece = std::make_unique<King>(*dynamic_cast<King*>(other.piece.get()));
        } 
    }
}


// Move constructor
Tile& Tile::operator=(Tile&& other) noexcept {
        if (this != &other) {
            x = other.x;
            y = other.y;
            piece = std::move(other.piece);
        }
        return *this;
}