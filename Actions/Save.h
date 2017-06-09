#ifndef _SAVE_H
#define _SAVE_H

#include "Action.h"
#include "../Statements/Statement.h"

class Save : public Action
{
private:
	Point Position;	//Position where the user clicks to add the stat.
public:
	Save(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	void ReadActionParameters();

	//delete an assignemnt statement from the list of statements
	void Execute();
};

#endif
