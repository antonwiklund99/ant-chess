#ifndef BITBOARDS_GUARD
#define BITBOARDS_GUARD

#include "enums.h"

struct Magic {
  static Magic rookTable[64];
  static Magic bishopTable[64];
  static void initMagic();
  Bitboard ptr[4096];
  Bitboard mask;
  Bitboard magic;
  int shift;

  Magic(Bitboard used[4096], Bitboard ms, Bitboard mg, int s)
      : mask(ms), magic(mg), shift(s) {
    for (int i = 0; i < 4096; i++) {
      ptr[i] = used[i];
    }
  }
  Magic() {}
};

namespace Bitboards {
void initEasyBitboards();

extern Bitboard knight[64];
extern Bitboard king[64];
}; // namespace Bitboards

int transform(Bitboard, Bitboard, int);
#endif
