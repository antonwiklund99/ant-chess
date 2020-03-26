#include <iostream>
#include <string>
#include <cctype>
#include <iterator>
#include <stdexcept>
#include "board.h"
#include "move.h"
#include "magic.h"
#include "utils.h"
using std::ostream;
using std::string;

Board::Board() {
  reset();
}

Board::Board(string s) {
  for (int i = 0; i < 8; i++) {
    pieceBitboards[i] = 0;
  }
  Bitboard mask = 1;
  int shiftCount = 0;

  for (auto it = s.begin(); it != s.end(); it++) {
    if (*it == '/') {
      continue;
    }
    else if (isalpha(*it)) {
      Piece c = islower(*it) ? nWhite : nBlack;
      Piece p;
      switch (tolower(*it)) {
      case 'p' : {p = nPawn; break;}
      case 'n' : {p = nKnight; break;}
      case 'b' : {p = nBishop; break;}
      case 'r' : {p = nRook; break;}
      case 'q' : {p = nQueen; break;}
      case 'k' : {p = nKing; break;}
      default  : {throw std::invalid_argument("Unknow letter in fen string");}
      }
      pieceBitboards[c] |= mask;
      pieceBitboards[p] |= mask;
      mask <<= 1;
      shiftCount++;
    }
    else if (*it != '0' && isdigit(*it)){
      mask <<= (*it - '0');
      shiftCount += (*it - '0');
    }
    else {
      throw std::invalid_argument("Unknow character in fen string");
    }
  }
  if (shiftCount != 64) {
    throw std::invalid_argument("Not right amount of squares in fen string");
  }
}

void Board::reset() {
  pieceBitboards[0] = 0x000000000000ffff;
  pieceBitboards[1] = 0xffff000000000000;
  pieceBitboards[2] = 0x00ff00000000ff00;
  pieceBitboards[3] = 0x4200000000000042;
  pieceBitboards[4] = 0x2400000000000024;
  pieceBitboards[5] = 0x8100000000000081;
  pieceBitboards[6] = 0x0800000000000008;
  pieceBitboards[7] = 0x1000000000000010;
}

bool Board::isAttacked(Bitboard target, Color attackingColor) const {
  int sq = bitScanForward(target);
  if (attackingColor == cWhite) {
    Bitboard pawns = getBlackPawns();
    if (wPawnWestAttack(target, pawns) | wPawnEastAttack(target, pawns)) return true;

    Bitboard sliders = getWhiteBishops() | getWhiteQueen();
    const Magic& m1 = Magic::bishopTable[sq];
    Bitboard occ = m1.mask & getOccupied();
    if (m1.ptr[transform(occ, m1.magic, m1.shift)] & sliders) return true;

    sliders = getWhiteRooks() | getWhiteQueen();
    const Magic& m2 = Magic::rookTable[sq];
    occ = m2.mask & getOccupied();
    if (m2.ptr[transform(occ, m2.magic, m2.shift)] & sliders) return true;
  }
  else {
    Bitboard pawns = getWhitePawns();
    if (bPawnWestAttack(target, pawns) | bPawnEastAttack(target, pawns)) return true;

    Bitboard sliders = getBlackBishops() | getBlackQueen();
    const Magic& m1 = Magic::bishopTable[sq];
    Bitboard occ = m1.mask & getOccupied();
    if (m1.ptr[transform(occ, m1.magic, m1.shift)] & sliders) return true;

    sliders = getBlackRooks() | getBlackQueen();
    const Magic& m2 = Magic::rookTable[sq];
    occ = m2.mask & getOccupied();
    if (m2.ptr[transform(occ, m2.magic, m2.shift)] & sliders) return true;
  }
  return false;
}

// makes the move on board, can also be used to unmake move since it toggles the bits
void Board::unsafeMakeMove(const Move& m) {
  Bitboard fromBB = 1ULL << m.getFrom();
  Bitboard toBB = 1ULL << m.getTo();
  Bitboard fromToBB = fromBB ^ toBB;
  pieceBitboards[m.piece] ^= fromToBB;
  pieceBitboards[m.color] ^= fromToBB;
  if (m.isCapture()) {
    // if capture toggle captured piece's bitboards
    pieceBitboards[m.cPiece] ^= toBB;
    pieceBitboards[m.cColor] ^= toBB;
  }
}

Piece Board::pieceOnSq(int n) const {
  Bitboard bb = 1ULL << n;
  if (bb & pieceBitboards[nPawn]) return nPawn;
  if (bb & pieceBitboards[nKnight]) return nKnight;
  if (bb & pieceBitboards[nBishop]) return nBishop;
  if (bb & pieceBitboards[nRook]) return nRook;
  if (bb & pieceBitboards[nQueen]) return nQueen;
  if (bb & pieceBitboards[nKing]) return nKing;
  return nEmpty;
}

Bitboard wSinglePush(Bitboard pawns, Bitboard emptySqs) {
  return northOne(pawns) & emptySqs;
}

Bitboard wDoublePush(Bitboard singlePushes, Bitboard emptySqs) {
  return northOne(singlePushes) & RANK_4 & emptySqs;
}

Bitboard bSinglePush(Bitboard pawns, Bitboard emptySqs) {
  return southOne(pawns) & emptySqs;
}

Bitboard bDoublePush(Bitboard singlePushes, Bitboard emptySqs) {
  return southOne(singlePushes) & RANK_5 & emptySqs;
}

Bitboard wPawnEastAttack(Bitboard wpawns, Bitboard bpieces) {
  return northEastOne(wpawns) & bpieces;
}

Bitboard wPawnWestAttack(Bitboard wpawns, Bitboard bpieces) {
  return northWestOne(wpawns) & bpieces;
}

Bitboard bPawnEastAttack(Bitboard bpawns, Bitboard wpieces) {
  return southEastOne(bpawns) & wpieces;
}

Bitboard bPawnWestAttack(Bitboard bpawns, Bitboard wpieces) {
  return southWestOne(bpawns) & wpieces;
}

// Cout bitboard
ostream& operator<<(ostream& os, const Board& b) {
  Bitboard mask = 1;
  os << "  A B C D E F G H\n";
  for (int i = 0; i < 64; i++) {
    if (i % 8 == 0) os << i/8 + 1 << " ";
    if (b.getBlackPawns() & mask)
      os << "♙ ";
    else if (b.getWhitePawns() & mask)
      os << "♟ ";
    else if (b.getBlackKnights() & mask)
      os << "♘ ";
    else if (b.getWhiteKnights() & mask)
      os << "♞ ";
    else if (b.getBlackBishops() & mask)
      os << "♗ ";
    else if (b.getWhiteBishops() & mask)
      os << "♝ ";
    else if (b.getBlackRooks() & mask)
      os << "♖ ";
    else if (b.getWhiteRooks() & mask)
      os << "♜ ";
    else if (b.getBlackQueen() & mask)
      os << "♕ ";
    else if (b.getWhiteQueen() & mask)
      os << "♛ ";
    else if (b.getBlackKing() & mask)
      os << "♔ ";
    else if (b.getWhiteKing() & mask)
      os << "♔ ";
    else
      os << "  ";

    mask <<= 1;
    if ((i + 1) % 8 == 0)
      os << "\n";
  }
  return os;
}
