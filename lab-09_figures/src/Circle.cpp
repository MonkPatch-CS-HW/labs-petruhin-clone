#include "Circle.hpp"
#include <string.h>
#include <iostream>

Circle::Circle(int id, int x, int y, int radius, const char *label) : Figure(id, x, y), radius(radius) {
  char *newlabel = new char[strlen(label) + 1];
  strcpy(newlabel, label);
  this->label = newlabel;
}

Circle::~Circle() {
  delete[] this->label;
}

void Circle::print() const
{
  // Circle ‹id›: x = ‹x› y = ‹y› radius = ‹radius› label = ‹label›
  std::cout << "Circle " << id << ": x = " << x << " y = " << y << " radius = " << radius << " label = " << label << std::endl;
}

bool Circle::is_inside(int x, int y) const
{
  int dx = x - this->x;
  int dy = y - this->y;
  int dsquare = dx * dx + dy * dy;
  return dsquare <= radius * radius;
}

void Circle::zoom(int factor)
{
  radius *= factor;
}