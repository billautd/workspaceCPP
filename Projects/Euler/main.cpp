#include "Utils.h"
#include <iostream>


const u64 euler1(const u64 max) {
	u64 result{ 0 };
	for (u64 i{ 0 }; i < max; i++) {
		if (i % 3 == 0 || i % 5 == 0)
			result += i;
	}
	return result;
}

const u64 euler2(const u64 maxInclude) {
	u64 result{ 2 };
	u64 fibo1{ 1 };
	u64 fibo2{ 2 };
	u64 fibo3{ 0 };
	while (fibo1 + fibo2 <= maxInclude) {
		fibo3 = fibo1 + fibo2;
		fibo1 = fibo2;
		fibo2 = fibo3;

		if (fibo3 % 2 == 0)
			result += fibo3;
	}
	return result;
}

const u64 euler3(const u64 prime) {
	return vectorMax(primeDecomposition(prime));
}

const u64 euler4() {
	u64 max{ 0 };
	for (u64 i{ 999 }; i >= 1; i--) {
		for (u64 j{ 999 }; j >= 1; j--) {
			if (isPalindrome(i * j) && i * j > max) {
				max = i * j;
			}
		}
	}
	return max;
}

const u64 euler5(const u64 maxInclude) {
	u64 result{ 0 };
	std::vector<u64> toDivide{ 20, 19, 18, 17, 16, 15, 14, 13, 12, 11 };

	while (!isDivisible(result, toDivide))
		result += 20;
	return result;
}

const u64 euler6(const u64 maxInclude) {
	u64 result{ 0 };
	for (u64 i{ 1 }; i <= maxInclude; i++)
		result += i;
	result *= result;

	u64 sum{ 0 };
	for (u64 i{ 1 }; i <= maxInclude; i++)
		sum += i * i;

	return result - sum;
}

const u64 euler7(const u64 rank) {
	u64 rankResult{ 0 };
	u64 result{ 0 };
	while (rankResult < rank) {
		result++;
		if (isPrime(result))
			rankResult++;
	}
	return result;
}

const u64 euler8(std::string filePath) {
	std::ifstream file;
	file.open(filePath);

	std::vector<short> numbers;

	//Init vector with all numbers
	char c;
	while (file.get(c))
		numbers.push_back(static_cast<short>(c - '0'));

	if (numbers.size() < 13)
		return 0;

	u64 max{ 0 };
	for (size_t i{ 0 }; i < numbers.size() - 13; i++) {
		std::vector<short> thirteenNumbers{ numbers.begin() + i, numbers.begin() + i + 13 };
		if (std::find(thirteenNumbers.begin(), thirteenNumbers.end(), 0) != thirteenNumbers.end())
			continue;

		u64 product{ productVector<short>(thirteenNumbers) };
		if (product > max)
			max = product;
	}
	return max;
}

const u64 euler9(const u64 sum) {
	for (u64 a{ 1 }; a <= sum; a++) {
		for (u64 b{ a }; b <= sum; b++) {
			for (u64 c{ b }; c <= sum; c++) {
				if ((pow(c, 2) == pow(b, 2) + pow(a, 2)) && (a + b + c == sum))
					return a * b * c;
			}
		}
	}
}

const u64 euler10(const u64 max) {
	return sumVector<u64>(primesBelow(max));
}


int main(int argc, char** argv) {
	//std::cout << "Euler 1 : " << euler1(1000) << '\n';                         233168
	//std::cout << "Euler 2 : " << euler2(4000000) << '\n';                      4613732
	//std::cout << "Euler 3 : " << euler3(600851475143) << '\n';                 6857
	//std::cout << "Euler 4 : " << euler4() << '\n';                             906609
	//std::cout << "Euler 5 : " << euler5(20) << '\n';                           232792560
	//std::cout << "Euler 6 : " << euler6(100) << '\n';                          25164150
	//std::cout << "Euler 7 : " << euler7(10001) << '\n';                        104743
	//std::cout << "Euler 8 : " << euler8("./TextFiles/euler8.txt") << '\n';     23514624000
	//std::cout << "Euler 9 : " << euler9(1000) << '\n';                         31875000
	//std::cout << "Euler 10 : " << euler10(10) << '\n';                         142913828923


	return 0;
}