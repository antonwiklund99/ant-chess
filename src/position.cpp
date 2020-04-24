#include "board.h"
#include "position.h"
#include "bitboards.h"
#include "utils.h"
#include <vector>
using std::string; using std::vector;

Position::Position(string fen) {
	vector<string> args;
	split(fen, args, ' ');
	if (args.size() != 6)
		throw new std::invalid_argument("FEN-string doesn't contain the correct amount of elements");
	Board b(args[0]);
	board = b;
	turn = (args[1] == "w") ? cWhite : cBlack;
	// TODO CASTLING STUFF
	// TODO EN PASSANT
	wcastling = true;
	bcastling = true;
	halfMoveClock = std::stoi(args[4]);
	fullMoveNumber = std::stoi(args[5]);
}

bool Position::makeMove(const Move& m) {
  board.unsafeMakeMove(m);
  if (board.isAttacked(turn == cWhite ? board.getWhiteKing() : board.getBlackKing(),
                       turn == cWhite ? cBlack : cWhite)) {
    board.unsafeMakeMove(m);
    return false;
  }
  else {
		if (turn == cBlack) fullMoveNumber++;
		if (m.isCapture() || m.piece == nPawn) {
			halfMoveClock = 0;
		}
		else halfMoveClock++;
    turn = (turn == cWhite ? cBlack : cWhite);
    //castling stuff
    return true;
  }
}

void Position::unmakeMove(const Move&m) {
	// THIS WILL FUCK UP HALFMOVECLOCK
	if (turn == cWhite) fullMoveNumber--;
  turn = (turn == cWhite ? cBlack : cWhite);
  board.unsafeMakeMove(m);
}

void addFromBitboard(int from, Bitboard moves, const Position& pos, vector<Move>& moveVec,
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

void generateMoves(const Position& p, vector<Move>& moveVec) {
  generateMoves(p, moveVec, p.turn);
}
//Pseudo-legal moves
void generateMoves(const Position& pos, vector<Move>& moveVec, Color turn) {
  Bitboard own, opponent, pawns, knights, king, rooks, bishops, queen, empty = pos.board.getEmpty();
	moveVec.clear();
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
        moveVec.push_back(Move(idx + 7, idx, 4, nPawn, cBlack, pos.board.pieceOnSq(idx), cWhite));
      } while (pawnEastAttacks &= pawnEastAttacks - 1);

    if (pawnWestAttacks) do {
        int idx = bitScanForward(pawnWestAttacks);
        moveVec.push_back(Move(idx + 9, idx, 4, nPawn, cBlack, pos.board.pieceOnSq(idx), cWhite));
      } while (pawnWestAttacks &= pawnWestAttacks - 1);
  }
  // TODO: Add en-passant https://en.wikipedia.org/wiki/En_passant

  // Knight
	if (knights) {
		do {
      int origin = bitScanForward(knights);
      Bitboard attacks = Bitboards::knight[origin] & ~own;
      addFromBitboard(origin, attacks, pos, moveVec, opponent, turn, nKnight);
		} while (knights &= knights - 1);
	}

  // King
	if (king) {
		int idx = bitScanForward(king);
		Bitboard kingMoves = Bitboards::king[idx] & ~own;
		addFromBitboard(idx, kingMoves, pos, moveVec, opponent, turn, nKing);
	}

  // Rook
	if (rooks) {
		do {
			int from = bitScanForward(rooks);
			const Magic& m = Magic::rookTable[from];
			Bitboard occ = pos.board.getOccupied() & m.mask;
			Bitboard moves = m.ptr[transform(occ, m.magic, m.shift)] &~own;
			addFromBitboard(from, moves, pos, moveVec, opponent, turn, nRook);
		} while (rooks &= rooks - 1);
	}

  // Bishop
	if (bishops) {
		do {
			int from = bitScanForward(bishops);
			const Magic& m = Magic::bishopTable[from];
			Bitboard occ = pos.board.getOccupied() & m.mask;
			Bitboard moves = m.ptr[transform(occ, m.magic, m.shift)] &~own;
			addFromBitboard(from, moves, pos, moveVec, opponent, turn, nBishop);
		} while (bishops &= bishops - 1);
	}

  // Queen
	if (queen) {
		int idx = bitScanForward(queen);
		const Magic& bm = Magic::bishopTable[idx], rm = Magic::rookTable[idx];
		Bitboard bocc = pos.board.getOccupied() & bm.mask, rocc = pos.board.getOccupied() & rm.mask;
		Bitboard moves = (bm.ptr[transform(bocc, bm.magic, bm.shift)] |
											rm.ptr[transform(rocc, rm.magic, rm.shift)]) &~own;
		addFromBitboard(idx, moves, pos, moveVec, opponent, turn, nQueen);
	}
}

vector<Move> legalMoves(Position &p) {
	vector<Move> x;
	generateMoves(p, x);
	for (auto i = x.begin(); i != x.end();) {
		if (p.makeMove(*i)) {
			p.unmakeMove(*i);
			i++;
		}
		else {
			x.erase(i);
		}
	}
	return x;
}
