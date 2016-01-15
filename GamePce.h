#ifndef _UBQ_GAME_PIECE_H_
#define _UBQ_GAME_PIECE_H_

#ifdef _DEBUG
#pragma message("Include: " __FILE__", Stamp:" __TIMESTAMP__)
#endif

#define PA_NONE      0    // No piece attributes 
#define PA_CLICK     1    // Piece maybe clicked
#define PA_DRAG      2    // Piece may be dragged to a new place
#define PA_DBLCLK    4    // not supported yet
#define PA_INVISIBLE 8    // Piece is not displayed

#define SHAPE_RECT  0
#define SHAPE_OVAL  1
#define SHAPE_PIECE 2

class CUbqGamePiece : public CObject
{
  // construction 
public:    
  CUbqGamePiece(int id, int type, int Shape, class CUbqGameImage* pImage, int attr, CRect Area);
  ~CUbqGamePiece();
    
  // methods
public:
  BOOL IsInside(CPoint Point);
  void SetImage(class CUbqGameImage* pImage) {m_pImage = pImage;}
  void SetAttribute(int attr) { this->attr = attr; }
  int  GetType() { return this->type; }
  int  GetAttribute() { return this->attr; }

  void SetID(long id) {this->m_nID = id;}
  int  GetID ()      {return this->m_nID;}

  // members
public:
  CRect m_rArea;
  int   id;
  BOOL  m_nShape;
  class CUbqGameImage* m_pImage;
    
private:
  int attr;
  int type;
  long m_nID;
  long m_nXRadiusSquare;
  long m_nYRadiusSquare;

};

#endif // _UBQ_GAME_PIECE_H_
