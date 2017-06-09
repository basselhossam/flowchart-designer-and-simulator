
#ifndef _ADDVARASSIGN_H
#define _ADDVARASSIGN_H

#include "Action.h"
#include "..\Statements\VarAssign.h"

class AddVarAssign : public Action
{
private:
	string lhs;
	string rhs;
	Point inlet;
	string txt;   //this will be the text of the statement
	int width, height, t_width, t_height;
	bool draw;
	bool redo;
	VarAssign*newstat;
public:
	AddVarAssign(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual	void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	void Execute();

	void undo();
};

#endif