#include <string>
#include <SFML/System/Vector2.hpp>

#include "Item.hpp"

Item::Item (std::string name) : 
  name(name)
{}

Item::~Item ()
{}

std::string Item::getName () const
{
  return name;
}

