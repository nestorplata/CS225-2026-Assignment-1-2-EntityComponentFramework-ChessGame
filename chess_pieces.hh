#pragma once
#include <string>
#include <iostream>

#include "chess_base.hh"
//vec 2 class
struct Vec2
{
    public:
    int x, y;

    public:
    Vec2(int x = 0, int y = 0)
    {
        this->x=x;
        this->y=y;
    };
    Vec2() :x(0), y(0) {};

    Vec2 operator+(const Vec2& v) const { return {x + v.x, y + v.y}; }
    Vec2 operator-(const Vec2& v) const { return {x - v.x, y - v.y}; }
    Vec2 operator/(const Vec2& v) const { return {x / v.x, y / v.y}; }
    Vec2 operator/=(const Vec2& v) const { return {x / v.x, y / v.y}; }
    Vec2 operator+=(const Vec2& v) const { return {x + v.x, y + v.y}; }
    bool operator!=(const Vec2& v) const { return {x != v.x || y != v.y}; }
    bool operator==(const Vec2& v) const { return {x == v.x && y == v.y}; }


};

//CheckCollision, Horizontal and Vertical
struct CollisionInfo
{
    public:
    bool IsCollision = false;
    Vec2 CollisionAt;
    Piece* CollidedPiece = nullptr;
    CollisionInfo() : IsCollision(false), CollisionAt(-1,-1) {};

    
    
};


// Component Name identifiers
    static const  char* POS_COMP_NAME = "Position";
    static const char* VIS_COMP_NAME = "Visual";





class Pawn: public Piece
{
    protected:
        bool (Pawn::*Behavior)(int sx, int sy, int fx, int fy);
        int ChangeX;
        int ChangeY;
    public:

        Pawn(int x, int y, bool iswhite, char letter): Piece(iswhite, x,y,letter)
        {
            Behavior = &Pawn::FirstBehaviour;
        }
        
        Pawn() : Pawn(true,0,0,'P'){};
        PieceType getType() override { return PieceType::PAWN; } 
        bool canMoveTo(int x, int y) override;

    protected:

        bool GeneralBehavior(int sx, int sy, int fx, int fy);
        bool FirstBehaviour(int sx, int sy, int fx, int fy);
        bool EatBehaviour(int sx, int sy, int fx, int fy);
    public:




};


class Knight: public Piece
{


    public:
        Knight(int x, int y, bool iswhite, char letter): Piece(iswhite, x,y,letter)
        {
        }
        
        Knight() : Knight(true,0,0,'N'){};

    protected:
        bool GeneralBehavior(int sx, int sy, int fx, int fy);

    public:
    PieceType getType() override { return PieceType::KNIGHT; } 
    bool canMoveTo(int x, int y) override;

};

class Bishop: public Piece
{    public:
        Bishop(int x, int y, bool iswhite, char letter): Piece(iswhite, x,y,letter)
        {
        }
        
        Bishop() : Bishop(true,0,0,'B'){};

    protected:
        bool GeneralBehavior(int sx, int sy, int fx, int fy);

    public:
    PieceType getType() override { return PieceType::BISHOP; } 
    bool canMoveTo(int x, int y) override;
};

class Rook: public Piece
{    public:
        Rook(int x, int y, bool iswhite, char letter): Piece(iswhite, x,y,letter)
        {
        }
        
        Rook() : Rook(true,0,0,'R'){};

    protected:
        bool GeneralBehavior(int sx, int sy, int fx, int fy);

    public:
    PieceType getType() override { return PieceType::ROOK; } 
    bool canMoveTo(int x, int y) override;

};

class Queen: public Piece
{    public:
        Queen(int x, int y, bool iswhite, char letter): Piece(iswhite, x,y,letter)
        {
        }
        
        Queen() : Queen(true,0,0,'Q'){};

    protected:
        bool GeneralBehavior(int sx, int sy, int fx, int fy);

    public:
    PieceType getType() override { return PieceType::QUEEN; } 
    bool canMoveTo(int x, int y) override;
};

class King: public Piece
{    public:
        King(int x, int y, bool iswhite, char letter): Piece(iswhite, x,y,letter)
        {
        }
        
        King() : King(true,0,0,'K'){};

    protected:
        bool GeneralBehavior(int sx, int sy, int fx, int fy);

    public:
    PieceType getType() override { return PieceType::KING; } 
        bool canMoveTo(int x, int y) override;


};

