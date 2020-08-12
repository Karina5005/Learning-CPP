#ifndef LAB11_EMPLOYEES_H_INCLUDED
#define LAB11_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <iostream>
#include <fstream>
#include "employees.h"

enum employee_type {
	DEVELOPER = 1, SMANAGER = 2
};

class Employee {
public:
	Employee() {};
	virtual ~Employee() { delete[] _name; };

	virtual int salary() const = 0;

	virtual std::ostream &output(std::ostream &out) const = 0;
    virtual std::ofstream &output(std::ofstream &out) const = 0;

	friend std::ostream &operator<<(std::ostream &out, Employee &employer) { return employer.output(out); }
	friend std::ofstream &operator<<(std::ofstream &out, Employee &employer) { return employer.output(out); }

protected:
	char *_name;
	int32_t _base_salary;

private:
	Employee(Employee &other) {};
	Employee &operator=(Employee &other) { return other; };
};


class Developer: public Employee {
public:
	Developer() {};

	virtual int salary() const;
	
	std::ostream &output(std::ostream &out) const;
    std::ofstream &output(std::ofstream &out) const;

	friend std::istream &operator>>(std::istream &in, Developer &developer);
	friend std::ostream &operator<<(std::ostream &out, const Developer &developer);
	friend std::ifstream &operator>>(std::ifstream &in, Developer &developer);
	friend std::ofstream &operator<<(std::ofstream &out, const Developer &developer);

private:
	bool _has_bonus;

	Developer(Developer &other) : Employee() {};
	Developer &operator=(Developer &other) { return other; };
};

class SalesManager : public Employee {
public:
	SalesManager() {};

	virtual int salary() const { return _base_salary + _sold_nm * _price * 0.01; }

	std::ostream &output(std::ostream &out) const;
    std::ofstream &output(std::ofstream &out) const;

	friend std::istream &operator>>(std::istream &in, SalesManager &manager);
	friend std::ostream &operator<<(std::ostream &out, const SalesManager &manager);
	friend std::ifstream &operator>>(std::ifstream &in, SalesManager &manager);
	friend std::ofstream &operator<<(std::ofstream &out, const SalesManager &manager);

private:
	int32_t _sold_nm, _price;

	SalesManager(SalesManager &other) : Employee() {};
	SalesManager &operator=(SalesManager &other) { return other; };
};

class EmployeesArray {
public:
	EmployeesArray() :  _employees(nullptr), _size(0) {};
	~EmployeesArray();

	void add(const Employee *employer);
	int total_salary() const;
	
	friend std::ostream &operator<<(std::ostream &out, const EmployeesArray &_size);
	friend std::ifstream &operator>>(std::ifstream &in, EmployeesArray &_size);
	friend std::ofstream &operator<<(std::ofstream &out, const EmployeesArray &_size);
private:
	Employee **_employees;
	int32_t _size;

	EmployeesArray(Employee &other) {};
	EmployeesArray &operator=(EmployeesArray &other) { return other; };
};

#endif

