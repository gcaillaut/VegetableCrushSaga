#include <chrono>
#include <iostream>

#include <SFML/Graphics/Texture.hpp>

#include "Board.hpp"
#include "Item.hpp"
#include "Game.hpp"

Board::Board (unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int cell_size) :
  cell_size(cell_size),
  total_size(width * height),
  cols(width),
  rows(height),
	last_move_value(0),
	combo_wombo(0),
  items(total_size),
  available_items(game.getItemFactory().getAvailableKeys()),
  generator(std::chrono::system_clock::now().time_since_epoch().count())
{
  dimensions = {x, y, width*cell_size, height*cell_size};

  board_shape.setPosition(x, y);
  board_shape.setFillColor(sf::Color::White);
  board_shape.setOutlineColor(sf::Color::Green);
  board_shape.setOutlineThickness(5);
  board_shape.setSize(sf::Vector2f(dimensions.width, dimensions.height));

  randomFill();
}

Board::~Board ()
{}

void Board::randomFill ()
{
  for (unsigned int i(0) ; i < total_size ; ++i)
		{
			changeItem(i % cols, i / cols);


			/* items[i] = std::move(game.getItemFactory().createObject("PATATO"));
				 removed_items[i] = false;

				 sf::Vector2u texture_size(items[i]->getTexture()->getSize());
				 items[i]->setScale(static_cast<float>(cell_size) / texture_size.x,
				 static_cast<float>(cell_size) / texture_size.y);

				 if(i<total_size-1){
				 items[i+1] = std::move(game.getItemFactory().createObject("Salad"));
				 removed_items[i+1] = false;

				 sf::Vector2u texture_size(items[i+1]->getTexture()->getSize());
				 items[i+1]->setScale(static_cast<float>(cell_size) / texture_size.x,
				 static_cast<float>(cell_size) / texture_size.y);
				 }

				 if(i<total_size-2){
				 items[i+2] = std::move(game.getItemFactory().createObject("Carrot"));
				 removed_items[i+2] = false;

				 sf::Vector2u texture_size(items[i+2]->getTexture()->getSize());
				 items[i+2]->setScale(static_cast<float>(cell_size) / texture_size.x,
				 static_cast<float>(cell_size) / texture_size.y);
				 }
			*/
		}
}

const std::vector<std::unique_ptr<Item> >& Board::getItems () const
{
  return items;
}

std::unique_ptr<Item>& Board::getItemAt (const unsigned int ind)
{
  return items[ind];
}

unsigned int Board::getTotalSize () const
{
  return total_size;
}

unsigned int Board::getRowsCount () const
{
  return rows;
}

unsigned int Board::getColsCount () const
{
  return cols;
}

unsigned int Board::getCellSize () const
{
  return cell_size;
}

const sf::Rect<unsigned int>& Board::getDimensions() const
{
  return dimensions;
}

const sf::RectangleShape &Board::getBoardShape() const
{
  return board_shape;
}

unsigned Board::posToInd (const sf::Vector2u pos) const
{
	return (pos.x - dimensions.left) / cell_size + (pos.y - dimensions.top) / cell_size * cols;
}

unsigned Board::posToInd (const unsigned x, const unsigned y) const
{
	return (x - dimensions.left) / cell_size + (y - dimensions.top) / cell_size * cols;
}

void Board::swapItems (const unsigned int src, const unsigned int dest)
{
  std::swap(items[src], items[dest]);
}

void Board::changeItem(unsigned int x, unsigned int y)
{
  unsigned int pos(x + y*cols);
  unsigned int key_ind(generator() % available_items.size());

  items[pos] = std::move(game.getItemFactory().createObject(available_items[key_ind]));

  sf::Vector2u texture_size(items[pos]->getTexture()->getSize());
  items[pos]->setOrigin(texture_size.x / 2, texture_size.y / 2);
  items[pos]->setScale(static_cast<float>(cell_size) / texture_size.x,
											 static_cast<float>(cell_size) / texture_size.y);

  items[pos]->setPosition(0, -static_cast<int>(cell_size));
}

bool Board::areNext(unsigned int source, unsigned int target) const
{
  unsigned int tmp(source % cols);

  if (target >= total_size)
		return false;
  if (tmp == 0 && source == target + 1)
		return false;
  if (tmp == cols - 1 && source == target - 1)
		return false;

  return target == source - 1
	  || target == source + 1
	  || target == source + cols
	  || target == source - cols;
}

void Board::resetSelected(unsigned int selected)
{
  items[selected]->setColor(sf::Color::White);
}


void Board::clearRemoved()
{
  std::for_each(items.begin(), items.end(), [](std::unique_ptr<Item> &item) { item->repair(); });
}

void Board::fillBlanks()
{
  for (unsigned int i(0) ; i < total_size ; ++i)
		{
			if (items[i]->isDestroyed())
				{
					changeItem(i % cols, i / cols);
				}
		}
}

std::pair<unsigned int, unsigned int> Board::update ()
{
	last_move_value = 0;
	combo_wombo = 0;

  if (!areItemsMoving())
		{
			do {

				fillBlanks();

				updateRowsAndCols();

				for (unsigned int i = 0; i < cols; ++i)
					applyGravity(i);

			} while (!isStable());
		}

  updatePositions();

	return std::make_pair(last_move_value, combo_wombo);
}

void Board::updateLine (const unsigned int begin, const unsigned int end, const unsigned int offset)
{
  Item *previous_item(items[begin].get());
  unsigned int cpt(0);

  unsigned int current = begin + offset;

  while (current < end)
		{
			Item *current_item(items[current].get());
			if (previous_item && current_item)
				{
					if (*previous_item != *current_item)
						{
							if (cpt >= 2)
								{
									markForRemoval(current - offset*(cpt+1), current - offset, offset);
								}
							cpt = 0;
						}
					else
						{
							++cpt;
							if (cpt >= 2 && current == end - offset)
								{
									markForRemoval(current - offset*(cpt), current, offset);
								}
						}
				}
			else {cpt = 0;}

			current += offset;
			previous_item = current_item;
		}
}

void Board::markForRemoval (unsigned int begin, const unsigned int end, const unsigned int offset)
{
	
		++combo_wombo;

  while (begin <= end)
		{
			items[begin]->destroy();
			last_move_value += items[begin]->getValue() * combo_wombo;
			begin += offset;
		}
}

bool Board::isStable () const
{
  return !std::any_of(items.cbegin(), items.cend(), [](const std::unique_ptr<Item> &item)
											{
												return item->isDestroyed();
											});
}

void Board::updateRowsAndCols ()
{
  for (unsigned int i(0) ; i < rows; ++i)
		{
			updateLine(i * cols, (i+1) * cols, 1);
		}

  for (unsigned int i(0) ; i < cols; ++i)
		{
			updateLine(i, cols * rows + i, cols);
		}
}

void Board::applyGravity (const unsigned int col)
{
  for (int i(col + cols * (rows-1)) ; i >= 0; i -= cols)
		{
			/*
			 * Si l'item i est supprimé, on doit le remplacer par l'item au dessus le plus proche
			 */
			if (items[i]->isDestroyed())
				{
					int next(i - cols);

					/*
					 * si next < 0, alors il n'y a pas d'item au dessus de i
					 */
					while (next >= 0 && items[next]->isDestroyed())
						{
							next -= cols;
						}

					if (next >= 0)
						{
							swapItems(i, next);
						}
				}
		}
}

void Board::updatePositions ()
{
  for (unsigned int j = 0; j < rows; ++j)
		{
			for (unsigned int i = 0; i < cols; ++i)
				{
					if (items[i + j*cols].get())
						{
							float new_x(i * cell_size + cell_size / 2 + dimensions.left);
							float new_y(j * cell_size + cell_size / 2 + dimensions.top);

							items[i + j*cols]->goTo(sf::Vector2f(new_x, new_y));
						}
				}
		}
}

bool Board::areItemsMoving()
{
  return std::any_of(items.cbegin(), items.cend(), [](const std::unique_ptr<Item>& i)
										 { return i->isMoving(); });
}
