#include <string>
#include <vector>
#include <fstream>
#include "Candidate.h"
#include "Voter.h"
using namespace std;
#pragma once


class VotingSystem
{
public:
	VotingSystem();
	~VotingSystem();
	void execute();


private:
	/// <summary>
	/// Stores all the candidate information in the memory.
	/// </summary>
	vector<Candidate> candidates = vector<Candidate>();

	/// <summary>
	/// Stores all the voter information in the memory.
	/// </summary>
	vector<Voter> voters = vector<Voter>();

	/// <summary>
	/// 
	/// </summary>
	const string voterFileName = "Voter.txt";

	/// <summary>
	/// 
	/// </summary>
	const string candidateFileName = "Candidate.txt";

	bool dataChanged = false;


	/// <summary>
	/// Shows the user menu options and lets them select from them.
	/// P - Print Candidate info.
	/// A - Add vote to candidate.
	/// S - Displays the candidate with the fewest votes.
	/// L - Displays the candidate with the most votes.
	/// Q - Quites the program.
	/// </summary>
	/// <returns>A char corresponding to the option selected by the user.</returns>
	char selectMenuOption();

	/// <summary>
	/// 
	/// </summary>
	void displayCandidateInfo();

	/// <summary>
	/// Allows the user to select a candidate and a voter. And then vote for the candidate on behalf of of the voter if they haven't already voted.
	/// </summary>
	void addVotes();

	/// <summary>
	/// 
	/// </summary>
	void displayCandidateWithFewestVotes();

	/// <summary>
	/// 
	/// </summary>
	void displayCandidateWithMostVotes();

	/// <summary>
	/// 
	/// </summary>
	void saveVoterData();

	/// <summary>
	/// 
	/// </summary>
	void saveCandidateData();

	/// <summary>
	/// 
	/// </summary>
	void loadVoterData();

	/// <summary>
	/// 
	/// </summary>
	void loadCandidateData();

};

