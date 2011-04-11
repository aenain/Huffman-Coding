#include <iostream>
#include <bitset>
#include "translation.h"
using namespace std;

void Translation::fill_with_zeros(char tab[], const unsigned int length) {
  for(int i = 0; i < length; i++)
    tab[i] = '\0';
}

void Translation::match_and_erase(string & decode_buffer, const chars_by_code & codes) {
  string look_for;
  chars_by_code::const_iterator result;
  static long_int_type decoded_bits = 0;

  for (string::iterator it = decode_buffer.begin(); it != decode_buffer.end(); it++) {
    if (look_for.empty() && it != decode_buffer.begin()) it = decode_buffer.begin();
    if (decode_buffer.empty()) break; // if we removed last char there is nothing left.

    look_for += *it;

    if ( (result = codes.find(look_for)) != codes.end() ) {
      decoded_bits += look_for.length();
      decoded_buffer += result -> second;
      look_for.clear();
      decode_buffer.erase( decode_buffer.begin(), ++it );

      if (decoded_bits >= how_many_bits || decoded_buffer.length() > 1024) {
        out << decoded_buffer;
        decoded_buffer.clear();

        if (decoded_bits >= how_many_bits) {
          out.close();
          state = terminated;
          break;
        }
      }
    }
  }
}

unsigned int Translation::match_and_erase(string & encode_buffer, const codes_by_char & codes, bool force_end) {
  static long_int_type encoded_bits = 0;
  static unsigned int bits_left_in_current_byte = 8;
  static bitset<8> current_byte;
  static unsigned int index = 0;
  static string eight_chars;
  
  for (string::iterator it = encode_buffer.begin(); it != encode_buffer.end(); it++) {
    eight_chars += *it;

    if (! bits_left_in_current_byte)
      bits_left_in_current_byte = 8;

    bits_left_in_current_byte--;

    if (*it == '1')
      current_byte.set(bits_left_in_current_byte);

    encoded_bits++;

    if (eight_chars.length() == 8) {
      eight_chars.clear();
      bits_left_in_current_byte = 0;
      cout << "byte(" << index << ") " << current_byte.to_string() << endl;
      //encoded_buffer[index++] = static_cast<unsigned char>(current_byte.to_ulong());
      index++;
      out << static_cast<unsigned char>( current_byte.to_ulong() );
      current_byte.reset();
    }
/*
    if (index >= 1024) {
      out << encoded_buffer;
      index = 0;
    }
*/
  }

  if (force_end && bits_left_in_current_byte) {
    //encoded_buffer[index++] = static_cast<unsigned char>(current_byte.to_ulong());
    //out << encoded_buffer;
    cout << "byte(" << index << ") " << current_byte.to_string() << endl;
    out << static_cast<unsigned char>(current_byte.to_ulong());    
  }

  encode_buffer.clear();

  how_many_bits = encoded_bits;
  return bits_left_in_current_byte;
}

void Translation::translate(const codes_by_char & codes, const int_type by_ascii[]) { // txt -> binary
  long_int_type position_in_binary;
  state = in_progress;

  if ( out.good() && in.good() ) {
    for (int i = 0; i <= Occurrences::ASCII_SIZE; i++) // ascii table with occurrences to binary.
      out << by_ascii[i] << ' ';

    position_in_binary = out.tellp();
    out << position_in_binary << ' ';

    char input_buffer[1024];
    string encode_buffer;
    bitset<8> bits;

    fill_with_zeros(input_buffer, 1024);
    in.read( input_buffer, 1024 );

    long_int_type number_of_char = 0;
    unsigned int bits_left_in_current_byte = 0;
    long_int_type number_of_loaded_chars = 1024;
    bool immediate_break = false;
    codes_by_char::const_iterator result;
    
    while (! immediate_break) {
      for (int i = 0; i < number_of_loaded_chars; i++) {
        if (input_buffer[i] == '\0') {// eof
          immediate_break = true;
          break;
        }

        if ((result = codes.find(input_buffer[i])) != codes.end())
          encode_buffer += result -> second; // dodanie do bufora kodu danego znaku.

        bits_left_in_current_byte = match_and_erase(encode_buffer, codes);          
      }

      if (number_of_char >= number_of_loaded_chars) {
        number_of_char = 0;
        fill_with_zeros(input_buffer, 1024);
        in >> input_buffer;
      }
    }

    if (bits_left_in_current_byte) {
      match_and_erase(encode_buffer, codes, true); // forces completion last byte with garbage :)
      out.seekp(position_in_binary);
      out << how_many_bits;
    }
    cout << "kodowanie: " << how_many_bits << endl;
  }

  in.close();
  out.close();
}

void Translation::translate(const chars_by_code & codes, long_int_type & position_in_binary) { // binary -> txt
  state = in_progress;

  if ( in.good() ) {
    char input_buffer[1024];
    unsigned char current_byte;
    string decode_buffer;
    bitset<8> bits;

    in.seekg(position_in_binary); // move after table of ascii (the current value will be number of bits to read)
    in >> how_many_bits; // how many bits are valid? (rest is a garbage)
    how_many_bits = 183; // TODO! ZAHARDCODE'owane!!
    cout << "dekodowanie: " << how_many_bits << endl;

    position_in_binary = in.tellg();
    position_in_binary++;
    in.seekg(position_in_binary);

    in.read( input_buffer, 1024 );
    long_int_type number_of_loaded_bytes = 1024;

    long_int_type number_of_bit = 0;
    long_int_type number_of_byte = 0;
    unsigned int count_divisions = 0;

    while (number_of_bit <= how_many_bits) {
      bits.reset();
      current_byte = static_cast<unsigned char>( input_buffer[number_of_byte % number_of_loaded_bytes] );
      count_divisions = 0;
      while (count_divisions < 8) {
        if (current_byte % 2)
          bits.set(count_divisions);

        current_byte /= 2;
        number_of_bit++;
        count_divisions++;
      }

      decode_buffer += bits.to_string();
      cout << "byte(" << number_of_byte << ") " << bits.to_string() << endl;
      match_and_erase(decode_buffer, codes);

      if (state == terminated) break;

      number_of_byte++;
      if (number_of_byte >= number_of_loaded_bytes) {
        number_of_byte = 0;
        in >> input_buffer; // does it really work?
      }
    }
  }

  in.close();
}
