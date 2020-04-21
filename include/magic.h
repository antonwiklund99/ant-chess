#ifndef MAGIC_GUARD
#define MAGIC_GUARD

#include <atomic>
#include "enums.h"

struct Magic {
  static Magic rookTable[64];
  static Magic bishopTable[64];
	static std::atomic_bool magicSetUp;
  Bitboard ptr[4096];
  Bitboard mask;
  Bitboard magic;
  int shift;

  Magic(Bitboard used[4096], Bitboard ms, Bitboard mg, int s): mask(ms), magic(mg), shift(s) {
    for (int i = 0; i < 4096; i++) {
      ptr[i] = used[i];
    }
  }
  Magic() {}
};

void initMagic();

int countOnes(Bitboard);
int transform(Bitboard, Bitboard, int);
Bitboard rookAttacks(int, Bitboard);
Bitboard bishopAttacks(int, Bitboard);
Bitboard rmask(int);
#endif
