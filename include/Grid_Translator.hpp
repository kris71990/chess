#include <map>

#ifndef GRID_TRANSLATOR_H
#define GRID_TRANSLATOR_H

namespace Grid_Translator {
  const std::map<int, char> to_letter = 
    {
      { 0, 'a' },
      { 1, 'b' },
      { 2, 'c' },
      { 3, 'd' },
      { 4, 'e' },
      { 5, 'f' },
      { 6, 'g' },
      { 7, 'h' },
    };

  const std::map<char, int> to_index =
    {
      { 'a', 0 },
      { 'b', 1 },
      { 'c', 2 },
      { 'd', 3 },
      { 'e', 4 },
      { 'f', 5 },
      { 'g', 6 },
      { 'h', 7 },
    };
}

#endif