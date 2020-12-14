#pragma once
#include "Utils.h"

//Go through number twice even though we get a pair, optimizable
uint64_t euler21(uint64_t limit) {
	uint64_t total{ 0 };
	bool alreadyAdded{ false };
	for (uint64_t i = 2; i < limit; i++) {
		uint64_t sum1{ vectorSum(getProperDivisors(i)) };
		uint64_t sum2{ vectorSum(getProperDivisors(sum1)) };
		if (i == sum2 && sum2 != sum1)
			total += i;

	}

	return total;
}

uint64_t euler22() {
	std::ifstream file;
	file.open("TextFiles/euler22.txt");
	if (!file.is_open()) {
		std::cerr << "Error opening euler22 file";
		return 0;
	}


	std::vector<std::string> names;

	//Read char by char
	char c;
	std::string name;
	while (file.get(c)) {
		//If second "
		if (c == '"' && !name.empty()) {
			names.push_back(name);
			name = "";
			//Get ,
			file.get(c);
		}
		else if (c != '"')
			name += c;
	}

	//Sort alphabetically
	std::sort(names.begin(), names.end());


	//Calculate total
	uint64_t total{ 0 };
	for (size_t i = 1; i <= names.size(); i++) {
		std::string currentName{ names.at(i - 1) };
		for (size_t j = 0; j < currentName.size(); j++)
			total += charToAlphabeticalPosition(currentName.at(j)) * i;
	}
	return total;
}

uint64_t euler23() {
	//Get all abundant numbers < 28123
	std::vector<uint16_t> abundants;
	//Numbers will be removed if can be written as sum of two abundant numbers
	std::vector<uint16_t> numbers{ 0 };
	for (uint64_t i = 1; i < 28123; i++) {
		numbers.push_back(i);
		if (vectorSum(getProperDivisors(i)) > i)
			abundants.push_back(i);
	}
	numbers.push_back(28123);

	for (size_t i = 0; i < abundants.size(); i++) {
		for (size_t j = 0; j < abundants.size(); j++) {
			uint16_t index{ static_cast<uint16_t>(abundants.at(i) + abundants.at(j)) };
			if (index < numbers.size())
				numbers.at(index) = 0;
		}
	}

	return vectorSum(numbers);
}

//Search for what permutation is the millionth one instead of writing them all
uint64_t euler24() {
	uint64_t rank = 1000000 - 1;
	std::string millionthPermutation;
	millionthPermutation += std::to_string(10 * fact(10) / rank);
	return 0;
}