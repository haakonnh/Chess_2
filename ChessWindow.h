#pragma once
#include "AnimationWindow.h"
#include "Board.h"
#include "Image.h"
#include <random>
#include <cstdlib>
class ChessWindow: public TDT4102::AnimationWindow {
    public:
        ChessWindow();
        void drawTiles();
        void drawPieces();
        void play();
        void handleClick();
        void clearIsPossibleMove();
        Tile getTile(int x, int y);
        int randomNumber(int lower, int higher);
        int getIsWhitesTurn() {return isWhitesTurn;};
        void setIsWhitesTurn(bool isWhitesTurn) {this -> isWhitesTurn = isWhitesTurn;};
    private:
        Board board;
        bool isWhitesTurn = true;
};
