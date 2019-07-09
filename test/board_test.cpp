#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Chess unit tests
#include <boost/test/unit_test.hpp>
#include <vector>
#include <algorithm>
#include "board.h"
#include "piece.h"
#include "move.h"
#include <array>
#include <cctype>
#include <iostream>
BOOST_AUTO_TEST_SUITE(board_tests)

BOOST_AUTO_TEST_CASE(constructors_test) {
	Board b0;
	BOOST_CHECK_EQUAL(b0.get_next_move(), 'w');
	BOOST_CHECK(!b0.board_is_check());
	BOOST_CHECK(!b0.board_is_checkmate());
	BOOST_CHECK_EQUAL(b0.get_black_pieces().size(), 16);
	std::vector<Piece> bp0 = b0.get_black_pieces();
	std::vector<Piece> wp0 = b0.get_white_pieces();
	std::sort(bp0.begin(), bp0.end());
	std::sort(wp0.begin(), wp0.end());
	for (std::vector<Piece>::size_type i = 0; i != bp0.size(); ++i) {
		BOOST_CHECK(bp0[i].symbol == std::toupper(wp0[i].symbol));
		BOOST_CHECK(bp0[i].x == wp0[i].x);
	}

	std::array<std::array<char, 8>, 8> simpleBoard = {{
																										 {'R','0','0','0','0','R','K','0'},
																										 {'0','0','0','0','B','P','P','0'},
																										 {'B','Q','0','0','P','N','0','P'},
																										 {'P','0','0','P','0','0','0','0'},
																										 {'0','0','p','0','0','0','0','0'},
																										 {'p','p','0','b','0','0','0','0'},
																										 {'0','b','q','n','0','p','p','p'},
																										 {'r','0','0','0','r','0','k','0'}
																										 }};
	Board b1(simpleBoard, 'w');
	BOOST_CHECK_EQUAL(b1.get_next_move(), 'w');
	BOOST_CHECK(!b1.board_is_check());
	BOOST_CHECK(!b1.board_is_checkmate());
	BOOST_CHECK_EQUAL(b1.get_black_pieces().size(), 13);
	BOOST_CHECK_EQUAL(b1.get_white_pieces().size(), 13);


	std::array<std::array<char, 8>, 8> checkedBoard = {{
																										 {'0','r','0','0','0','K','0','0'},
																										 {'0','0','0','0','0','P','0','0'},
																										 {'0','0','0','0','0','0','0','P'},
																										 {'P','0','R','0','0','P','0','0'},
																										 {'p','B','n','0','0','0','0','0'},
																										 {'0','p','0','0','0','r','0','0'},
																										 {'0','0','0','0','0','p','k','p'},
																										 {'0','0','0','0','0','0','0','0'}
																										 }};
	Board b2(checkedBoard, 'b');
	BOOST_CHECK_EQUAL(b2.get_next_move(), 'b');
	BOOST_CHECK_EQUAL(b2.board_is_check(), true);
	BOOST_CHECK(!b2.board_is_checkmate());
	BOOST_CHECK_EQUAL(b2.get_black_pieces().size(), 7);
	BOOST_CHECK_EQUAL(b2.get_white_pieces().size(), 8);

	std::array<std::array<char, 8>, 8> checkmatedBoard = {{
																												 {'0','r','0','0','0','K','0','0'},
																												 {'0','0','0','0','0','P','0','0'},
																												 {'0','0','0','0','0','q','0','P'},
																												 {'P','0','0','0','0','P','0','0'},
																												 {'p','B','n','0','0','0','0','0'},
																												 {'0','p','0','0','0','r','0','0'},
																												 {'0','0','0','0','0','p','k','p'},
																												 {'0','0','0','0','0','0','0','0'}
																												 }};
	Board b3(checkmatedBoard, 'b');
	BOOST_CHECK_EQUAL(b3.board_is_check(), true);
	BOOST_CHECK_EQUAL(b3.board_is_checkmate(), true);
}

BOOST_AUTO_TEST_CASE(CHECKMATE_TEST) {
	std::array<std::array<char, 8>, 8> checkmatedBoard = {{
																												 {'0','r','0','0','0','K','0','0'},
																												 {'0','0','0','0','0','P','0','0'},
																												 {'R','0','0','0','0','q','0','P'},
																												 {'P','0','0','0','0','P','0','0'},
																												 {'p','B','n','0','0','0','0','0'},
																												 {'0','p','0','0','0','r','0','0'},
																												 {'0','0','0','0','0','p','k','p'},
																												 {'0','0','0','0','0','0','0','0'}
																												 }};
	Board b0(checkmatedBoard, 'b');
	auto lg = b0.get_legal_moves();
	BOOST_CHECK(is_checkmate(checkmatedBoard, 'b', lg));
}

BOOST_AUTO_TEST_SUITE_END()
