#ifndef PIECE_GUARD
#define PIECE_GUARD

enum PieceType {
                ptNIL    = 0,
                ptWPAWN  = 1,
                ptBPAWN  = 2,
                ptKNIGHT = 3,
                ptBISHOP = 4,
                ptROOK   = 5,
                ptQUEEN  = 6,
                ptKING   = 7,
};

// Color is represented by 4th bit, it is toggled for black
enum PieceCode {
                pcEMPTY   = ptNIL,

                pcWPAWN   = ptWPAWN,
                pcWKNIGHT = ptKNIGHT,
                pcWBISHOP = ptBISHOP,
                pcWROOK   = ptROOK,
                pcWQUEEN  = ptQUEEN,
                pcWKING   = ptKING,

                pcBLACK   = 8,
                pcBPAWN   = ptBPAWN + pcBLACK,
                pcBKNIGHT = ptKNIGHT + pcBLACK,
                pcBBISHOP = ptBISHOP + pcBLACK,
                pcBROOK   = ptROOK + pcBLACK,
                pcBQUEEN  = ptQUEEN + pcBLACK,
                pcBKING   = ptKING + pcBLACK,
};

enum Color {
            cWhite = 0,
            cBlack = 1
};

class Piece {
 public:
  Color color() const { return (Color) (pc >> 3); }
  PieceType type() const { return (PieceType) (pc & 7); }
  Piece(PieceCode p) : pc(p) {}

 private:
  PieceCode pc;
};
#endif
