huffman: additionals.o translation.o huffman.cpp
	g++ -O2 additionals.o translation_mode.o occurrences.o huffman_coding.o translation.o huffman.cpp -o huffman

translation.o: huffman_coding.o translation.h translation.cpp
	g++ -O2 -c translation.cpp

huffman_coding.o: occurrences.o huffman_coding.h huffman_coding.cpp
	g++ -O2 -c huffman_coding.cpp

occurrences.o: translation_mode.o occurrences.h occurrences.cpp
	g++ -O2 -c occurrences.cpp

translation_mode.o: additionals.o translation_mode.h translation_mode.cpp
	g++ -O2 -c translation_mode.cpp

additionals.o: additionals.h additionals.cpp
	g++ -O2 -c additionals.cpp
