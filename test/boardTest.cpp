#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Chess unit tests
#include "board.h"
#include "magic.h"
#include "move.h"
#include "piece.h"
#include "piecePatterns.h"
#include "position.h"
#include <algorithm>
#include <array>
#include <boost/test/unit_test.hpp>
#include <cctype>
#include <iostream>
#include <vector>

BOOST_AUTO_TEST_SUITE(board_tests)
BOOST_AUTO_TEST_CASE(genMoveTest) {}

BOOST_AUTO_TEST_CASE(isAttackedTest) {
  PiecePatterns::initEasyBitboards();
  initMagic();
  Position p1(Board("rnb1kbnr/ppp1pppp/8/3p4/q7/2P2P2/PP1PP1PP/RNBQKBNR"),
              cWhite, true, true, 1);
  BOOST_CHECK(p1.board.isAttacked(p1.board.getBlackQueen(), cWhite));
  BOOST_CHECK(!p1.board.isAttacked(p1.board.getBlackKing(), cWhite));
  BOOST_CHECK(p1.board.isAttacked(p1.board.getWhiteQueen(), cBlack));
}

BOOST_AUTO_TEST_SUITE_END()
