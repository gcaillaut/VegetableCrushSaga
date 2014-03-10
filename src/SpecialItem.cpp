#include <SFML/System/Vector2.hpp>

#include "Globals.hpp"
#include "Board.hpp"
#include "SpecialItem.hpp"

SpecialItem::SpecialItem (const std::string &name, const unsigned int points) :
  Item(name, points)
{}

SpecialItem::~SpecialItem ()
{}

void SpecialItem::create_callback (Board& board, unsigned int pos)
{
	Item::create_callback (board, pos);
}

void SpecialItem::destroy_callback (Board & board, unsigned int pos)
{
	
}

SpecialItem *SpecialItem::clone()
{
  SpecialItem* item = new SpecialItem(name, value);
  resetItem(item);

  return item;
}
