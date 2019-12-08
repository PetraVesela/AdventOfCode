// 3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#define SECOND

int _tmain(int argc, _TCHAR* argv[])
{
	/* retrieving input */
	
	std::ifstream input;
	std::string instr;
	std::vector<std::vector<short>> dims;

	input.open("input.txt");

	while (input >> instr)
	{
		std::vector<short> dim;
		dim.push_back(std::stoi(instr));
		for (unsigned short i = 0; i < 2; i++)
		{
			input >> instr;
			dim.push_back(std::stoi(instr));
		}
		dims.push_back(dim);
	}

	input.close();

#ifdef SECOND

	std::vector<std::vector<short>> dims2;
	
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < dims.size(); j=j+3)
		{
			std::vector<short> dim;
			dim.push_back(dims[j][i]);
			dim.push_back(dims[j+1][i]);
			dim.push_back(dims[j+2][i]);
			dims2.push_back(dim);
		}
		
	}
	
	dims = dims2;

#endif //SECOND
	/* SOLUTION */
	unsigned int triangles = 0; 
	
	for (size_t i = 0; i < dims.size(); i++)
		if (dims[i][0]+dims[i][1] > dims[i][2] && 
			dims[i][0]+dims[i][2] > dims[i][1] && 
			dims[i][2]+dims[i][1] > dims[i][0])
			
			triangles++;

	std::cout << triangles;

	
	return 0;
}

