#include "VotingSystem.h"
#include <string>
#include <iostream>
#include <iomanip>
#include "helper.h"
#include <Windows.h>
#include <dos.h>

//Imports the correct file depending on whether the software is running on windows or linux.
// Used for the sleep function. 
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
using namespace std;

void VotingSystem::execute() {

	//Splash screen
	splashScreen();
	char option = -1; // initialised to -1 because the value is not chosen. -1 because all characters can be represented as byte. 

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

void VotingSystem::splashScreen()
{
	string splashScreen;
	// loads the splashscreen information from the file.
	ifstream splashScreenDataFile("splashScreen.txt");

	while (getline(splashScreenDataFile, splashScreen))
	{
		cout << splashScreen << endl;
	}

	splashScreenDataFile.close();

	splash();

}

void VotingSystem::splash()
{
	HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, 2);

	cout << "      INITIALISING: ";

	char x = 219;

	cout << x;

	for (int i = 0; i < 32; i++)
	{
		Sleep(50); //stops the thread for 50ms.
		cout << x;
	}

	SetConsoleTextAttribute(H, 7);

	system("cls");
}

char VotingSystem::selectMenuOption() 
{

	HANDLE G = GetStdHandle(STD_OUTPUT_HANDLE); //Light Blue Menu
	SetConsoleTextAttribute(G, 3);

	string mainMenu;
	char selection, result = ' ';

	ifstream mainMenuDataFile("mainMenu.txt");

	while (getline(mainMenuDataFile, mainMenu)) 
	{
		cout << mainMenu << endl;
	}

	mainMenuDataFile.close();

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
		cout << "Unknown selection, please try again";

		Sleep(1000); //Stops the tread for 1sec for the user to read. 


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

	vector<Candidate> candidateData = loadCandidateData();


	// Exits the code early if the list is empty with a message. 
	if (candidateData.size() == 0) {
		cout << "The list is empty.";
		return;
	}

	int count = 0;
	while (count < candidateData.size()) {
		cout << "Candidate " << count +1 << "\nCandidate ID: " << candidateData[count].candidateId << "\nCandidate name: " << candidateData[count].firstName << " " << candidateData[count].lastName << "\n"
			<< "Candidate Votes: " << candidateData[count].votes << "\nCandidate Suburb: " << candidateData[count].suburb << "\n" << "Candidate Postcode: " << candidateData[count].postcode << "\n" << endl;


		count++;
	}



}
void VotingSystem::displayCandidateWithFewestVotes() {

	header();

	vector<Candidate> candidates = loadCandidateData();


	if (candidates.size() == 0) {
		cout << "Unable to determine the smallest number - list is empty";
		return; // exits early if the list is empty;
	}


	Candidate* leastVotedCandidate = &candidates[0];

	for (int i = 0; i < candidates.size(); i++)
	{
		if (candidates[i].votes < leastVotedCandidate->votes) {
			leastVotedCandidate = &candidates[i];
		}
	}

	cout << "Candidate id: " << leastVotedCandidate->candidateId << " (" << leastVotedCandidate->firstName << " " << leastVotedCandidate->lastName << ") has the least number of votes(votes: " << leastVotedCandidate->votes << ").";

}
void VotingSystem::displayCandidateWithMostVotes() {

	header();

	vector<Candidate> candidates = loadCandidateData();


	if (candidates.size() == 0) {
		cout << "Unable to determine the largest number - list is empty";
		return; // exits early if the list is empty;
	}

	
	Candidate* mostVotedCandidate = &candidates[0];

	for (int i = 0; i < candidates.size(); i++)
	{
		if (candidates[i].votes > mostVotedCandidate->votes) {
			mostVotedCandidate = &candidates[i];
		}
	}

	cout << "Candidate id: " << mostVotedCandidate->candidateId << " (" << mostVotedCandidate->firstName << " " << mostVotedCandidate->lastName << ") has the most number of votes (votes: " << mostVotedCandidate->votes << ").";

}

void VotingSystem::addVotes() {

	header();

	string voterId;
	string candidateId;
	fstream voterFile(voterFileName);
	fstream candidateFile(candidateFileName);


	// Makes sure there is voter and candidate data to add votes. 
	if (isFileEmpty(&voterFile) || isFileEmpty(&candidateFile)) {
		cout << "Unable to add votes - no data";
		return;
	}




	cout << "Please enter voter ID:";
	cin >> voterId;



	int voterFileRecordLocation = findRecordWithId(voterId.c_str(), &voterFile, Voter::totalRowSize, Voter::voterIdSize);

	// Makes sure the voter is in the file.
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
		candidateFile.close();
		return;
	}


	cout << "Please enter the candidate ID:";
	cin >> candidateId;


	int candidateFileRecordLocation = findRecordWithId(candidateId.c_str(), &candidateFile, Candidate::totalRowSize, Candidate::candidateIdSize);
	
	//Ensures the candidate id is valid. 
	while (candidateFileRecordLocation == -1)
	{
		cout << "Invalid candidate id. Please try again: ";
		cin >> candidateId;

		candidateFileRecordLocation = findRecordWithId(candidateId.c_str(), &candidateFile, Candidate::totalRowSize, Candidate::candidateIdSize);
	}


	// Sets the voter's status as voted. 
	voterFile.seekg(votedBitLocation);
	voterFile << '1';


	//Finds and reads the candidate's number of votes.
	int votesLocation = candidateFileRecordLocation + Candidate::candidateIdSize;
	char* votesChar = new char[Candidate::votesSize +1 ]; //buffer larger than the input to later clear the garbage data at the end of the buffer. 
	candidateFile.seekg(votesLocation);
	candidateFile.read(votesChar, Candidate::votesSize);
	votesChar[Candidate::votesSize] = 0; //clears the garbage data at the of the buffer. 
	strStrip(votesChar);
	int votes = stoi(votesChar);

	//increments the votes.
	votes++;

	//writes the number of votes back to file. 
	candidateFile.seekg(votesLocation);
	candidateFile << setfill(' ') << left
		<< setw(Candidate::votesSize) << votes;

	//clean up.
	delete[] votesChar;
	voterFile.close();
	candidateFile.close();

	cout << "Candidate " << candidateId << " has "<< votes <<" votes." << endl;

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

	//inputs from user.
	//Not heavily validated as they are for development purposes only. 
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

	// writes input to files. 
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


	//inputs from user.
	//Not heavily validated as they are for development purposes only.
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

	// writes input to files. 
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
	// buffers were created with +1 size to later delete the corrupted end. 
	char* id = new char[Voter::voterIdSize + 1];
	char* firstName = new char[Voter::firstNameSize + 1];
	char* lastName = new char[Voter::lastNameSize + 1];
	char* suburb = new char[Voter::suburbSize + 1];


	while (voterFile.peek() != -1) {
		Voter voter = Voter();
	
		// reads information from the file. 

		voterFile.read(id, Voter::voterIdSize);

		char votedBit[1];
		voterFile.read(votedBit, Voter::votedSize);
		voter.voted = votedBit[0] == '1';

		voterFile.read(firstName, Voter::firstNameSize);
		voterFile.read(lastName, Voter::lastNameSize);
		voterFile.read(suburb, Voter::suburbSize);
		voterFile.read(voter.postcode, Voter::postcodeSize);

		//deletes the corrupted ending.
		id[Voter::voterIdSize] = 0;
		firstName[Voter::firstNameSize] = 0;
		lastName[Voter::lastNameSize] = 0;
		suburb[Voter::suburbSize] = 0;

		//Removes the empty spaces from the char array
		strStrip(id);
		strStrip(firstName);
		strStrip(lastName);
		strStrip(suburb);


		//copies the char buffer array to the object's values.
		strcpy_s(voter.voterId, id);
		strcpy_s(voter.firstName, firstName);
		strcpy_s(voter.lastName, lastName);
		strcpy_s(voter.suburb, suburb);

		voterFile.ignore();

		// adds the voter to the array.
		voters.push_back(voter);

	}
	voterFile.close();
	return voters;
}

vector<Candidate> VotingSystem::loadCandidateData() {
	ifstream candidateFile(candidateFileName);
	vector<Candidate> candidates = vector<Candidate>();
	// buffers were created with +1 size to later delete the corrupted end. 
	char* id = new char[Candidate::candidateIdSize +1];
	char* firstName = new char[Candidate::firstNameSize+1];
	char* lastName = new char[Candidate::lastNameSize + 1];
	char* suburb = new char[Candidate::suburbSize + 1];
	while (candidateFile.peek() != -1) {
		Candidate candidate = Candidate();

		// reads information from the file. 
		candidateFile.read(id, Candidate::candidateIdSize);

		char votesChar[Candidate::votesSize];
		candidateFile.read(votesChar, Candidate::votesSize);
		candidate.votes = stoi(votesChar);

		candidateFile.read(firstName, Candidate::firstNameSize);
		candidateFile.read(lastName, Candidate::lastNameSize);
		candidateFile.read(suburb, Candidate::suburbSize);
		candidateFile.read(candidate.postcode, Candidate::postcodeSize);

		//deletes the corrupted ending.
		id[Candidate::candidateIdSize] = 0;
		firstName[Candidate::firstNameSize] = 0;
		lastName[Candidate::lastNameSize] = 0;
		suburb[Candidate::suburbSize] = 0;
		
		//Removes the empty spaces from the char array
		strStrip(id);
		strStrip(firstName);
		strStrip(lastName);
		strStrip(suburb);

		//copies the char buffer array to the object's values.
		strcpy_s(candidate.candidateId, id);
		strcpy_s(candidate.firstName, firstName);
		strcpy_s(candidate.lastName, lastName);
		strcpy_s(candidate.suburb, suburb);

		candidateFile.ignore();

		// adds the voter to the array.
		candidates.push_back(candidate);
	}
	delete[] id, firstName, lastName, suburb;
	candidateFile.close();
	return candidates;
}
