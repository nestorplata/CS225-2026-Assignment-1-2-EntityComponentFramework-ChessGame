#include "chess_base.hh"
#include "chess_pieces.hh"
//
void ChessBoard::initializeBoard()
{
  int line = 0;
  int collumn = 0;
  int Size=(int)(sizeof(board)/sizeof(Piece*));

  for ( ;line!=Size; line+=Size)
  {        
    bool IsWhite = (bool)line;
      for ( ;collumn!=Size; collumn+=Size)
      {
        bool IsLeft = (bool)collumn;

        setPieceAt(new Rook(IsWhite, collumn, line, 'P'), collumn, line);
        setPieceAt(new Knight(IsWhite, collumn, line, 'P'), collumn+1-1*IsLeft, line);
        setPieceAt(new Bishop(IsWhite, collumn, line, 'P'), collumn+1-1*IsLeft, line);
      }
      setPieceAt(new Queen(IsWhite, collumn, line, 'P'), 3, line);
      setPieceAt(new King(IsWhite, collumn, line, 'P'), 4, line);
  }

}

  // Get the piece located at the coordinates x, y, be carefull! you may need to swap the coordinates
  Piece* ChessBoard::getPieceAt(int x, int y)
  {
    if(x < 1 || x > BOARD_SIZE || y < 1 || y > BOARD_SIZE)
    {
        return nullptr;
    }
    return board[x-1][y-1];
  }

  // Set the submited piece at the coordinates x, y, be carefull! you may need to swap the coordinates
  void ChessBoard::setPieceAt(Piece* piece, int x, int y)
  {
    if(x < 1 || x > BOARD_SIZE || y < 1 || y > BOARD_SIZE)
    {
        return;
    }
    board[x-1][y-1] = piece;
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



  



