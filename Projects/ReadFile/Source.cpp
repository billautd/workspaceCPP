#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <Windows.h>

int main() {
	SetConsoleOutputCP(CP_UTF8);
	std::ifstream file;
	file.open("new.txt");

	std::ofstream newFile;
	newFile.open("new2.txt", std::ios_base::app | std::ios_base::out);

	std::string line{ "" };
	uint64_t i{ 0 };
	while (std::getline(file, line)) {
		newFile << line.substr(line.find("by") + 3) << '\n';
	}
	return 0;
}

