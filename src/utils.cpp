#include <iostream>
#include "utils.h"
#include "enums.h"
#include <string>
#include <vector>
using std::vector; using std::string;

constexpr Bitboard debruijn64 = Bitboard(0x03f79d71b4cb0a89);
constexpr int index64[64] = {
                             0,  1, 48,  2, 57, 49, 28,  3,
                             61, 58, 50, 42, 38, 29, 17,  4,
                             62, 55, 59, 36, 53, 51, 43, 22,
                             45, 39, 33, 30, 24, 18, 12,  5,
                             63, 47, 56, 27, 60, 41, 37, 16,
                             54, 35, 52, 21, 44, 32, 23, 11,
                             46, 26, 40, 15, 34, 20, 31, 10,
                             25, 14, 19,  9, 13,  8,  7,  6
};

int bitScanForward(Bitboard b) {
  return index64[((b & -b) * debruijn64) >> 58];
}

int popFirstBit(Bitboard& b) {
  int j = bitScanForward(b);
  b &= b - 1;
  return j;
}

int countOnes(Bitboard b) {
  int n = b ? 1 : 0;
  while (b &= b - 1) {n++;}
  return n;
}

void printBitboardRows(Bitboard b) {
  Bitboard mask = 1;
  for (int i = 0; i < 64; i++) {
    std::cout << ((mask & b) ? 1 : 0);
    mask <<= 1;
    if ((i + 1) % 8 == 0)
      std::cout << "\n";
  }
  std::cout << std::endl;
}

void split(string s, vector<string>& res, char delim) {
	res.clear();
	string b = "";
	for (size_t i = 0; i != s.size(); i++) {
		if (s[i] == delim && b != "") {
			res.push_back(b);
			b = "";
		}
		else {
			b += s[i];
		}
	}
	if (!b.empty()) res.push_back(b);
}

Bitboard northOne(Bitboard b) { return b << 8; }
Bitboard southOne(Bitboard b) { return b >> 8; }

Bitboard westOne(Bitboard b) { return (b & notAFile) >> 1; }
Bitboard southWestOne(Bitboard b) { return (b & notAFile) >> 9; }
Bitboard northWestOne(Bitboard b) { return (b & notAFile) << 7; }

Bitboard eastOne(Bitboard b) { return (b & notHFile) << 1; }
Bitboard southEastOne(Bitboard b) { return (b & notHFile) >> 7; }
Bitboard northEastOne(Bitboard b) { return (b & notHFile) << 9; }
