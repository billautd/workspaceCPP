#pragma once
#include "Utils.h"
#include <iostream>
#include <sstream>

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
	file.close();


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
	std::vector<uint16_t> sumDigits;
	//Init digits
	if (!std::getline(file, number)) {
		std::cerr << "No number\n";
		return 0;
	}
	for (size_t i = 0; i < number.size(); i++)
		sumDigits.insert(sumDigits.begin(), std::stoi(number.substr(i, 1)));

	//Get digits of sum
	while (std::getline(file, number))
		digitsAdd(&sumDigits, number);

	file.close();


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

//Dynamic programming
uint64_t euler15(uint64_t gridSize) {
	//Init grid of points
	uint64_t** grid{ new uint64_t * [gridSize + 1]{0} };
	for (uint64_t i = 0; i < gridSize + 1; i++)
		grid[i] = new uint64_t[gridSize + 1]{ 0 };

	//Init ways on the right and bottom sides
	for (uint64_t i = 0; i < gridSize; i++) {
		grid[i][gridSize] = 1;
		grid[gridSize][i] = 1;
	}

	//Add number of possible ways from adjacent points
	while (grid[0][0] == 0) {
		for (uint64_t i = 0; i < gridSize; i++) {
			for (uint64_t j = 0; j < gridSize; j++) {
				if (grid[i][j] == 0 && grid[i + 1][j] != 0 && grid[i][j + 1] != 0)
					grid[i][j] = grid[i + 1][j] + grid[i][j + 1];
			}
		}
	}
	//Print grid
	for (uint64_t i = 0; i < gridSize + 1; i++) {
		for (uint64_t j = 0; j < gridSize + 1; j++) {
			std::cout << grid[i][j] << " ";
		}
		std::cout << '\n';
	}
	return grid[0][0];
}

uint64_t euler16(uint64_t power) {
	if (power == 0)
		return 1;
	std::vector<uint16_t> digits;
	digits.push_back(2);
	for (uint16_t i = 2; i <= power; i++)
		digitsMultiply(&digits, 2);

	return vectorSum(digits);
}

uint64_t euler17() {
	std::vector < std::string> oneToNineteen{ "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
		"eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };
	std::vector<std::string> dozens{ "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety" };
	std::string hundred{ "hundred" };
	std::string thousand{ "thousand" };
	std::string andStr{ "and" };

	uint64_t sum{ 0 };
	for (uint64_t i = 1; i <= 1000; i++) {
		if (i == 1000) {
			sum += oneToNineteen.at(0).size() + thousand.size();
			break;
		}
		//Hundred 
		if (i >= 100) {
			sum += oneToNineteen.at(i / 100 - 1).size();
			sum += hundred.size();
			if (i % 100 != 0)
				sum += andStr.size();
		}

		//10 - 19
		if (i % 100 >= 10 && i % 100 <= 19) {
			sum += oneToNineteen.at(i % 100 - 1).size();
		}
		else {
			//Dozens
			if ((i % 100) / 10 != 0)
				sum += dozens.at((i % 100) / 10 - 2).size();

			//Unity
			if (i % 10 != 0)
				sum += oneToNineteen.at(i % 10 - 1).size();
		}

	}
	return sum;
}

uint64_t euler18() {
	//Init triangle
	std::vector<std::vector<uint64_t>> triangle;
	std::ifstream file;
	file.open("TextFiles/euler18.txt");
	if (!file.is_open()) {
		std::cerr << "Error opening euler18.txt file";
		return 0;
	}
	uint64_t value{ 0 };
	std::string line{ "" };
	while (std::getline(file, line)) {
		std::stringstream lineSS{ line };
		std::vector<uint64_t> currentLine;
		while (lineSS >> value)
			currentLine.push_back(value);
		triangle.push_back(currentLine);
	}
	file.close();

	//For each point in triangle, store highest weight of path from summit to this point
	//Weights is a triangle like the one above
	//We take triangle and clear values except first node
	std::vector<std::vector<uint64_t>> weights{ triangle };
	for (uint64_t i = 1; i < weights.size(); i++) {
		for (uint64_t j = 0; j < weights.at(i).size(); j++)
			weights.at(i).at(j) = 0;
	}

	for (uint64_t i = 1; i < weights.size(); i++) {
		for (uint64_t j = 0; j < weights.at(i).size(); j++) {
			//If point is on the sides, only one weight possible
			if (j == 0)
				weights.at(i).at(0) = weights.at(i - 1).at(0) + triangle.at(i).at(0);
			else if (j == weights.at(i).size() - 1)
				weights.at(i).at(j) = weights.at(i - 1).at(j - 1) + triangle.at(i).at(j);
			else {
				//Check two possible weights and keep max
				uint64_t weight1{ weights.at(i - 1).at(j - 1) + triangle.at(i).at(j) };
				uint64_t weight2{ weights.at(i - 1).at(j) + triangle.at(i).at(j) };
				weights.at(i).at(j) = weight1 > weight2 ? weight1 : weight2;
			}
		}
	}

	uint64_t max{ 0 };
	for (uint64_t i = 0; i < weights.at(weights.size() - 1).size(); i++) {
		if (weights.at(weights.size() - 1).at(i) > max)
			max = weights.at(weights.size() - 1).at(i);
	}
	return max;
}

uint64_t euler19() {
	//<Day index, day of the month>
	//Day index is 1, 2, 3, 4, 5, 6, 7
	std::pair<uint16_t, uint16_t> day{ 1, 1 };
	//Month index is 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
	uint16_t month{ 1 };
	uint16_t year{ 1900 };

	std::vector<uint16_t> thirtyDaysMonths{ 4, 6, 9, 11 };

	uint64_t sundays{ 0 };
	while (year < 2000 || month < 12 || day.second < 31) {
		//std::cout << day.first << " " << day.second << " " << month << " " << year << '\n';
		if (year != 1900 && day.second == 1 && day.first == 7)
			sundays++;

		bool isLeapYear{ year % 4 == 0 && (year % 100 != 0 || year % 400 == 0) };
		day.first++;
		if (day.first > 7)
			day.first = 1;
		day.second++;
		if (day.second > 31 || (day.second > 30 && contains(thirtyDaysMonths, month)) || (day.second > 29 && month == 2 && isLeapYear) || (day.second > 28 && month == 2 && !isLeapYear)) {
			day.second = 1;
			month++;
		}
		if (month > 12) {
			month = 1;
			year++;
		}
	}
	return sundays;
}

//Based on euler16
uint64_t euler20(uint64_t value) {
	if (value == 0 || value == 1)
		return 1;
	std::vector<uint16_t> digits;
	digits.push_back(1);
	for (uint64_t i = 2; i < value; i++)
		digitsMultiply(&digits, i);

	return vectorSum(digits);
}