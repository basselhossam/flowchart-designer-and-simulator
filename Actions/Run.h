#ifndef RUN_H
#define RUN_H
#include "AllActions.h"


class Run : public Action
{
public:
	Run(ApplicationManager *pAppManager);
	//Read Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
	
};







#endif