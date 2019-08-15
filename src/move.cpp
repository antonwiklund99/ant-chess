#include <vector>
#include <iostream>
#include <bitset>
#include <string>
#include "move.h"
#include "board.h"
using std::string;

string Move::notation() {
  string ret;
  ret = indexToCordinate(getFrom());
  ret += (isCapture()) ? 'x' : '-';
  ret += indexToCordinate(getTo());
  return ret;
}

string indexToCordinate(unsigned int i) {
  string ret;
  char file = (i % 8) + 'a';
  char rank = (i / 8 + 1) + '0';
  ret += file;
  ret += rank;
  return ret;
}

void generateMoves(const Position& pos, std::vector<Move>& moveVec, Color turn) {
  // Pawn pushes
  Bitboard pawnSinglePushTargets = (turn == cWhite) ?
    wSinglePush(pos.board.getPawns(turn), pos.board.getEmpty()) :
    bSinglePush(pos.board.getPawns(turn), pos.board.getEmpty());
  Bitboard pawnDoublePushTargets = (turn == cWhite) ?
    wDoublePush(pawnSinglePushTargets, pos.board.getEmpty()) :
    bDoublePush(pawnSinglePushTargets, pos.board.getEmpty());

  if (pawnSinglePushTargets) do {
      int idx = bitScanForward(pawnSinglePushTargets);
      moveVec.push_back(Move(idx + ((turn == cWhite) ? -8 : 8), idx, 0));
  } while (pawnSinglePushTargets &= pawnSinglePushTargets - 1);

  if (pawnDoublePushTargets) do {
      int idx = bitScanForward(pawnDoublePushTargets);
      moveVec.push_back(Move(idx + ((turn == cWhite) ? -16 : 16), idx, 0));
    } while (pawnDoublePushTargets &= pawnDoublePushTargets - 1);

}

int bitScanForward(Bitboard b) {
  const Bitboard debruijn64 = Bitboard(0x03f79d71b4cb0a89);
  return index64[((b & -b) * debruijn64) >> 58];
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

Bitboard northOne(Bitboard b) {
  return b << 8;
}
Bitboard southOne(Bitboard b) {
  return b >> 8;
}
