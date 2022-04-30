#include <string>
using namespace std;
#pragma once


struct Candidate 
{

	const static int candidateIdSize = 10;
	const static int votesSize = 10;
	const static int firstNameSize = 30;
	const static int lastNameSize = 30;
	const static int suburbSize = 30;
	const static int postcodeSize = 4;


	const static int totalRowSize = candidateIdSize + votesSize + firstNameSize + lastNameSize + suburbSize + postcodeSize + 2; // +2 is for the endline at the each of each record. 


	char candidateId[candidateIdSize];
	int votes;

	char firstName[firstNameSize];
	char lastName[lastNameSize];
	char suburb[suburbSize];
	char postcode[postcodeSize];


};