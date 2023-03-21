#include <string.h>
#include "Scheme.hpp"
#include "Figure.hpp"

Scheme::Scheme(int capacity) : capacity(capacity)
{
  figures_ = new Figure *[capacity];
  size_ = 0;
}

Scheme::~Scheme()
{
  for (int i = 0; i < size_; i++)
    delete figures_[i];
  delete[] figures_;
}

void Scheme::push_back_figure(Figure *fg)
{
  figures_[size_++] = fg;
}

int Scheme::get_figure_index(int id)
{
  for (int i = 0; i < size_; i++)
  {
    if (figures_[i]->get_id() == id)
      return i;
  }
  return -1;
}

Figure *Scheme::get_figure(int id)
{
  int index = get_figure_index(id);
  if (index == -1)
    return nullptr;
  return figures_[index];
}

void Scheme::remove_figure(int id)
{
  int index = get_figure_index(id);
  if (index == -1)
    return;
  delete figures_[index];
  size_--;
  for (int i = index; i < size_; i++)
    figures_[i] = figures_[i + 1];
}

void Scheme::print_all_figures()
{
  for (int i = 0; i < size_; i++)
    figures_[i]->print();
}

void Scheme::zoom_figure(int id, int factor)
{
  Figure *figure = get_figure(id);
  if (figure == nullptr)
    return;
  figure->zoom(factor);
}

Figure *Scheme::is_inside_figure(int x, int y)
{
  for (int i = 0; i < size_; i++)
  {
    if (figures_[i]->is_inside(x, y))
      return figures_[i];
  }
  return nullptr;
}

void Scheme::move(int id, int new_x, int new_y)
{
  Figure *figure = get_figure(id);
  if (figure == nullptr)
    return;
  figure->move(new_x, new_y);
}