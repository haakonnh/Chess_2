
#pragma once
#include "Tile.h"
#include <vector>
#include <memory>

class Piece;

class Tile;

class Board {
    public:
        Board();
        void createTile(int row, int col, std::unique_ptr<Piece> piece = nullptr);
        std::vector<std::vector<Tile>> getBoard() { return boardMatrix; };
        // get reference board
        std::vector<std::vector<Tile>>& getBoardRef() { return boardMatrix; };

    private:
        std::vector<std::vector<Tile>> boardMatrix;
};