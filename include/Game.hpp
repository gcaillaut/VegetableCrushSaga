#ifndef INCLUDED_GAME_HPP
#define INCLUDED_GAME_HPP

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

#include "View.hpp"
#include "Factory.hpp"

class Item;

class Game
{
public:
  Game ();
  ~Game ();

  void init ();

  View* getCurrentView () const;
  void setCurrentView (View *view);

  const Factory<Item>& getItemFactory () const;

  sf::RenderWindow& getWindow ();
   
private:
  std::unique_ptr<sf::RenderWindow> window;
  View *current_view;
  Factory<Item> item_factory;
};

extern Game game;

#endif /* INCLUDED_GAME_HPP */
