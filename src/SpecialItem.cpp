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
	explode(board, pos, 3);
}

SpecialItem *SpecialItem::clone()
{
  SpecialItem* item = new SpecialItem(name, value);
  resetItem(item);

  return item;
}

void SpecialItem::explode (Board & board, unsigned pos, unsigned range)
{
	if (range > 0)
		{
			explode(board, pos + 1, range - 1);
			explode(board, pos - 1, range - 1);
			explode(board, pos + board.getColsCount(), range - 1);
			explode(board, pos - board.getColsCount(), range - 1);
		}
	else
		{
			std::unique_ptr<Item>& item(board.getItemAt(pos));
			if (item)
				{
					item->destroy();
				}
		}
}
