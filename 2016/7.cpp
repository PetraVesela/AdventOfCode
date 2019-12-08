// 7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#define SECOND

int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<std::string> IPs;
	
	/* retrieving input */
	
	std::ifstream input;
	std::string line;

	input.open("input.txt");

	while (input >> line) {
		
		IPs.push_back(line);
	}
	
	/* SOLUTION */
	
	std::regex in("\\[\\w+\\]");  // '[asdfhjkl]'
	std::regex out("\\]\\w+\\["); // ']asdfhjkl['
	std::regex left("^\\w+\\[");  // 'asdfhjkah]'
	std::regex right("\\]\\w+$"); // ']asdfhjkaa'
	//first part only:
	std::regex abba(".*(.)(.)\\2\\1");
	std::regex four("(\\w)\\1\\1\\1"); // 'aaaa'
	//second part only
	std::regex aba("(.).\\1");	// must use 'positive look-ahead assertion'
	std::regex abaca("(.).\\1.\\1");
	std::regex abab("(.)(.)\\1\\2");
	std::smatch match;
	
	unsigned int validIPs = 0;
	unsigned int validSSLs = 0; 

	for (std::string & IP : IPs) {

		//retrieving the sequences:
		std::sregex_iterator itin(IP.begin(), IP.end(), in);
		std::sregex_iterator itout(IP.begin(), IP.end(), out);
		std::sregex_iterator itleft(IP.begin(), IP.end(), left);
		std::sregex_iterator itright(IP.begin(), IP.end(), right);
		std::sregex_iterator end;
		
		std::vector<std::string> inside;
		std::vector<std::string> outside;
		
		while (itin != end) {
		  std::smatch match = *itin;
		  inside.push_back(match.str());
		  inside.back().erase(0,1); // delete the first [
		  inside.back().erase(inside.back().length()-1,1); //delete the last ]

		  itin++;
		}
		
		while (itout != end) {
		  std::smatch match = *itout;
		  outside.push_back(match.str().substr(1, match.str().length()-2));
		  itout++;
		}

		while (itleft != end) {
		  std::smatch match = *itleft;
		  outside.push_back(match.str());
		  outside.back().erase(outside.back().length()-1,1);
		  itleft++;
		}
		
		while (itright != end) {
		  std::smatch match = *itright;
		  outside.push_back(match.str());
		  outside.back().erase(0,1);
		  itright++;
		}

		//evaluation of IPs:
		bool inCheck = true;
		bool outCheck = false;

		for (std::string &inner : inside)
		{
			if(std::regex_search(inner, abba) && !std::regex_search(inner, four))  //not bullet-proof!
				inCheck = false;
		}
			
		for (std::string &outer : outside)
		{
			if(std::regex_search(outer, abba)&& !std::regex_search(outer, four))
				outCheck = true;
		}


		if (inCheck && outCheck)
			validIPs++;

#ifdef SECOND
		// evaluation of SSLs:
		
		std::vector<std::string> inABA;
		
		for (std::string &inner : inside)
		{
			std::sregex_iterator itabaca(inner.begin(), inner.end(), abaca);
			std::sregex_iterator itabab(inner.begin(), inner.end(), abab);
			std::sregex_iterator itSSL(inner.begin(), inner.end(), aba);
			std::sregex_iterator sEnd;

			while (itabaca != sEnd) {
			
				std::smatch match = *itabaca;
				std::string rest = match.str().substr(2,3);
				inABA.push_back(rest);
				itabaca++;
			}

			while (itabab != sEnd) {
			
				std::smatch match = *itabab;
				std::string rest2 = match.str().substr(1,3);
				inABA.push_back(rest2);
				itabab++;
			}
			while (itSSL != sEnd) {
			
				std::smatch match = *itSSL;
				std::string temp = match.str();

				if (temp[0]!=temp[1])
				inABA.push_back(temp);
				
				itSSL++;
			}	
		
		}
		
		if (!inABA.empty()) {

			bool valid = false;
			std::vector<std::string> inBAB;

			//creating the inverse xyx -> yxy
			for (std::string &xyx : inABA)
			{
				std::string yxy = xyx.substr(1,2).append(1,xyx[1]);
				inBAB.push_back(yxy);
			}
			
			//checking if there is the inverse:
			for (std::string &outer : outside)
			{
				std::sregex_iterator outSSL(outer.begin(), outer.end(), aba);
				std::sregex_iterator itabaca(outer.begin(), outer.end(), abaca);
				std::sregex_iterator itabab(outer.begin(), outer.end(), abab);
				std::sregex_iterator sEnd;

				while (itabaca != sEnd) {
			
				std::smatch match = *itabaca;
				std::string rest = match.str().substr(2,3);
				if(inBAB.end()!=std::find(inBAB.begin(), inBAB.end(), rest))
					{
						std::cout <<match.str() <<std::endl;
						valid = true;
						break;
					}

				itabaca++;
			}

				while (itabab != sEnd) {
			
				std::smatch match = *itabab;
				std::string rest = match.str().substr(1,3);
				if(inBAB.end()!=std::find(inBAB.begin(), inBAB.end(), rest))
					{
						//std::cout <<match.str() << std::endl;
						valid = true;
						break;
					}

				itabab++;
				
				}
				while (outSSL != end) {
			
					std::smatch match = *outSSL;
					if(inBAB.end()!=std::find(inBAB.begin(), inBAB.end(), match.str()))
					{
						
						//std::cout <<match.str() <<std::endl;
						valid = true;
							break;
					}
					outSSL++;
				}
			}
			if (valid)
			{
				validSSLs++;
			}
			
		}
		
		
		
#endif
	}

	std::cout << "Number of valid IPs: "<< validIPs << "\n" << "Number of valid SSL's: " << validSSLs << "\n";

	
	input.close();
	return 0;
}

