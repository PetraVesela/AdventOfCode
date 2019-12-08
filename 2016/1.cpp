// 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <set>

#define FIRST
#define SECOND					//choose either of these


int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<std::string> data;
	
	/* retrieving input */
	
	std::ifstream input;
	std::string instr;

	input.open("input.txt");

	while (input >> instr)
	{
		data.push_back(instr);
	}
	
	input.close();

	/* SOLUTION */

	// init
	/*enum dir {xp = 0, yp, xn, yn};
	dir direction = yp;*/

	short direction = 1;
	short a[2] = {0,0};

	
	// length of the step:
	std::regex distance("[[:digit:]]+");
	std::smatch match;


	for (std::string & instruction : data)
	{
		//determine the direction:
		if (instruction[0] == 'R')
		{
			direction--;
			if (direction == -1)
				direction = 3;
			
		}
		else
		{
			direction++;
			if (direction == 4)
				direction = 0;
		}

		// making the move
		std::regex_search(instruction, match, distance);
		short step = std::stoi(match[0]);
		
		switch(direction)
		{
		case 0:
			a[0] += step;
			break;
		case 1:
			a[1] += step;
			break;
		case 2:
			a[0] -= step;
			break;
		case 3:
			a[1] -= step;
			break;
		}
		
	
#ifdef SECOND
	
		//keeping the track of all the visited positions
		std::set<std::pair<short, short>> memory;
		memory.insert(std::pair<short,short>(0,0));
		
		//bulgarian constant section
		  bool temp = 1;
		  short b[2] = {0,0};	   //


		for (short i = 0; i < step; i++)
		{
			switch(direction)
			{
			case 0:
				if (memory.insert(std::pair<short,short>(a[0]-i,a[1])).second == false)
				{
					temp = false;
					b[0] = a[0]-i;
					b[1] = a[1];
					break;				//if you find an already visited position, remember the position and go home
				}
				else continue;
				
			case 1:
				if (memory.insert(std::pair<short,short>(a[0],a[1]-i)).second == false)
				{
					temp = false;
					b[0] = a[0];
					b[1] = a[1]-i;
					break;
				}
				else continue;

			case 2:
				if (memory.insert(std::pair<short,short>(a[0]+i,a[1])).second == false)
				{
					temp = false;
					b[0] = a[0]+i;
					b[1] = a[1];
					break;	
				}
				else continue;

			case 3:
				if (memory.insert(std::pair<short,short>(a[0],a[1]+i)).second == false)
				{
					temp = false;
					b[0] = a[0];
					b[1] = a[1]+i;
					break;
				}
				else continue;
			}

		}

		if(!temp)
			break;
		
	#endif	
	}

	

#ifdef FIRST
	std::cout << "Solution to the 1st part is: " << abs(a[0])+abs(a[1]) << std::endl;
#endif

#ifdef SECOND
	std::cout << "Solution to the 2nd part is: " << abs(b[0])+abs(b[1]) << std::endl;
#endif
	return 0;
}

