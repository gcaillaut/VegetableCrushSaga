#include <SFML/Window/Event.hpp>

#include "GameView.hpp"

#include "Controller.hpp"
#include "Game.hpp"
#include "Item.hpp"

#include <iostream>

GameView::GameView(Controller *controller, Game *game, sf::RenderWindow &window) :
  View(controller),
  game(game),
  window(window),
  running(true)
{
}

GameView::~GameView()
{
}

void GameView::clear()
{
  window.clear(sf::Color::White);
}

void GameView::draw()
{
  window.draw(game->getBoard().getBoardShape());
  
  auto& items = game->getBoard().getItems();
  for (auto& item: items)
  {
	if (item.get())
	  window.draw(*item);
  }
}

void GameView::display()
{
  window.display();
}

void GameView::sendEvents()
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

bool GameView::isRunning() const
{
  return running;
}

void GameView::loop()
{
  unsigned int fps(0);
  sf::Clock clock;

  while (running)
  {
	fps = 1.f / clock.getElapsedTime().asSeconds();
	window.setTitle("[P: " + std::to_string(game->getScore()) + "][x" + std::to_string(game->getCombo()) + "][FPS: " + std::to_string(fps) + "]");
	clock.restart();

	sendEvents();

	game->updateGame();

	clear();
	draw();
	display();
  }
}
