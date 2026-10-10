
#include "chess_pieces.hh"
#include "chess_base.hh"
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
        StartPos.x+=delta_Change.x;
        StartPos.y+=delta_Change.y;

        //Info.CollidedPiece = something::board->getPieceAt(StartPos.x, StartPos.y);
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

//methods to handle the movement of the pieces

//Pawn movement behavior on first move of pawn
bool Pawn::Is2Steps(int sx, int sy, int fx, int fy)
{

    if(IsInBounds(ChangeY,1,2)  && !CheckCollision(sx,sy,fx,fy).IsCollision)
    {
        Pawn::Behavior = Is1Step;
        return true;
    }
    return false;
}

//Pawn movement behavior after first move
bool Pawn::Is1Step(int sx, int sy, int fx, int fy)
{
    return ChangeY ==1  && !CheckCollision(sx,sy,fx,fy).IsCollision;
}

//Check if movement Straight is possible
bool IsStratightRoute(int sx, int sy, int fx, int fy, Piece* piece)
{
    int changeX = fx - sx;
    int changeY = fy - sy;
    if(0==changeX || 0==changeY)
    {
        return true;
        //CollisionInfo info = CheckCollision(sx,sy,fx,fy);

        //return info.IsCollision == false || 
        //(info.IsCollision==true &&info.CollidedPiece->isWhite() != piece->isWhite());
    }
    return false;
}

//Check if movement Diagonal is possible
bool IsDiagonalRoute(int sx, int sy, int fx, int fy, Piece* piece)
{
    int changeX = fx - sx;
    int changeY = fy - sy;

    if(changeX!=0 && abs(changeX) == abs(changeY))
    {
        CollisionInfo info = CheckCollision(sx,sy,fx,fy);
        return true;
        //info.IsCollision == false || 
        //(info.IsCollision==true &&info.CollidedPiece->isWhite() != piece->isWhite());
    }  
    return false;
}

//canMove Functions


bool Pawn::canMoveTo(int x, int y)
{
    PositionComponent* Position = getPosition();
    
    ChangeX = x - Position->getX();
    ChangeY = y - Position->getY();
    if(!isWhite()) ChangeY *=-1;
    if(abs(ChangeX) == 1 && ChangeY == 1  )
    {
        //Piece* target = something::board->getPieceAt(x,y);
        return true;//target && target->isWhite() != this->is_color_white;   
    }
    if(!ChangeX==0) return false;
    
    return (this->*Behavior)(Position->getX(), Position->getY(), x,y);

}

bool Knight::canMoveTo(int x, int y)
{
    PositionComponent* Position = getPosition();
    int changeX = Position->getX()- x;
    int changeY = Position->getY()- y;
    if (abs(changeX)+abs(changeY)==3 && abs(changeX-changeY)==1)
    {
        //Piece* target =  something::board->getPieceAt(x,y);
        return true;//target == nullptr || target->isWhite() != this->is_color_white;
    }
    return false;

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
    return IsDiagonalRoute(Position->getX(), Position->getY(), x,y, this) ||
    IsStratightRoute(Position->getX(), Position->getY(), x,y, this) ;
}

bool King::canMoveTo(int x, int y)
{
    PositionComponent* Position = getPosition();
    int changeX = Position->getX()- x;
    int changeY = Position->getY()- y;
    int TotalChange = abs(changeX)+abs(changeY);
    if (TotalChange==1 || TotalChange==2 && abs(changeX)==1)
    {
        //Piece* target =   something::board->getPieceAt(x,y);
        return true; //target == nullptr || target->isWhite() != this->is_color_white;
    }
    return false;
}
