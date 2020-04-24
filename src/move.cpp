#include <string>
#include "move.h"
using std::string;

string indexToCordinate(unsigned int i) {
  string ret;
  char file = (i % 8) + 'a';
  char rank = (i / 8) + '1';
  ret += file;
  ret += rank;
  return ret;
}

string Move::notation() {
  string ret;
	if (piece != nPawn) {

	}
  ret = indexToCordinate(getFrom());
  //ret += ((isCapture()) ? 'x' : '-');
  ret += indexToCordinate(getTo());
  return ret;
}
