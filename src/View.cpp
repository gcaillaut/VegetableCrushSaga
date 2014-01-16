#include <iostream>

#include <SFML/Window/Event.hpp>

#include "Game.hpp"
#include "View.hpp"
#include "Controller.hpp"

View::View (const std::string name) :
  controller(nullptr),
  name(name)
{}

View::~View ()
{}

void View::setController (Controller *c)
{
  if (!controller)
    {
      controller = c;
    }
  else
    {
      std::cerr << "Controller already set !" << std::endl;
    }
}

void View::update () const
{
  if (controller)
    {
      sf::Event event;
      sf::RenderWindow & window(game.getWindow());
      while (window.pollEvent(event))
        {
          controller->manageEvent(event);
        }
    }
}

void View::clear ()
{
  game.getWindow().clear();
}

std::string View::getName () const
{
  return name;
}
