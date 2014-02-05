#ifndef INCLUDED_CREATEFUNC_HPP
#define INCLUDED_CREATEFUNC_HPP

#define CREATE(name) Item* create ##name ()\
{\
  Item *item(new BasicItem( #name ));\
  item->setTexture(*game.getTexturesManager().getRessource( #name ));\
  return item;\
}

#include <memory>

#include "Game.hpp"

CREATE(Carrot)
CREATE(Strawberry)
CREATE(Mushroom)
CREATE(Aubergine)
CREATE(Banana)
CREATE(Watermelon)

#endif /* INCLUDED_CREATEFUNC_HPP */
