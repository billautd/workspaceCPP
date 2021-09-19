#include <iostream>
#include <fstream>
#include <codecvt>
#include <io.h>
#include <fcntl.h>
#include <string>


int main() {
	std::wifstream f("new.txt");
	std::wofstream newFile("new2.txt");
	f.imbue(std::locale(f.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::consume_header>));


	std::wstring line;
	while (std::getline(f, line)) {
			std::cout << line.c_str() << '\n';
	}
	return 0;
}