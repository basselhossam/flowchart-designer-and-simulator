#ifndef COPY_H
#define COPY_H
#include "Action.h"
#include "../Statements/Statement.h"



class Copy : public Action
{
private:
	//Point Position;	//Position where the user clicks to add the stat.
	static Statement*Copied;
public:
	Copy(ApplicationManager *pAppManager);
	//Read Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
	
};
#endif