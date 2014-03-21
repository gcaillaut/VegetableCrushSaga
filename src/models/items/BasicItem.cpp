#include <SFML/System/Vector2.hpp>

#include "models/items/BasicItem.hpp"

#include "models/Board.hpp"

BasicItem::BasicItem (const std::string &name, const unsigned int points) :
  Item(name, points)
{}

BasicItem::~BasicItem ()
{}

void BasicItem::create_callback (Board & board, unsigned int pos)
{
	Item::create_callback(board, pos);
}

void BasicItem::destroy_callback (Board & board, unsigned int pos)
{
	
}
