#include <SFML/Window/Event.hpp>

#include "View.hpp"
#include "Controller.hpp"

View::View (const std::string name, Controller & controller) :
  controller(controller),
  name(name)
{}

View::~View ()
{}

void View::update () const
{
  sf::Event event;
  /*
while (game.window.pollEvent(event))
{
controller.manageEvent(event);
}
   */
}

void View::clear ()
{
  // game.window.clear();
}

std::string View::getName () const
{
  return name;
}
