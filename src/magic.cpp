#include "magic.h"
#include "utils.h"
#include <stdexcept>
#include <iostream>

Bitboard randomBitboard() {
  Bitboard u1, u2, u3, u4;
  u1 = (Bitboard)(random()) & 0xFFFF; u2 = (Bitboard)(random()) & 0xFFFF;
  u3 = (Bitboard)(random()) & 0xFFFF; u4 = (Bitboard)(random()) & 0xFFFF;
  return u1 | (u2 << 16) | (u3 << 32) | (u4 << 48);
}

Bitboard randomBitboardFewBits() {
  return randomBitboard() & randomBitboard() & randomBitboard();
}

Bitboard rmask(int sq) {
  Bitboard ret = 0;
  int rank = sq/8, file = sq % 8;
  for (int r = rank + 1; r < 7; r++) ret |= (1ULL << (file + r*8));
  for (int r = rank - 1; r > 0; r--) ret |= (1ULL << (file + r*8));
  for (int f = file + 1; f < 7; f++) ret |= (1ULL << (f + rank*8));
  for (int f = file - 1; f > 0; f--) ret |= (1ULL << (f + rank*8));
  return ret;
}

Bitboard bmask(int sq) {
  Bitboard ret = 0;
  int rank = sq/8, file = sq % 8, r, f;
  for (r = rank + 1, f = file + 1; r <= 6 && f <= 6; r++, f++) ret |= (1ULL << (f + r*8));
  for (r = rank + 1, f = file - 1; r <= 6 && f >= 1; r++, f--) ret |= (1ULL << (f + r*8));
  for (r = rank - 1, f = file + 1; r >= 1 && f <= 6; r--, f++) ret |= (1ULL << (f + r*8));
  for (r = rank - 1, f = file - 1; r >= 1 && f >= 1; r--, f--) ret |= (1ULL << (f + r*8));
  return ret;
}

Bitboard rookAttacks(int sq, Bitboard block) {
  Bitboard result = 0ULL;
  int rank = sq/8, file = sq % 8, r, f;
  for (r = rank + 1; r <= 7; r++) {
    result |= (1ULL << (r*8 + file));
    if (block & (1ULL << (r*8 + file))) break;
  }
  for (r = rank - 1; r >= 0; r--) {
    result |= (1ULL << (r*8 + file));
    if (block & (1ULL << (r*8 + file))) break;
  }
  for (f = file + 1; f <= 7; f++) {
    result |= (1ULL << (f + rank*8));
    if (block & (1ULL << (f + rank*8))) break;
  }
  for(f = file - 1; f >= 0; f--) {
    result |= (1ULL << (f + rank*8));
    if (block & (1ULL << (f + rank*8))) break;
  }
  return result;
}

Bitboard bishopAttacks(int sq, Bitboard block) {
  Bitboard result = 0ULL;
  int rank = sq/8, file = sq%8, r, f;
  for (r = rank + 1, f = file + 1; r <= 7 && f <= 7; r++, f++) {
    result |= (1ULL << (f + r*8));
    if (block & (1ULL << (f + r * 8))) break;
  }
  for(r = rank + 1, f = file - 1; r <= 7 && f >= 0; r++, f--) {
    result |= (1ULL << (f + r*8));
    if (block & (1ULL << (f + r * 8))) break;
  }
  for(r = rank - 1, f = file + 1; r >= 0 && f <= 7; r--, f++) {
    result |= (1ULL << (f + r*8));
    if (block & (1ULL << (f + r * 8))) break;
  }
  for(r = rank - 1, f = file - 1; r >= 0 && f >= 0; r--, f--) {
    result |= (1ULL << (f + r*8));
    if (block & (1ULL << (f + r * 8))) break;
  }
  return result;
}

// Returns a bit combination from mask with a correct amount of bits (given by index)
// up to totalBits
Bitboard indexToBitboard(int index, int totalBits, Bitboard m) {
  int j;
  Bitboard ret = 0;
  for (int i = 0; i < totalBits; i++) {
    j = popFirstBit(m);
    if ((1 << i) & index) ret |= (1ULL << j);
  }
  return ret;
}

int transform(Bitboard b, Bitboard magic, int bits) {
  return (int)((b * magic) >> (64 - bits));
}

Magic find_magic(int sq, int m, int bishop) {
  // b - all possible block combinations
  // a - all possible attacks from square with b[i] blockers
  Bitboard mask, b[4096], a[4096], used[4096], magic;
  int j, i, fail;
  mask = bishop ? bmask(sq) : rmask(sq);
  int n = countOnes(mask);

  for(int i = 0; i < (1 << n); i++) {
    b[i] = indexToBitboard(i, n, mask);
    a[i] = bishop ? bishopAttacks(sq, b[i]) : rookAttacks(sq, b[i]);
  }

  for(int k = 0; k < 100000000; k++) {
    magic = randomBitboardFewBits();
    if (countOnes((mask * magic) & 0xFF00000000000000ULL) < 6) continue;
    for (i = 0; i < 4096; i++) used[i] = 0;
    for (i = 0, fail = 0; !fail && i < (1 << n); i++) {
      j = transform(b[i], magic, m);
      if (used[j] == 0ULL) used[j] = a[i];
      else if (used[j] != a[i]) fail = 1;
    }
    if(!fail) {
     return Magic(used, mask, magic, n);
    }
  }
  throw std::runtime_error("Search for magic number failed");
}

constexpr int RBits[64] = {
  12, 11, 11, 11, 11, 11, 11, 12,
  11, 10, 10, 10, 10, 10, 10, 11,
  11, 10, 10, 10, 10, 10, 10, 11,
  11, 10, 10, 10, 10, 10, 10, 11,
  11, 10, 10, 10, 10, 10, 10, 11,
  11, 10, 10, 10, 10, 10, 10, 11,
  11, 10, 10, 10, 10, 10, 10, 11,
  12, 11, 11, 11, 11, 11, 11, 12
};

constexpr int BBits[64] = {
  6, 5, 5, 5, 5, 5, 5, 6,
  5, 5, 5, 5, 5, 5, 5, 5,
  5, 5, 7, 7, 7, 7, 5, 5,
  5, 5, 7, 9, 9, 7, 5, 5,
  5, 5, 7, 9, 9, 7, 5, 5,
  5, 5, 7, 7, 7, 7, 5, 5,
  5, 5, 5, 5, 5, 5, 5, 5,
  6, 5, 5, 5, 5, 5, 5, 6
};


Magic Magic::bishopTable[64];
Magic Magic::rookTable[64];
std::atomic_bool Magic::magicSetUp(false);

// https://www.chessprogramming.org/Looking_for_Magics
void initMagic() {
  for (int sq = 0; sq < 64; sq++) {
    Magic::bishopTable[sq] = find_magic(sq, BBits[sq], true);
    Magic::rookTable[sq] = find_magic(sq, RBits[sq], false);
    //std::cout << "Found magic for " << sq + 1<< "/64" << std::endl;
  }
	Magic::magicSetUp.store(true);
}
