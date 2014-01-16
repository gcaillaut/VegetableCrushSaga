#include "Controller.hpp"
#include "View.hpp"

Controller::Controller (const std::string & name, View & view) : 
  name(name),
  view(view)
{}

Controller::~Controller ()
{}

void Controller::setCurrentView () const
{
  // game.view = view;
}

std::string Controller::getName () const
{
  return name;
}
