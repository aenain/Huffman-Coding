#ifndef TRANSLATION_H
#define TRANSLATION_H
#include <iostream>
#include "huffman_coding.h"

class Translation : public TranslationMode {
  public:
    void translate(const codes_by_char & codes, const int_type by_ascii[]); // txt -> binary
    void translate(const chars_by_code & codes); // binary -> txt
    Translation(const string & source_filename, const string & destination_filename,
                ios::openmode source_mode = ios::in, ios::openmode destination_mode = ios::out) :
                  in( source_filename.c_str(), source_mode ), out( destination_filename.c_str(), destination_mode ) { set_mode( source_mode ); };

  private:
    ifstream in;
    ofstream out;
};

#endif
