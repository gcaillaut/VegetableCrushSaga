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
  window.reset(new sf::RenderWindow(sf::VideoMode(800, 600), "Test", sf::Style::Default & ~sf::Style::Resize));

  textures_manager.createRessource("Salad");
  textures_manager.getRessource("Salad")->loadFromFile("assets/item3.jpg");

  textures_manager.createRessource("Carrot");
  textures_manager.getRessource("Carrot")->loadFromFile("assets/item1.jpg");

  textures_manager.createRessource("PATATO");
  textures_manager.getRessource("PATATO")->loadFromFile("assets/item2.jpg");

  textures_manager.createRessource("Kiwi");
  textures_manager.getRessource("Kiwi")->loadFromFile("assets/item4.jpg");
 
  item_factory.registerObject("Salad", &createSalad);
  item_factory.registerObject("Carrot", &createCarrot);
  item_factory.registerObject("PATATO", &createPATATO);
  item_factory.registerObject("Kiwi", &createKiwi);
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
