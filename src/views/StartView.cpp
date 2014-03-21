#include <SFML/Window/Event.hpp>

#include "views/StartView.hpp"
#include "controllers/GameController.hpp"

#include "Globals.hpp"

StartView::StartView(Controller *controller, sf::RenderWindow &window):
  View(controller),
  window(window)
{
  auto font = globals.getFontManager().getResource("wombo_font");

  start_text.setFont(*font);
  start_text.setColor(sf::Color::Green);
  start_text.setCharacterSize(180);
  start_text.setString("Vegetable Crush Saga");
  start_text.setPosition(40, window.getSize().y / 3);
}

StartView::~StartView()
{
}

void StartView::clear()
{
  window.clear(sf::Color::White);
}

void StartView::draw()
{
  window.draw(start_text);
}

void StartView::display()
{
  window.display();
}

void StartView::sendEvents()
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

	  default:
		break;
	}
  }
}

void StartView::loop()
{
  start_clock.restart();

  while (running)
  {
	sendEvents();

	if (start_clock.getElapsedTime().asMilliseconds() > 1500)
	{
	  globals.setCurrentView("Game");
	  running = false;
	}

	clear();
	draw();
	display();
  }
}
