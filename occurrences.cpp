#include <iostream>
#include "occurrences.h"
using namespace std;

void Occurrences::count() {
  if ( in.good() ) {
    string buffer;
    int_for_char index;
    int_type number_of_occurrences;
    char znak;

    fill_ascii_table_with_zeros();

    if (mode == code) { // txt -> binary
      while ( in >> buffer ) {
        for (string::iterator it = buffer.begin(); it != buffer.end(); it++) {
          index = static_cast<int_for_char>(*it);
          if (index < 0 || index > ASCII_SIZE) {} // TODO! error. Char not from ascii scope.
          by_ascii[ index ]++;
        }
      }
    }
    else {
      for (int i = 0; i <= ASCII_SIZE; i++) { // binary -> txt
        in >> number_of_occurrences;
        by_ascii[i] = number_of_occurrences;
      }
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
    // thanks to the line above there is no need to sort leaves before running Huffman's algorithm! :)

  return by_occurrences;
}
