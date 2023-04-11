#include <iostream>
#include <stdexcept>

#include "CommandProcessor.h"
#include "MatrixStorage.h"

CommandProcessor cp;
MatrixStorage ms;

int get_register(std::istream &in)
{
  char dollar;
  int reg;

  in >> dollar >> reg;

  if (dollar != '$')
    throw std::runtime_error("Incorrect register format");

  if (reg < 0 || reg > 9)
    throw std::runtime_error("Incorrect register number");

  return reg;
}

void load_handler(std::istream &in, std::ostream &out)
{
  int reg = get_register(in);

  std::string filename;
  in >> filename;

  ms.load(reg, filename);
}

void print_handler(std::istream &in, std::ostream &out)
{
  int reg = get_register(in);

  ms.print(reg, out);
}

void add_handler(std::istream &in, std::ostream &out)
{
  int reg1 = get_register(in);
  int reg2 = get_register(in);

  ms.add(reg1, reg2);
}

void mul_handler(std::istream &in, std::ostream &out)
{
  int reg1 = get_register(in);
  int reg2 = get_register(in);

  ms.mul(reg1, reg2);
}

void elem_handler(std::istream &in, std::ostream &out)
{
  int reg = get_register(in);
  size_t i, j;

  in >> i >> j;
  ms.print_elem(reg, i, j, out);
}

void exit_handler(std::istream &in, std::ostream &out)
{
  exit(0);
}

void exception_handler(const HandlerEntry &entry, std::exception &err)
{
  if (dynamic_cast<std::bad_alloc*>(&err))
  {
    std::cout << "Unable to allocate memory." << std::endl;
    return;
  }
  std::cout << err.what() << std::endl;
}

int main()
{
  cp.add_handler("load", load_handler);
  cp.add_handler("print", print_handler);
  cp.add_handler("add", add_handler);
  cp.add_handler("mul", mul_handler);
  cp.add_handler("elem", elem_handler);
  cp.add_handler("exit", exit_handler);
  cp.set_exception_handler(exception_handler);

  std::string command;
  while (std::cin >> command)
    cp.process_command(command, std::cin, std::cout);
}