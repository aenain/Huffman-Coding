#include <iostream>
#include "translation_mode.h"
using namespace std;

void TranslationMode::set_mode(const ios::openmode openmode) {
  mode = (openmode == ios::in) ? code : decode;
};

void TranslationMode::set_mode(const char * option) {
  if (option == code_option) {
    mode = code;
    source = ios::in;
    destination = ios::binary;
  }
  else if (option == decode_option) {
    mode = decode;
    source = ios::binary;
    destination = ios::out;
  }
  else {} // TODO! będzie lipa...
};
