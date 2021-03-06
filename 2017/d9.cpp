// day3.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main()
{
	std::vector<std::string> data;

	/* retrieving input */

	std::ifstream input;
	std::string tmp;

	input.open("inputs/9.txt");
	input >> tmp;
	std::vector<char> instr(tmp.begin(), tmp.end());
	input.close();


	///* SOLUTION *///

	// clean the exlamaction mark-ignored symbols
	for (size_t i = 0; i < instr.size(); i++) {
		if (instr[i] == '!')
			instr.erase (instr.begin() + i+1);
	}

	// clear the garbage
	size_t garbage = 0;
	
	size_t i = 1;
	while ( i < instr.size()) {
		if (instr[i] == '<') {
			size_t first = i;
			i -= 1;
			do {
				i++;

			} while (instr[i] != '>');
			i++;
			// count the length of the garbage:
			size_t excl = 0;
			std::vector<char> temp(instr.begin() + first+1, instr.begin() + i-1);
			for (size_t t = 0; t < temp.size(); t++) 
			{if (temp[t] == '!')
				excl++;
			}
			garbage += temp.size() - excl;

			// delete the garbage:
			instr.erase(instr.begin() + first, instr.begin() + i);
			i = first;
		}
		else i++;

	}
	// clear the comas

	for (size_t i = 0; i < instr.size(); i++) {
		 if (instr[i] == ',')
			instr.erase(instr.begin() + i);
	}


	// parse the groups:
	short level = 1;
	size_t score = 0;


	bool hasSomethingInside = false;
	i = 0;
	

	while (i < instr.size()) {
		
		switch (instr[i]){
			case '{': {
					
				if (instr[i + 1] == '{') {
					hasSomethingInside = true;
					level++;
						}
				break;
			};

			case '}': {
				score += level;
				if (instr[i + 1] == '}')
					level--;
				break;
			};
		
		}
		//

		i++;
	}

	std::cout << score << std::endl << garbage;
	return 0;
}
