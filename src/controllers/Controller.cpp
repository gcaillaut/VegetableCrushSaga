#include "controllers/Controller.hpp"
#include "views/View.hpp"

Controller::Controller ()
{}

Controller::~Controller ()
{}

void Controller::setView (View *view)
{
  current_view = view;
}
