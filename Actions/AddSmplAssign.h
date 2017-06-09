#pragma once

#include "Action.h"
#include "..\Statements\SmplAssign.h"

//Add Simple Assignment Statement Action
//This class is responsible for 
// 1 - Getting Assignment stat. coordinates from the user
// 2 - Creating an object of Assignment class and fill it parameters
// 3 - Adding the created object to the list of statements
class AddSmplAssign : public Action
{
private:
	string lhs;
	double rhs;
	Point inlet;
	string txt;   //this will be the text of the statement
	int width, height, t_width, t_height;
	bool draw;
	bool redo;
	SmplAssign*newstat;

public:
	AddSmplAssign(ApplicationManager *pAppManager);

	//Read Assignemt statements position and left & right hand side
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute() ;
	
	void undo();
};
