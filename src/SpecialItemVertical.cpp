#include "Globals.hpp"
#include "Board.hpp"
#include "SpecialItemVertical.hpp"

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
	explode(board, pos);
}

SpecialItemVertical *SpecialItemVertical::clone()
{
  SpecialItemVertical* item = new SpecialItemVertical(name, value);
  resetItem(item);

  return item;
}

void SpecialItemVertical::explode (Board & board, unsigned pos)
{
	if (pos < board.getTotalSize())
		{
			explode(board, pos + board.getColsCount());
		}

	if (pos / board.getColsCount() > 0)
		{
			explode(board, pos - board.getColsCount());
		}

	board.removeItemAt(pos);
}
