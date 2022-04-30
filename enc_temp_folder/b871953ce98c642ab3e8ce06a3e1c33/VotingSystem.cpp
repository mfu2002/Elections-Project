#include "VotingSystem.h"
#include <string>
#include <iostream>
#include <iomanip>
#include "helper.h"
using namespace std;

void VotingSystem::execute() {
	bool running = true;
	int option = -1;

	auto test = loadVoterData();

	while (running)
	{
		int option = selectMenuOption();
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
			AddCandidate();
			break;
		case 'Q':
			running = false;
			break;
		}
	}
}

char VotingSystem::selectMenuOption() {
	return 'A';
}

void VotingSystem::displayCandidateInfo() {
}
void VotingSystem::displayCandidateWithFewestVotes() {
}
void VotingSystem::displayCandidateWithMostVotes() {
}

void VotingSystem::addVotes() {

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

		int candidateFileRecordLocation = findRecordWithId(candidateId.c_str(), &candidateFile, Candidate::totalRowSize, Candidate::candidateIdSize);
	}



	voterFile.seekg(votedBitLocation);
	voterFile << '1';


	int votesLocation = candidateFileRecordLocation + Candidate::candidateIdSize;
	char* votesChar = new char[Candidate::votesSize +1 ];
	candidateFile.seekg(votesLocation);
	candidateFile.read(votesChar, Candidate::votesSize);
	votesChar[Candidate::votesSize] = 0;
	strtrim(votesChar);
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
		strtrim(currentId);

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

void VotingSystem::AddCandidate() {
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


		strtrim(id);
		strtrim(firstName);
		strtrim(lastName);
		strtrim(suburb);

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
		

		strtrim(id);
		strtrim(firstName);
		strtrim(lastName);
		strtrim(suburb);

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
