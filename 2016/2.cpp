// 2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>

#define FIRST
//#define SECOND

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
	

	///* SOLUTION *///


#ifdef FIRST
	/* Keypad implemented like:
		
		-1 1|0 1|1 1		1|2|3
		-1 0|0 0|1 0		4|5|6
		-1 1|0-1|1-1		7|8|9
	*/	
		short position[2] = {0, 0};
#endif //FIRST

#ifdef SECOND
	/* Keypad implemented like:
			|0 2|					1
		-1 1|0 1|1 1			  2|3|4
   -2 0|-1 0|0 0|1 0|2 0		5|6|7|8|9
		-1 1|0-1|1-1			  A|B|C
			|0-2|					D
	*/
		short position[2] = {-2,0};
#endif //SECOND

	std::cout << "Code is:" << std::endl;

	for (std::string &line : data )
	{

		for (size_t i = 0; i < line.length(); i++)
		{
			
#ifdef FIRST
			switch(line[i])
			{
			case 'L':
				position[0]--;
				if (position[0] == -2)
					position[0] = -1;
				break;
			case 'R':
				position[0]++;
				if (position[0] == 2)
					position[0] = 1;
				break;
			case 'U':
				position[1]++;
				if (position[1] == 2)
					position[1] = 1;
				break;
			case 'D':
				position[1]--;
				if (position[1] == -2)
					position[1] = -1;
				break;

			}
#endif // FIRST
		
#ifdef SECOND
		switch(line[i])
			{
				case 'L':
				position[0]--;
				if ((position[0] == -3) || ((position[0]==-2) && (abs(position[1])!=0)) || ((position[0]==-1) && (abs(position[1])==2)))
					position[0]++;
				break;
			case 'R':
				position[0]++;
				if ((position[0] == 3) || ((position[0]==2) && (abs(position[1])!=0)) || ((position[0]==1) && (abs(position[1])==2)))
					position[0]--;
				break;
			case 'U':
				position[1]++;
				if ((position[1] == 3) || ((position[1]==2) && (abs(position[0])!=0)) || ((position[1]==1) && (abs(position[0])==2)))
					position[1]--;
				break;
			case 'D':
				position[1]--;
				if ((position[1] == -3) || ((position[1]==-2) && (abs(position[0])!=0)) || ((position[1]==-1) && (abs(position[0])==2)))
					position[1]++;
				break;
			}
#endif //SECOND
		}

		std::cout << position[0]<< " " << position[1] << std::endl; 

	} 
	return 0;
}

