#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <iterator>
#include <stdexcept>
#include "board.h"
#include "move.h"
#include "utils.h"
#include "bitboards.h"
#include <bits/stdc++.h>
using std::ostream; using std::vector;
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
	// måste vända på fen strängen eftersom den svarta sidan kommer först i den, men i den interna
	// representationen är vit först, skulle bara kunnat loopa baklänges men jag använde en iterator
	// innan och pallar ej skriva om det (TODO)
	vector<string> rows;
	split(s, rows, '/');
	for (int i = rows.size() - 1; i != -1; i--) {
		for (auto j: rows[i]) {
			if (isalpha(j)) {
				Piece c = islower(j) ? nBlack : nWhite;
				Piece p;
				switch (tolower(j)) {
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
			else if (j != '0' && isdigit(j)){
				mask <<= (j - '0');
				shiftCount += (j - '0');
			}
			else {
				throw std::invalid_argument("Unknow character in fen string");
			}
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
	Bitboard pawns, line, diagonal, knights;
	if (attackingColor == cWhite) {
		pawns = getWhitePawns();
		if (wPawnWestAttack(pawns, target) | wPawnEastAttack(pawns, target)) return true;
		diagonal = getWhiteBishops() | getWhiteQueen();
		line = getWhiteRooks() | getWhiteQueen();
		knights = getWhiteKnights();
	}
	else {
		pawns = getBlackPawns();
		if (bPawnWestAttack(pawns, target) | bPawnEastAttack(pawns, target)) return true;
		diagonal = getBlackBishops() | getBlackQueen();
		line = getBlackRooks() | getBlackQueen();
		knights = getBlackKnights();
	}

	int sq;
	if (target) do {
			sq = bitScanForward(target);

			if (Bitboards::knight[sq] & knights) return true;

			const Magic& m1 = Magic::bishopTable[sq];
			Bitboard occ = m1.mask & getOccupied();
			if (m1.ptr[transform(occ, m1.magic, m1.shift)] & diagonal) return true;

			const Magic& m2 = Magic::rookTable[sq];
			occ = m2.mask & getOccupied();
			if (m2.ptr[transform(occ, m2.magic, m2.shift)] & line) return true;
		} while (target &= target - 1);
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
	else if (m.isQueenCastle()) {
		// lazy, can be improved
		fromToBB = (fromBB ^ (toBB >> 1)) >> 1;
		pieceBitboards[nRook] ^= fromToBB;
		pieceBitboards[m.color] ^= fromToBB;
	}
	else if (m.isKingCastle()) {
		fromToBB <<= 1;
		pieceBitboards[nRook] ^= fromToBB;
		pieceBitboards[m.color] ^= fromToBB;
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
  os << "  A B C D E F G H\n";
	for (int i = 0; i < 8; i++) {
		os << (8-i) << " ";
		for (int j = 0; j < 8; j++) {
			Bitboard mask = 1ULL << (64 - i*8 - (8-j));
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
		}
		os << std::endl;
	}
	os << std::endl;
  return os;
}
