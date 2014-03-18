#include "EndView.hpp"

#include <SFML/Window/Event.hpp>

#include "GameController.hpp"
#include "Globals.hpp"

EndView::EndView(Controller *controller, sf::RenderWindow &window):
  View(controller),
  window(window)
{
  rectangle.setPosition(0, 0);
  rectangle.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
  rectangle.setFillColor(sf::Color(0, 0, 0, 0));

  auto font = globals.getFontManager().getRessource("wombo_font");

  gameover_text.setFont(*font);
  gameover_text.setColor(sf::Color(255, 0, 0, 64));
  gameover_text.setCharacterSize(300);
  gameover_text.setString("Game Over");
  gameover_text.setOrigin(gameover_text.getGlobalBounds().width / 2,
						  gameover_text.getGlobalBounds().height / 2);
  gameover_text.setPosition(window.getSize().x / 2, window.getSize().y / 3);
}

EndView::~EndView()
{
}

void EndView::clear()
{
  window.clear(sf::Color::White);
}

void EndView::draw()
{
  window.draw(globals.getLastCapture());
  window.draw(rectangle);
  window.draw(gameover_text);
}

void EndView::display()
{
  window.display();
}

void EndView::sendEvents()
{
  sf::Event event;
  while (window.pollEvent(event))
  {
	switch (event.type)
	{
	  case sf::Event::Closed:
		globals.shutdown();
		running = false;
		break;

	  case sf::Event::KeyPressed:
		if (event.key.code == sf::Keyboard::Escape)
		{
		  globals.shutdown();
		  running = false;
		}
		break;

	  default:
		break;
	}
  }
}

void EndView::loop()
{
  gameover_clock.restart();

  while (running)
  {
	sendEvents();

	updateText();

	clear();
	draw();
	display();
  }
}

void EndView::updateText()
{
  if (gameover_clock.getElapsedTime().asSeconds() < 6)
  {
	sf::Color rectangleColor = rectangle.getFillColor();
	sf::Color textColor = gameover_text.getColor();

	float delta = (float)(1.f/60.f * 35.f);
	rectangleColor.a += (rectangleColor.a + delta > 255 ? 0 : std::ceil(delta));
	textColor.a += (textColor.a + delta > 255 ? 0 : std::ceil(delta));

	rectangle.setFillColor(rectangleColor);
	gameover_text.setColor(textColor);
  }
  else
  {
	globals.shutdown();
	running = false;
  }
}
