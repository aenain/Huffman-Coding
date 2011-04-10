#include <iostream>
#include "occurrences.h"
using namespace std;

void Occurrences::count() {
  if ( in.good() ) {
    string buffer;
    int_for_char index;

    fill_ascii_table_with_zeros();

    while (in >> buffer)
      for (string::iterator it = buffer.begin(); it != buffer.end(); it++) {
        index = static_cast<int_for_char>(*it);
        if (index < 0 || index > ASCII_SIZE) {} // TODO! error. Char not from ascii scope.
        by_ascii[ index ]++;
      }

  }

  in.close();
}

void Occurrences::fill_ascii_table_with_zeros() {
  for(int i = 0; i <= ASCII_SIZE; i++)
    by_ascii[i] = 0;
}

map_by_occurrences Occurrences::as_map() {
  // by_ascii -> by_occurrences
  for (int i = 0; i <= ASCII_SIZE; i++)
    by_occurrences.insert( pair<int_type, char>(by_ascii[i], static_cast<char>(i)) );

  return by_occurrences;
}
