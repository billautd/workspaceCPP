#pragma once
#include "Utils.h"

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

uint64_t euler8(size_t consecutive) {
	//Read number
	std::string number{};
	std::ifstream file;
	file.open("TextFiles/euler8.txt");
	if (!file.is_open()) {
		std::cerr << "Cannot open Euler 8 file\n";
		return 0;
	}
	std::getline(file, number);
	file.close();


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

//Can't do with floor(sqrt(a² + b²)) == sqrt(a² + b²) because of double precision
uint64_t euler9(uint64_t sum) {
	for (uint64_t c = 1; c <= sum; c++) {
		for (uint64_t b = 1; b < c; b++) {
			for (uint64_t a = 1; a < b; a++) {
				if (a * a + b * b == c * c && a + b + c == sum)
					return a * b * c;
			}
		}
	}
	return 0;
}

uint64_t euler10(uint64_t limit) {
	uint64_t sum{ 0 };
	for (uint64_t i = 2; i < limit; i++) {
		if (isPrime(i))
			sum += i;
	}
	return sum;
}