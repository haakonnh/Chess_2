#include "ChessWindow.h"
#include <iostream>

// Constructor for ChessWindow.
ChessWindow::ChessWindow(): AnimationWindow{400, 50, 800, 800, "Chess 2"}, gameOver{{300, 350}, 200, 100} {
    board = Board();
}

// Plays the game.
void ChessWindow::play() {
    // Main loop.
    static bool lastLeftClickState = false;
    static bool lastRightClickState = false;
    
    while (!should_close()) {
        // Handle inputs.
        wait_for(0.04);
       
        handleClick();
        

        
        
        // Draw things.
        drawTiles();
        drawPieces();
        
        // Next frame, reloop.
        
        next_frame();
    }
}


void ChessWindow::drawTiles() {

    // clear board

    
    bool isEven = false;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {

                // Draws a green square if the tile is a possible move.
                if (board.getBoardRef().at(i).at(j).getIsPossibleMove()) {
                    draw_rectangle({j*100, i*100}, 100, 100, TDT4102::Color::light_green);
                }
                
                // Draws a square with alternating colors.
                else if (isEven) {  
                    draw_rectangle({j*100, i*100}, 100, 100, TDT4102::Color::dark_khaki);
                }
                else if (!isEven) {
                    draw_rectangle({j*100, i*100}, 100, 100, TDT4102::Color::mint_cream);
                }
                isEven = !isEven;
            }
            isEven = !isEven;
        }
}

// Draws pieces on board.
void ChessWindow::drawPieces() {
    std::vector<TDT4102::Image> renderedImages;

    for (auto& row: board.getBoardRef()) {
        for (Tile& tile: row) {
            if (tile.getPiece() != nullptr) {
                // place image at current square
                TDT4102::Image image = TDT4102::Image("img/" + tile.getPiece()->getImage());
                renderedImages.push_back(image);
                draw_image({tile.getY()*100, tile.getX()*100}, image, 100, 100);

            }
        }
    }

    renderedImages.clear();
}

// Handles clicks every frame.
void ChessWindow::handleClick() {
    static bool lastLeftClickState = false;
    static bool lastRightClickState = false;

    bool currentLeftClickState = is_left_mouse_button_down();
    bool currentRightClickState = is_right_mouse_button_down();
    //if (!(currentRightClickState && !lastRightClickState) && !(currentLeftClickState && !lastLeftClickState)) return;
    if (currentRightClickState && !lastRightClickState) {
        // Convert coords to row and col
        TDT4102::Point mouseCoords = get_mouse_coordinates();
        // Get tile
        Tile& clickedTile = getTile(mouseCoords.x, mouseCoords.y);
        // If clicked tile has no piece, return
        if (clickedTile.getPiece() == nullptr) {
            //std::cout << "nullptr" << std::endl;
            return;
        }
        // If it aint your turn, you cant check possible moves
        if (clickedTile.getPiece() -> getIsWhite() != isWhitesTurn) return;

        // If clicked tile has a piece, calculate possible moves
        clickedTile.getPiece() -> calculatePossibleMoves(board, clickedTile);
        std::vector<std::shared_ptr<Tile>>& possibleMoves = clickedTile.getPiece() -> possibleMoves;
        for (std::shared_ptr<Tile>& tile: possibleMoves) {
            //std::cout << tile -> getY() << ", " << tile -> getX() << std::endl;
        }

        // Set isPossibleMove to true for all possible moves
        for (std::shared_ptr<Tile>& tile: possibleMoves) {
            //std::cout << "Color set" << std::endl;
            int x = tile -> getX();
            int y = tile -> getY();
            board.getBoardRef().at(x).at(y).setIsPossibleMove(true);
        }

        // Set isPossibleMove to false if the tile is not in possibleMoves, needs ref here
        for (auto& row: board.getBoardRef()) {
            // needs ref here, because we want to change the isPossibleMove value
            for (Tile& tile: row) {
                if (tile.getIsPossibleMove()) {
                    bool isInPossibleMoves = false;
                    for (std::shared_ptr<Tile> possibleMove: possibleMoves) {
                        if (tile.getX() == possibleMove -> getX() && tile.getY() == possibleMove -> getY()) {
                            isInPossibleMoves = true;
                        }
                    }
                    if (!isInPossibleMoves) {
                        tile.setIsPossibleMove(false);
                    }
                }
            }
        }
    }

    // If left mouse button is clicked, move piece randomly to a possible move
    if (currentLeftClickState && !lastLeftClickState) {
        int x = get_mouse_coordinates().x;
        int y = get_mouse_coordinates().y;
        Tile& clickedTile = getTile(x, y);
        // That aint a piece
        if (clickedTile.getPiece() == nullptr) {
            //std::cout << "nullptr" << std::endl;
            return;
        }
        // It aint your turn man
        if (clickedTile.getPiece() -> getIsWhite() != isWhitesTurn) return;
        // Clear coloring for possible moves.
        clearIsPossibleMove();

        // Calculate possible moves, so that random move is chosen cororectly. 
        clickedTile.getPiece() -> calculatePossibleMoves(board, clickedTile);
        std::vector<std::shared_ptr<Tile>>& possibleMoves = clickedTile.getPiece() -> possibleMoves;
        if (possibleMoves.size() == 0) return;
        // Create random number
        int generatedNumber = randomNumber(0, possibleMoves.size() - 1);
        // Generate random move
        auto randomTile = (possibleMoves.at(generatedNumber)).get();

        // Move piece to random square.
        std::unique_ptr<Piece> selectedPiece = clickedTile.movePiece();
        auto& boardRef = board.getBoardRef();
        Tile& randomMove = boardRef.at(randomTile -> getX()).at(randomTile -> getY());
        boardRef.at(y / 100).at(x / 100).setPiece(nullptr);

        // This is game over.
        if (randomMove.getPiece() != nullptr && randomMove.getPiece() -> getPieceType() == PieceType::King) {
            gameIsOver = true;
            if (randomMove.getPiece() -> getIsWhite()) {
                gameOver.setText("Black wins!");
            }
            else if (!(randomMove.getPiece() -> getIsWhite())) {
                gameOver.setText("White wins!");
            }
            add(gameOver);
        }

        // If the piece being moved is either a rook or king, we want to signify that the piece has moved, such that
        // castling can be handled properly.<
        if (selectedPiece -> getPieceType() == PieceType::Rook || selectedPiece -> getPieceType() == PieceType::King) {
            selectedPiece -> setHasMoved(true);
        }

        // Logic for queening.
        if (selectedPiece -> getPieceType() == PieceType::Pawn && (randomMove.getX() == 0 || randomMove.getX() == 7 )) {
            bool color = selectedPiece -> getIsWhite();
            randomMove.setPiece(std::make_unique<Queen>(Queen(color)));
            //std::cout << "Queen" << std::endl;
        }
       
        
        // Castle!
        else if (selectedPiece -> getPieceType() == PieceType::King && abs(randomMove.getY() - clickedTile.getY()) > 1) {
            //std::cout << abs(randomMove.getY() - clickedTile.getY()) << " abs." <<std::endl;
            if (abs(randomMove.getY() - clickedTile.getY()) > 1) {
                if (clickedTile.getY() > randomMove.getY()) { // castle queenside - left.
                    std::unique_ptr<Piece> castleRook = boardRef.at(y / 100).at((x / 100) - 4).movePiece();
                    boardRef.at(y / 100).at((x / 100) - 4).setPiece(nullptr);
                    randomMove.setPiece(std::move(selectedPiece));
                    boardRef.at(clickedTile.getX()).at(clickedTile.getY() - 1).setPiece(std::move(castleRook));    
                }
                else { // castle kingside - right
                    std::unique_ptr<Piece> castleRook = boardRef.at(y / 100).at((x / 100) + 3).movePiece();
                    boardRef.at(y / 100).at((x / 100) + 3).setPiece(nullptr);
                    randomMove.setPiece(std::move(selectedPiece));
                    boardRef.at(clickedTile.getX()).at(clickedTile.getY()).setPiece(nullptr);
                    boardRef.at(clickedTile.getX()).at(clickedTile.getY() + 1).setPiece(std::move(castleRook));

                }
            }
        }
        else randomMove.setPiece(std::move(selectedPiece));
        //std::cout << "Move to: " << randomMove.getY() << ", " << randomMove.getX() << std::endl;
        // std::cout << pieceTypeMap.at(selectedPiece -> getPieceType() ) << " moved." << std::endl;
        isWhitesTurn = !isWhitesTurn;
    }

    // Set last state to current state.
    lastLeftClickState = currentLeftClickState;
    lastRightClickState = currentRightClickState;


}

// Clear all possible moves.
void ChessWindow::clearIsPossibleMove() {
    for (auto& row: board.getBoardRef()) {
        for (Tile& tile: row) {
            tile.setIsPossibleMove(false);
        }
    }
}

// Return clicked tile5
Tile& ChessWindow::getTile(int x, int y) {
    return board.getBoardRef().at(y / 100).at(x / 100);
}

// Return random number in specific range
int ChessWindow::randomNumber(int lower, int higher) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(lower, higher);
    return dis(gen);
}