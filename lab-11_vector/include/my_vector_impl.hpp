#ifndef MY_VECTOR_IMPL_H_
#define MY_VECTOR_IMPL_H_

#include "my_vector.hpp"

namespace containers
{
  unsigned int ceil_pow2(unsigned long long num)
  {
    if (num <= 1)
      return num;

    num = (num << 1) - 1;

    unsigned int log = 0;
    while (num >>= 1)
      log++;

    return 1 << log;
  }

  template <typename T>
  my_vector<T>::my_vector()
      : capacity_(0), size_(0), array_(nullptr)
  {
  }

  template <typename T>
  my_vector<T>::my_vector(std::size_t n)
  {
    resize(n);
  }

  template <typename T>
  my_vector<T>::my_vector(const my_vector<T> &other)
  {
    *this = other;
  }

  template <typename T>
  my_vector<T> &my_vector<T>::operator=(const my_vector &other)
  {
    if (this == &other)
      return *this;

    clear();
    reserve(other.size_);
    capacity_ = other.capacity_;

    while (size_ < other.size_)
      push_back(other.array_[size_]);

    return *this;
  }

  template <typename T>
  void my_vector<T>::reserve(std::size_t n)
  {
    std::size_t new_capacity = ceil_pow2(n);
    std::size_t new_size = size_;

    if (n <= capacity_)
      return;

    T *new_array = reinterpret_cast<T *>(operator new(new_capacity * sizeof(T)));
    for (size_t i = 0; i < size_; i++)
      new (new_array + i) T(array_[i]);

    clear();

    operator delete(array_);

    array_ = new_array;
    capacity_ = new_capacity;
    size_ = new_size;
  }

  template <typename T>
  void my_vector<T>::resize(std::size_t n)
  {
    reserve(n);

    while (size_ < n)
      push_back(T());

    clear_until(n);
  }

  template <typename T>
  void my_vector<T>::clear_until(std::size_t n)
  {
    while (size_ > n)
      pop_back();
  }

  template <typename T>
  void my_vector<T>::clear()
  {
    clear_until(0);
  }

  template <typename T>
  T &my_vector<T>::operator[](std::size_t index) const
  {
    if (index >= size_)
      throw std::out_of_range("index out of range");

    return array_[index];
  }

  template <typename T>
  void my_vector<T>::push_back(const T &t)
  {
    reserve(size_ + 1);
    new (array_ + size_) T(t);
    size_++;
  }

  template <typename T>
  void my_vector<T>::pop_back()
  {
    if (size_ == 0)
      throw std::out_of_range("index out of range");

    array_[size_ - 1].~T();
    size_--;
  }

  template <typename T>
  std::size_t my_vector<T>::size() const
  {
    return size_;
  }

  template <typename T>
  std::size_t my_vector<T>::capacity() const
  {
    return capacity_;
  }

  template <typename T>
  bool my_vector<T>::empty() const
  {
    return size_ == 0;
  }

  template <typename T>
  std::ostream &operator<<(std::ostream &out, const my_vector<T> &mv)
  {
    out << mv[0];
    for (size_t i = 1; i < mv.size(); i++)
      out << ' ' << mv[i];

    return out;
  }

  template <typename T>
  my_vector<T>::~my_vector()
  {
    clear();
    operator delete(array_);
  }
}

#endif // MY_VECTOR_IMPL_H_