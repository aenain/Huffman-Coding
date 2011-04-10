#include <iostream>
#include "translation.h"
using namespace std;

void Translation::translate(const codes_by_char & codes, const int_type by_ascii[]) {
  if ( out.good() && in.good() ) {
    string buffer; // testowo do txt

    for (int i = 0; i <= Occurrences::ASCII_SIZE; i++)
      out << by_ascii[i] << ',';

    while ( in >> buffer )
      for (string::iterator it = buffer.begin(); it != buffer.end(); it++)
        out << codes.find(*it) -> second;
  }

  in.close();
  out.close();
}

void Translation::translate(const chars_by_code & codes) {
  if ( out.good() && in.good() ) {
    string buffer;

    
  }

  in.close();
  out.close();
}
