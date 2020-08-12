#include "employees.h"
#include "bin_manip.h"
#define NAME_SIZE 100

void EmployeesArray::add(const Employee *employer) {
	Employee **tmp = new Employee *[_size + 1];
	for (int i = 0; i < _size; i++) {
		tmp[i] = _employees[i];
	}

	tmp[_size++] = (Employee*)employer;
	if (_size) {
		delete[] _employees;
	}
	_employees = tmp;
}

EmployeesArray::~EmployeesArray() {
	for (int i = 0; i < _size; i++) {
		delete _employees[i];
	}
	delete[] _employees;
}

int EmployeesArray::total_salary() const {
	int salary = 0;
	for (int i = 0; i < _size; i++) {
		salary += _employees[i]->salary();
	}
	return salary;
}

int Developer::salary() const {
	int salary = _base_salary;
	if (_has_bonus) { salary += 1000; }
	return salary;
}

std::ostream &operator<<(std::ostream &out, const write_le_int32(value)) {
	return value(out);
}

std::istream &operator>>(std::istream &in, const read_le_int32(value)) {
	return value(in);
}

std::ostream &operator<<(std::ostream &out, const write_bool(value)) {
	return value(out);
}

std::istream &operator>>(std::istream &in, const read_bool(value)) {
	return value(in);
}

std::ostream &operator<<(std::ostream &out, const write_c_str(value)) {
	return value(out);
}

std::istream &operator>>(std::istream &in, const read_c_str(value)) {
	return value(in);
}

std::ostream &Developer::output(std::ostream &out) const {
    out << *this;
    return out;
}

std::ofstream &Developer::output(std::ofstream &out) const {
    out << *this;
    return out;
}

std::ostream &SalesManager::output(std::ostream &out) const {
    out << *this;
    return out;
}

std::ofstream &SalesManager::output(std::ofstream &out) const {
    out << *this;
    return out;
}

std::istream &operator>>(std::istream &in, Developer &developer) {
	std::string name;
	in >> name >> developer._base_salary >> developer._has_bonus;
	developer._name = new char[name.size() + 1];
	strcpy(developer._name, name.c_str());
	return in;
}

std::ostream &operator<<(std::ostream &out, const Developer &developer) {
	out << "Developer\n" << "Name: " << developer._name << '\n'
		<< "Base Salary: " << developer._base_salary << '\n'
		<< "Has bonus: " << (developer._has_bonus ? "+" : "-") << '\n';
	return out;
}

std::ifstream &operator>>(std::ifstream &in, Developer &developer) {
	in >> read_c_str(&developer._name, NAME_SIZE) >> read_le_int32(developer._base_salary) 
	   >> read_bool(developer._has_bonus);
	return in;
}

std::ofstream &operator<<(std::ofstream &out, const Developer &developer) {
	out << write_le_int32(DEVELOPER) << write_c_str(developer._name)
		<< write_le_int32(developer._base_salary) << write_bool(developer._has_bonus);
	return out;
}

std::istream &operator>>(std::istream &in, SalesManager &manager) {
	std::string name;
	in >> name >> manager._base_salary >> manager._sold_nm >> manager._price;
	manager._name = new char[name.size() + 1];
	strcpy(manager._name, name.c_str());
	return in;
}

std::ostream &operator<<(std::ostream &out, const SalesManager &manager) {
	out << "Sales Manager\n" << "Name: " << manager._name << "\n"
		<< "Base Salary: " << manager._base_salary << "\n"
		<< "Sold items: " << manager._sold_nm << "\n" << "Item price: " << manager._price << "\n";
	return out;
}

std::ifstream &operator>>(std::ifstream &in, SalesManager &manager) {
	in >> read_c_str(&manager._name, NAME_SIZE);
	in >> read_le_int32(manager._base_salary)
       >> read_le_int32(manager._sold_nm) >> read_le_int32(manager._price);
	return in;
}

std::ofstream &operator<<(std::ofstream &out, const SalesManager &manager) {
	out << write_le_int32(SMANAGER) << write_c_str(manager._name)
		<< write_le_int32(manager._base_salary) << write_le_int32(manager._sold_nm) 
		<< write_le_int32(manager._price);
	return out;
}

std::ostream &operator<<(std::ostream &out, const EmployeesArray &list) {
    for (int i = 0; i < list._size; i++) {
        out << i + 1 << ". " << *(list._employees[i]);
	}
    out << "== Total salary: " << list.total_salary() << '\n';
    return out;
}

std::ifstream &operator>>(std::ifstream &in, EmployeesArray &list) {
	int32_t num, type;
	in >> read_le_int32(num);
	for (int i = 0; i < num; i++) {
		in >> read_le_int32(type);
		if (type == 1) {
			Developer *d = new Developer();
			in >> *d;
			list.add(d);
			break;
		} else if (type == 2) {
			SalesManager *s = new SalesManager();
			in >> *s;
			list.add(s);
			break;
		}
	}
	return in;
}

std::ofstream &operator<<(std::ofstream &out, const EmployeesArray &list) {
	out << write_le_int32(list._size);
	for (int i = 0; i < list._size; i++) {
		out << *(list._employees[i]);
	}
	return out;
}
