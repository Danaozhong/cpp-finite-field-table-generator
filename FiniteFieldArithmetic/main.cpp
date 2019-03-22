/*
* 2014 IceFire Editions
* Calculation of primitive polynomial addition / multiplication table.
*
* main.cpp
* A small tool to generate addition and multiplication tables based
* on using primitive polynomials. This software is open-source and can 
* be used, modified, etc. :)
*/

#include <fstream>
#include <iostream>
#include <bitset>
#include "GaloisNumber.h"


using namespace std;
using namespace Galois;


bool QueryNullOrOne()
{
	char selection = '0';
	while (!(std::cin >> selection) || selection != '1' && selection != '0')
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input. Please select again." << endl;
	}
	if ('1' == selection)
	{
		return true;
	}
	return false;
}

bool QueryBool()
{
	char selection = 'n';
	while (!(std::cin >> selection) || selection != 'y' && selection != 'n')
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input. Please select again." << endl;
	}
	if ('y' == selection)
	{
		return true;
	}
	return false;
}

bool QueryStoreInFile(std::ofstream &fileStream)
{
	std::cout << "Would you like to store the results in a text file (y/n)? " << std::endl;

	if (false == QueryBool())
	{
		return false;
	}
	for (;;)
	{
		std::cout << "Please enter a file to store the output data (or press ENTER for the default path)." << std::endl;
		std::string filePath;
		std::cin.clear();
		std::cin.sync();
		std::getline(std::cin, filePath); 

		if (filePath == "")
		{
			filePath = "C:\\results.txt";
		}
		
		/*if (boost::filesystem::exists(filePath))
		{
			std::cout << "File already exists! Would you like to overwrite (y/n)?" << std::endl;
			if (false == QueryBool())
			{
				continue;
			}
		}
		*/

		// try to open file for writing
		fileStream.open(filePath, std::ios::out | std::ios::trunc);

		if (false == fileStream.is_open())
		{
			// file couldn't be opened.
			std::cout << "File could not be opened. Please select a different file." << std::endl;
			continue;
		}
		return true;
	}
}

int main()
{
	bitset<1024> primitivePoly(0);

	// query generator polynomial from user
	for (int i = 5; i >= 0; i--)
	{
		cout << "Please enter primitive polynom parameter for position x^" << i << ":" << endl;
		bool param = QueryNullOrOne();
		primitivePoly[i] = 0;
		if (true == param)
		{
			primitivePoly[i] = 1;
		}
	}

	// ask if the user would like to store the results in a file
	std::ofstream fileStream;
	if (QueryStoreInFile(fileStream))
	{
		Galois::IO::DrawAdditionTable(primitivePoly, fileStream);
		Galois::IO::DrawMultiplicationTable(primitivePoly, fileStream);
		fileStream.close();
	}

	// user GUI output
	Galois::IO::DrawAdditionTable(primitivePoly, std::cout);
	Galois::IO::DrawMultiplicationTable(primitivePoly, std::cout);


	return 0;
}
