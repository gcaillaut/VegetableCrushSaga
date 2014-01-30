#include "Controller.hpp"
#include "View.hpp"

Controller::Controller ()
{}

Controller::~Controller ()
{}

void Controller::setView (View *view)
{
  current_view = view;
}
