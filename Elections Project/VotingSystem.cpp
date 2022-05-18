#include "VotingSystem.h"
#include <string>
#include <iostream>
#include <iomanip>
#include "helper.h"
#include <Windows.h>
#include <dos.h>
using namespace std;

void splash();
void delay(int length);

void VotingSystem::execute() {

	splashScreen();
	char option = -1;

	while (option != 'Q')
	{
		option = selectMenuOption();
		switch (option)
		{
		case 'P':
			displayCandidateInfo();
			break;
		case 'A':
			addVotes();
			break;
		case 'S':
			displayCandidateWithFewestVotes();
			break;
		case 'L':
			displayCandidateWithMostVotes();
			break;
		case 'V':
			addVoter();
			break;
		case 'C':
			addCandidate();
			break;
		}
	}
}

void VotingSystem::splashScreen() //logo
{
	string splashScreen;

	ifstream MyReadFile("splashScreen.txt");

	while (getline(MyReadFile, splashScreen))
	{
		cout << splashScreen << endl;
	}

	MyReadFile.close();

	splash();

}

void splash() //loading animation
{
	HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, 2);

	cout << "      INITIALISING: ";

	char x = 219;

	cout << x;

	for (int i = 0; i < 32; i++)
	{
		delay(5);
		cout << x;
	}

	SetConsoleTextAttribute(H, 7);

	system("cls");
}

void delay(int length) //Allows for loading animation
{
	int increase = 0, time;

	time = length * 1e6;

	for (int j = 0; j < time; j++) 
	{
		increase *= j;
		increase++;
		increase++;
	}
}

char VotingSystem::selectMenuOption() 
{

	HANDLE G = GetStdHandle(STD_OUTPUT_HANDLE); //Light Blue Menu
	SetConsoleTextAttribute(G, 3);

	string mainMenu;
	char selection, result = ' ';

	ifstream MyReadFile("mainMenu.txt");

	while (getline(MyReadFile, mainMenu)) 
	{
		cout << mainMenu << endl;
	}

	MyReadFile.close();

	SetConsoleTextAttribute(G, 7); //Reverts Colour Back To White

	cout << "Enter Selection: ";
	
	cin >> selection;

	switch (selection) //Ensures that both lower and upper case accepted. 
	{
	case 'P':
	case 'p':
	{
		result = 'P';
		break;
	}
	case 'A':
	case 'a':
	{
		result = 'A';
		break;
	}
	case 'S':
	case 's':
		result = 'S';
		break;

	case 'L':
	case 'l':
	{
		result = 'L';
		break;
	}
	case 'V':
	case 'v':
	{
		result = 'V';
		break;
	}
	case 'C':
	case 'c':
	{
		result = 'C';
		break;
	}
	case 'Q':
	case 'q':
	{
		result = 'Q';
		break;
	}
	default:
	{
		for (int h = 0; h < 1; h++)
		{
			cout << "Invalid Input - Please Try Again: ";

			delay(10);
		}

		system("cls");
	}
	}

	system("cls");
	return result;
}

void header()
{
	HANDLE D = GetStdHandle(STD_OUTPUT_HANDLE); //Light Blue Menu
	SetConsoleTextAttribute(D, 3);

	cout << "\t\t\t\t\t\t  FLASH INDUSTRIES" <<endl;

	SetConsoleTextAttribute(D, 7);
}

void VotingSystem::displayCandidateInfo() {

	header();
	//gets to here
	vector<Candidate> CandidateData = loadCandidateData();
	int count = 0;
	while (count < CandidateData.size()) {
		cout << "Candidate " << count +1 << "\nCandidate ID: " << CandidateData[count].candidateId << "\nCandidate name: " << CandidateData[count].firstName << " " << CandidateData[count].lastName << "\n"
			<< "Candidate Votes: " << CandidateData[count].votes << "\nCandidate Suburb: " << CandidateData[count].suburb << "\n" << "Candidate Postcode: " << CandidateData[count].postcode << "\n" << endl;


		count++;
	}

}
void VotingSystem::displayCandidateWithFewestVotes() {

	header();

}
void VotingSystem::displayCandidateWithMostVotes() {

	header();
}

void VotingSystem::addVotes() {

	header();

	string voterId;
	string candidateId;

	cout << "Please enter voter ID:";
	cin >> voterId;


	fstream voterFile(voterFileName);

	int voterFileRecordLocation = findRecordWithId(voterId.c_str(), &voterFile, Voter::totalRowSize, Voter::voterIdSize);


	while (voterFileRecordLocation == -1)
	{
		cout << "Invalid voter id. Please try again: ";
		cin >> voterId;

		voterFileRecordLocation = findRecordWithId(voterId.c_str(), &voterFile, Voter::totalRowSize, Voter::voterIdSize);
	}

	int votedBitLocation = voterFileRecordLocation + Voter::voterIdSize;

	voterFile.seekg(votedBitLocation);

	char votedBit[1];
	voterFile.read(votedBit, 1);
	if (votedBit[0] == '1') {
		cout << "You have already voted. You can't vote again. ";
		voterFile.close();
		return;
	}


	cout << "Please enter the candidate ID:";
	cin >> candidateId;

	fstream candidateFile(candidateFileName);

	int candidateFileRecordLocation = findRecordWithId(candidateId.c_str(), &candidateFile, Candidate::totalRowSize, Candidate::candidateIdSize);

	while (candidateFileRecordLocation == -1)
	{
		cout << "Invalid candidate id. Please try again: ";
		cin >> candidateId;

		candidateFileRecordLocation = findRecordWithId(candidateId.c_str(), &candidateFile, Candidate::totalRowSize, Candidate::candidateIdSize);
	}



	voterFile.seekg(votedBitLocation);
	voterFile << '1';


	int votesLocation = candidateFileRecordLocation + Candidate::candidateIdSize;
	char* votesChar = new char[Candidate::votesSize +1 ];
	candidateFile.seekg(votesLocation);
	candidateFile.read(votesChar, Candidate::votesSize);
	votesChar[Candidate::votesSize] = 0;
	strStrip(votesChar);
	int votes = stoi(votesChar);
	votes++;

	candidateFile.seekg(votesLocation);
	candidateFile << setfill(' ') << left
		<< setw(Candidate::votesSize) << votes;

	delete[] votesChar;
	voterFile.close();
	candidateFile.close();

	cout << "Voter " << voterId << " voted for candidate " << candidateId << " successfully." << endl;

}

int VotingSystem::findRecordWithId(const char* id, fstream* file, int recordLength, const int idLength) {

	int pos = 0;
	char* currentId = new char[idLength + 1];  // +1 because readline returns a corrupted ending.  
	file->seekg(pos);

	while (file->peek() != -1)
	{
		file->read(currentId, idLength);
		currentId[idLength] = 0; // to remove that corrupted ending and set it to null;
		strStrip(currentId);

		if (strcmp(currentId, id) == 0) {
			delete[] currentId;
			return pos;
		}
		pos += recordLength;
		file->seekg(pos);
	}
	delete[] currentId;
	return -1;
}


void VotingSystem::addVoter() {

	header();

	Voter voter = Voter();
	cout << "Voter Id: ";
	cin >> voter.voterId;

	cout << "First Name: ";
	cin >> voter.firstName;

	cout << "Last Name: ";
	cin >> voter.lastName;

	cout << "Suburb: ";
	cin >> voter.suburb;

	cout << "Postcode: ";
	cin >> voter.postcode;

	char voted;
	cout << "Voted: ";
	cin >> voted;

	voter.voted = voted == '1';


	ofstream voterFile(voterFileName, ios_base::app);
	voterFile << setfill(' ') << left
		<< setw(Voter::voterIdSize) << voter.voterId
		<< setw(Voter::votedSize) << (voter.voted ? '1' : '0')
		<< setw(Voter::firstNameSize) << voter.firstName
		<< setw(Voter::lastNameSize) << voter.lastName
		<< setw(Voter::suburbSize) << voter.suburb
		<< setw(Voter::postcodeSize) << voter.postcode << '\n';
	voterFile.close();
}

void VotingSystem::addCandidate() {

	header();

	Candidate candidate = Candidate();
	cout << "Candidate Id: ";
	cin >> candidate.candidateId;

	cout << "First Name: ";
	cin >> candidate.firstName;

	cout << "Last Name: ";
	cin >> candidate.lastName;

	cout << "Suburb: ";
	cin >> candidate.suburb;

	cout << "Postcode: ";
	cin >> candidate.postcode;


	candidate.votes = 0;


	ofstream candidateFile(candidateFileName, ios_base::app);
	candidateFile << setfill(' ') << left
		<< setw(Candidate::candidateIdSize) << candidate.candidateId
		<< setw(Candidate::votesSize) << candidate.votes
		<< setw(Candidate::firstNameSize) << candidate.firstName
		<< setw(Candidate::lastNameSize) << candidate.lastName
		<< setw(Candidate::suburbSize) << candidate.suburb
		<< setw(Candidate::postcodeSize) << candidate.postcode << '\n';
	candidateFile.close();
}



vector<Voter> VotingSystem::loadVoterData() {
	fstream voterFile(voterFileName);
	vector<Voter> voters = vector<Voter>();
	char* id = new char[Voter::voterIdSize + 1];
	char* firstName = new char[Voter::firstNameSize + 1];
	char* lastName = new char[Voter::lastNameSize + 1];
	char* suburb = new char[Voter::suburbSize + 1];
	while (voterFile.peek() != -1) {
		Voter voter = Voter();
	
		voterFile.read(id, Voter::voterIdSize);

		char votedBit[1];
		voterFile.read(votedBit, Voter::votedSize);
		voter.voted = votedBit[0] == '1';

		voterFile.read(firstName, Voter::firstNameSize);
		voterFile.read(lastName, Voter::lastNameSize);
		voterFile.read(suburb, Voter::suburbSize);
		voterFile.read(voter.postcode, Voter::postcodeSize);

		id[Voter::voterIdSize] = 0;
		firstName[Voter::firstNameSize] = 0;
		lastName[Voter::lastNameSize] = 0;
		suburb[Voter::suburbSize] = 0;


		strStrip(id);
		strStrip(firstName);
		strStrip(lastName);
		strStrip(suburb);

		strcpy_s(voter.voterId, id);
		strcpy_s(voter.firstName, firstName);
		strcpy_s(voter.lastName, lastName);
		strcpy_s(voter.suburb, suburb);

		voterFile.ignore();
		voters.push_back(voter);

	}
	voterFile.close();
	return voters;
}

vector<Candidate> VotingSystem::loadCandidateData() {
	ifstream candidateFile(candidateFileName);
	vector<Candidate> candidates = vector<Candidate>();
	char* id = new char[Candidate::candidateIdSize +1];
	char* firstName = new char[Candidate::firstNameSize+1];
	char* lastName = new char[Candidate::lastNameSize + 1];
	char* suburb = new char[Candidate::suburbSize + 1];
	while (candidateFile.peek() != -1) {
		Candidate candidate = Candidate();

		candidateFile.read(id, Candidate::candidateIdSize);

		char votesChar[Candidate::votesSize];
		candidateFile.read(votesChar, Candidate::votesSize);
		candidate.votes = stoi(votesChar);

		candidateFile.read(firstName, Candidate::firstNameSize);
		candidateFile.read(lastName, Candidate::lastNameSize);
		candidateFile.read(suburb, Candidate::suburbSize);
		candidateFile.read(candidate.postcode, Candidate::postcodeSize);

		id[Candidate::candidateIdSize] = 0;
		firstName[Candidate::firstNameSize] = 0;
		lastName[Candidate::lastNameSize] = 0;
		suburb[Candidate::suburbSize] = 0;
		

		strStrip(id);
		strStrip(firstName);
		strStrip(lastName);
		strStrip(suburb);

		strcpy_s(candidate.candidateId, id);
		strcpy_s(candidate.firstName, firstName);
		strcpy_s(candidate.lastName, lastName);
		strcpy_s(candidate.suburb, suburb);

		candidateFile.ignore();

		candidates.push_back(candidate);
	}
	delete[] id, firstName, lastName, suburb;
	candidateFile.close();
	return candidates;
}
