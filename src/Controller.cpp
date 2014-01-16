#include "Game.hpp"
#include "Controller.hpp"
#include "View.hpp"

std::map<std::string, Controller*> Controller::controllers;

Controller::Controller (const std::string & name, View *view) : 
  name(name),
  view(view)
{
  view->setController(this);
  controllers[name] = this;
}

Controller::~Controller ()
{}

void Controller::setCurrentView () const
{
  game.setCurrentView(view);
}

std::string Controller::getName () const
{
  return name;
}
