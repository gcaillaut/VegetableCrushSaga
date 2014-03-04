#include <SFML/Graphics/Texture.hpp>

#include "Globals.hpp"

#include "Item.hpp"
#include "Factory.hpp"
#include "BasicItem.hpp"

#include "createFunc.hpp"

Globals globals;

Globals::Globals () :
  window(nullptr),
  current_view(nullptr),
  running(true)
{
}

Globals::~Globals ()
{}

void Globals::init ()
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

View* Globals::getCurrentView () const
{
  return current_view;
}

void Globals::setCurrentView (std::string name)
{
  current_view = this->getView(name);
  current_view->activate();
}

const Factory<Item>& Globals::getItemFactory () const
{
  return item_factory;
}

TexturesManager& Globals::getTexturesManager ()
{
  return textures_manager;
}

sf::RenderWindow& Globals::getWindow ()
{
  return *window;
}

void Globals::gameLoop()
{
  while (running)
  {
	current_view->loop();
  }
}

void Globals::shutdown()
{
  running = false;
}

void Globals::addView(std::string name, View *view)
{
  if (view_map.find(name) == view_map.end())
  {
	view_map[name] = view;
  }
}

View* Globals::getView(std::string name)
{
  if (view_map.find(name) != view_map.end())
  {
	return view_map[name];
  }
  else
  {
	return nullptr;
  }
}

void Globals::captureScreen()
{
  sf::Image image(window->capture());
  gameTexture.loadFromImage(image);
  gameSprite.setTexture(gameTexture);
}

const sf::Sprite &Globals::getLastCapture() const
{
  return gameSprite;
}

void Globals::addTexture(std::string name)
{
  static unsigned int counter = 1;

  textures_manager.createRessource(name);
  textures_manager.getRessource(name)->loadFromFile("assets/item" + std::to_string(counter) + ".png");

  ++counter;
}
