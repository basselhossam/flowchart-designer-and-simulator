#ifndef _GENERATE_H
#define _GENERATE_H

#include "Action.h"
#include "../ApplicationManager.h"
#include "../Statements/allstatements.h"

class Generate : public Action
{
private:
	Point Position;	//Position where the user clicks to add the stat.
public:
	Generate(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	void ReadActionParameters();

	//delete an assignemnt statement from the list of statements
	void Execute();
};

#endif