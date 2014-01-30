#include <SFML/Window/Event.hpp>

#include "GraphicView.hpp"

#include "Controller.hpp"
#include "Graphic.hpp"
#include "Item.hpp"


GraphicView::GraphicView(Controller *controller, Graphic *graphic, sf::RenderWindow &window) :
  View(controller),
  graphic(graphic),
  window(window),
  running(true)
{
}

GraphicView::~GraphicView()
{
}

void GraphicView::clear()
{
  window.clear(sf::Color::White);
}

void GraphicView::draw()
{
  graphic->updateGame();
  
  auto& items = graphic->getBoard().getItems();
  for (auto& item: items)
    {    
      if (item.get())
        window.draw(*item);
    }
}

void GraphicView::display()
{
  window.display();
}

void GraphicView::sendEvents()
{
  sf::Event event;
  while (window.pollEvent(event))
    {
      switch (event.type)
        {
        case sf::Event::Closed:
          running = false;
          break;

        case sf::Event::KeyPressed:
          if (event.key.code == sf::Keyboard::Escape)
            {
              running = false;
            }
          break;

        case sf::Event::MouseButtonPressed:
          if (event.mouseButton.button == sf::Mouse::Left)
            {
              controller->onClick(event.mouseButton.x, event.mouseButton.y);
            }
          break;

        case sf::Event::MouseButtonReleased:
          if (event.mouseButton.button == sf::Mouse::Left)
            {
              controller->onClickRelease(event.mouseButton.x, event.mouseButton.y);
            }
          break;

        case sf::Event::LostFocus:
          controller->onLostFocus();
          break;
          
        case sf::Event::GainedFocus:
          controller->onGainedFocus();
          break;

        default:
          break;
        }
    }
}

bool GraphicView::isRunning() const
{
  return running;
}
