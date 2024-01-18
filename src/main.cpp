/*
 * 2014 Clemens Zangl
 * Calculation of primitive polynomial addition / multiplication table.
 *
 * main.cpp
 * A small tool to generate addition and multiplication tables based
 * on using primitive polynomials.
 */

#include <bitset>
#include <fstream>
#include <iostream>
#include <string>


#include "draw_tables.h"
#include "galois_number.h"

using namespace std;
using namespace Galois;

bool QueryNullOrOne() {
  char selection = '0';
  while (!(std::cin >> selection) || selection != '1' && selection != '0') {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid input. Please enter a 1 or 0. Please enter again." << endl;
  }
  if ('1' == selection) {
    return true;
  }
  return false;
}

bool QueryBool() {
  char selection = 'n';
  while (!(std::cin >> selection) || selection != 'y' && selection != 'n') {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid input. Please select again." << endl;
  }
  if ('y' == selection) {
    return true;
  }
  return false;
}

bool QueryStoreInFile(std::ofstream &fileStream) {
  std::cout << "Would you like to store the results in a text file (y/n)? "
            << std::endl;

  if (false == QueryBool()) {
    return false;
  }
  for (;;) {
    std::cout << "Please enter a file to store the output data (or press ENTER "
                 "for the default path)."
              << std::endl;
    std::string filePath;
    std::cin.clear();
    std::cin.sync();
    std::getline(std::cin, filePath);

    if (filePath == "") {
      filePath = "results.txt";
    }

    // try to open file for writing
    fileStream.open(filePath, std::ios::out | std::ios::trunc);

    if (false == fileStream.is_open()) {
      // file couldn't be opened.
      std::cout << "File could not be opened. Please select a different file."
                << std::endl;
      continue;
    }
    return true;
  }
}

int main() {
  bitset<1024> primitivePoly(0);

  // query generator polynomial from user. We support at most
  // polynomials of degree 5, as otherwise the tables will
  // get too long.
  for (int i = 5; i >= 0; i--) {
    cout << "Please enter primitive polynomial coefficient for x^" << i << ":"
         << endl;
    primitivePoly[i] = QueryNullOrOne();
  }

  // ask if the user would like to store the results in a file
  std::ofstream fileStream;
  if (QueryStoreInFile(fileStream)) {
    Galois::IO::DrawAdditionTable(primitivePoly, fileStream);
    Galois::IO::DrawMultiplicationTable(primitivePoly, fileStream);
    fileStream.close();
  }

  // print the addition and multiplication tables on stdout
  Galois::IO::DrawAdditionTable(primitivePoly, std::cout);
  Galois::IO::DrawMultiplicationTable(primitivePoly, std::cout);

  return 0;
}
