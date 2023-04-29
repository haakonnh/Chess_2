#pragma once
#include "Board.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <map>


class Tile;

class Board;

enum class PieceType {Pawn, Knight, Bishop, Rook, Queen, King, NONE};

const std::map<PieceType, std::string> pieceTypeMap {
    {PieceType::Pawn, "Pawn"},
    {PieceType::Knight, "Knight"},
    {PieceType::Bishop, "Bishop"},
    {PieceType::Rook, "Rook"},
    {PieceType::Queen, "Queen"},
    {PieceType::King, "King"}
};

class Piece {
    public:
        Piece(bool isWhite): isWhite(isWhite) {};
        bool getIsWhite() { return isWhite; };
        bool canMove() { return (possibleMoves.empty()) ? false : true; };
        bool getIsDead() { return isDead; };
        void setIsDead(bool isDead) { this->isDead = isDead; };

        // Does maybe not have to be public, idk because of inheritance. 
        std::vector<std::shared_ptr<Tile>> possibleMoves;

        // Adds diagonal moves to the possibleMoves vector if legal.
        void addDiagonalMoves(int row, int col, Board);

        // Adds straight moves to the possibleMoves vector if legal.
        void addStraightMoves(int row, int col, Board board);

        // Adds a move to the possibleMoves vector.
        void addMove(int row, int col, Board board);
        
        void setPieceType(PieceType pieceType) {this -> pieceType = pieceType;};
        PieceType getPieceType() {return pieceType;};
        void setHasMoved(bool hasMoved) {this -> hasMoved = hasMoved;};
        bool getHasMoved() {return hasMoved;};

        // Pure virtual / abstract class.
        virtual void calculatePossibleMoves(Board board, Tile currentTile) = 0;
        virtual std::string getImage() = 0;
        virtual ~Piece() {};

    private: 
        bool isWhite;
        bool isDead = false;
        PieceType pieceType = PieceType::NONE;
        // Only relevant for rook or king for castling purposes.
        bool hasMoved = false;
};

class Pawn: public Piece {
    public:
        Pawn(bool isWhite): Piece(isWhite) {setPieceType(PieceType::Pawn);};
        std::string getImage() override { return getIsWhite() ? "WhitePawn.png" : "BlackPawn.png"; };
        void calculatePossibleMoves(Board board, Tile currentTile) override;
};

class Knight: public Piece {
    public:
        Knight(bool isWhite): Piece(isWhite) {setPieceType(PieceType::Knight);};
        std::string getImage() override { return getIsWhite() ? "WhiteKnight.png" : "BlackKnight.png"; };
        void calculatePossibleMoves(Board board, Tile currentTile) override;
};

class Bishop: public Piece {
    public:
        std::string getImage() override { return getIsWhite() ? "WhiteBishop.png" : "BlackBishop.png"; };
        Bishop(bool isWhite): Piece(isWhite) {setPieceType(PieceType::Bishop);};
        void calculatePossibleMoves(Board board, Tile currentTile) override;
};

class Rook: public Piece {
    public:
        std::string getImage() override { return getIsWhite() ? "WhiteRook.png" : "BlackRook.png"; };
        Rook(bool isWhite): Piece(isWhite) {setPieceType(PieceType::Rook);};
        void calculatePossibleMoves(Board board, Tile currentTile) override;
};

class Queen: public Piece {
    public:
        std::string getImage() override { return getIsWhite() ? "WhiteQueen.png" : "BlackQueen.png"; };
        Queen(bool isWhite): Piece(isWhite) {setPieceType(PieceType::Queen);};  
        void calculatePossibleMoves(Board board, Tile currentTile) override;
};

class King: public Piece {
    public:
        std::string getImage() override { return getIsWhite() ? "WhiteKing.png" : "BlackKing.png"; };
        King(bool isWhite): Piece(isWhite) {setPieceType(PieceType::King);};
        void calculatePossibleMoves(Board board, Tile currentTile) override;
};