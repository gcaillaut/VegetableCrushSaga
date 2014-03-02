#include "View.hpp"
#include "Controller.hpp"

View::View (Controller *controller) :
  controller(controller),
  running(true)
{}

View::~View () 
{}

bool View::isRunning() const
{
  return running;
}

void View::activate()
{
  running = true;
}
