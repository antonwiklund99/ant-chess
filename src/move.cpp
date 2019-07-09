#include "move.h"
#include "board.h"
#include <string>
#include <cctype>
#include <algorithm>
#include <stdexcept>
using std::string;
using std::islower;
using std::find;
using std::tolower;
using std::to_string;
using std::domain_error;

// Move constructor from long algebraic chess move notation
// format = [piece, except pawn][cordinate from][x if capture][cordinate to]
Move::Move(string s, char turn) {
	bool is_pawn = islower(s[0]);
	capture = find(s.begin(), s.end(), 'x') != s.end();
	int index = 1;
	char p;

	if (is_pawn) {
		index = 0;
		p = 'P';
	}
	else {
		p = s[0];
	}

	piece = (turn == 'w') ? tolower(p) : p;
	from_x = letter_to_index(s[index]);
	from_y = s[index + 1] - '0';
	to_x = letter_to_index(s[index + 3]);
	to_y = s[index + 4] - '0';

	// Run checks on values
	!(from_x >= 0 && from_x < 8) ? throw domain_error("from_x is not withing range 0-7") : NULL ;
	!(from_y >= 0 && from_y < 8) ? throw domain_error("from_y is not withing range 0-7") : NULL ;
	!(to_x >= 0 && to_x < 8) ? throw domain_error("to_x is not withing range 0-7") : NULL ;
	!(to_y >= 0 && to_y < 8) ? throw domain_error("to_y is not withing range 0-7") : NULL ;
	string validLetters = "KQBNRP";
	(find(validLetters.begin(), validLetters.end(), toupper(piece)) == validLetters.end()) ?
		throw domain_error("Piece symbol is not valid") : NULL ;
}

// Move constructor given all values
Move::Move(int fx, int fy, int tx, int ty, bool x, char p):
		from_x(fx), from_y(fy), to_x(tx), to_y(ty), capture(x), piece(p) {
	// Run checks on values
	!(from_x >= 0 && from_x < 8) ? throw domain_error("from_x is not withing range 0-7") : NULL ;
	!(from_y >= 0 && from_y < 8) ? throw domain_error("from_y is not withing range 0-7") : NULL ;
	!(to_x >= 0 && to_x < 8) ? throw domain_error("to_x is not withing range 0-7") : NULL ;
	!(to_y >= 0 && to_y < 8) ? throw domain_error("to_y is not withing range 0-7") : NULL ;
	string validLetters = "KQBNRP";
	(find(validLetters.begin(), validLetters.end(), toupper(piece)) == validLetters.end()) ?
		throw domain_error("Piece symbol is not valid") : NULL ;
}

bool operator== (const Move& lhs, const Move& rhs) {
	return (lhs.from_x == rhs.from_x && lhs.to_x == rhs.to_x && lhs.from_y == rhs.from_y &&
					lhs.to_y == rhs.to_y && lhs.piece == rhs.piece && lhs.capture == rhs.capture);
}

string Move::notation() {
	string out;
	if (toupper(piece) != 'P') {
		out.push_back(toupper(piece));
	}
	out.push_back(index_to_letter(from_x));
	out += to_string(from_y);
	out.push_back((capture) ? 'x' : '-');
	out.push_back(index_to_letter(to_x));
	out += to_string(to_y);
	return out;
}

int letter_to_index(char c) {
	switch(c) {
	case 'a': return 0;
	case 'b': return 1;
	case 'c': return 2;
	case 'd': return 3;
	case 'e': return 4;
	case 'f': return 5;
	case 'g': return 6;
	case 'h': return 7;
	default: throw domain_error("Letter is not a valid index");
	}
}

char index_to_letter(int i) {
	switch(i) {
	case 0: return 'a';
	case 1: return 'b';
	case 2: return 'c';
	case 3: return 'd';
	case 4: return 'e';
	case 5: return 'f';
	case 6: return 'g';
	case 7: return 'h';
	default: throw domain_error("Index is not a valid number");
	}
}
