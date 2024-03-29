#pragma once
#include "AnimationWindow.h"
#include "Board.h"
#include "Image.h"
#include <random>
#include <cstdlib>
#include "widgets/TextInput.h"

class ChessWindow: public TDT4102::AnimationWindow {
    public:
        ChessWindow();
        void drawTiles();
        void drawPieces();
        void play();
        void handleClick();
        void clearIsPossibleMove();
        Tile& getTile(int x, int y);
        int randomNumber(int lower, int higher);
        int getIsWhitesTurn() const {return isWhitesTurn;};
        void setIsWhitesTurn(bool isWhitesTurn) {this -> isWhitesTurn = isWhitesTurn;};
    private:
        Board board;
        bool isWhitesTurn = true;
        bool gameIsOver = false;
        int tileSize = 80;
        TDT4102::TextInput gameOver;
};
