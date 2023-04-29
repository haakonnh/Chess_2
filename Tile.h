#pragma once
#include "Piece.h"
#include "Color.h"
#include <iostream>

class Piece;

class Tile {
    public:
        Tile(int x, int y, Piece* piece = nullptr)
        : x(x), y(y), piece(piece) {};
        // get piece
        Piece* getPiece() { return piece; };
        // set piece
        void setPiece(Piece* piece) { this->piece = piece; };
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
        Piece* piece;
        int x;
        int y;
};