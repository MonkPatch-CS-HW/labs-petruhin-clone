#include "my_vector.hpp"
#include <iostream>

MyVector::MyVector() : MyVector(2)
{
}

MyVector::MyVector(std::size_t init_capacity)
{
  _capacity = init_capacity;
  _size = 0;
  _data = new int[_capacity];
}

MyVector::MyVector(const MyVector &other)
{
  _capacity = other._capacity;
  _size = other._size;
  _data = new int[_capacity];
  for (std::size_t i = 0; i < _size; i++)
    _data[i] = other._data[i];
}

std::size_t MyVector::capacity()
{
  return _capacity;
}

std::size_t MyVector::size()
{
  return _size;
}

void MyVector::set(std::size_t index, int value)
{
  _data[index] = value;
}

int MyVector::get(std::size_t index)
{
  return _data[index];
}

void MyVector::reserve(std::size_t new_capacity)
{
  if (new_capacity > _capacity)
  {
    int *new_data = new int[new_capacity];
    for (std::size_t i = 0; i < _size; i++)
    {
      new_data[i] = _data[i];
    }
    delete[] _data;
    _data = new_data;
    _capacity = new_capacity;
  }
}

void MyVector::resize(std::size_t new_size)
{
  if (new_size > _size)
  {
    reserve(new_size);
    for (std::size_t i = _size; i < new_size; i++)
    {
      _data[i] = 0;
    }
  }
  _size = new_size;
}

void MyVector::push_back(int value)
{
  if (_size == _capacity)
  {
    reserve(_capacity * 2);
  }
  _data[_size] = value;
  _size++;
}

void MyVector::insert(std::size_t index, int value)
{
  if (_size == _capacity)
  {
    reserve(_capacity * 2);
  }
  for (std::size_t i = _size; i > index; i--)
  {
    _data[i] = _data[i - 1];
  }
  _data[index] = value;
  _size++;
}

void MyVector::erase(std::size_t index)
{
  for (std::size_t i = index; i < _size - 1; i++)
  {
    _data[i] = _data[i + 1];
  }
  _size--;
}

MyVector::~MyVector()
{
  delete[] _data;
}