#include <memory>
#include <iostream>
#include "employees.h"
#include "bin_manip.h"

std::vector<std::shared_ptr<Employee>> probes = {Developer().make_one(), SalesManager().make_one()};

int32_t Developer::get_type() const
{
  return 1;
}

int32_t SalesManager::get_type() const
{
  return 2;
}

std::string Developer::get_name() const
{
  return "Developer";
}

std::string SalesManager::get_name() const
{
  return "Sales Manager";
}

std::shared_ptr<Employee> Developer::make_one() const
{
  return std::make_shared<Developer>();
}

std::shared_ptr<Employee> SalesManager::make_one() const
{
  return std::make_shared<SalesManager>();
}

int Developer::salary() const
{
  int salary = _base_salary;
  if (_has_bonus)
  {
    salary += 1000;
  }
  return salary;
}

int SalesManager::salary() const
{
  return _base_salary + _sold_nm * _price * 0.01;
}

void EmployeesArray::add(std::shared_ptr<Employee> ptr)
{
  _employees.push_back(ptr);
}

int EmployeesArray::total_salary() const
{
  int sum = 0;
  for (auto &employee : _employees)
    sum += employee->salary();
  return sum;
}

void Employee::read_text(std::istream &in)
{
  in >> _name >> _base_salary;
}

void Employee::write_text(std::ostream &out) const
{
  out << "Name: " << _name << std::endl
      << "Base Salary: " << _base_salary << std::endl;
}

void Employee::read_bin(std::ifstream &in)
{
  in >> read_c_str(_name) >> read_le_int32(_base_salary);
}

void Employee::write_bin(std::ofstream &out) const
{
  out << write_c_str(_name) << write_le_int32(_base_salary);
}

void Developer::read_text(std::istream &in)
{
  Employee::read_text(in);
  in >> _has_bonus;
}

void Developer::write_text(std::ostream &out) const
{
  Employee::write_text(out);
  out << "Has bonus: " << (_has_bonus ? '+' : '-') << std::endl;
}

void Developer::read_bin(std::ifstream &in)
{
  Employee::read_bin(in);
  in >> read_bool(_has_bonus);
}

void Developer::write_bin(std::ofstream &out) const
{
  Employee::write_bin(out);
  out << write_bool(_has_bonus);
}

void SalesManager::read_text(std::istream &in)
{
  Employee::read_text(in);
  in >> _sold_nm >> _price;
}

void SalesManager::write_text(std::ostream &out) const
{
  Employee::write_text(out);
  out << "Sold items: " << _sold_nm << std::endl
      << "Item price: " << _price << std::endl;
}

void SalesManager::read_bin(std::ifstream &in)
{
  Employee::read_bin(in);
  in >> read_le_int32(_sold_nm) >> read_le_int32(_price);
}

void SalesManager::write_bin(std::ofstream &out) const
{
  Employee::write_bin(out);
  out << write_le_int32(_sold_nm) << write_le_int32(_price);
}

std::shared_ptr<Employee> EmployeesArray::make_of_type(int type) const
{
  for (auto &probe : probes)
  {
    if (probe->get_type() != type)
      continue;
    std::shared_ptr<Employee> ptr = probe->make_one();
    return ptr;
  }
  throw std::runtime_error(std::string("no probe with id") + std::to_string(type));
}

bool EmployeesArray::read_one_bin(std::ifstream &in, std::shared_ptr<Employee> &ptr) const
{
  int32_t type;
  if (!(in >> read_le_int32(type)))
    return false;

  ptr = make_of_type(type);

  if (!(in >> *ptr))
    return false;

  return true;
}

bool EmployeesArray::read_one_text(std::istream &in, std::shared_ptr<Employee> &ptr) const
{
  int32_t type;
  if (!(in >> type))
    return false;

  ptr = make_of_type(type);

  if (!(in >> *ptr))
    return false;

  return true;
}

bool EmployeesArray::add_one_text(std::istream &in)
{

  std::shared_ptr<Employee> ptr;
  if (!read_one_text(in, ptr))
    return false;

  add(ptr);
  return true;
}

bool EmployeesArray::add_one_bin(std::ifstream &in)
{
  std::shared_ptr<Employee> ptr;
  if (!read_one_bin(in, ptr))
    return false;

  add(ptr);
  return true;
}

void EmployeesArray::write_one_bin(std::ofstream &fout, std::shared_ptr<Employee> ptr) const
{
  fout << ptr->get_type();
  fout << *ptr;
}

void EmployeesArray::write_all_text(std::ostream &out) const
{
  int index = 0;
  for (auto &empl : _employees)
  {
    out << ++index << ". " << empl->get_name() << std::endl
        << *empl;
  }
  out << "== Total salary: " << total_salary() << std::endl << std::endl;
}

void EmployeesArray::write_all_bin(std::ofstream &out) const
{
  out << write_le_int32(_employees.size());
  for (auto &empl : _employees)
  {
    out << write_le_int32(empl->get_type())
        << *empl;
  }
}

void EmployeesArray::add_all_bin(std::ifstream &in)
{
  int32_t count;
  in >> read_le_int32(count);
  while (count-- && add_one_bin(in))
    ;
}

std::istream &operator>>(std::istream &in, Employee &empl)
{
  empl.read_text(in);
  return in;
}

std::ostream &operator<<(std::ostream &out, const Employee &empl)
{
  empl.write_text(out);
  return out;
}

std::ifstream &operator>>(std::ifstream &in, Employee &empl)
{
  empl.read_bin(in);
  return in;
}

std::ofstream &operator<<(std::ofstream &out, const Employee &empl)
{
  empl.write_bin(out);
  return out;
}

std::ostream &operator<<(std::ostream &out, EmployeesArray &ea)
{
  ea.write_all_text(out);
  return out;
}

std::ofstream &operator<<(std::ofstream &out, EmployeesArray &ea)
{
  ea.write_all_bin(out);
  return out;
}

std::ifstream &operator>>(std::ifstream &in, EmployeesArray &ea)
{
  ea.add_all_bin(in);
  return in;
}
