#ifndef POSITION_GUARD
#define POSITION_GUARD

#include "board.h"
#include "enums.h"
#include "move.h"
#include <stack>
#include <vector>

class Info {
public:
  Info(unsigned int x, Bitboard ep) : encodedInfo(x), ep(ep) {}
  bool getWKingCastling() { return encodedInfo & 1; };
  bool getWQueenCastling() { return encodedInfo & 2; };
  bool getBKingCastling() { return encodedInfo & 4; };
  bool getBQueenCastling() { return encodedInfo & 8; };
  unsigned int getHalfMoveClock() { return encodedInfo >> 4; };
  Bitboard getEnPassants() { return ep; };

private:
  // bit 1 - wKingsidecastling
  // bit 2 - wQueensidecastling
  // bit 3 - bKingsidecastling
  // bit 4 - bQueensidecastling
  // bit 5-32 - halfmoveclock (max 50 so will only ever use 6 bits)
  unsigned int encodedInfo;
  Bitboard ep;
};

class Position {
public:
  Board board;
  Color turn;
  std::stack<Info *> states;
  bool wKingsideCastling;
  bool wQueensideCastling;
  bool bKingsideCastling;
  bool bQueensideCastling;
  unsigned int halfMoveClock;
  unsigned int fullMoveNumber;
  uint64_t hash;
  Position(const std::string&);
  Position()
      : turn(cWhite), wKingsideCastling(true), wQueensideCastling(true),
        bKingsideCastling(true), bQueensideCastling(true), halfMoveClock(0),
        fullMoveNumber(1) { calcHash(); }

  bool makeMove(const Move &);
  void unmakeMove(const Move &);
  Info *getInfo(Bitboard);
  Bitboard getPossibleEnPassants() const;
private:
  void calcHash();
};

void initRandomHashes();
void generateMoves(const Position &, std::vector<Move> &, Color);
void generateMoves(const Position &, std::vector<Move> &);
std::vector<Move> legalMoves(Position &);
Bitboard perft(int, Position &);
#endif
