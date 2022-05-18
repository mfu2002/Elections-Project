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
	void execute();


private:
	/// <summary>
	/// 
	/// </summary>
	const string voterFileName = "Voter.txt";

	/// <summary>
	/// 
	/// </summary>
	const string candidateFileName = "Candidate.txt";


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
	void splashScreen();

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
	/// <returns></returns>
	vector<Voter> loadVoterData();
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	vector<Candidate> loadCandidateData();


	/// <summary>
	/// 
	/// </summary>
	/// <param name="id"></param>
	/// <param name="file"></param>
	/// <param name="recordLength"></param>
	/// <param name="idLength"></param>
	/// <returns></returns>
	int findRecordWithId(const char* id, fstream* file, int recordLength, int idLength);

	/// <summary>
	/// 
	/// </summary>
	void addVoter();

	/// <summary>
	/// 
	/// </summary>
	void addCandidate();
};

