#include "chess_base.hh"

const static class ComponentNames
{
    public:
    inline static const  char* POS_COMP_NAME = "Position";
    inline static const char* VIS_COMP_NAME = "Visual";
};

class ChessPieces: public Piece
{
    PieceType pieceType;

    PieceType getType() override { return pieceType; } 
    virtual bool canMoveTo(int x, int y) override ;


};

class Pawn: public ChessPieces
{
    bool canMoveTo(int x, int y) override;
}