#ifndef INCLUDED_BOARD_HPP
#define INCLUDED_BOARD_HPP

#include <memory>
#include <vector>

class Item;

class Board
{
public:
  Board (unsigned int width, unsigned int height);
  ~Board ();
  
private:
  std::vector<std::unique_ptr<Item>> items;
  unsigned int width;
  unsigned int height;
};

#endif /* INCLUDED_BOARD_HPP */
