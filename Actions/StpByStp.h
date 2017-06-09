#ifndef STPBYSTP_H
#define STPBYSTP_H
#include "AllActions.h"


class StpByStp : public Action
{
	bool op;
	bool nxt;
	int varx;   //initial coordinates for writing the variables
	int vary;
public:
	StpByStp(ApplicationManager *pAppManager);
	//Read Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
	
};

#endif