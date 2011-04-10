#include <iostream>
#include "huffman_coding.h"
using namespace std;

// Zobacz: http://pl.wikipedia.org/wiki/Kodowanie_Huffmana - Algorytm statycznego kodowania Huffmana
void HuffmanCoding::build_tree() {
  map_to_nodes();

  while ( nodes.size() > 1 ) {
    Node *first  = new Node; // to create new nodes - reserve memory and so on.
    Node *second = new Node;
    Node *root   = new Node;

    *first = nodes.front();
    nodes.erase( nodes.begin() );

    *second = nodes.front();
    nodes.erase( nodes.begin() );

    first  -> parent = root;
    second -> parent = root;

    root -> left = first;
    root -> right = second;
    root -> occurrences = first -> occurrences + second -> occurrences;

    nodes.insert( nodes.begin(), *root );

    sort();
  }

  tree = *( nodes.begin() );
}

void HuffmanCoding::map_to_nodes() {
  Node node;

  node.parent = node.left = node.right = NULL;

  for (map_by_occurrences::iterator it = by_occurrences.begin(); it != by_occurrences.end(); it++) {
    if (it -> first == 0) continue; // it has no occurrences

    node.occurrences = it -> first;
    node.symbol = it -> second;

    nodes.push_back(node);
  }
}


void HuffmanCoding::to_map() {
  code = "";
  build_code(&tree);

  // TODO! make this as an option for debugging :)
  for (codes_by_char::iterator it = codes.begin(); it != codes.end(); it++)
    cout << it -> first << ": " << it -> second << endl;
}

void HuffmanCoding::build_code(Node *node) {
  if (! node -> left && ! node -> right) {// current node is a leaf
    codes.insert( pair<char, string>(node -> symbol, code) ); // txt -> binary
    chars.insert( pair<string, char>(code, node -> symbol) );
  }
  else {
    if (node -> left) {
      code += '0';
      build_code( node -> left );
    }
    if (node -> right) {
      code += '1';
      build_code( node -> right );
    }
  }
  if (! code.empty())
    code.erase( code.length() - 1, code.length() );
  else {} // TODO! what to do if code is empty?
}

void HuffmanCoding::sort() {
  Node node;

  if (nodes.size() > 1) {
    for (int i = 1; i < nodes.size(); i++) {
      node = nodes[i];
      int j = i - 1;

      while (j >= 0 && ( nodes[j].occurrences > node.occurrences || (nodes[j].occurrences == node.occurrences && symbol( &(nodes[j]) ) > symbol( &node )) )) {
        nodes[j + 1] = nodes[j];
        j = j - 1;
      }

      nodes[j + 1] = node;
    }
  }
}

char HuffmanCoding::symbol(Node * node) {
  Node *current = node;

  while (current) {
    if (! current -> left) return current -> symbol;
    current = current -> left;
  }

  return NULL;
}
