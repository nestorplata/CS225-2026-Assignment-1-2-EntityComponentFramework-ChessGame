#include "chess_base.hh"
#include "chess_pieces.hh"

namespace something
{
  ChessBoard *board;
}
void ChessBoard::initializeBoard()
{
  using namespace something;
int collumn=0;
int line=0;
bool IsWhite = true;
bool IsRight = false;

  for ( collumn = 0;collumn<=7; collumn+=7)
  {    

    for ( line = 0;line<=7; line+=7)
     {

       setPieceAt(new Rook(line,collumn, IsWhite, 'R'), line, collumn);
       setPieceAt(new Knight(line+1-2*IsRight, collumn, IsWhite, 'N'), line+1-2*IsRight, collumn);
       setPieceAt(new Bishop(line+2-4*IsRight, collumn, IsWhite, 'B'), line+2-4*IsRight, collumn);
        for (int i = 0; i < 4; ++i) {
            setPieceAt(new Pawn(i+4*(!IsRight), collumn+(IsWhite ? 1 : -1), IsWhite, 'P'), i+4*(!IsRight), collumn+(IsWhite ? 1 : -1));
        }
         IsRight = !IsRight;
     }
      setPieceAt(new Queen(3, collumn, IsWhite, 'Q'), 3, collumn);
      setPieceAt(new King(4, collumn, IsWhite, 'K'), 4, collumn);
      IsWhite = !IsWhite;
  
    }


}

  // Get the piece located at the coordinates x, y, be carefull! you may need to swap the coordinates
   Piece* ChessBoard::getPieceAt(int x, int y)
  {
    return board[x][y];
  }

  // Set the submited piece at the coordinates x, y, be carefull! you may need to swap the coordinates
  void ChessBoard::setPieceAt(Piece* piece, int x, int y)
  {
    board[x][y] = piece;
  }
  
  // destructor, must release all memory allocated for pieces in the board
  ChessBoard::~ChessBoard()   
  {
      for (int i = 0; i < BOARD_SIZE; ++i) {
          for (int j = 0; j < BOARD_SIZE; ++j) {
              if(board[i][j]) free(board[i][j]);
          }
      }
  }

Piece::Piece(bool iswhite)
{

    is_color_white = iswhite;

}

//Overload constructor, set the color and attach a new Position and Visual component with the coordinates (x,y) and letter
Piece::Piece(bool iswhite, int x, int y, char letter)
{
    is_color_white = iswhite;
    attach(static_cast<Component*>(new PositionComponent(x,y)));
    attach(static_cast<Component*>(new VisualComponent(is_color_white ? std::tolower(letter) : std::toupper(letter))));
}

 bool Piece::isWhite()
 {
     return is_color_white;
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

    Piece::~Piece()
    {
        free(getPosition());
        free(getVisual());
        // Destructor implementation
    }









  



