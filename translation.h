#ifndef TRANSLATION_H
#define TRANSLATION_H
#include <iostream>
#include "huffman_coding.h"

class Translation : public TranslationMode {
  public:
    void translate(const codes_by_char & codes, const int_type by_ascii[]); // txt -> binary
    void translate(const chars_by_code & codes, long_int_type & position_in_binary); // binary -> txt
    Translation(const string & source_filename, const string & destination_filename,
                ios::openmode source_mode = ios::in, ios::openmode destination_mode = ios::out) :
                  in( source_filename.c_str(), source_mode ), out( destination_filename.c_str(), destination_mode ) { set_mode( source_mode ); };

  private:
    ifstream in;
    ofstream out;
    long_int_type how_many_bits;
    string decoded_buffer;
    unsigned char encoded_buffer[1024];
    enum State { in_progress, terminated }; // state of (en/de)coding
    State state;
    unsigned int match_and_erase(string & encode_buffer, const codes_by_char & codes, bool force_end = false);
    void match_and_erase(string & decode_buffer, const chars_by_code & codes);
    void fill_with_zeros(char tab[], const unsigned int length);
};

#endif
