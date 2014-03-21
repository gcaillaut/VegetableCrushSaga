#include "models/Board.hpp"
#include "models/items/SpecialItemVertical.hpp"

#include "Globals.hpp"

SpecialItemVertical::SpecialItemVertical (const std::string &name, const unsigned int points) :
  Item(name, points)
{}

SpecialItemVertical::~SpecialItemVertical ()
{}

void SpecialItemVertical::create_callback (Board& board, unsigned int pos)
{
	Item::create_callback (board, pos);
}

void SpecialItemVertical::destroy_callback (Board & board, unsigned int pos)
{
	if (!destroyed)
		{
			int width(board.getColsCount());
			explode(board, pos - width, -width);
			explode(board, pos + width, width);
 		}
}

SpecialItemVertical *SpecialItemVertical::clone()
{
  SpecialItemVertical* item = new SpecialItemVertical(name, value);
  resetItem(item);

  return item;
}

void SpecialItemVertical::explode (Board & board, unsigned pos, int offset)
{
	if (pos < board.getTotalSize()
			&& pos / board.getColsCount() > 0)
		{
			explode(board, pos + offset, offset);
			board.removeItemAt(pos);
		}
}
