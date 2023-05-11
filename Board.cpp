#include "Board.h"

void Board::createTile(int row, int col, std::unique_ptr<Piece> piece) {
    boardMatrix.at(row).at(col) = Tile(row, col, std::move(piece));
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
    createTile(0, 0, std::make_unique<Rook>(Rook(false)));
    createTile(0, 1, std::make_unique<Knight>(Knight(false)));
    createTile(0, 2, std::make_unique<Bishop>(Bishop(false)));
    createTile(0, 3, std::make_unique<Queen>(Queen(false)));
    createTile(0, 4, std::make_unique<King>(King(false)));
    createTile(0, 5, std::make_unique<Bishop>(Bishop(false)));
    createTile(0, 6, std::make_unique<Knight>(Knight(false)));
    createTile(0, 7, std::make_unique<Rook>(Rook(false)));

    // Black pawns.
    for (int i = 0; i < 8; i++) {
        createTile(1, i, std::make_unique<Pawn>(Pawn(false)));
    }

    // Empty spaces.
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            createTile(i, j);
        }
    }

    // White pawns.
    for (int i = 0; i < 8; i++) {
        createTile(6, i, std::make_unique<Pawn>(Pawn(true)));
    }

    // White pieces.
    createTile(7, 0, std::make_unique<Rook>(Rook(true)));
    createTile(7, 1, std::make_unique<Knight>(Knight(true)));
    createTile(7, 2, std::make_unique<Bishop>(Bishop(true)));
    createTile(7, 3, std::make_unique<Queen>(Queen(true)));
    createTile(7, 4, std::make_unique<King>(King(true)));
    createTile(7, 5, std::make_unique<Bishop>(Bishop(true)));
    createTile(7, 6, std::make_unique<Knight>(Knight(true)));
    createTile(7, 7, std::make_unique<Rook>(Rook(true)));
    
}