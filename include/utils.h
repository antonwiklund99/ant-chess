#ifndef UTIL_GUARD
#define UTIL_GUARD

#include "enums.h"
#include "move.h"
#include <string>
#include <vector>

int bitScanForward(Bitboard);
int popFirstBit(Bitboard &);
int countOnes(Bitboard);

Bitboard northOne(Bitboard);
Bitboard southOne(Bitboard);

Bitboard westOne(Bitboard);
Bitboard southWestOne(Bitboard);
Bitboard northWestOne(Bitboard);

Bitboard eastOne(Bitboard);
Bitboard southEastOne(Bitboard);
Bitboard northEastOne(Bitboard);

Bitboard noNoEa(Bitboard b);
Bitboard noEaEa(Bitboard b);
Bitboard soEaEa(Bitboard b);
Bitboard soSoEa(Bitboard b);
Bitboard noNoWe(Bitboard b);
Bitboard noWeWe(Bitboard b);
Bitboard soWeWe(Bitboard b);
Bitboard soSoWe(Bitboard b);

void printBitboardRows(Bitboard);
std::string bitboardToString(Bitboard);
void split(std::string, std::vector<std::string> &, char);
int indexOf(std::vector<Move> &v, const std::string &s);
#endif
