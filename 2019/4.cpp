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

enum whatToCheck{ justAfter, justBefore, both };
	
int main() {
	long start = 111122; //236491;
	long stop = 713787;

	int numOfPasswords = 0;
	for (long int i = start; i < stop; i++) {
		std::vector<short> digits;
		collect_digits(digits, i);
		short j = 0;

		if ((std::is_sorted(digits.begin(), digits.end()))
			&& (std::adjacent_find(digits.begin(), digits.end()) != digits.end()))
		{
			// Part 2  -- just check neighbouring element being different
			auto it = std::adjacent_find(digits.begin(), digits.end());
			
			int dist = std::distance(digits.begin(), it);

			whatToCheck a = (dist < 4 && dist > 0) ? both : 
						(dist == 0) ? justAfter :justBefore;

			switch (a)
			{
				case both:
					if (*it == *(std::prev(it)) || *it == *(std::next(it, 2)))
						continue;
					break;		
				case justBefore:
					if (*it == *(std::prev(it)))
						continue;
					break;
				case justAfter:
					if (*it == *(std::next(it, 2)))
						continue;
					break;
			};
			numOfPasswords++;

				
			// end of Part 2
		}
		else
			continue;
	}
	std::cout << numOfPasswords;
	return 0;
}