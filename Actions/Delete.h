#ifndef _DELETE_H
#define _DELETE_H

#include "Action.h"

class Statement;
class Connector;


class Delete : public Action
{
	Statement*deletedst;
	Connector*deletedco;
	int deletedstat;
	int deletedconn;
	bool redo;
public:
	Delete(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	void ReadActionParameters();

	//delete an assignemnt statement from the list of statements
	void Execute();

	void undo();

};

#endif

