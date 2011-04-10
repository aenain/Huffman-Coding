huffman: additionals.o occurrences.o huffman.cpp
	g++ -O2 additionals.o occurrences.o huffman.cpp -o huffman

occurrences.o: occurrences.h occurrences.cpp
	g++ -O2 -c occurrences.cpp

additionals.o: additionals.h additionals.cpp
	g++ -O2 -c additionals.cpp
