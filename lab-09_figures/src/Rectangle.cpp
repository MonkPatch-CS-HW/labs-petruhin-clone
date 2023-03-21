#include <iostream>
#include "Rectangle.hpp"

Rectangle::Rectangle(int id, int x, int y, int width, int height) : Figure(id, x, y), width(width), height(height) {}

void Rectangle::print() const
{
  // Rectangle ‹id›: x = ‹x› y = ‹y› width = ‹width› height = ‹height›
  std::cout << "Rectangle " << id << ": x = " << x << " y = " << y << " width = " << width << " height = " << height << std::endl;
}

bool Rectangle::is_inside(int x, int y) const
{
  return (this->x - width / 2 <= x && x <= this->x + width / 2) && (this->y - height / 2 <= y && y <= this->y + height / 2);
}

void Rectangle::zoom(int factor)
{
  width *= factor;
  height *= factor;
}