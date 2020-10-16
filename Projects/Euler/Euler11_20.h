#pragma once
#include "Utils.h"
#include <iostream>

uint64_t euler11() {
	//Init grid container
	uint64_t** grid{ new uint64_t * [20]{0} };
	for (uint64_t i = 0; i < 20; i++)
		grid[i] = new uint64_t[20]{ 0 };

	std::ifstream file;
	file.open("TextFiles/euler11.txt");
	if (!file.is_open()) {
		std::cerr << "Unable to open Euler 11 file";
		return 0;
	}
	uint64_t value{ 0 };
	uint64_t count{ 0 };
	while (file >> value) {
		grid[count / 20][count % 20] = value;
		count++;
	}

	//Search for max product
	uint64_t max{ 0 };

	//Print grid
	//for (uint16_t i = 0; i < 20; i++) {
	//	for (uint16_t j = 0; j < 20; j++) {
	//		std::cout << grid[i][j] << " ";
	//	}
	//	std::cout << '\n';
	//}

	uint64_t product{ 0 };
	//Horizontally 
	for (uint64_t i = 0; i < 20; i++) {
		for (uint64_t j = 0; j < 17; j++) {
			product = grid[i][j] * grid[i][j + 1] * grid[i][j + 2] * grid[i][j + 3];
			if (product > max)
				max = product;
		}
	}

	//Vertically
	for (uint64_t i = 0; i < 17; i++) {
		for (uint64_t j = 0; j < 20; j++) {
			product = grid[i][j] * grid[i + 1][j] * grid[i + 2][j] * grid[i + 3][j];
			if (product > max)
				max = product;
		}
	}

	//Diagonally top left to bottom right
	for (uint64_t i = 0; i < 17; i++) {
		for (uint64_t j = 0; j < 17; j++) {
			product = grid[i][j] * grid[i + 1][j + 1] * grid[i + 2][j + 2] * grid[i + 3][j + 3];
			if (product > max)
				max = product;
		}
	}

	//Diagonally top right to bottom left
	for (uint64_t i = 0; i < 17; i++) {
		for (uint64_t j = 0; j < 17; j++) {
			product = grid[i + 3][j] * grid[i + 2][j + 1] * grid[i + 1][j + 2] * grid[i][j + 3];
			if (product > max)
				max = product;
		}
	}

	return max;
}

//Could've used getDivisors(divs).size() but a bit more operations
uint64_t euler12(uint64_t divisors) {
	uint64_t rank{ 1 };
	uint64_t currentValue{ 0 };
	uint64_t currentDivs{ 1 };
	while (true) {
		currentValue += rank;
		if (currentValue == UINT64_MAX) {
			std::cerr << "No fitting number found\n";
			return 0;
		}
		for (uint64_t i = 2; i <= currentValue; i++) {
			if (currentValue % i == 0)
				currentDivs++;
		}
		std::cout << currentValue << " : " << currentDivs << '\n';
		if (currentDivs > divisors)
			return currentValue;
		rank++;
		currentDivs = 1;
	}
	return 0;
}

uint64_t euler13() {
	//Read file
	std::ifstream file;
	file.open("TextFiles/euler13.txt");
	if (!file.is_open()) {
		std::cerr << "Cannot open euler13 file\n";
		return 0;
	}
	std::string number{};
	std::vector<short> sumDigits;
	//Init digits
	if (!std::getline(file, number)) {
		std::cerr << "No number\n";
		return 0;
	}
	for (size_t i = 0; i < number.size(); i++)
		sumDigits.insert(sumDigits.begin(), std::stoi(number.substr(i, 1)));

	//Get digits of sum
	while (std::getline(file, number)) {
		for (size_t i = 0; i < number.size(); i++) {
			sumDigits.at(i) += std::stoi(number.substr(number.size() - 1 - i, 1));
			size_t j = i;
			while (sumDigits.at(j) > 9) {
				sumDigits.at(j) -= 10;
				if (j + 1 > sumDigits.size() - 1) {
					sumDigits.push_back(1);
					break;
				}
				else
					sumDigits.at(j + 1)++;
				j++;
			}
		}
	}

	//Get 10 digits
	uint64_t sum{ 0 };
	for (short i = 0; i < 10; i++) {
		sum += sumDigits.at(sumDigits.size() - 1 - i) * static_cast<uint64_t>(pow(10, 9 - i));
	}
	return sum;
}

uint64_t euler14(uint64_t limit) {
	uint64_t maxSize{ 1 };
	uint64_t maxNumber{ 1 };
	for (uint64_t i = 1; i < limit; i++) {
		uint64_t currentNbr{ i };
		uint64_t currentSize{ 1 };
		while (currentNbr != 1) {
			if (currentNbr % 2 == 0)
				currentNbr /= 2;
			else
				currentNbr = 3 * currentNbr + 1;
			currentSize++;
		}
		if (currentSize > maxSize) {
			maxSize = currentSize;
			maxNumber = i;
		}
	}
	return maxNumber;
}

uint64_t euler15(uint64_t gridSize) {
	return 0;
}