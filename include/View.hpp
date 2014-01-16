#ifndef INCLUDED_VIEW_HPP
#define INCLUDED_VIEW_HPP

#include <string>

class Controller;

class View
{
public:
  View (const std::string name, Controller & controller);
  virtual ~View ();

  void update () const;
  void clear ();
  virtual void draw () = 0;

  std::string getName () const;
   
private:
  Controller & controller;
  std::string name;
};

#endif /* INCLUDED_VIEW_HPP */
