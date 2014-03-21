#include "models/Board.hpp"
#include "models/items/SpecialItemBomb.hpp"

#include "Globals.hpp"

SpecialItemBomb::SpecialItemBomb (const std::string &name, const unsigned int points) :
  Item(name, points)
{}

SpecialItemBomb::~SpecialItemBomb ()
{}

void SpecialItemBomb::create_callback (Board& board, unsigned int pos)
{
	Item::create_callback (board, pos);
}

void SpecialItemBomb::destroy_callback (Board & board, unsigned int pos)
{
	if (!destroyed)
		explode(board, pos, 3);
}

SpecialItemBomb *SpecialItemBomb::clone()
{
  SpecialItemBomb* item = new SpecialItemBomb(name, value);
  resetItem(item);

  return item;
}

void SpecialItemBomb::explode (Board & board, unsigned pos, unsigned range)
{
	if (range > 0)
		{
			if (pos % board.getColsCount() > 0)
				{
					explode(board, pos - 1, range - 1);
				}

			if (pos % board.getColsCount() < board.getColsCount() - 1)
				{
					explode(board, pos + 1, range - 1);
				}

			if (pos / board.getColsCount() > 0)
				{
					explode(board, pos - board.getColsCount(), range - 1);
				}

			if (pos < board.getTotalSize())
				{
					explode(board, pos + board.getColsCount(), range - 1);
				}
		}

	board.removeItemAt(pos);
}
