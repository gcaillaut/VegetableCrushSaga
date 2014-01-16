#ifndef TEST_HPP
#define TEST_HPP

#include <vector>
#include <memory>
#include <cstdlib>

#include <SFML/Graphics/RectangleShape.hpp>

class Test
{
public:
  Test() { srand(time(0)); }
  ~Test() {}

  void addRectangle(sf::Vector2f pos)
  {
    sf::RectangleShape* shape = new sf::RectangleShape();
    shape->setPosition(pos);
    unsigned int size = rand() % 50;

    shape->setSize(sf::Vector2f(size, size));
    shape->setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
    
    rectangles.emplace_back(shape);
  }

  std::vector<std::unique_ptr<sf::RectangleShape>>& getRectangles()
  {
    return rectangles;
  }

private:
  std::vector<std::unique_ptr<sf::RectangleShape>> rectangles;
};

#endif
