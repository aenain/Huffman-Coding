#ifndef OCCURRENCES_H
#define OCCURRENCES_H
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include "translation_mode.h"
using namespace std;

typedef unsigned short int int_for_char;
typedef unsigned long int int_type;
typedef unsigned long long int long_int_type;
typedef multimap<int_type, char> map_by_occurrences;

class Occurrences : public TranslationMode {
  public:
    static const int_for_char ASCII_SIZE = 127;
    int_type by_ascii[ASCII_SIZE + 1]; // tab which contains occurrences for character given by ascii code.
    long_int_type position_in_binary; // position in binary file after reading table of occurrences.
    map_by_occurrences by_occurrences; // occurrences are keys and chars are values.
    void count();
    map_by_occurrences as_map(); // changes by_ascii to by_occurrences and returns reference to this multimap
    Occurrences(const string & filename, ios::openmode source_mode = ios::in) : in( filename.c_str(), source_mode ) { set_mode(source_mode); };

  private:
    ifstream in;
    void fill_ascii_table_with_zeros();
};

#endif
