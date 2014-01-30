#ifndef INCLUDED_CREATEFUNC_HPP
#define INCLUDED_CREATEFUNC_HPP

#include <memory>

#include "Game.hpp"

Item* createSalad ()
{
  Item *item(new BasicItem("Salad"));
  item->setTexture(*game.getTexturesManager().getRessource("Salad"));
  return item;
}

Item* createCarrot ()
{
  Item *item(new BasicItem("Carrot"));
  item->setTexture(*game.getTexturesManager().getRessource("Carrot"));
  return item;
}

Item* createPATATO ()
{
  Item *item(new BasicItem("PATATO"));
  item->setTexture(*game.getTexturesManager().getRessource("PATATO"));
  return item;
}

Item* createKiwi ()
{
  Item *item(new BasicItem("Kiwi"));
  item->setTexture(*game.getTexturesManager().getRessource("Kiwi"));
  return item;
}

#endif /* INCLUDED_CREATEFUNC_HPP */
