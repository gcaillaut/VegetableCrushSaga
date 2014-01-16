#ifndef INCLUDED_GAME_HPP
#define INCLUDED_GAME_HPP

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

#include "View.hpp"

class Game
{
public:
  Game ();
  ~Game ();

  void init ();

  View* getCurrentView () const;
  void setCurrentView (View *view);

  sf::RenderWindow& getWindow ();
   
private:
  std::unique_ptr<sf::RenderWindow> window;
  View *current_view;
};

extern Game game;

#endif /* INCLUDED_GAME_HPP */
