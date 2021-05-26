#pragma once
#include <vector>
#include <cstdint>
#include <string>
#include <fstream>
typedef uint64_t u64;

const bool isPrime(const u64 number);
const std::vector<u64> primeDecomposition(const u64 prime);
const u64 vectorMax(const std::vector<u64> numbers);
const bool isPalindrome(const u64 number);
const bool isDivisible(const u64 number, const std::vector<u64> numbers);
const std::vector<u64> primesBelow(const u64 max);

template <class T>
const u64 productVector(std::vector<T> numbers) {
	u64 product{ 1 };
	for (const T i : numbers)
		product *= i;

	return product;
}

template <class T>
const u64 sumVector(std::vector<T> numbers) {
	u64 product{ 0 };
	for (const T i : numbers)
		product += i;

	return product;
}

const bool isPrime(const u64 number) {
	if (number == 0 || number == 1)
		return false;
	for (u64 i{ 2 }; i <= floor(sqrt(static_cast<double>(number))); i++) {
		if (number % i == 0)
			return false;
	}
	return true;
}

const std::vector<u64> primeDecomposition(const u64 number) {
	if (number == 0 || number == 1)
		return std::vector<u64>{};
	if (number == 2)
		return std::vector<u64>{2};
	if (number == 3)
		return std::vector<u64>{3};


	std::vector<u64> primes{};
	for (u64 i{ 2 }; i <= floor(sqrt(static_cast<double>(number))); i++) {
		if (isPrime(i) && number % i == 0)
			primes.push_back(i);
	}
	return primes;
}

const u64 vectorMax(const std::vector<u64> numbers) {
	if (numbers.empty())
		return 0;
	u64 max{ numbers.at(0) };
	for (size_t i{ 1 }; i < numbers.size(); i++) {
		if (numbers.at(i) > max)
			max = numbers.at(i);
	}

	return max;
}

const bool isPalindrome(const u64 number) {
	std::string numberStr{ std::to_string(number) };
	size_t numberStrSize{ numberStr.size() };
	for (size_t i{ 0 }; i < numberStrSize; i++) {
		if (numberStr.at(i) != numberStr.at(numberStrSize - i - 1))
			return false;
	}
	return true;
}

const bool isDivisible(const u64 number, const std::vector<u64> numbers) {
	if (number == 0)
		return false;
	for (const u64 i : numbers) {
		if (number % i != 0)
			return false;
	}
	return true;
}

const std::vector<u64> primesBelow(const u64 max) {
	std::vector<u64> primes{};
	for (u64 i{ 0 }; i < max; i++) {
		if (isPrime(i))
			primes.push_back(i);
	}
	return primes;
}