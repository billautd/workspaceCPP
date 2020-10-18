#pragma once
#include <vector>
#include <fstream>
#include <string>

bool isPrime(const uint64_t value) {
	if (value < 2)
		return false;
	for (uint64_t i = 2; i <= sqrt(value); i++) {
		if (value % i == 0)
			return false;
	}
	return true;
}

std::vector<uint64_t> primeDecomposition(const uint64_t value) {
	if (isPrime(value))
		return std::vector<uint64_t>(value);

	std::vector<uint64_t> primes;
	uint64_t current{ value };
	uint64_t i{ 2 };
	while (i <= sqrt(current)) {
		if (current % i == 0) {
			current /= i;
			primes.push_back(i);
			i = 2;
		}
		else
			i++;
	}
	//Last number is a prime
	primes.push_back(current);
	return primes;
}

bool checkPalindrome(const uint64_t value) {
	std::string str{ std::to_string(value) };
	for (size_t i = 0; i < str.size() / 2; i++) {
		char char1{ str.at(i) };
		char char2{ str.at(str.size() - 1 - i) };
		if (char1 != char2)
			return false;
	}
	return true;
}

short charToDigit(const char value) {
	return value - '0';
}

std::vector<uint64_t> getDivisors(uint64_t value) {
	if (value == 0)
		return std::vector<uint64_t>{};
	std::vector<uint64_t> divisors{};
	for (uint64_t i = 1; i <= value; i++) {
		if (value % i == 0)
			divisors.push_back(i);
	}
	return divisors;
}

template <class T>
bool contains(const std::vector<T> vector, T value) {
	for (size_t i = 0; i < vector.size(); i++) {
		if (vector.at(i) == value)
			return true;
	}
	return false;
}

void digitsAdd(std::vector<uint16_t>* digits, std::string number) {
	for (size_t i = 0; i < number.size(); i++) {
		if (i >= digits->size())
			digits->push_back(std::stoi(number.substr(number.size() - 1 - i, 1)));
		else
			digits->at(i) += std::stoi(number.substr(number.size() - 1 - i, 1));
		size_t j = i;
		while (digits->at(j) > 9) {
			digits->at(j) -= 10;
			if (j + 1 > digits->size() - 1) {
				digits->push_back(1);
				break;
			}
			else
				digits->at(j + 1)++;
			j++;
		}
	}
}

void digitsAdd(std::vector<uint16_t>* digits, uint64_t value) {
	std::string str{ std::to_string(value) };
	digitsAdd(digits, str);
}

void digitsAdd(std::vector<uint16_t>* digits1, std::vector<uint16_t> digits2) {
	std::string str{ "" };
	for (uint16_t i = 0; i < digits2.size(); i++)
		str.insert(str.begin(), std::to_string(digits2.at(i)).at(0));
	digitsAdd(digits1, str);
}


//Multiplies digit by digit
//Ex : 225x347 = 225*7 + 225*4*10 + 225*3*100
void digitsMultiply(std::vector<uint16_t>* digits, std::string value) {
	std::vector<uint16_t> originalValue{ *digits };
	std::vector<uint16_t> originalValueCopy{ *digits };
	for (uint64_t i = 0; i < value.size(); i++) {
		//Get digit
		int digit{ std::stoi(value.substr(value.size() - 1 - i, 1)) };
		//Multiply all digits by current digit
		for (uint16_t j = 0; j < originalValueCopy.size(); j++)
			originalValueCopy.at(j) *= digit;

		//Carry
		for (uint64_t j = 0; j < originalValueCopy.size(); j++) {
			if (originalValueCopy.at(j) > 9) {
				if (j == originalValueCopy.size() - 1)
					originalValueCopy.push_back(originalValueCopy.at(j) / 10);
				else
					originalValueCopy.at(j + 1) += originalValueCopy.at(j) / 10;
				originalValueCopy.at(j) %= 10;

			}
		}

		//Add to original digits
		if (i == 0)
			*digits = originalValueCopy;
		else {
			//Multiply by rank (10^i)
			for (uint16_t k = 0; k < i; k++)
				originalValueCopy.insert(originalValueCopy.begin(), 0);
			//New vector size is always >= to previous one
			digitsAdd(digits, originalValueCopy);
		}
		//Restore original value
		originalValueCopy = originalValue;
	}
}

void digitsMultiply(std::vector<uint16_t>* digits, uint64_t value) {
	std::string str{ std::to_string(value) };
	digitsMultiply(digits, str);
}

void digitsMultiply(std::vector<uint16_t>* digits1, std::vector<uint16_t> digits2) {
	std::string str{ "" };
	for (uint16_t i = 0; i < digits2.size(); i++)
		str.insert(str.begin(), std::to_string(digits2.at(i)).at(0));
	digitsMultiply(digits1, str);
}

template<class T>
uint64_t vectorSum(const std::vector<T> vector) {
	uint64_t sum{ 0 };
	for (uint64_t i = 0; i < vector.size(); i++)
		sum += vector.at(i);
	return sum;
}