#include <iostream>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Clock.hpp>
 
#include "Graphic.hpp"

#include "Item.hpp"

Graphic::Graphic(unsigned int width, unsigned int height, unsigned int cell_size) :  
  board(width, height, cell_size),
  first_selected(false), 
  second_selected(false),
  active_input(true)
{}

Graphic::~Graphic()
{}

void Graphic::setClickPosition(const float x, const float y)
{
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

      board.getItemAt(ind_in_board)->setColor(sf::Color::Yellow);
    }
}

void Graphic::setReleasePosition(const float x, const float y)
{
  if (!first_selected)
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
					sf::Vector2u offset(1, board.getWidth());

					int dir_x((std::abs(delta.x) < std::abs(delta.y)) ? 0 : static_cast<int>(std::abs(delta.x)) / delta.x);
					int dir_y((dir_x == 0) ? static_cast<int>(std::abs(delta.y)) / delta.y : 0);
 
					second_item = first_item + sf::Vector2u(cell_size * dir_x, cell_size * dir_y);
					second_selected = true; 
					// board.getItemAt(ind_in_board)->setColor(sf::Color::Blue);
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
                  board.swapItems(ind_second_item, ind_first_item);
                  board.clearRemoved();
                }
              else
                {
                  registerMove(ind_first_item, ind_second_item);
                  registerMove(ind_second_item, ind_first_item);
                  board.swapItems(ind_second_item, ind_first_item);
                  board.clearRemoved();
                }
            }

          board.resetSelected(ind_second_item);
          board.resetSelected(ind_first_item);
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
