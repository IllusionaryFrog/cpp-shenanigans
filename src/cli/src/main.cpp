#include "hashmap.h"

#include <iostream>
#include <string>

using namespace shenanigans;

int main() {
  hashmap<char,int> map(26 + 1);

  std::cout << "(" << map.size() << ", " << map.capacity() << ")" << std::endl;

  for (int i=0; i<26; i++) map.insert('a' + i, 0);
  map.insert(' ', 0);

  std::string text = "just some random text";

  for (const char& letter : text) map.get(letter)++;

  for (int i=0; i<26; i++) {
    char letter = i + 'a';
    int count = map.get(letter);
    if (count != 0) std::cout << "(" << letter << ": " << count << ") ";
  }

  std::cout << "\n(" << map.size() << ", " << map.capacity() << ")" << std::endl;

  map.clear();

  std::cout << "\n(" << map.size() << ", " << map.capacity() << ")" << std::endl;

  for (int i=0; i<26; i++) map.insert('a' + i, 0);
  map.insert(' ', 0);

  for (const char& letter : text) map.get(letter)++;
  for (const char& letter : text) map.get(letter)++;

  for (int i=0; i<26; i++) {
    char letter = i + 'a';
    int count = map.get(letter);
    if (count != 0) std::cout << "(" << letter << ": " << count << ") ";
  }

  std::cout << "\n(" << map.size() << ", " << map.capacity() << ")" << std::endl;

  map.insert('\n', 0);

  std::cout << "\n(" << map.size() << ", " << map.capacity() << ")" << std::endl;

  map.insert(' ', 0);

  return 0;
}
