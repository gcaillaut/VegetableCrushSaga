#include <iostream>

#include "Game.hpp"
#include "TestView.hpp"
#include "TestController.hpp"

#include "RessourcesManager.hpp"
#include "Factory.hpp"

int main ()
{
  /*
  game.init();

  Test test;
  TestView view(&test, "Test");
  TestController controller(&view, &test);

  while (game.getWindow().isOpen())
    {
      view.update();
      view.clear();
      view.draw();
    }
  */
  RessourcesManager<int, std::string> manager;
  manager.createRessource("a");
  manager.createRessource("b");

  std::cout << *manager.getRessource("a") << std::endl; // ok
  manager.eraseRessource("a");
  std::cout << *manager.getRessource("a") << std::endl; // fail
  
  return 0;
}
