#include <SFML/Graphics/Texture.hpp>

#include "Globals.hpp"

#include "Item.hpp"
#include "Factory.hpp"
#include "BasicItem.hpp"

#include "createFunc.hpp"

Globals globals;

Globals::Globals () :
  window(nullptr),
  current_view(nullptr)
{}

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

void Globals::setCurrentView (View *view)
{
  current_view = view;
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

void Globals::addTexture(std::string name)
{
  static unsigned int counter = 1;

  textures_manager.createRessource(name);
  textures_manager.getRessource(name)->loadFromFile("assets/item" + std::to_string(counter) + ".png");

  ++counter;
}
