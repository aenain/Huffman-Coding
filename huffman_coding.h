#ifndef HUFFMAN_CODING_H
#define HUFFMAN_CODING_H
#include <iostream>
#include "occurrences.h"
using namespace std;

typedef struct Node {
  int_type occurrences;
  char symbol;
  struct Node *parent, *left, *right;
} Node;

typedef vector<Node> Nodes;
typedef map<char, string> codes_by_char; // map of codes for certain chars (for coding)
typedef map<string, char> chars_by_code; // map of chars for certain codes (for decoding)

class HuffmanCoding {
  public:
    codes_by_char codes;
    chars_by_code chars;
    void build_tree();
    void to_map();
    HuffmanCoding(const map_by_occurrences & occurrences) : by_occurrences( occurrences ) {};

  private:
    Node tree; // tree is a root of Huffman's tree
    Nodes nodes; // it contains nodes created from map (occurrences) and then it's used by Huffman's algorithm.
    string code;
    map_by_occurrences by_occurrences;
    void build_code(Node *node);
    void map_to_nodes(); // converts map (occurrences) to vector of nodes.
    void sort(); // insertion sort for nodes used in Huffman's algorithm.
    char symbol(Node * node); // returns recursive symbol (character) of itself or it's deepest left child (only deepest children are leaves and have symbols)
};

#endif
