#include "piece.h"
#include <cctype>
#include <string>
#include <stdexcept>
#include <algorithm>
using std::domain_error;
using std::string;
using std::find;

Piece::Piece(char c, int ypos, int xpos) {
	string validLetters = "KQBNRP";
	(find(validLetters.begin(), validLetters.end(), toupper(c)) == validLetters.end()) ?
		throw domain_error("Piece symbol is not valid") : NULL ;
	symbol = c;

	!(ypos >= 0 && ypos < 8) ? throw domain_error("Piece y is not within range 0-7") : NULL;
	!(xpos >= 0 && xpos < 8) ? throw domain_error("Piece x is not within range 0-7") : NULL;
	y = ypos;
	x = xpos;
	color = isupper(symbol) ? 'b' : 'w';
}

bool operator== (const Piece& lhs, const Piece& rhs) {
	return (tolower(lhs.symbol) == tolower(rhs.symbol) && lhs.y == rhs.y && lhs.x == rhs.x);
}

bool operator< (const Piece& lhs, const Piece& rhs) {
	return (pieceValue(lhs.symbol) < pieceValue(rhs.symbol));
}

int pieceValue(char c) {
	switch(tolower(c)) {
	case 'p' : return 1;
	case 'n' : return 2;
	case 'b' : return 3;
	case 'r' : return 5;
	case 'q' : return 9;
	case 'k' : return 10;
	default  : break;
	}
	return -1;
}
