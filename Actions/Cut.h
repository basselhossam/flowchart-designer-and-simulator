#ifndef CUT_H
#define CUT_H

#include "Action.h"

class Statement;

class Cut : public Action
{
private:
	Point Position;	//Position where the user clicks to add the stat.
	Statement*ptr;
public:
	Cut(ApplicationManager *pAppManager);
	//Read Assignemt statements position
	void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	void Execute();

	//void undo();
};

#endif