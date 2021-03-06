// d12.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>

int main()
{
	/* retrieving input */

	std::ifstream input;
	std::string line;

	std::map < size_t, std::vector<size_t>> programs;
	//std::vector<std::vector<size_t>> programs;
	std::vector<size_t> connectedPrograms;

	input.open("inputs/12.txt");
	size_t i = 0;
	while (std::getline(input, line)) {

		std::stringstream ss(line);
		std::vector<size_t> tmp;
		std::string s;
		ss >> i;
		ss >> s;	//throw away the  '<->'
		for (s; ss >> s; )
			tmp.push_back(stoi(s));
		programs.insert(std::pair<size_t, std::vector<size_t>>(i, tmp));
	}

	input.close();
	 
	/* SOLUTION */
	short groups = 0;
	while (!programs.empty()) {
		connectedPrograms.clear();
		connectedPrograms.insert(connectedPrograms.end(), programs.begin()->second.begin(), programs.begin()->second.end());
		int sizeBefore = connectedPrograms.size();
		int sizeAfter = 0;
		while (sizeBefore != sizeAfter) {
	
			sizeBefore = connectedPrograms.size();
			for (size_t a = 0; a < connectedPrograms.size(); a++) {
		
				connectedPrograms.insert(connectedPrograms.end(), programs[connectedPrograms[a]].begin(), programs[connectedPrograms[a]].end());
				std::sort(connectedPrograms.begin(), connectedPrograms.end());
				std::vector<size_t>::iterator it;
				it = std::unique(connectedPrograms.begin(), connectedPrograms.end());
				connectedPrograms.resize(std::distance(connectedPrograms.begin(), it));
			}
			sizeAfter = connectedPrograms.size();
		}

		//std::cout << connectedPrograms.size();
		// Delete the regrouped elements and start again: 

		for (size_t a = 0; a < connectedPrograms.size(); a++) {
			programs.erase(connectedPrograms[a]);
		}
		groups++;


	}

	std::cout << std::endl << groups;
    return 0;
}

