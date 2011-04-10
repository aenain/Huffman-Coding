#include <iostream>
#include "translation.h"
using namespace std;

// argv[0] - nazwa programu
// argv[1] - [-c|-d] opcje: (c)oding lub (d)ecoding
// argv[2] - zrodlo translacji (w przypadku kodowania plik *.txt)
// argv[3] - cel translacji (w przypadku dekodowania plik *.txt)
// translator obsluguje tylko znaki alfabetu lacinskiego!

int main(int argc, char * argv[]) {
  if (argc == 4) {
    codes_by_char codes;
    chars_by_code chars;

    TranslationMode translation_mode;
    translation_mode.set_mode( argv[1] );

    Occurrences occurrences(argv[2], translation_mode.source);
    occurrences.count();

    HuffmanCoding huffman_coding( occurrences.as_map() );
    huffman_coding.build_tree();
    huffman_coding.to_map();

    //Translation translation( argv[2], argv[3], translation_mode.source, translation_mode.destination );
    Translation translation( argv[2], argv[3] ); // test dla plików txt

    if (translation_mode.mode == TranslationMode::code)
      translation.translate( huffman_coding.codes, occurrences.by_ascii );

    else
      translation.translate( huffman_coding.chars );

  }
  else
    cout << "Wrong number of arguments." << endl;
}
