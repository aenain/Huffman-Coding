// http://pastebin.com/ErnPg5tV

#include <iostream>
#include <vector>
#include <string>

bool in_array(const char element, const std::vector<char> elements) {
  int max = elements.size();

  if (max == 0) return false;

  for (int i = 0; i < max; i++)
    if (elements[i] == element)
      return true;

  return false;
}

bool operator==(const char* c_text, std::string text) {
  std::string::iterator s = text.begin();

  while(*c_text != '\0' && s != text.end()) {
    if (*c_text != *s) return false;
    c_text++;
    s++;
  }
  return true;
}
