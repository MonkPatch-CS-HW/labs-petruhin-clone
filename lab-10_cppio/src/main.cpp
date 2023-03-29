#include <iostream>
#include <fstream>
#include <vector>
#include "employees.h"

EmployeesArray ea;

int run_command(std::string command)
{
  if (command == "add")
  {
    ea.add_one_text(std::cin);
    return 0;
  }

  if (command == "list")
  {
    ea.write_all_text(std::cout);
    return 0;
  }

  if (command == "save")
  {
    std::string filename;
    std::cin >> filename;

    std::ofstream fout(filename, std::ios_base::binary | std::ios_base::out);
    fout << ea;
    fout.close();
    return 0;
  }

  if (command == "load")
  {
    std::string filename;
    std::cin >> filename;

    std::ifstream fin(filename, std::ios_base::binary);
    fin >> ea;
    fin.close();
    return 0;
  }

  return -1;
}

int main()
{
  int result = 0;
  std::string command;
  while (result == 0)
  {
    std::cin >> command;
    result = run_command(command);
  }
  return 0;
}
