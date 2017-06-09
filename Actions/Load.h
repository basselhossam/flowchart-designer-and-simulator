#ifndef LOAD_H
#define LOAD_H
#include "AllActions.h"


class Load : public Action
{
	int statcount;
	int conncount;
	int deletedstat;
	int deletedconn;
	bool redo;
public:
	Load(ApplicationManager *pAppManager);
	//Read Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
	
	void undo();
};







#endif