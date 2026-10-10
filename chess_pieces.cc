
#include "chess_base.hh"
#include "chess_pieces.hh"
#include "main.cpp"

Piece::Piece(bool iswhite)
{

    is_color_white = iswhite;

}

//Overload constructor, set the color and attach a new Position and Visual component with the coordinates (x,y) and letter
Piece::Piece(bool iswhite, int x, int y, char letter)
{
    is_color_white = iswhite;
    attach(new PositionComponent(x,y));
    attach(new VisualComponent(letter));
    // Constructor implementation
}

bool Piece::canMoveTo(int x, int y)  {
        return (!board.getPieceAt(x,y));
    }

PositionComponent* Piece::getPosition()
    {
        return dynamic_cast<PositionComponent*> (getComponent("Position"));
    }
        
        // Get the visual component attached to the entity
VisualComponent* Piece::getVisual()
    {
        return dynamic_cast<VisualComponent*> (getComponent("Visual"));
    }

    
CollisionInfo CheckCollision(Vec2 StartPos, Vec2 EndPos)
{
    CollisionInfo Info;
    //get dx, dy Operator
    Vec2 Change = EndPos-StartPos;

    //unit Operator 
    Vec2 delta_Change = Vec2(0,0);

    //prevent 0/0
    if(Change.x) delta_Change.x = Change.x/abs(Change.x);
    if(Change.y) delta_Change.y = Change.y/abs(Change.y);

    while(EndPos != StartPos)
    {
        StartPos+=delta_Change;
        Info.CollidedPiece =board.getPieceAt(StartPos.x, StartPos.y);
        if(Info.CollidedPiece != nullptr) 
        {
            Info.IsCollision =true;
            Info.CollisionAt = StartPos;
            return Info;
        }
    }
    return Info;

}


CollisionInfo CheckCollision(int sx, int sy, int fx, int fy)
{
    return CheckCollision(Vec2(sx, sy), Vec2(fx,fy));

}

template<typename T>
bool IsInBounds(const T& value, const T& low, const T& high) {
    return !(value < low) && !(high < value);
}






bool Pawn::canMoveTo(int x, int y)
{
    PositionComponent* Position = getPosition();
    
    ChangeX = x - Position->getX();
    ChangeY = y - Position->getY();
    if(abs(ChangeX) == 1 && ChangeY == 1 )
    {
        Piece* target = board.getPieceAt(x,y);
        return target && target->isWhite() != this->is_color_white;   
    }
    if(!ChangeX==0) return false;
    
    return (this->*Behavior)(Position->getX(), Position->getY(), x,y);

}

bool Pawn::FirstBehaviour(int sx, int sy, int fx, int fy)
{
    if(IsInBounds(ChangeY,1,2)  && !CheckCollision(sx,sy,fx,fy).IsCollision)
    {
        Pawn::Behavior = GeneralBehavior;
        return true;
    }
    return false;
}

bool Pawn::GeneralBehavior(int sx, int sy, int fx, int fy)
{

    return ChangeY ==1  && !CheckCollision(sx,sy,fx,fy).IsCollision;
}

bool Knight::canMoveTo(int x, int y)
{
    PositionComponent* Position = getPosition();
    int changeX = Position->getX()- x;
    int changeY = Position->getY()- y;
    if (abs(changeX)+abs(changeY)==3 && abs(changeX-changeY)==1)
    {
        Piece* target = board.getPieceAt(x,y);
        return target == nullptr || target->isWhite() != this->is_color_white;
    }
    return false;

}

bool IsStratightRoute(int sx, int sy, int fx, int fy, Piece* piece)
{
    int changeX = fx - sx;
    int changeY = fy - sy;
    if(0==changeX || 0==changeY)
    {
        CollisionInfo info = CheckCollision(sx,sy,fx,fy);
        return info.IsCollision == false || 
        (info.IsCollision==true &&info.CollidedPiece->isWhite() != piece->isWhite());
    }
}

bool IsDiagonalRoute(int sx, int sy, int fx, int fy, Piece* piece)
{
    int changeX = fx - sx;
    int changeY = fy - sy;

    if(abs(changeX) == abs(changeY))
    {
        CollisionInfo info = CheckCollision(sx,sy,fx,fy);
        return info.IsCollision == false || 
        (info.IsCollision==true &&info.CollidedPiece->isWhite() != piece->isWhite());
    }
}

bool Bishop::canMoveTo(int x, int y)
{
    PositionComponent* Position = getPosition();
    return IsDiagonalRoute(Position->getX(), Position->getY(), x,y, this);
}

bool Rook::canMoveTo(int x, int y)
{
    PositionComponent* Position = getPosition();
    return IsStratightRoute(Position->getX(), Position->getY(), x,y, this);
}

bool Queen::canMoveTo(int x, int y)
{
    PositionComponent* Position = getPosition();
    return IsStratightRoute(Position->getX(), Position->getY(), x,y, this) 
    || IsDiagonalRoute(Position->getX(), Position->getY(), x,y, this)    ;
}

bool King::canMoveTo(int x, int y)
{
    PositionComponent* Position = getPosition();
    int changeX = Position->getX()- x;
    int changeY = Position->getY()- y;
    if(IsInBounds(changeX+changeY,-2,2))
    {
        Piece* target = board.getPieceAt(x,y);
        return target == nullptr || target->isWhite() != this->is_color_white;
    }
    return false;
}






