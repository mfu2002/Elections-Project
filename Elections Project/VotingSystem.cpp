#include "VotingSystem.h"
#include <string>
using namespace std;

void VotingSystem::execute() {
	bool running = true;
	int option = -1;
	while (running)
	{
		int option = selectMenuOption();
		switch (option)
		{
		case 1:
			displayCandidateInfo();
			break;
		case 2:
			addVotes();
			break;
		case 3:
			displayCandidateWithFewestVotes();
			break;
		case 4:
			displayCandidateWithMostVotes();
			break;
		case 5:
			running = false;
			break;
		}
	}
}

char VotingSystem::selectMenuOption() {
	return 'a';
}

void VotingSystem::displayCandidateInfo() {
}
void VotingSystem::addVotes() {

	///TODO: remember to change dataChanged variable to true if data is changed.

}
void VotingSystem::displayCandidateWithFewestVotes() {
}
void VotingSystem::displayCandidateWithMostVotes() {
}


void VotingSystem::loadVoterData() {
	string recordValue;
	ifstream voterFile(voterFileName);
	while (voterFile.peek() != -1) {
		Voter* voter = new Voter();
		std::getline(voterFile, recordValue, '|');
		voter->voterId = recordValue;

		std::getline(voterFile, recordValue, '|');
		voter->firstName = recordValue;

		std::getline(voterFile, recordValue, '|');
		voter->lastName = recordValue;

		std::getline(voterFile, recordValue, '|');
		voter->suburb = recordValue;

		std::getline(voterFile, recordValue, '|');
		voter->postcode = stoi(recordValue);

		std::getline(voterFile, recordValue);
		voter->voted = recordValue == "1";
		voters.push_back(*voter);

	}

	voterFile.close();
}

void VotingSystem::loadCandidateData() {
	string recordValue;
	ifstream candidateFile(candidateFileName);
	while (candidateFile.peek() != -1) {
		Candidate* candidate = new Candidate();
		std::getline(candidateFile, recordValue, '|');
		candidate->candidateId = recordValue;

		std::getline(candidateFile, recordValue, '|');
		candidate->firstName = recordValue;

		std::getline(candidateFile, recordValue, '|');
		candidate->lastName = recordValue;

		std::getline(candidateFile, recordValue, '|');
		candidate->suburb = recordValue;

		std::getline(candidateFile, recordValue, '|');
		candidate->postcode = recordValue;

		std::getline(candidateFile, recordValue);
		candidate->votes = stoi(recordValue);

		candidates.push_back(*candidate);
	}

	candidateFile.close();
}

void VotingSystem::saveVoterData() {
	ofstream voterFile(voterFileName);

	for (Voter voter : voters)
	{
		voterFile << voter.voterId + '|' + voter.firstName + '|' + voter.lastName + '|' + voter.suburb + '|' + voter.postcode + '|' + (voter.voted ? '1' : '0') + '\n';
	}

	voterFile.close();
}

void VotingSystem::saveCandidateData() {
	ofstream candidateFile(candidateFileName);

	for (Candidate candidate : candidates)
	{
		candidateFile << candidate.candidateId + '|' + candidate.firstName + '|' + candidate.lastName + '|' + candidate.suburb + '|' + candidate.postcode + '|' + to_string(candidate.votes) + '\n';
	}

	candidateFile.close();
}


VotingSystem::VotingSystem()
{
	loadCandidateData();
	loadVoterData();
}

VotingSystem::~VotingSystem()
{
	if (dataChanged) {
		saveVoterData();
		saveCandidateData();
	}
}