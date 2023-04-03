#include <iostream>

#include <cstring>
#include <cassert>
#include "my_vector.h"

namespace product
{

  class Product
  {
  public:
    Product(const char *name, int quantity, double price);
    ~Product();

  private:
    char *name_;
    int quantity_;
    double price_;
  };

  Product::Product(const char *name, int quantity, double price) : quantity_(quantity), price_(price)
  {
    name_ = new char[strlen(name) + 1];
    strcpy(name_, name);
  }

  Product::~Product()
  {
    delete[] name_;
  }

} // namespace product

int main()
{
  containers::my_vector<int> v;
  v.push_back(2);
  const int n{3};
  v.push_back(n);
  containers::my_vector<int> vv = v;
  v = vv;
  vv.pop_back();
  vv.clear();
  assert(vv.empty());
  assert(v.size() == 2);
  std::cout << v << std::endl;
  vv.resize(10);

  // test_my_vector<int>(5, 10);
  // test_my_vector<Product>(Product("asdf", 4, 12.0), Product("qwe", -1, 7.5));

  return 0;
}
