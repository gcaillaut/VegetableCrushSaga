#ifndef INCLUDED_CONTROLLER_HPP
#define INCLUDED_CONTROLLER_HPP

#include <map>

#include <SFML/Window/Event.hpp>

class View;

class Controller
{
public:
  Controller (const std::string & name, View & view);
  virtual ~Controller ();

  virtual void manageEvent (const sf::Event event) = 0;
  void setCurrentView () const;

  std::string getName () const;

private:
  std::string name;
  View & view;
  
  static std::map<std::string, Controller&> controllers;
};

#endif /* INCLUDED_CONTROLLER_HPP */
