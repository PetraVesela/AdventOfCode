// 4.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <fstream>
#include <map>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <ctime>
#include <regex>
#include <iomanip>
#include <vector>

void updateMinutes(std::vector<int> &minutes, const std::vector<int> &eventTimestamps) {

	if (!eventTimestamps.size())
		return;

	for (int i = 0; i < eventTimestamps.size(); i += 2) 
		std::transform(minutes.begin() + eventTimestamps[i], minutes.begin() + eventTimestamps[i + 1], minutes.begin() + eventTimestamps[i], [](int x) {return x + 1; });
	
};

int main()
{
	std::ifstream input;
	std::string line, timestamp;
	std::map<time_t, std::string> instrs;
		
	input.open("inputs/4.txt");
	size_t i = 0;
	const std::regex ID("#[0-9]+");
	std::smatch match;

	// first, order the events by the timestamp:
	while (std::getline(input, line)) {
		
		timestamp = line.substr(1, 16);
		timestamp.replace(timestamp.begin(), timestamp.begin() + 2, "20"); //normalize to 2018
		struct tm tm = {0}; // don't forget to initialize to zero!
		std::istringstream iss(timestamp);
		iss >> std::get_time(&tm, "%Y-%m-%d %R");
		time_t time = mktime(&tm);
		
		instrs.insert(std::pair<time_t, std::string>(time, line));
	}

	std::unordered_map<int, std::vector<int>> plan;
	unsigned int currentID = 0;

	for (auto it = instrs.begin(); it != instrs.end(); it++) {

		if (it->second[25] == '#') {
			// get the current ID:
			std::sregex_iterator itID(it->second.begin(), it->second.end(), ID);
			std::smatch match = *itID;
			currentID = std::stoi(match.str().erase(0, 1));
			it++;
			// get adjacent instructions:

			std::vector<int> eventTimestamps;		// provided that guide starts and ends the shift awake.
			while (it != instrs.end() && it->second[25] != '#') {
				eventTimestamps.push_back(std::stoi(it->second.substr(15, 16)));
				it++;
			}

			// add it to the "plan" if it's not there yet
			if (!plan.count(currentID)) {
				std::vector<int>minutes(60, 0);
				updateMinutes(minutes, eventTimestamps);
				plan.insert(std::pair<int, std::vector<int>>(currentID, minutes));
			}
			else
				updateMinutes(plan[currentID], eventTimestamps);
			it--; // to get back to the ID-containing line
		}
	}
		unsigned int maximum = 0;
		for ( auto &p : plan)
		{
			unsigned int sum = 0;
			for (unsigned short i = 0; i < 60; i++)
				sum += p.second[i];
			
			std::cout << p.first << "-" << *std::max_element(p.second.begin(), p.second.end()) << std::endl;
			std::cout << sum << std::endl;

			// you can finish this by hand <3
		}
	    return 0;
}

