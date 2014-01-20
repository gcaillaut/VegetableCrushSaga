#include <SFML/System/Vector2.hpp>

#include "Board.hpp"
#include "BasicItem.hpp"

BasicItem::BasicItem (std::string name) :
  Item(name)
{}

BasicItem::~BasicItem ()
{}

void BasicItem::update (Board & board, sf::Vector2f pos)
{

}
