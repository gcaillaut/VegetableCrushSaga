#include "models/Board.hpp"
#include "models/items/SpecialItemHorizontal.hpp"

#include "Globals.hpp"

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
	if (!destroyed)
		{
			destroy();
			explode(board, pos - 1, -1);
			explode(board, pos - 1, 1);
 		}
}

void SpecialItemHorizontal::explode (Board & board, unsigned pos, int offset)
{
	if (pos % board.getColsCount() < board.getColsCount() - 1 
			&& pos % board.getColsCount() > 0)
		{
			explode(board, pos + offset, offset);
		}
	board.removeItemAt(pos);
}
