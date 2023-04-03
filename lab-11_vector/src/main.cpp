#include <iostream>
#include <sstream>

#include <cstring>
#include <cassert>
#include "my_vector.h"

namespace product
{

  class Product
  {
  public:
    Product(const char *name, int quantity, double price);
    Product(const Product &other);
    Product &operator=(const Product &other);
    ~Product();

    friend std::ostream &operator<<(std::ostream &out, const Product &p);

  private:
    char *name_dup(const char *name);

    char *name_;
    int quantity_;
    double price_;
  };

  char *Product::name_dup(const char *name)
  {
    char *new_str = new char[strlen(name) + 1];
    strcpy(new_str, name);
    return new_str;
  }

  Product::Product(const char *name, int quantity, double price) : name_(name_dup(name)), quantity_(quantity), price_(price)
  {
  }

  Product::Product(const Product &other)
  {
    *this = other;
  }

  Product &Product::operator=(const Product &other)
  {
    quantity_ = other.quantity_;
    price_ = other.price_;
    name_ = name_dup(other.name_);

    return *this;
  }

  Product::~Product()
  {
    delete[] name_;
  }

  std::ostream &operator<<(std::ostream &out, const Product &p)
  {
    out << p.name_ << ' ' << p.quantity_ << ' ' << p.price_;
    return out;
  }

} // namespace product

template <typename T>
void test_my_vector(const T &arg1, const T &arg2)
{
  containers::my_vector<T> v1;
  assert(v1.capacity() == 0);
  assert(v1.size() == 0);
  v1.push_back(arg1);
  assert(v1.capacity() == 1);
  assert(v1.size() == 1);
  std::stringstream ss1, ss2;
  ss1 << v1;
  ss2 << arg1;
  const char *s1 = ss1.str().c_str();
  const char *s2 = ss2.str().c_str();
  assert(strcmp(s1, s2) == 0);
  v1.push_back(arg1);
  v1.push_back(arg2);
  v1.pop_back();
  assert(v1.size() == 2);
  assert(v1.capacity() == 4);
  containers::my_vector<T> v2;
  v2 = v1;
  v1.clear();
  assert(v1.size() == 0);
  assert(v1.capacity() == 4);
  v1.reserve(10);
  assert(v1.size() == 0);
  assert(v1.capacity() == 16);
  assert(v2.size() == 2);
  assert(v2.capacity() == 2);
}

template <typename T>
void test_my_vector_default_constructible(const T &arg1, const T &arg2)
{
  containers::my_vector<T> v1(10);
  assert(v1.size() == 10);
  assert(v1.capacity() == 16); 
  v1.resize(20);
  assert(v1.size() == 20);
  assert(v1.capacity() == 32);
}

int main()
{
  test_my_vector_default_constructible<int>(5, 10);
  test_my_vector<int>(5, 10);
  test_my_vector<product::Product>(product::Product("asdf", 4, 12.0), product::Product("qwe", -1, 7.5));
  return 0;
}
