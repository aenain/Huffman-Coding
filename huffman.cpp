#include <iostream>
#include <string>
#include "additionals.h"
#include "occurrences.h"
using namespace std;

// argv[0] - nazwa programu
// argv[1] - [-c|-d] opcje: (c)oding lub (d)ecoding
// argv[2] - zrodlo translacji (w przypadku kodowania plik *.txt)
// argv[3] - cel translacji (w przypadku dekodowania plik *.txt)
// translator obsluguje tylko znaki alfabetu lacinskiego!

int main(int argc, char * argv[]) {
  if (argc == 4) {
    string code_option("-c"), decode_option("-d");
    enum Mode { code, decode };
    Mode mode;

    if (argv[1] == code_option) mode = code;
    else if (argv[1] == decode_option) mode = decode;
    else {} // TODO! error. Some weird mode?

    ios::openmode openmode = (mode == decode) ? ios::binary : ios::in;

    Occurrences occurrences(argv[2], openmode);
    occurrences.count();

    //HuffmanCoding huffman_coding( occurrences.as_map() ); // 
    //huffman_coding.build_tree();
    //Translation translation( huffman_coding.as_map(), argv[3] );
    //translation.translate();

  }
  else
    cout << "Wrong number of arguments." << endl;
}
