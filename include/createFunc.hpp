#ifndef INCLUDED_CREATEFUNC_HPP
#define INCLUDED_CREATEFUNC_HPP

Item* createSalad ()
{
  Item *item(new BasicItem("Salad"));
  return item;
}

Item* createCarrot ()
{
  Item *item(new BasicItem("Carrot"));
  return item;
}

#endif /* INCLUDED_CREATEFUNC_HPP */
