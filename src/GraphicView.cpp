#include <SFML/Window/Event.hpp>
#include <SFML/Audio/Music.hpp>

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

	if (graphic->getCombo() > 3)
		{
			drawComboWombo();
		}

	else
		{
			drawBoard();
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
	sf::Texture texture;
	sf::Sprite orang_outang, orang_outang2;
	sf::Vector2u size(window.getSize());
	sf::Music combo_sound;
	combo_sound.openFromFile("assets/combo_breaker.ogg");

	texture.loadFromFile("assets/ORANG_OUTANG.jpg");
	orang_outang.setTexture(texture);
	orang_outang.setPosition(size.x, size.y / 2);
	orang_outang.scale(0.5f, 0.5f);

	float x = size.x;
	float a = -1/x;
	float b = x*-a;
	float c = 0.f;
	orang_outang2 = orang_outang;

	combo_sound.play();
	while (x > -static_cast<int>(texture.getSize().x))
		{
			
			clear();

			drawBoard();
			
			window.draw(orang_outang);
			window.draw(orang_outang2);
 
			x -= 18.f;
			float y =  a*x*x + b*x + c;
			orang_outang.setPosition(x, y);
			orang_outang2.setPosition(size.x - x, y);
 
			display();
			graphic->updateGame();
		}
}

void GraphicView::drawBoard ()
{
	window.draw(graphic->getBoard().getBoardShape());
  
	auto& items = graphic->getBoard().getItems();
	for (auto& item: items)
		{    
			if (item)
				{
					window.draw(*item);
				}
		}
}

bool GraphicView::isRunning() const
{
  return running;
}
