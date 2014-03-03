#include <iostream>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Clock.hpp>

#include "Graphic.hpp"
#include "Game.hpp"
#include "Item.hpp"

Graphic::Graphic(unsigned int x, unsigned int y, unsigned int width, unsigned int height,
								 unsigned int cell_size) :
  board(x, y, width, height, cell_size),
	view(nullptr),
  first_selected(false),
  second_selected(false),
  active_input(true),
	score(0)
{
	do
		board.update();
	while (!board.isStable());
}

Graphic::~Graphic()
{}

void Graphic::setClickPosition(const float x, const float y)
{
  if (!board.getDimensions().contains(x, y))
		{
			return;
		}

  sf::Vector2u selected(static_cast<unsigned int>(x),
												static_cast<unsigned int>(y));
  unsigned cell_size(board.getCellSize());
  unsigned ind_in_board(board.posToInd(selected));

  if (ind_in_board < board.getTotalSize())
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
		}
}

void Graphic::setReleasePosition(const float x, const float y)
{
  if (!board.getDimensions().contains(x, y) || !first_selected)
		{
			return;
		}

  sf::Vector2u selected(static_cast<unsigned int>(x),
												static_cast<unsigned int>(y));
  unsigned cell_size(board.getCellSize());
  unsigned ind_in_board(board.posToInd(selected));

  if (ind_in_board < board.getTotalSize())
		{
			if (ind_in_board != board.posToInd(first_item) && !second_selected)
				{
					// Alors, alors ...
					// Ici, on récupère la position du deuxième item selectionné lors d'un drag&drop
					// Le principe, c'est de recupérer le vecteur formé par les positions des deux items (delta)
					// Et, grace a ce vecteur, on peut connaitre la position de l'item qu'il faut sélectionner
					sf::Vector2i delta(std::move(selected - first_item));

					// Devrait être dans Board
					sf::Vector2u offset(1, board.getColsCount());

					int dir_x((std::abs(delta.x) < std::abs(delta.y)) ? 0 : static_cast<int>(std::abs(delta.x)) / delta.x);
					int dir_y((dir_x == 0) ? static_cast<int>(std::abs(delta.y)) / delta.y : 0);

					second_item = first_item + sf::Vector2u(cell_size * dir_x, cell_size * dir_y);
					second_selected = true;
				}
		}

  // Si on drag en dehors de la fenêtre
  else
		{
			board.resetSelected(board.posToInd(first_item));
			first_selected = false;
		}
}

void Graphic::executeMovement()
{
	std::cout << game.espace << __func__ << std::endl;
	game.espace+="  ";
  if (first_selected)
		{
			if (second_selected)
				{
					unsigned ind_first_item(board.posToInd(first_item));
					unsigned ind_second_item(board.posToInd(second_item));

					if (board.areNext(ind_first_item, ind_second_item))
						{
							board.swapItems(ind_first_item, ind_second_item);
							board.updateRowsAndCols();

							if (!board.isStable())
								{
									registerMove(ind_first_item, ind_second_item);
								}
							else
								{
									registerMove(ind_first_item, ind_second_item);
									registerMove(ind_second_item, ind_first_item);
								}

							board.swapItems(ind_second_item, ind_first_item);
							board.clearRemoved();
						}
		
					board.resetSelected(ind_second_item);
					board.resetSelected(ind_first_item);
					first_selected = second_selected = false;
				}
		}
	game.espace=game.espace.substr(0, game.espace.size()-2);
}

void Graphic::registerMove(unsigned int source, unsigned int target)
{
  move_registered.push(sf::Vector2u(source, target));
}

void Graphic::updateGame()
{
	std::cout << game.espace << __func__ << std::endl;
	game.espace+="  ";
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

	unsigned int old_score(score);
	std::pair<unsigned int, unsigned int> score_combo_wombo = board.update();

	score += score_combo_wombo.first;
	combo_wombo = score_combo_wombo.second;

	if (score != old_score)
		std::cout << "Score: " << score << std::endl;

	if (combo_wombo > 1)
		std::cout<< "Combo_wombo: " << combo_wombo << std::endl;

	game.espace=game.espace.substr(0, game.espace.size()-2);
}

void Graphic::setActive (bool value)
{
  active_input = value;
}

void Graphic::setView (View &new_view)
{
	view = &new_view;
}

Board& Graphic::getBoard ()
{
  return board;
}

bool Graphic::isActive ()
{
  return active_input;
}

unsigned int Graphic::getScore () const
{
	return score;
}

unsigned int Graphic::getCombo () const
{
	return combo_wombo;
}
