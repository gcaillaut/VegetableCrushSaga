#include <SFML/Window/Event.hpp>

#include "GraphicView.hpp"

#include "Controller.hpp"
#include "Graphic.hpp"
#include "Item.hpp"

#include <iostream>

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

	if (graphic->getCombo() > 0)
		{
			drawComboWombo();
		}

	else
		{
			window.draw(graphic->getBoard().getBoardShape());
  
			auto& items = graphic->getBoard().getItems();
			for (auto& item: items)
				{    
					if (item.get())
						window.draw(*item);
				}
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

void GraphicView::drawComboWombo ()
{
	std::cout << "COMBO" << std::endl;
	sf::Texture texture;
	sf::Sprite orang_outang;
	sf::Vector2u size(window.getSize());

	texture.loadFromFile("assets/ORANG_OUTANG.jpg");
	orang_outang.setTexture(texture);
	orang_outang.setPosition(size.x, size.y / 2);
	orang_outang.scale(0.5f, 0.5f);
 
	while (orang_outang.getPosition().x > -static_cast<int>(texture.getSize().x))
		{

			clear();

			window.draw(graphic->getBoard().getBoardShape());
  
			auto& items = graphic->getBoard().getItems();
			for (auto& item: items)
				{    
					if (item.get())
						window.draw(*item);
				}
			
			window.draw(orang_outang);

			orang_outang.move(sf::Vector2f(-20.f, 0.f));

			display();
		}
}

bool GraphicView::isRunning() const
{
  return running;
}
