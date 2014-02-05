#include <SFML/Graphics/Texture.hpp>

#include "Game.hpp"
#include "Item.hpp"
#include "Factory.hpp"

#include "BasicItem.hpp"
#include "createFunc.hpp"

Game game;

Game::Game () :
  window(nullptr),
  current_view(nullptr)
{}

Game::~Game ()
{}

void Game::init ()
{
  window.reset(new sf::RenderWindow(sf::VideoMode(1280, 720), "Test",
									sf::Style::Default & ~sf::Style::Resize));
  window->setFramerateLimit(60);

  addTexture("Carrot");
  addTexture("Strawberry");
  addTexture("Mushroom");
  addTexture("Aubergine");
  addTexture("Banana");
  addTexture("Watermelon");

  item_factory.registerObject("Carrot", createCarrot);
  item_factory.registerObject("Strawberry", createStrawberry);
  item_factory.registerObject("Mushroom", createMushroom);
  item_factory.registerObject("Aubergine", createAubergine);
  item_factory.registerObject("Banana", createBanana);
  item_factory.registerObject("Watermelon", createWatermelon);
}

View* Game::getCurrentView () const
{
  return current_view;
}

void Game::setCurrentView (View *view)
{
  current_view = view;
}

const Factory<Item>& Game::getItemFactory () const 
{
  return item_factory;
}

TexturesManager& Game::getTexturesManager ()
{
  return textures_manager;
}

sf::RenderWindow& Game::getWindow ()
{
  return *window;
}

void Game::addTexture(std::string name)
{
  static unsigned int counter = 1;

  textures_manager.createRessource(name);
  textures_manager.getRessource(name)->loadFromFile("assets/item" + std::to_string(counter) + ".png");

  ++counter;
}
