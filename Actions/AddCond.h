#ifndef ADDCOD_H
#define ADDCOND_H
#include "Action.h"

class Conditional;

class AddCond : public Action
{
private:
	string lhs;
	string rhs;
	string op;
	Point inlet;
	string txt;   //this will be the text of the statement
	int width, height, t_width, t_height;
	bool draw;
	bool redo;
	Conditional*newstat;

public:
	AddCond(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

	void undo();
	
};







#endif