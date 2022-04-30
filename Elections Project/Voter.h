#include <string>
using namespace std;
#pragma once


struct Voter 
{
public:

	const static int voterIdSize = 10;
	const static int votedSize = 1;
	const static int firstNameSize = 30;
	const static int lastNameSize = 30;
	const static int suburbSize = 30;
	const static int postcodeSize = 4;


	const static int totalRowSize = voterIdSize + votedSize + firstNameSize + lastNameSize + suburbSize + postcodeSize + 2; // +2 is for the endline at the each of each record. 

	char voterId[voterIdSize];
	bool voted;

	char firstName[firstNameSize];
	char lastName[lastNameSize];
	char suburb[suburbSize];
	char postcode[postcodeSize];

};