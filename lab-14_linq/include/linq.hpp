#ifndef LINQ_H_
#define LINQ_H_

#include <iostream>
#include <utility>
#include <vector>

namespace linq {
namespace impl {

template <typename T, typename Iter> class range_enumerator;
template <typename T> class drop_enumerator;
template <typename T> class take_enumerator;
template <typename T, typename U, typename F> class select_enumerator;
template <typename T, typename F> class until_enumerator;
template <typename T, typename F> class where_enumerator;

template <typename T> class enumerator {
public:
  virtual const T &operator*() = 0; // Получает текущий элемент.
  virtual enumerator<T> &operator++() = 0; // Переход к следующему элементу
  virtual operator bool() = 0; // Возвращает true, если есть текущий элемент

  auto drop(int count) { return drop_enumerator<T>(*this, count); }

  auto take(int count) { return take_enumerator<T>(*this, count); }

  template <typename U = T, typename F> auto select(F func) {
    return select_enumerator<T, U, F>(*this, func);
  }

  template <typename F> auto until(F predicate) {
    return until_enumerator<T, F>(*this, predicate);
  }

  auto until_eq(T elem) {
    return until([=](T it) { return it == elem; });
  }

  template <typename F> auto where(F predicate) {
    return where_enumerator<T, F>(*this, predicate);
  }

  auto where_neq(T elem) {
    return where([=](T it) { return it != elem; });
  }

  std::vector<T> to_vector() {
    std::vector<T> res;
    while (*this) {
      res.reserve(res.size() + 1);
      res.push_back(* *this);
      ++*this;
    }

    return res;
  }

  template <typename Iter> void copy_to(Iter it) {
    while (*this) {
      *it = **this;
      ++*this;
      ++it;
    }
  }
};

template <typename T, typename Iter>
class range_enumerator : public enumerator<T> {
public:
  range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {}

  const T &operator*() override { return *begin_; }

  range_enumerator<T, Iter> &operator++() override {
    if (!*this)
      return *this;

    ++begin_;

    return *this;
  }

  operator bool() override { return begin_ != end_; }

private:
  Iter begin_, end_;
};

template <typename T> class drop_enumerator : public enumerator<T> {
public:
  drop_enumerator(enumerator<T> &parent, int count)
      : parent_(parent), count_(count) {
    while (count_-- > 0)
      ++parent_;
  }

  const T &operator*() override { return *parent_; }

  drop_enumerator<T> &operator++() override {
    if (!*this)
      return *this;

    ++parent_;

    return *this;
  }

  operator bool() override { return parent_; }

private:
  enumerator<T> &parent_;
  int count_;
};

template <typename T> class take_enumerator : public enumerator<T> {
public:
  take_enumerator(enumerator<T> &parent, int count)
      : parent_(parent), count_(count) {}

  const T &operator*() override { return *parent_; }

  take_enumerator<T> &operator++() override {
    if (!*this)
      return *this;

    ++parent_;
    --count_;

    return *this;
  }

  operator bool() override { return count_ > 0 && parent_; }

private:
  enumerator<T> &parent_;
  int count_;
};

template <typename T, typename U, typename F>
class select_enumerator : public enumerator<U> {
public:
  select_enumerator(enumerator<T> &parent, F func)
      : parent_(parent), func_(func), changed_(true) {}

  const U &operator*() override {
    if (changed_) {
      value_ = func_(*parent_);
      changed_ = false;
    }

    return value_;
  }

  select_enumerator<T, U, F> &operator++() override {
    if (!*this)
      return *this;

    ++parent_;
    changed_ = true;

    return *this;
  }

  operator bool() override { return parent_; }

private:
  enumerator<T> &parent_;
  F func_;
  U value_;
  bool changed_;
};

template <typename T, typename F>
class until_enumerator : public enumerator<T> {
public:
  until_enumerator(enumerator<T> &parent, F predicate)
      : parent_(parent), predicate_(predicate), valid_(true) {
    if (*this && predicate_(*parent_))
      valid_ = false;
  }

  const T &operator*() override { return *parent_; }

  until_enumerator<T, F> &operator++() override {
    if (!*this)
      return *this;

    ++parent_;

    if (*this && predicate_(*parent_))
      valid_ = false;

    return *this;
  }

  operator bool() override { return valid_ && parent_; }

private:
  enumerator<T> &parent_;
  F predicate_;
  bool valid_;
};

template <typename T, typename F>
class where_enumerator : public enumerator<T> {
public:
  where_enumerator(enumerator<T> &parent, F predicate)
      : parent_(parent), predicate_(predicate) {
    if (!predicate_(*parent_))
      ++*this;
  }

  const T &operator*() override { return *parent_; }

  where_enumerator<T, F> &operator++() override {
    while (true) {
      if (!*this)
        break;

      ++parent_;

      if (*this && predicate_(*parent_))
        break;
    }

    return *this;
  }

  operator bool() override { return parent_; }

private:
  enumerator<T> &parent_;
  F predicate_;
};

} // namespace impl

template <typename T> auto from(T begin, T end) {
  return impl::range_enumerator<typename std::iterator_traits<T>::value_type,
                                T>(begin, end);
}

} // namespace linq

#endif
