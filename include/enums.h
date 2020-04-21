#ifndef ENUM_GUARD
#define ENUM_GUARD

#include <cstdint>

typedef uint64_t Bitboard;

enum Color {
            cWhite = 0,
            cBlack = 1
};

// Represents each bitboard type in board class
enum Piece {
                nWhite,
                nBlack,
                nPawn,
                nKnight,
                nBishop,
                nRook,
                nQueen,
                nKing,
                nEmpty
};

constexpr Bitboard RANK_1 = 0x00000000000000ff;
constexpr Bitboard RANK_2 = 0x000000000000ff00;
constexpr Bitboard RANK_3 = 0x0000000000ff0000;
constexpr Bitboard RANK_4 = 0x00000000ff000000;
constexpr Bitboard RANK_5 = 0x000000ff00000000;
constexpr Bitboard RANK_6 = 0x0000ff0000000000;
constexpr Bitboard RANK_7 = 0x00ff000000000000;
constexpr Bitboard RANK_8 = 0xff00000000000000;

constexpr Bitboard notAFile = 0xfefefefefefefefe; // ~0x0101010101010101
constexpr Bitboard notBFile = (notAFile << 1) + 1;
constexpr Bitboard notCFile = (notBFile << 1) + 1;
constexpr Bitboard notDFile = (notCFile << 1) + 1;
constexpr Bitboard notEFile = (notDFile << 1) + 1;
constexpr Bitboard notFFile = (notEFile << 1) + 1;
constexpr Bitboard notGFile = (notFFile << 1) + 1;
constexpr Bitboard notHFile = 0x7f7f7f7f7f7f7f7f; // ~0x8080808080808080
#endif
