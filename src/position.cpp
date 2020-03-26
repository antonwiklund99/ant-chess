#include "board.h"
#include "position.h"
#include "magic.h"
#include "piecePatterns.h"
#include "utils.h"
#include <vector>

bool Position::makeMove(const Move& m) {
  board.unsafeMakeMove(m);
  if (board.isAttacked(turn == cWhite ? board.getWhiteKing() : board.getBlackKing(),
                       turn == cWhite ? cBlack : cWhite)) {
    board.unsafeMakeMove(m);
    return false;
  }
  else {
    turn = (turn == cWhite ? cBlack : cWhite);
    //castling stuff
    //halfmoveclock stuff
    return true;
  }
}

void Position::unmakeMove(const Move&m) {
  turn = (turn == cWhite ? cBlack : cWhite);
  board.unsafeMakeMove(m);
}

void addFromBitboard(int from, Bitboard moves, const Position& pos, std::vector<Move>& moveVec,
                     Bitboard targets, Color turn, Piece p) {
  Bitboard captures = moves & targets;
  moves ^= captures;
  while (captures) {
    int idx = bitScanForward(captures);
    moveVec.push_back(Move(from, idx, CAPTURE_FLAG, p, turn, pos.board.pieceOnSq(idx),
                           (turn == cWhite ? cBlack : cWhite)));
    captures &= captures - 1;
  }
  while (moves) {
    moveVec.push_back(Move(from, bitScanForward(moves), 0, p, turn, nEmpty, cWhite));
    moves &= moves - 1;
  }
}

void generateMoves(const Position& p, std::vector<Move>& moveVec) {
  generateMoves(p, moveVec, p.turn);
}

void generateMoves(const Position& pos, std::vector<Move>& moveVec, Color turn) {
  Bitboard own, opponent, pawns, knights, king, rooks, bishops, queen, empty = pos.board.getEmpty();
  if (turn == cWhite) {
    own = pos.board.getWhites();
    opponent = pos.board.getBlacks();
    pawns = pos.board.getWhitePawns();
    knights = pos.board.getWhiteKnights();
    rooks = pos.board.getWhiteRooks();
    bishops = pos.board.getWhiteBishops();
    queen = pos.board.getWhiteQueen();
    king = pos.board.getWhiteKing();

    // Pawn pushes
    Bitboard pawnSinglePushTargets = wSinglePush(pawns, empty);
    Bitboard pawnDoublePushTargets = wDoublePush(pawnSinglePushTargets, empty);

    if (pawnSinglePushTargets) do {
        int idx = bitScanForward(pawnSinglePushTargets);
        moveVec.push_back(Move(idx - 8, idx, 0, nPawn, cWhite, nEmpty, cBlack));
      } while (pawnSinglePushTargets &= pawnSinglePushTargets - 1);

    if (pawnDoublePushTargets) do {
        int idx = bitScanForward(pawnDoublePushTargets);
        moveVec.push_back(Move(idx - 16, idx, DOUBLE_PAWN_PUSH_FLAG, nPawn, cWhite, nEmpty, cBlack));
      } while (pawnDoublePushTargets &= pawnDoublePushTargets - 1);

    // Pawn attacks
    Bitboard pawnEastAttacks = wPawnEastAttack(pawns, opponent);
    Bitboard pawnWestAttacks = wPawnWestAttack(pawns, opponent);

    if (pawnEastAttacks) do {
        int idx = bitScanForward(pawnEastAttacks);
        moveVec.push_back(Move(idx - 9, idx, CAPTURE_FLAG, nPawn, turn, pos.board.pieceOnSq(idx),
                               cBlack));
      } while (pawnEastAttacks &= pawnEastAttacks - 1);

    if (pawnWestAttacks) do {
        int idx = bitScanForward(pawnWestAttacks);
        moveVec.push_back(Move(idx - 7, idx, CAPTURE_FLAG, nPawn, turn, pos.board.pieceOnSq(idx),
                               cBlack));
      } while (pawnWestAttacks &= pawnWestAttacks - 1);
  }
  else {
    own = pos.board.getBlacks();
    opponent = pos.board.getWhites();
    pawns = pos.board.getBlackPawns();
    knights = pos.board.getBlackKnights();
    rooks = pos.board.getBlackRooks();
    bishops = pos.board.getBlackBishops();
    queen = pos.board.getBlackQueen();
    king = pos.board.getBlackKing();

    // Pawn pushes
    Bitboard pawnSinglePushTargets = bSinglePush(pawns, empty);
    Bitboard pawnDoublePushTargets = bDoublePush(pawnSinglePushTargets, empty);

    if (pawnSinglePushTargets) do {
        int idx = bitScanForward(pawnSinglePushTargets);
        moveVec.push_back(Move(idx + 8, idx, 0, nPawn, turn, nEmpty, cWhite));
      } while (pawnSinglePushTargets &= pawnSinglePushTargets - 1);

    if (pawnDoublePushTargets) do {
        int idx = bitScanForward(pawnDoublePushTargets);
        moveVec.push_back(Move(idx + 16, idx, DOUBLE_PAWN_PUSH_FLAG, nPawn, turn, nEmpty, cWhite));
      } while (pawnDoublePushTargets &= pawnDoublePushTargets - 1);

    // Pawn attacks
    Bitboard pawnEastAttacks = bPawnEastAttack(pawns, opponent);
    Bitboard pawnWestAttacks = bPawnWestAttack(pawns, opponent);

    if (pawnEastAttacks) do {
        int idx = bitScanForward(pawnEastAttacks);
        moveVec.push_back(Move(idx + 9, idx, 4, nPawn, cBlack, pos.board.pieceOnSq(idx), cWhite));
      } while (pawnEastAttacks &= pawnEastAttacks - 1);

    if (pawnWestAttacks) do {
        int idx = bitScanForward(pawnWestAttacks);
        moveVec.push_back(Move(idx + 7, idx, 4, nPawn, cBlack, pos.board.pieceOnSq(idx), cWhite));
      } while (pawnWestAttacks &= pawnWestAttacks - 1);
  }
  // TODO: Add en-passant https://en.wikipedia.org/wiki/En_passant

  // Knight
  do {
      int origin = bitScanForward(knights);
      Bitboard attacks = PiecePatterns::knight[origin] & ~own;
      addFromBitboard(origin, attacks, pos, moveVec, opponent, turn, nKnight);
  } while (knights &= knights - 1);

  // King
  int idx = bitScanForward(king);
  Bitboard kingMoves = PiecePatterns::king[idx] & ~own;
  addFromBitboard(idx, kingMoves, pos, moveVec, opponent, turn, nKing);

  // Rook
  do {
    int from = bitScanForward(rooks);
    const Magic& m = Magic::rookTable[from];
    Bitboard occ = pos.board.getOccupied() & m.mask;
    Bitboard moves = m.ptr[transform(occ, m.magic, m.shift)] &~own;
    addFromBitboard(from, moves, pos, moveVec, opponent, turn, nRook);
  } while (rooks &= rooks - 1);

  // Bishop
  do {
    int from = bitScanForward(bishops);
    const Magic& m = Magic::bishopTable[from];
    Bitboard occ = pos.board.getOccupied() & m.mask;
    Bitboard moves = m.ptr[transform(occ, m.magic, m.shift)] &~own;
    addFromBitboard(from, moves, pos, moveVec, opponent, turn, nBishop);
  } while (bishops &= bishops - 1);

  // Queen
  idx = bitScanForward(queen);
  const Magic& bm = Magic::bishopTable[idx], rm = Magic::rookTable[idx];
  Bitboard bocc = pos.board.getOccupied() & bm.mask, rocc = pos.board.getOccupied() & rm.mask;
  Bitboard moves = (bm.ptr[transform(bocc, bm.magic, bm.shift)] |
                    rm.ptr[transform(rocc, rm.magic, rm.shift)]) &~own;
  addFromBitboard(idx, moves, pos, moveVec, opponent, turn, nQueen);
}
