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
  combo_mode(false),
  running(true)
{
  font.loadFromFile("assets/font.ttf");
  combo_text.setFont(font);
  combo_text.setColor(sf::Color(0, 0, 0, 255));
  combo_text.setCharacterSize(200);

  combo_text.setPosition(window.getSize().x / 2, window.getSize().y / 2);
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

	showComboText();

	display();
  }
}

void GameView::showComboText()
{
  static unsigned int prev_combo = 0;

  unsigned int current_combo = game->getCombo();

  if (current_combo > 1 && prev_combo != current_combo)
  {
	combo_text.setCharacterSize(200.f * (1.5f + (current_combo / 10.f)));

	combo_text.setString("x" + std::to_string(current_combo));
	combo_text.setColor(sf::Color(0, 0, 0, 255));


	combo_text.setPosition(window.getSize().x / 2 - combo_text.getGlobalBounds().width / 2,
						  window.getSize().y / 2 - combo_text.getGlobalBounds().height);

	combo_mode = true;
	combo_clock.restart();

  }

  prev_combo = current_combo;

  // Combo
  if (combo_mode)
  {
	if (combo_clock.getElapsedTime().asSeconds() < 3)
	{
	  window.draw(combo_text);

	  sf::Color color = combo_text.getColor();
	  float delta = (float)(1.f/60.f * 70.f);
	  color.a -= (color.a - delta < 0 ? 0 : delta);

	  combo_text.setColor(color);
	}
	else
	{
	  combo_mode = false;
	}
  }
}
