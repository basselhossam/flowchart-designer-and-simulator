#ifndef _ADDSINGLEOPERATOR_H
#define _ADDSINGLEOPERATOR_H

#include "Action.h"
#include "../Statements/SingleOperator.h"

class AddSingleOperator:public Action
{
private:
	string lhs;
	string rhs1;
	string op;
	string rhs2;
	Point inlet;
	string txt;   //this will be the text of the statement
	int width, height, t_width, t_height;
	bool draw;
	bool redo;
	SingleOperator*newstat;

public:
	AddSingleOperator(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

	void undo();

};

#endif