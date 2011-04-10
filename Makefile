huffman: additionals.o huffman.cpp
	g++ -O2 additionals.o huffman.cpp -o huffman

additionals.o: additionals.h additionals.cpp
	g++ -O2 -c additionals.cpp
