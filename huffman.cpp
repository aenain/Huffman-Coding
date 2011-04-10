#include <iostream>
#include <string>
#include "additionals.h"
using namespace std;

// argv[0] - nazwa programu
// argv[1] - [-c|-d] opcje: (c)oding lub (d)ecoding
// argv[2] - źródło translacji (w przypadku kodowania plik *.txt)
// argv[3] - cel translacji (w przypadku dekodowania plik *.txt)

int main(int argc, char * argv[]) {
  if (argc == 4) {
    string code_option("-c"), decode_option("-d");
    enum Mode { code, decode };
    Mode mode;

    if (argv[1] == code_option) mode = code;
    else if (argv[1] == decode_option) mode = decode;
    else {} // TODO! error. Some weird mode?
  }
  else
    cout << "Wrong number of arguments." << endl;
}
