#ifndef LAB10_EMPLOYEES_H_INCLUDED
#define LAB10_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <string>
#include <vector>
#include <memory>

class Employee
{
public:
  virtual int32_t get_type() const = 0;
  virtual std::string get_name() const = 0;
  virtual int salary() const = 0;
  virtual std::shared_ptr<Employee> make_one() const = 0;

  virtual void write_text(std::ostream& out) const;
  virtual void read_text(std::istream& in);

  virtual void write_bin(std::ofstream& out) const;
  virtual void read_bin(std::ifstream& in);

  friend std::istream& operator>>(std::istream& in, Employee& empl);
  friend std::ostream& operator<<(std::ostream& out, const Employee& empl);

  friend std::ifstream& operator>>(std::ifstream& in, Employee& empl);
  friend std::ofstream& operator<<(std::ofstream& out, const Employee& empl);
protected:
  std::string _name;
  int32_t _base_salary;
};

class Developer : public Employee
{
public:
  int32_t get_type() const override;
  std::string get_name() const override;
  int salary() const override;
  std::shared_ptr<Employee> make_one() const override;

  void write_text(std::ostream& out) const override;
  void read_text(std::istream& in) override;

  void write_bin(std::ofstream& out) const override;
  void read_bin(std::ifstream& in) override;
private:
  bool _has_bonus;
};

class SalesManager : public Employee
{
public:
  int32_t get_type() const override;
  std::string get_name() const override;
  int salary() const override;
  std::shared_ptr<Employee> make_one() const override;

  void write_text(std::ostream& out) const override;
  void read_text(std::istream& in) override;

  void write_bin(std::ofstream& out) const override;
  void read_bin(std::ifstream& in) override;
private:
  int32_t _sold_nm, _price;
};

class EmployeesArray final
{
public:
  void add(std::shared_ptr<Employee> employee);
  int total_salary() const;
  void write_all_text(std::ostream &out) const;
  void write_all_bin(std::ofstream &out) const;
  void add_all_bin(std::ifstream &in);
  bool add_one_text(std::istream &in);

  friend std::ostream& operator<<(std::ostream &out, EmployeesArray& ea);
  friend std::ofstream& operator<<(std::ofstream& out, EmployeesArray& ea);
  friend std::ifstream& operator>>(std::ifstream& in, EmployeesArray& ea);
private:
  std::shared_ptr<Employee> make_of_type(int type) const;
  bool add_one_bin(std::ifstream &in);
  bool read_one_bin(std::ifstream &in, std::shared_ptr<Employee> &ptr) const;
  bool read_one_text(std::istream &in, std::shared_ptr<Employee> &ptr) const;
  void write_one_bin(std::ofstream &fout, std::shared_ptr<Employee> ptr) const;

  std::vector<std::shared_ptr<Employee>> _employees;
};

#endif
