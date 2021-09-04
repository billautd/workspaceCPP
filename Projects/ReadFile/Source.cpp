#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <sstream>
#include <vector>
#include <Windows.h>

std::vector<std::string> ignoredWords{ "Progressive", "Avant-garde", "Experimental", "Melodic/Progressive", "Technical", "Technical/Melodic", "Melodic",
"Experimental/Psychedelic", "Gothic/Doom", "Progressive/Power", "Progressive/Thrash", "Experimental/Technical", "Thrash/Progressive", "Alternative/Progressive",
"Experimental/Sludge", "Black/Death/Progressive", "Grindcore/Avant-garde/Death", "Technical/Brutal", "Progressive/Death", "Progressive/Alternative",
"Atmospheric/Avant-garde", "Heavy/Progressive", "Progressive/Heavy", "Progressive/Groove", "Groove/Progressive", "Progressive/Melodic", "Progressive/Technical",
"Metalcore/Progressive", "Experimental/Depressive", "Symphonic", "Progressive/Symphonic", "Power/Progressive", "Black/Doom/Progressive", "Brutal/Technical",
"Progressive/Folk/Death", "Experimental/Progressive", "Atmospheric", "Avant-garde/Experimental", "Technical/Progressive",
"Heavy/Progressive/Gothic", "Death/Thrash/Progressive", "Progressive/Doom", "Avant-garde/Groove", "Progressive/Avant-garde", "Progressive/Brutal", "Symphonic/Progressive",
"Progressive/Gothic", "Atmospheric/Progressive", "Melodic/Technical", "Black/Doom", "Grindcore/Death", "Heavy/Progressive/Thrash", "Progressive/Southern",
"Deathcore/Death", "Progressive/Hard", "Avant-garde/Death", "Progressive/Post-metal/Rock", "Stoner", "Progressive/Atmospheric", "Avant-garde/Progressive",
"Progressive/Folk", "Folk", "Gothic/Progressive", "Ambient", "Progressive/Black", "Avant-garde/Black", "Progressive/Stoner", "Doom/Death", "Slam/Brutal",
"Doom/Sludge", "Avant-garde/Psychedelic", "Death/Progressive", "Black/Death/Doom/Progressive", "Progressive/Groover/Post-Black", "Progressive/Gothic/Goom",
"Slam/Brutal/Technical", "Experimental/Avant-garde", "Avant-garde/Sludge", "Rock/Metal", "Industrial", "Doom/Gothic", "Progressive/Sludge/Post-metal",
"Brutal", "Thrash/Speed", "Avant-garde/Atmospheric", "Brutal/Progressive", "Progressive/Industrial", "Raw", "Progressive/Stoner/Doom/Death", "Progressive/Power/Folk",
"Power/Speed", "Heavy/Power", "Power", "Power/Heavy", "Power/Thrash", "Thrash/Power", "Heavy/Thrash/Power", "Power/Doom", "Doom/Power", "Power/Death", "Death/Power",
"Gothic/Power", "Power/Gothic", "Heavy/Power/Speed", "Folk/Power/Heavy", "Neoclassical/Power", "Power/Neoclassical", " Folk/Power", "Power/Folk", "Symphonic/Melodic",
"Melodic/Symphonic", "Symphonic/Gothic", "Gothic/Symphonic", "Doom/Symphonic", "Symphonic/Doom", "Symphonic/Power", "Power/Symphonic", "Symphonic/Heavy", "Heavy/Symphonic" };


bool const AllUppercase(const std::string word) {
	//if (word.substr(0, 3).compare("RIO") == 0)
	//	return false;
	for (const char& c : word) {
		if (c <= -1)
			return true;
		if (c <= 47 || (c >= 58 && c <= 64) || (c >= 91 && c <= 96) || c >= 123)
			return true;
		if (!std::isupper(c) && !std::isdigit(c))
			return false;
	}
	return true;
}

const std::string ToLowerString(const std::string value) {
	std::string toReturn{ "" };
	for (const char c : value) {
		toReturn += std::tolower(c);
	}
	return toReturn;
}

int main() {
	SetConsoleOutputCP(CP_UTF8);

	std::ifstream file;
	std::ifstream gamesFile;
	std::ofstream newFile;
	file.open("new.txt");
	gamesFile.open("Games.txt");
	newFile.open("new2.txt", std::ios_base::app | std::ios_base::out);

	//std::string line{ "" };
	//uint64_t i{ 1 };
	//while (std::getline(file, line)) {
	//	std::istringstream ss{ line };
	//	std::vector<std::string> words;
	//	std::string word;
	//	while (ss >> word)
	//		words.emplace_back(word);

	//	std::string newLine{ words.at(0) + " " };
	//	for (int i = 1; i < words.size() - 1; i++) {
	//		std::string currentWord{ words.at(i) };
	//		std::string nextWord{ words.at(i + 1) };
	//		if (std::find(ignoredWords.begin(), ignoredWords.end(), nextWord) != ignoredWords.end() ||
	//			currentWord.compare("United") == 0)
	//			break;
	//		else
	//			newLine += (currentWord + " ");

	//	}

	//	if (newLine.at(newLine.size() - 1) == ' ')
	//		newLine = newLine.substr(0, newLine.size() - 1);
	//	newFile << newLine << '\n';





		//std::istringstream ss{ line };
		//std::vector<std::string> words;
		//std::string word;
		//while (ss >> word)
		//	words.emplace_back(word);

		//std::string newLine{ line };
		//for (const std::string& word : words) {
		//	if (AllUppercase(word))
		//		newLine += (word + " ");
		//	else
		//		break;
		//}

		//if (newLine.at(newLine.size() - 1) == ' ')
		//	newLine = newLine.substr(0, newLine.size() - 1);
		//size_t commaPos = newLine.find(',');
		//if (commaPos <= newLine.size()) {
		//	std::string beforeComma{ newLine.substr(0, commaPos) };
		//	std::string afterComma{ newLine.substr(commaPos + 2) };
		//	newLine = afterComma + " " + beforeComma;
		//}
		//newFile << newLine << '\n';

	//}

	std::string line{ "" };
	std::string gamesLine{ "" };
	bool isInGamesFile{ false };

	while (std::getline(file, line)) {
		gamesLine = "";
		gamesFile.clear();
		gamesFile.seekg(0);
		isInGamesFile = false;
		std::cout << line << '\n';

		while (std::getline(gamesFile, gamesLine) && isInGamesFile == false) {
			const std::string toLowerGames{ ToLowerString(gamesLine) };
			const std::string toLowerLine{ ToLowerString(line) };
			if (toLowerGames.compare(toLowerLine) == 0 || toLowerGames.compare("(F) " + toLowerLine) == 0 ||
				toLowerGames.compare("(S) " + toLowerLine) == 0 || toLowerGames.compare("(100F) " + toLowerLine) == 0)
				isInGamesFile = true;
		}

		if (!isInGamesFile)
			newFile << line << '\n';

	}
	return 0;
}


