#ifndef INCLUDED_BASICITEM_HPP
#define INCLUDED_BASICITEM_HPP

#include "Item.hpp"

class Board;

class BasicItem : public Item
{
public:
  BasicItem(std::string name);
  virtual ~BasicItem ();

  virtual void update(Board & board, sf::Vector2f pos);

private:
  
};

#endif /* INCLUDED_BASICITEM_HPP */
