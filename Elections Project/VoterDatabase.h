#include "Voter.h"
#include <string>
#pragma once
class VoterDatabase
{
public:
	VoterDatabase();
	~VoterDatabase();

	void addOrUpdateVoter(Voter* voter);
	void removeVoter(string voterId);
	Voter get(string voterId);
	Voter* getAll();

private:

};