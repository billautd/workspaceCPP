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