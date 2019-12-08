// 4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <regex>
#define SECOND

void findTheOccurences(std::string str, std::vector<std::pair<unsigned short, char>> &vals){


	for(size_t i = 0; i < str.length(); i++) {

		vals[(int)str[i]-97].first++;

	}

};



int _tmain(int argc, _TCHAR* argv[])
{
	/* retrieving input */
	
	std::ifstream input;
	std::string entry;
	std::vector<std::string> rooms;
	std::regex north("north");

	input.open("inputs/4.txt");

	while (input >> entry) {
		entry.erase(std::remove(entry.begin(), entry.end(), '-'), entry.end());
		rooms.push_back(entry);
	}

	input.close();

	
	/* SOLUTION */

	long sum = 0; 

	
	for (std::string &room : rooms)	{
		
		std::vector<std::pair<unsigned short, char>> alphabet;
		
		for (unsigned int h = 0; h < 26; h++) {
	
		alphabet.push_back(std::pair<unsigned short, char>(0, (h+97))); // a = 97 in ASCII
		
		}
		
		//retrieving the ID:
		std::size_t pos = room.find("[");
		short ID = std::stoi(room.substr(pos-3, 3));

		//retrieveing the checksum in [] brackets:
		std::string checksum = room.substr(pos+1,5); 

		//checking the room-ness:

		findTheOccurences(room.substr(0, room.length()-10), alphabet);
		
		//sort by value using std::sort
		std::sort(alphabet.rbegin(), alphabet.rend());

		//sort by keys:
		std::vector<char> actualOrder;
		
		
		short i = 0, j = 0, k = 0;

		while (actualOrder.size() < 5) {
			
			while (alphabet[i].first == alphabet[i+1].first)
			i++;
						
			j = i; 

			if( i!=k) {
				
				while (j!=k-1)
				{
				actualOrder.push_back(alphabet[j].second);
				j--;
				
			} 
				k = actualOrder.size();
				i = k; 
			}
			else {
				actualOrder.push_back(alphabet[j].second);
				k = actualOrder.size();
				i = k;
			}
			
		}
		unsigned int a = 0;
		for (a; a < 5 ; a++) {
		
			if (actualOrder[a]!=checksum[a])
			break;
		}
		if (a==5) {
			sum+=ID;
			
#ifdef SECOND

		for ( char &letter : room )
		{
			letter += ID%26;
			if (letter > 97+25)
				letter -= 26;
		}
		
		if (std::regex_search(room,north)) 
		 std::cout << "North Pole Objects Stored at: "<< ID << std::endl;

#endif SECOND
		}
	}

		
	std::cout << "Sum of all the codes is: " << sum << std::endl;

	
	return 0;
}

