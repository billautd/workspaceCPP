#pragma once
#include <vector>
#include <string>
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

uint64_t euler1(const uint64_t limit) {
	uint64_t sum{ 0 };
	for (uint64_t i = 2; i < limit; i++) {
		if (i % 3 == 0 || i % 5 == 0)
			sum += i;
	}
	return sum;
}

uint64_t euler2(const uint64_t limit) {
	uint64_t sum{ 0 };
	uint64_t fib1{ 1 };
	uint64_t fib2{ 2 };
	while (fib2 <= limit) {
		if (fib2 % 2 == 0)
			sum += fib2;
		uint64_t fib3{ fib2 };
		fib2 += fib1;
		fib1 = fib3;
	}
	return sum;
}

uint64_t euler3(const uint64_t value) {
	std::vector<uint64_t> primes{ primeDecomposition(value) };

	uint64_t max{ primes.at(0) };
	for (size_t i = 1; i < primes.size(); i++) {
		if (primes.at(i) > max)
			max = primes.at(i);
	}
	return max;
}


uint64_t euler4() {
	uint64_t max{ 0 };
	for (uint64_t i = 100; i <= 999; i++) {
		for (uint64_t j = 100; j <= 999; j++) {
			if (checkPalindrome(i * j) && i * j > max)
				max = i * j;
		}
	}
	return max;
}

uint64_t euler5(const uint64_t value) {
	uint64_t current{ 1 };
	while (current < UINT64_MAX) {
		short i{ 2 };
		while (i < value) {
			if (current % i == 0)
				i++;
			else {
				i = 2;
				break;
			}
		}
		if (i == value && current % value == 0)
			return current;
		else {
			current++;
		}
	}
	return 0;
}

uint64_t euler6(const uint64_t limit) {
	uint64_t sumOfSquares{ 0 };
	uint64_t squareOfSum{ 0 };
	for (uint64_t i = 1; i <= limit; i++)
		sumOfSquares += (i * i);
	for (uint64_t i = 1; i <= limit; i++)
		squareOfSum += i;
	squareOfSum *= squareOfSum;
	return squareOfSum - sumOfSquares;
}



uint64_t euler7(const uint64_t rank) {
	uint64_t current{ 0 };
	uint64_t currentRank{ 0 };
	while (currentRank < rank && current < UINT64_MAX) {
		if (isPrime(current)) {
			currentRank++;
		}
		current++;
	}
	return --current;
}

uint64_t euler8(std::string number, size_t consecutive) {
	uint64_t product{ 1 };
	uint64_t max{ 0 };

	for (size_t i = 0; i <= number.size() - consecutive; i++) {
		for (size_t j = i; j < consecutive + i; j++) {
			product *= charToDigit(number.at(j));
		}
		if (product > max)
			max = product;
		product = 1;
	}
	return max;
}