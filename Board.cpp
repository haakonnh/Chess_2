#include "Board.h"

void Board::createTile(int row, int col, Piece* piece) {
    boardMatrix.at(row).at(col) = Tile(row, col, piece);
}

// Initializes the board to the starting chess position.
Board::Board() {
    // create boardmatrix
    for (int i = 0; i < 8; i++) {
        std::vector<Tile> row;
        for (int j = 0; j < 8; j++) {
            row.push_back(Tile(i, j));
        }
        boardMatrix.push_back(row);
    }
    // Fill boardmatrix with standard chess starting pieces

    // Black pieces
    createTile(0, 0, new Rook(false));
    createTile(0, 1, new Knight(false));
    createTile(0, 2, new Bishop(false));
    createTile(0, 3, new Queen(false));
    createTile(0, 4, new King(false));
    createTile(0, 5, new Bishop(false));
    createTile(0, 6, new Knight(false));
    createTile(0, 7, new Rook(false));

    // Black pawns.
    for (int i = 0; i < 8; i++) {
        createTile(1, i, new Pawn(false));
    }

    // Empty spaces.
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            createTile(i, j);
        }
    }

    // White pawns.
    for (int i = 0; i < 8; i++) {
        createTile(6, i, new Pawn(true));
    }

    // White pieces.
    createTile(7, 0, new Rook(true));
    createTile(7, 1, new Knight(true));
    createTile(7, 2, new Bishop(true));
    createTile(7, 3, new Queen(true));
    createTile(7, 4, new King(true));
    createTile(7, 5, new Bishop(true));
    createTile(7, 6, new Knight(true));
    createTile(7, 7, new Rook(true));
    
}