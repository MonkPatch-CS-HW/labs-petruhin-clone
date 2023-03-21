#include "Figure.hpp"

Figure::Figure(int id, int x, int y) : id(id), x(x), y(y) {}

Figure::~Figure() {}

int Figure::get_id()
{
  return id;
}

void Figure::move(int x, int y)
{
  this->x = x;
  this->y = y;
}
