#include "Globals.hpp"
#include "Board.hpp"
#include "SpecialItemHorizontal.hpp"

SpecialItemHorizontal::SpecialItemHorizontal (const std::string &name, const unsigned int points) :
  Item(name, points)
{}

SpecialItemHorizontal::~SpecialItemHorizontal ()
{}

void SpecialItemHorizontal::create_callback (Board& board, unsigned int pos)
{
	Item::create_callback (board, pos);
}

void SpecialItemHorizontal::destroy_callback (Board & board, unsigned int pos)
{
	explode(board, pos);
}

SpecialItemHorizontal *SpecialItemHorizontal::clone()
{
  SpecialItemHorizontal* item = new SpecialItemHorizontal(name, value);
  resetItem(item);

  return item;
}

void SpecialItemHorizontal::explode (Board & board, unsigned pos)
{
	if (pos % board.getColsCount() > 0 && pos % board.getColsCount() < board.getColsCount())
		{
			explode(board, pos + 1);
			explode(board, pos - 1);
		}
	else
		{
			board.removeItemAt(pos);
		}
}
