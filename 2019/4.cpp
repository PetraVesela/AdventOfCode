#include <algorithm>
#include <iostream>
#include <vector>
#include <regex>

void collect_digits(std::vector<short>& digits, long num) {
	if (num > 9) {
		collect_digits(digits, num / 10);
	}
	digits.push_back(num % 10);
}

int main() {
	long start = 236491; // input
	long stop = 713787;
	std::regex repeated("(\\d)\\1{2,}"); 
	std::regex couple("(\\d)\\1{1}");

	int numOfPasswords = 0;
	for (long int i = start; i < stop; i++) {
		std::vector<short> digits;
		collect_digits(digits, i);
		short j = 0;

		if ((std::is_sorted(digits.begin(), digits.end()))
			&& (std::adjacent_find(digits.begin(), digits.end()) != digits.end()))
		{
			// Part 2  --  check with regex 
			std::string tmp = std::to_string(i);
			std::smatch res;
			std::string tmpPrefix, tmpSuffix;

			std::regex_search(tmp, res, repeated); // find a sequence longer than 2
			if (!res.empty()) {

				std::smatch resPrefix, resSuffix;
				tmpPrefix = res.prefix().str();	 // check if there are 2 same either in prefix...

				std::regex_search(tmpPrefix, resPrefix, couple);
				if (!resPrefix.empty()) { // make sure it's not a triplet
					
					std::regex_match(tmpPrefix, res, repeated);
					if (res.empty()) { // not a triplet
						numOfPasswords++;
						continue;
					}
					
				}

				tmpSuffix = res.suffix();	 // ... or in suffix

				std::regex_search(tmpSuffix, resSuffix, couple);
				if (!resSuffix.empty())
				{
					std::regex_match(tmpSuffix, res, repeated);
					if (res.empty()) {
						numOfPasswords++;
						continue;
					}
				}
			}
			else numOfPasswords++;

		}
		else continue;
	}

	std::cout << numOfPasswords;
	return 0;
}