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

	/// <summary>
	/// Entry point for the system.
	/// </summary>
	void execute();


private:
	/// <summary>
	/// Name of the file that contains voter information. 
	/// </summary>
	const string voterFileName = "Voter.txt";

	/// <summary>
	/// Name of the file that contains candidate information. 
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
	/// Creates a splash screen (logo) on the console.
	/// </summary>
	void splashScreen();

	/// <summary>
	/// Outputs information regaring each candidate on the terminal. 
	/// </summary>
	void displayCandidateInfo();

	/// <summary>
	/// Allows the user to select a candidate and a voter. And then vote for the candidate on behalf of of the voter if they haven't already voted.
	/// </summary>
	void addVotes();

	/// <summary>
	/// Outputs the information regarding the candidate with the least votes. 
	/// </summary>
	void displayCandidateWithFewestVotes();

	/// <summary>
	/// Outputs the information regarding the candidate with the most votes. 
	/// </summary>
	void displayCandidateWithMostVotes();

	/// <summary>
	/// Loads voter data into memory.
	/// </summary>
	/// <returns>A collection of all the voters.</returns>
	vector<Voter> loadVoterData();
	/// <summary>
	/// Loads the candidate data into memory.
	/// </summary>
	/// <returns>A collection of all the candidates.</returns>
	vector<Candidate> loadCandidateData();


	/// <summary>
	/// Finds the record in the database using the id.
	/// </summary>
	/// <param name="id">Record Id</param>
	/// <param name="file">File that needs to be search.</param>
	/// <param name="recordLength">Length of the each record in the file. (sum of the characters lengths of each field)</param>
	/// <param name="idLength">length of the id field. </param>
	/// <returns>returns the cursor location of the recrod.</returns>
	int findRecordWithId(const char* id, fstream* file, int recordLength, int idLength);

	/// <summary>
	/// Gets voter info from the user and adds it to the file.
	/// This functions will not be exposed to the end user. Only used for debugging and development purposes. 
	/// </summary>
	void addVoter();

	/// <summary>
	/// Gets candidate info from the user and adds it to the file.
	/// This functions will not be exposed to the end user. Only used for debugging and development purposes. 
	/// </summary>
	void addCandidate();

	/// <summary>
	/// Creates a loading animation
	/// </summary>
	void splash();
};