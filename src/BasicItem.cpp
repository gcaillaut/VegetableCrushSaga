#include <SFML/System/Vector2.hpp>

#include "Board.hpp"
#include "BasicItem.hpp"

BasicItem::BasicItem (const std::string &name, const unsigned int points) :
  Item(name, points)
{}

BasicItem::~BasicItem ()
{}

void BasicItem::update (Board & board, sf::Vector2f pos)
{

}
