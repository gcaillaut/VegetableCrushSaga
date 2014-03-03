#include <string>
#include <cmath>
#include <SFML/System/Vector2.hpp>

#include "Item.hpp"

Item::Item (const std::string &name, const unsigned int points) : 
  name(name),
	value(points),
  destroyed(false),
  moving(true)
{}

Item::~Item ()
{}

void Item::goTo (const sf::Vector2f & pos)
{  
  sf::Vector2f current = getPosition();

  if (current == pos)
    {
      moving = false;
      return;
    }

  int speedx(15);
  int speedy(10);

  moving = true;

  if (current.x > pos.x - 10 && current.x < pos.x + 10 && current.x != pos.x)
    {
      setPosition(pos.x, current.y);
    }
  else if (current.x != pos.x)
    {
      int dir(current.x < pos.x ? 1 : -1);
	  move(dir * speedx, 0);
    }

  // Si pos.y == current.y, déplacement fini
  else if (current.y > pos.y - 10 && current.y < pos.y + 10 && current.y != pos.y)
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
	if (!destroyed)
		{
			destroyed = true;
			setColor(sf::Color::Black);
			scale(0.5f, 0.5f);
		}
}

void Item::repair () 
{
	if (destroyed)
		{
			destroyed = false;
			setColor(sf::Color::White);
			scale(2.f, 2.f);
		}
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
