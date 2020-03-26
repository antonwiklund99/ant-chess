#include <iostream>
#include <string>
#include "move.h"
using std::string;

string Move::notation() {
  string ret;
  ret = indexToCordinate(getFrom());
  ret += ((isCapture()) ? 'x' : '-');
  ret += indexToCordinate(getTo());
  return ret;
}

string indexToCordinate(unsigned int i) {
  string ret;
  char file = (i % 8) + 'a';
  char rank = (i / 8 + 1) + '0';
  ret += file;
  ret += rank;
  return ret;
}
