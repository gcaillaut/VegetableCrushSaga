#include <SFML/Window/Event.hpp>

#include "GameView.hpp"

#include "GameController.hpp"
#include "Game.hpp"
#include "Item.hpp"

#include "Globals.hpp"

#include <iostream>

GameView::GameView(Controller *controller, Game *game, sf::RenderWindow &window) :
  View(controller),
  game(game),
  window(window),
  combo_mode(false)
{
  initializeGUI();
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
  window.draw(grass_sprite);
  window.draw(game->getBoard().getBoardShape());
  
  auto& items = game->getBoard().getItems();
  for (auto& item: items)
		{
			if (item.get())
				window.draw(*item);
		}

  window.draw(points_text);
  window.draw(combo_text);

  showComboText();
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
					static_cast<GameController*>(controller)->onQuit();
					running = false;
					break;

				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape)
						{
							static_cast<GameController*>(controller)->onEscape();
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

void GameView::loop()
{
  unsigned int fps(0);
  sf::Clock clock;

  while (running)
		{
			fps = 1.f / clock.getElapsedTime().asSeconds();
			window.setTitle("Vegetable Crush Saga - [FPS: " + std::to_string(fps) + "]");
			clock.restart();

			sendEvents();

			game->updateGame();

			points_text.setString("Points: " + std::to_string(game->getScore()));
			combo_text.setString("Combo: x" + std::to_string(game->getCombo()));

			clear();
			draw();
			display();
		}
}

void GameView::showComboText()
{
  static unsigned int prev_combo = 0;

  unsigned int current_combo = game->getCombo();

  if (current_combo > 1 && prev_combo != current_combo)
		{
			popup_text.setCharacterSize(200.f * (1.5f + (((current_combo < 30) ? current_combo : 30) / 10.f)));

			popup_text.setString("x" + std::to_string(current_combo));
			popup_text.setColor(sf::Color(0, 0, 0, 255));


			popup_text.setPosition(window.getSize().x / 2 - popup_text.getGlobalBounds().width / 2,
														 window.getSize().y / 2 - popup_text.getGlobalBounds().height);

			combo_mode = true;
			combo_clock.restart();

		}

  prev_combo = current_combo;

  // Combo
  if (combo_mode)
		{
			if (combo_clock.getElapsedTime().asSeconds() < 3)
				{
					window.draw(popup_text);

					sf::Color color = popup_text.getColor();
					float delta = (float)(1.f/60.f * 70.f);
					color.a -= (color.a - delta < 0 ? 0 : delta);

					popup_text.setColor(color);
				}
			else
				{
					combo_mode = false;
				}
		}
}

void GameView::initializeGUI()
{
  font.loadFromFile("assets/font.ttf");
  popup_text.setFont(font);
  popup_text.setColor(sf::Color(0, 0, 0, 255));
  popup_text.setCharacterSize(200);

  popup_text.setPosition(window.getSize().x / 2, window.getSize().y / 2);

  points_text.setFont(font);
  points_text.setColor(sf::Color::White);
  points_text.setPosition(20, 0);
  points_text.setCharacterSize(40);
  points_text.setString("Score: 0");

  combo_text.setFont(font);
  combo_text.setColor(sf::Color::White);
  combo_text.setPosition(20, 40);
  combo_text.setCharacterSize(40);
  combo_text.setString("Combo: x0");

  grass_texture.loadFromFile("assets/grass.png");
  grass_texture.setRepeated(true);

  grass_sprite.setTexture(grass_texture);
  grass_sprite.setPosition(0, 0);
  grass_sprite.setColor(sf::Color(180, 180, 180));

  float grass_width = (float)window.getSize().x / grass_texture.getSize().x;
  float grass_height = (float)window.getSize().y / grass_texture.getSize().y;

  sf::IntRect texture_rect = grass_sprite.getTextureRect();
  texture_rect.width *= grass_width;
  texture_rect.height *= grass_height;

  grass_sprite.setTextureRect(texture_rect);
}
