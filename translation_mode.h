#ifndef MODE_H
#define MODE_H
#include <iostream>
#include <fstream>
#include <string>
#include "additionals.h"
using namespace std;

class TranslationMode {
  public:
    enum Mode { code, decode };
    Mode mode;
    ios::openmode source, destination;
    void set_mode(const ios::openmode openmode);
    void set_mode(const char * option);

    TranslationMode() : code_option("-c"), decode_option("-d") {};


  private:
    string code_option;
    string decode_option;
};

#endif
