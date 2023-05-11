#pragma once
#include "Piece.h"
#include "Color.h"
#include <iostream>
#include <memory>

class Piece;

class Tile {
    public:
        Tile(int x, int y, std::unique_ptr<Piece> piece = nullptr)
        : x(x), y(y), piece(std::move(piece)) {};
        // Copy constructor
        Tile(const Tile& other);
        // Move constructor
        Tile& operator=(Tile&& other) noexcept;
        // get piece
        Piece* getPiece() { return piece.get();};

        // move piece
        std::unique_ptr<Piece> movePiece() { return std::move(piece); };
        // set piece
        void setPiece(std::unique_ptr<Piece> piece) { this -> piece = std::move(piece); };
        // set x and y
        void setX(int x) { this->x = x; };
        void setY(int y) { this->y = y; };
        // get x and y
        int getX() { return x; };
        int getY() { return y; };
        void setIsPossibleMove(bool isPossibleMove) { this->isPossibleMove = isPossibleMove; };
        bool getIsPossibleMove() { return isPossibleMove; };
    private:
        bool isPossibleMove = false;
        std::unique_ptr<Piece> piece;
        int x;
        int y;
};