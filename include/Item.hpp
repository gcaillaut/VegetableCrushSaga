#ifndef INCLUDED_ITEM_HPP
#define INCLUDED_ITEM_HPP

#include <string>

#include <SFML/Graphics/Sprite.hpp>

class Board;
 
class Item : public sf::Sprite
{
public:
  Item(std::string name);
  virtual ~Item ();
  
  virtual void update(Board & board, sf::Vector2f pos) = 0;

  std::string getName () const;

private:
  const std::string name;
};

#endif /* INCLUDED_ITEM_HPP */
