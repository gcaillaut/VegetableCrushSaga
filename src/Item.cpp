#include <string>
#include <cmath>
#include <SFML/System/Vector2.hpp>

#include "Item.hpp"

#define PI 3.14159265358979323846

Item::Item (std::string name) : 
  name(name),
  destroyed(false),
  moving(false)
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

  int speedx(18);
  int speedy(8);

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

  rotate(10.f);
}

std::string Item::getName () const
{
  return name;
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
