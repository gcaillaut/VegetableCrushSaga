#include "controllers/EndController.hpp"
#include "models/Game.hpp"

#include "Globals.hpp"

EndController::EndController():
  Controller()
{
}

EndController::~EndController()
{
}

void EndController::onClick(const float x, const float y)
{
}

void EndController::onClickRelease(const float x, const float y)
{
}

void EndController::onLostFocus()
{
}

void EndController::onGainedFocus()
{
}

void EndController::onRecommencer()
{
  globals.setRetry(true);
  globals.shutdown();
}

void EndController::onQuitter()
{
  globals.shutdown();
}
