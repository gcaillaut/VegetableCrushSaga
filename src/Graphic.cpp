#include <iostream>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Clock.hpp>

#include "Graphic.hpp"

#include "Item.hpp"

Graphic::Graphic(unsigned int x, unsigned int y, unsigned int width, unsigned int height,
				 unsigned int cell_size) :
  board(x, y, width, height, cell_size),
  first_selected(false),
  second_selected(false),
  active_input(true)
{}

Graphic::~Graphic()
{}

void Graphic::setClickPosition(const float x, const float y)
{
  if (!board.getDimensions().contains(x, y))
  {
	return;
  }

  unsigned int cell_size(board.getCellSize());
  unsigned int selected((static_cast<unsigned int>(x) - board.getDimensions().left) / cell_size
						+ (static_cast<unsigned int>(y) - board.getDimensions().top) / cell_size
						* board.getRowsCount());

  if (selected < board.getTotalSize())
  {
	if (!first_selected)
	{
	  first_item = selected;
	  first_selected = true;
	}

	else
	{
	  second_item = selected;
	  second_selected = true;
	}

	board.getItemAt(selected)->setColor(sf::Color::Blue);
  }
}

void Graphic::setReleasePosition(const float x, const float y)
{
  if (!board.getDimensions().contains(x, y) || !first_selected)
  {
	return;
  }

  unsigned int cell_size(board.getCellSize());
  unsigned int selected((static_cast<int>(x) - board.getDimensions().left) / cell_size
						+ (static_cast<int>(y) - board.getDimensions().top) / cell_size
						* board.getRowsCount());

  if (selected < board.getTotalSize())
  {
	if (selected != first_item && !second_selected)
	{
	  second_item = selected;
	  second_selected = true;
	}
  }

  // Si on drag en dehors de la fenêtre
  else
  {
	board.resetSelected(first_item);
	first_selected = false;
  }
}

void Graphic::executeMovement()
{
  if (first_selected)
  {
	if (second_selected)
	{
	  if (board.areNext(first_item, second_item))
	  {
		board.swapItems(first_item, second_item);
		board.updateRowsAndCols();

		if (!board.isStable())
		{
		  registerMove(first_item, second_item);
		  board.swapItems(second_item, first_item);
		  board.clearRemoved();
		}
		else
		{
		  registerMove(first_item, second_item);
		  registerMove(second_item, first_item);
		  board.swapItems(second_item, first_item);
		  board.clearRemoved();
		}
	  }

	  board.resetSelected(second_item);
	  board.resetSelected(first_item);
	  first_selected = second_selected = false;
	}
  }
}

void Graphic::registerMove(unsigned int source, unsigned int target)
{
  move_registered.push(sf::Vector2u(source, target));
}

void Graphic::updateGame()
{
  active_input = !board.areItemsMoving();

  if (!move_registered.empty())
  {
	sf::Vector2u current_move(move_registered.top());

	if (active_input)
	{
	  move_registered.pop();
	  board.swapItems(current_move.x, current_move.y);
	}

	board.updatePositions();
  }

  board.update();
}

void Graphic::setActive (bool value)
{
  active_input = value;
}

Board& Graphic::getBoard ()
{
  return board;
}

bool Graphic::isActive ()
{
  return active_input;
}
