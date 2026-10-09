#include<stdlib.h>
#include <iostream>

#include "chess_base.hh"
#include "chess_pieces.hh"
#include "framework.hh"


    bool Piece::isWhite()
    {
        return is_color_white;
    }

    Piece::Piece(bool iswhite)
    {
        is_color_white=iswhite;

    }
   Piece::Piece(bool iswhite, int x, int y, char letter)
    {
        is_color_white = iswhite;
        attach(new PositionComponent(x, y));
        attach(new VisualComponent(letter));

    }
    
    Piece::Piece(bool iswhite)
    {
        is_color_white = iswhite;
    }
       
        //Overload constructor, set the color and attach a new Position and Visual component with the coordinates (x,y) and letter
        // Get the posicion component attached to the entity
    PositionComponent* Piece::getPosition()
    {
        return dynamic_cast<PositionComponent*> (getComponent("Position"));
    }
        
        // Get the visual component attached to the entity
    VisualComponent* Piece::getVisual()
    {
        return dynamic_cast<VisualComponent*> (getComponent("Visual"));
    }
