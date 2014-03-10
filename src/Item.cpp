#include <string>
#include <cmath>
#include <SFML/System/Vector2.hpp>

#include "Item.hpp"
#include "Board.hpp"

std::unique_ptr<Item> Item::null_item(nullptr);

Item::Item (const std::string &name, const unsigned int points) : 
  name(name),
  value(points),
  destroyed(false),
  moving(true),
  swapped(false)
{}

Item::~Item ()
{}

void Item::create_callback(Board& board, unsigned int pos)
{
	unsigned cell_size(board.getCellSize());
	std::unique_ptr<Item>& item(board.getItemAt(pos));

	sf::Vector2u texture_size(board.getItemAt(pos)->getTexture()->getSize());
  item->setOrigin(texture_size.x / 2, texture_size.y / 2);
  item->setScale(static_cast<float>(cell_size) / texture_size.x,
											 static_cast<float>(cell_size) / texture_size.y);
  item->scale(0.8f, 0.8f);
  item->setPosition(0, -static_cast<int>(cell_size));
}

void Item::destroy_callback(Board& board, unsigned int pos)
{
}

void Item::goTo (const sf::Vector2f & pos)
{  
  if (!swapped)
		setPosition(pos.x, getPosition().y);

  sf::Vector2f current = getPosition();

  if (current == pos)
		{
			moving = false;
			return;
		}

  int speedy(8);
  moving = true;

  if (swapped)
		{
			int speedx(8);

			if (current.x > pos.x - 10 && current.x < pos.x + 10 && current.x != pos.x)
				{
					setPosition(pos.x, current.y);
					swapped = false;
				}
			else if (current.x != pos.x)
				{
					int dir(current.x < pos.x ? 1 : -1);
					move(dir * speedx, 0);
				}
		}

  // Si pos.y == current.y, déplacement fini
  if (current.y > pos.y - 10 && current.y < pos.y + 10 && current.y != pos.y)
		{
			setPosition(current.x, pos.y);
		}
  else if (current.y != pos.y)
		{
			int dir(current.y < pos.y ? 1 : -1);
			move(0, dir * speedy);
		}
}

std::string Item::getName () const
{
  return name;
}

unsigned int Item::getValue () const
{
  return value;
}

void Item::destroy ()
{
  destroyed = true;
}

bool Item::isDestroyed () const
{
  return destroyed;
}

bool Item::isMoving () const
{
  return moving;
}

bool Item::operator==(const Item& item) const
{
  return name==item.name;
}

bool Item::operator!=(const Item& item) const
{
  return name!=item.name;
}

void Item::resetItem(Item *item)
{
  item->destroyed = destroyed;
  item->moving = moving;
  item->setPosition(getPosition());
  item->setRotation(getRotation());
  item->setScale(getScale());
  item->setOrigin(getOrigin());
  item->setColor(getColor());
  item->setTexture(*getTexture());
  item->setTextureRect(getTextureRect());
}
