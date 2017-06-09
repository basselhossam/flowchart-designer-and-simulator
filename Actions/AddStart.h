#pragma once
#include "Action.h"
#include "..\Statements\Start.h"


class AddStart :
	public Action
{
	Point Position;	//Position where the user clicks to add the stat.
	Point inlet;
	string txt;   //this will be the text of the statement
	Statement * ptr;
	int width, height, t_width, t_height;
	bool draw;
	bool redo;
	Start*newstat;

public:
	AddStart (ApplicationManager *pAppManager);

	//Read start statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

	void undo();

};

