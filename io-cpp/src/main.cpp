#include <iostream>
#include <cstdint>
#include <cstdio>
#include <string>
#include "employees.h"


int main() {
	std::string command, file;
	EmployeesArray list_workers;
	while (1) {
		std::cin >> command;
		if (command == "exit") {
			break;
		}
		if (command == "load") {
			std::cin >> file;
			std::ifstream in;
			in.open(file.c_str(), std::ios_base::binary);
			in >> list_workers;
			in.close();
			continue;
		}
		if (command == "save") {
			std::cin >> file;
			std::ofstream out;
			out.open(file.c_str(), std::ios_base::binary);
			out << list_workers;
			out.close();
			continue;
		}
		if (command == "add") {
			std::int32_t type;
			std::cin >> type;
			switch (type) {
			case 1: {
				Developer *d = new Developer;
				std::cin >> *d;
				list_workers.add(d);
				break;
			}
			case 2: {
				SalesManager *s = new SalesManager;
				std::cin >> *s;
				list_workers.add(s);
				break;
			}
			}
		}
		if (command == "list") {
			std::cout << list_workers;
		}
	}
	return 0;
}

