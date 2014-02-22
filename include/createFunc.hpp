#ifndef INCLUDED_CREATEFUNC_HPP
#define INCLUDED_CREATEFUNC_HPP

#define CREATE(name, value) Item* create ##name ()		\
{\
  Item *item(new BasicItem( #name , value));																\
  item->setTexture(*globals.getTexturesManager().getRessource( #name ));\
  return item;\
}

#include <memory>

#include "Globals.hpp"

CREATE(Carrot, 5)
CREATE(Strawberry, 5)
CREATE(Mushroom, 5)
CREATE(Aubergine, 32)
CREATE(Banana, 5)
CREATE(Watermelon, 5)

#endif /* INCLUDED_CREATEFUNC_HPP */
