#include "Piece.h"

// These functions require the board matrix to see where pieces are located.
// The purpose of this is to calculate all possible moves, and then when a piece
// is held up, the possible moves will be highlighted. 

void Piece::addMove(int row, int col, Board& board) {
    auto& boardRef = board.getBoardRef();
    possibleMoves.push_back(std::make_shared<Tile>(boardRef.at(row).at(col)));
    
}
void Pawn::calculatePossibleMoves(Board& board, Tile& currentTile) {
    // Reset possibleMoves vector and retrieve row and col from mouse position. 
    possibleMoves = {};
    int row = currentTile.getX();
    int col = currentTile.getY();

    // This prints out the coordinates of pressed pawn. 
    std::cout << "Pawn at: " << col << ", " << row << std::endl;

    if (!isWhite) {
        if (row != 7) { // black pawn is not last rank.
            if (board.getBoardRef().at(row + 1).at(col).getPiece() == nullptr) {
                addMove(row + 1, col, board);
            }

            // Captures.
            if (col + 1 < 8) {
                Piece* upRightPiece = board.getBoardRef().at(row + 1).at(col + 1).getPiece();
                if (upRightPiece != nullptr && upRightPiece->getIsWhite() != isWhite) {
                    addMove(row + 1, col + 1, board);
                }
            }
            if (col - 1 >= 0) {
                Piece* upLeftPiece = board.getBoardRef().at(row + 1).at(col - 1).getPiece();
                if (upLeftPiece != nullptr && upLeftPiece -> getIsWhite() != isWhite) {
                    addMove(row + 1, col - 1, board);
                }
            }
            
        }
        if (row == 1) { // black pawn is on second rank
            if (board.getBoardRef().at(row + 2).at(col).getPiece() == nullptr &&
            board.getBoardRef().at(row + 1).at(col).getPiece() == nullptr) {
                addMove(row + 2, col, board);
            }
        }

        
    }
    else {
        if (row != 0) { // white pawn is not on second rank and not on last rank.
            if (board.getBoardRef().at(row - 1).at(col).getPiece() == nullptr) {
                addMove(row - 1, col, board);
            }
            // Captures.
            if (col + 1 < 8) {
                Piece* downRightPiece = board.getBoardRef().at(row - 1).at(col + 1).getPiece();
                if (downRightPiece != nullptr && downRightPiece->getIsWhite() != isWhite) {
                    addMove(row - 1, col + 1, board);
                }
            }
            if (col - 1 >= 0) {
                Piece* downLeftPiece = board.getBoardRef().at(row - 1).at(col - 1).getPiece();
                if (downLeftPiece != nullptr && downLeftPiece -> getIsWhite() != isWhite) {
                    addMove(row - 1, col - 1, board);
                }
            }
        }
        if (row == 6) { // white pawn is on second rank.
            if (board.getBoardRef().at(row - 2).at(col).getPiece() == nullptr 
            && board.getBoardRef().at(row - 1).at(col).getPiece() == nullptr) {
                addMove(row - 2, col, board);
            }
        }
    }
}

void Knight::calculatePossibleMoves(Board& board, Tile& currentTile) {
    // Reset possibleMoves vector and retrieve row and col from mouse position. 
    possibleMoves = {};
    int row = currentTile.getX();
    int col = currentTile.getY();

    std::cout << "Knight at: " << row << ", " <<  col << std::endl;

    auto& boardRef = board.getBoardRef();
    if ((row + 2 < 8) && (col - 1 >= 0) && (boardRef.at(row + 2).at(col - 1).getPiece() == nullptr
    || boardRef.at(row + 2).at(col - 1).getPiece() -> getIsWhite() != isWhite)) {
        possibleMoves.push_back(std::make_shared<Tile>(boardRef.at(row + 2).at(col - 1)));
    }
    if ((row + 1 < 8) && (col - 2 >= 0) && (boardRef.at(row + 1).at(col - 2).getPiece() == nullptr
    || boardRef.at(row + 1).at(col - 2).getPiece() -> getIsWhite() != isWhite)) {
        possibleMoves.push_back(std::make_shared<Tile>(boardRef.at(row + 1).at(col - 2)));
    }
    if ((row + 1 < 8) && (col + 2 < 8) && (boardRef.at(row + 1).at(col + 2).getPiece() == nullptr
    || boardRef.at(row + 1).at(col + 2).getPiece() -> getIsWhite() != isWhite)) {
        possibleMoves.push_back(std::make_shared<Tile>(boardRef.at(row + 1).at(col + 2)));
    }
    if ((row + 2 < 8) && (col + 1 < 8) && (boardRef.at(row + 2).at(col + 1).getPiece() == nullptr
    || boardRef.at(row + 2).at(col + 1).getPiece() -> getIsWhite() != isWhite)) {
        possibleMoves.push_back(std::make_shared<Tile>(boardRef.at(row + 2).at(col + 1)));
    }
    if ((row - 1 >= 0) && (col - 2 >= 0) && (boardRef.at(row - 1).at(col - 2).getPiece() == nullptr
    || boardRef.at(row - 1).at(col - 2).getPiece() -> getIsWhite() != getIsWhite())) {
        possibleMoves.push_back(std::make_shared<Tile>(boardRef.at(row - 1).at(col - 2)));
    }
    if ((row - 2 >= 0) && (col - 1 >= 0) && (boardRef.at(row - 2).at(col - 1).getPiece() == nullptr
    || boardRef.at(row - 2).at(col - 1).getPiece() -> getIsWhite() != isWhite)) {
        possibleMoves.push_back(std::make_shared<Tile>(boardRef.at(row - 2).at(col - 1)));
    }
    if ((row - 2 >= 0) && (col + 1 < 8) && (boardRef.at(row - 2).at(col + 1).getPiece() == nullptr
    || boardRef.at(row - 2).at(col + 1).getPiece() -> getIsWhite() != isWhite)) {
        possibleMoves.push_back(std::make_shared<Tile>(boardRef.at(row - 2).at(col + 1)));
    }
    if ((row + 1 < 8) && (col + 2 < 8) && (boardRef.at(row + 1).at(col + 2).getPiece() == nullptr
    || boardRef.at(row + 1).at(col + 2).getPiece() -> getIsWhite() != isWhite)) {
        possibleMoves.push_back(std::make_shared<Tile>(boardRef.at(row + 1).at(col + 2)));
    }

    
}



void Rook::calculatePossibleMoves(Board& board, Tile& currentTile) {
    // Reset possibleMoves vector and retrieve row and col from mouse position. 
    possibleMoves = {};
    int row = currentTile.getX();
    int col = currentTile.getY();

    std::cout << "Rook at:" << row << ", " <<  col << std::endl;

    // add straight moves to possible moves
    addStraightMoves(row, col, board);
}

void Bishop::calculatePossibleMoves(Board& board, Tile& currentTile) {
    // Reset possibleMoves vector and retrieve row and col from mouse position. 
    possibleMoves = {};
    int row = currentTile.getX();
    int col = currentTile.getY();

    // add diagonal moves to possible moves
    addDiagonalMoves(row, col, board);
}

void Queen::calculatePossibleMoves(Board& board, Tile& currentTile) {
    // Reset possibleMoves vector and retrieve row and col from mouse position. 
    possibleMoves = {};
    int row = currentTile.getX();
    int col = currentTile.getY();

    addDiagonalMoves(row, col, board);
    addStraightMoves(row, col, board);
}

void King::calculatePossibleMoves(Board& board, Tile& currentTile) {
    // Reset possibleMoves vector and retrieve row and col from mouse position. 
    possibleMoves = {};
    int row = currentTile.getX();
    int col = currentTile.getY();
    // Probably need check logic around here
    auto& boardRef = board.getBoardRef();
    // Looping through all possible king moves.
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (row + dx >= 0 && row + dx < 8 && col + dy >= 0 && col + dy < 8) {
                if (!(dx == 0 && dy == 0)) {
                    int x = row + dx;
                    int y = col + dy;
                    // If suggested square is either empty or occupied by enemy piece, it is a possible move.
                    if (boardRef.at(x).at(y).getPiece() == nullptr || 
                    boardRef.at(x).at(y).getPiece() -> getIsWhite() != isWhite) {
                        possibleMoves.push_back(std::make_shared<Tile>(boardRef.at(x).at(y)));
                    }
                }
            }
        }
    }
    // Castling
    if (!getHasMoved()) { 
        auto& boardRef = board.getBoardRef();

        // Kingside
        if ((boardRef.at(row).at(col + 1).getPiece() == nullptr) && (boardRef.at(row).at(col + 2).getPiece() == nullptr)) {
            if (boardRef.at(row).at(col + 3).getPiece() != nullptr && !boardRef.at(row).at(col + 3).getPiece()->getHasMoved()) {
                possibleMoves.push_back(std::make_shared<Tile>(boardRef.at(row).at(col + 2)));
            }
        }

        // Queenside
        else if ((boardRef.at(row).at(col - 1).getPiece() == nullptr) && (boardRef.at(row).at(col - 2).getPiece() == nullptr)
        && (boardRef.at(row).at(col - 3).getPiece() == nullptr)) {
            if (boardRef.at(row).at(col - 4).getPiece() != nullptr && !boardRef.at(row).at(col - 4).getPiece()->getHasMoved()) {
                possibleMoves.push_back(std::make_shared<Tile>(boardRef.at(row).at(col - 2)));
            }
        }
    }

}



void Piece::addStraightMoves(int row, int col, Board& board) {
    auto& boardRef = board.getBoardRef();
    for (int i = row + 1; i < 8; i++) { // checking moves in the downwards direction
        Piece* piece = boardRef.at(i).at(col).getPiece();
        if (piece == nullptr) {
            possibleMoves.push_back(std::make_shared<Tile>(boardRef.at(i).at(col)));
        }
        // Break if the piece meets a piece of same color.
        else if (piece != nullptr && piece -> getIsWhite() == isWhite) break;
        // Add move and break if piece meets capturable piece.
        else {
            possibleMoves.push_back(std::make_shared<Tile>(boardRef.at(i).at(col)));
            break;
        }

    }

    for (int i = row - 1; i >= 0; i--) { // checking moves in upwards direction
        Piece* piece = boardRef.at(i).at(col).getPiece();
        if (piece == nullptr) {
            possibleMoves.push_back(std::make_shared<Tile>(boardRef.at(i).at(col)));
        }
        // Break if the piece meets a piece of same color.
        else if (piece != nullptr && piece -> getIsWhite() == isWhite) break;
        // Add move and break if piece meets capturable piece.
        else {
            possibleMoves.push_back(std::make_shared<Tile>(boardRef.at(i).at(col)));
            break;
        }
    }

    for (int i = col - 1; i >= 0; i--) { // checking moves in left direction
        Piece* piece = boardRef.at(row).at(i).getPiece();
        if (piece == nullptr) {
            possibleMoves.push_back(std::make_shared<Tile>(boardRef.at(row).at(i)));
        }
        // Break if the piece meets a piece of same color.
        else if (piece != nullptr && piece -> getIsWhite() == isWhite) break;
        // Add move and break if piece meets capturable piece.
        else {
            possibleMoves.push_back(std::make_shared<Tile>(boardRef.at(row).at(i)));
            break;
        }
    }

    for (int i = col + 1; i < 8; i++) { // checking moves in right direction
        Piece* piece = boardRef.at(row).at(i).getPiece();
        if (piece == nullptr) {
            possibleMoves.push_back(std::make_shared<Tile>(boardRef.at(row).at(i)));
        }
        // Break if the piece meets a piece of same color.
        else if (piece != nullptr && piece -> getIsWhite() == isWhite) break;
        // Add move and break if piece meets capturable piece.
        else {
            possibleMoves.push_back(std::make_shared<Tile>(boardRef.at(row).at(i)));
            break;
        }
    }
}

void Piece::addDiagonalMoves(int row, int col, Board& board) {
    auto& boardRef = board.getBoardRef();

    for (int i = row + 1, j = col + 1; i < 8 && j < 8; i++, j++) { // diagonal down right
        Piece* piece = boardRef.at(i).at(j).getPiece();
        if (piece == nullptr) {
            possibleMoves.push_back(std::make_shared<Tile>(boardRef.at(i).at(j)));
        }
        // Break if the piece meets a piece of same color.
        else if (piece != nullptr && piece -> getIsWhite() == isWhite) break;
        // Add move and break if piece meets capturable piece.
        else {
            possibleMoves.push_back(std::make_shared<Tile>(boardRef.at(i).at(j)));
            break;
        }
    }
    for (int i = row + 1, j = col - 1; i < 8 && j >= 0; i++, j--) { // diagonal down left
        Piece* piece = boardRef.at(i).at(j).getPiece();
        if (piece == nullptr) {
            possibleMoves.push_back(std::make_shared<Tile>(boardRef.at(i).at(j)));
        }
        // Break if the piece meets a piece of same color.
        else if (piece != nullptr && piece -> getIsWhite() == isWhite) break;
        // Add move and break if piece meets capturable piece.
        else {
            possibleMoves.push_back(std::make_shared<Tile>(boardRef.at(i).at(j)));
            break;
        }
    }
    for (int i = row - 1, j = col + 1; i >= 0 && j < 8; i--, j++) { // diagonal up right
        Piece* piece = boardRef.at(i).at(j).getPiece();
        if (piece == nullptr) {
            possibleMoves.push_back(std::make_shared<Tile>(boardRef.at(i).at(j)));
        }
        // Break if the piece meets a piece of same color.
        else if (piece != nullptr && piece -> getIsWhite() == isWhite) break;
        // Add move and break if piece meets capturable piece.
        else {
            possibleMoves.push_back(std::make_shared<Tile>(boardRef.at(i).at(j)));
            break;
        }
    }
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) { // diagonal up left
        Piece* piece = boardRef.at(i).at(j).getPiece();
        if (piece == nullptr) {
            possibleMoves.push_back(std::make_shared<Tile>(boardRef.at(i).at(j)));
        }
        // Break if the piece meets a piece of same color.
        else if (piece != nullptr && piece -> getIsWhite() == isWhite) break;
        // Add move and break if piece meets capturable piece.
        else {
            possibleMoves.push_back(std::make_shared<Tile>(boardRef.at(i).at(j)));
            break;
        }
    }
}

