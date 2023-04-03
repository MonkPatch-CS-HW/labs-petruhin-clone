#ifndef MY_VECTOR_HPP_
#define MY_VECTOR_HPP_

#include <cstddef>
#include <iostream>

namespace containers
{
  template <typename T>
  class my_vector
  {
  public:
    my_vector();
    my_vector(std::size_t n);
    my_vector(const my_vector<T> &other);
    my_vector<T> &operator=(const my_vector &other);
    ~my_vector();

    void init(std::size_t n, std::size_t sz = 0);

    std::size_t size() const;
    std::size_t capacity() const;
    bool empty() const;

    void resize(std::size_t n);
    void reserve(std::size_t n);

    T &operator[](std::size_t index) const;

    template <typename Y>
    friend std::ostream &operator<<(std::ostream &out, const my_vector<Y> &mv);

    void push_back(const T &t);
    void pop_back();
    void clear();

  private:
    size_t capacity_ = 0;
    size_t size_ = 0;
    T *array_ = nullptr;
  };

}

#include "my_vector_impl.hpp"

#endif // MY_VECTOR_HPP_
