#ifndef MY_VECTOR_IMPL_H_
#define MY_VECTOR_IMPL_H_

#include "my_vector.hpp"

namespace containers
{
  unsigned int log2_ceil(unsigned long long num)
  {
    num = (num << 1) - 1;
    unsigned int log = 0;
    while (num >>= 1)
      log++;
    return log;
  }

  template <typename T>
  std::ostream &operator<<(std::ostream &out, const my_vector<T> &mv)
  {
    if (mv.size_ > 0)
    {
      std::cout << '<' << mv[0] << '>';
      for (std::size_t i = 0; i < mv.size_; i++)
      {
        std::cout << ' ' << '<' << mv[i] << '>';
      }
    }
    return out;
  }

  template <typename T>
  my_vector<T>::my_vector() : my_vector(2)
  {
  }

  template <typename T>
  my_vector<T>::my_vector(std::size_t n)
  {
    reserve(n);
  }

  template <typename T>
  my_vector<T>::my_vector(const my_vector<T> &other)
  {
    *this = other;
  }

  template <typename T>
  my_vector<T>::~my_vector()
  {
    delete array_;
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
  void my_vector<T>::init(std::size_t n, std::size_t sz)
  {
    clear();
    reserve(n);
  }

  template <typename T>
  my_vector<T> &my_vector<T>::operator=(const my_vector<T> &other)
  {
    init(other.size_);

    while (size_ < other.size_)
    {
      array_[size_] = other.array_[size_];
      size_++;
    }

    return *this;
  }

  template <typename T>
  void my_vector<T>::reserve(std::size_t n)
  {
    std::size_t new_size = size_;
    std::size_t new_cap = log2_ceil(n);

    if (new_cap <= capacity_)
      return;

    T *new_array = reinterpret_cast<T *>(new unsigned char[capacity_]);
    for (std::size_t i = 0; i < size_; i++)
      new_array[i] = array_[i];

    clear();
    delete[] array_;

    array_ = new_array;
    capacity_ = new_cap;
    size_ = new_size;
  }

  template <typename T>
  void my_vector<T>::resize(std::size_t n)
  {
    if (n < size_)
      return;

    reserve(n);

    for (int i = size_; i < n; i++)
      new (&array_[i]) T();
  }

  template <typename T>
  T &my_vector<T>::operator[](std::size_t index) const
  {
    if (index > size_)
      throw std::out_of_range("my_vector out of range");
    return array_[index];
  }

  template <typename T>
  void my_vector<T>::clear()
  {
    while (!empty())
      pop_back();
  }

  template <typename T>
  void my_vector<T>::push_back(const T &t)
  {
    reserve(++size_);

    array_[size_ - 1] = t;
  }

  template <typename T>
  void my_vector<T>::pop_back()
  {
    array_[size_--].~T();
  }
}

#endif // MY_VECTOR_IMPL_H_