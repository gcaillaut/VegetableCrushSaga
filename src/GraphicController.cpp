#include "GraphicController.hpp"
#include "Graphic.hpp"

GraphicController::GraphicController(Graphic *graphic): Controller(), graphic(graphic)
{
}

GraphicController::~GraphicController()
{
}

void GraphicController::onClick(const float x, const float y)
{
  if (graphic->isActive())
    {
      graphic->setClickPosition(x, y);
    }
}

void GraphicController::onClickRelease(const float x, const float y)
{
  if (graphic->isActive())
    {
      graphic->setReleasePosition(x, y);
      graphic->executeMovement();
    }
}

void GraphicController::onLostFocus()
{
  graphic->setActive(false);
}

void GraphicController::onGainedFocus()
{
  graphic->setActive(true);
}
