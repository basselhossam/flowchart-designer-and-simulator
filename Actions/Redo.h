#pragma once
#include "Action.h"
#include "../ApplicationManager.h"

class Redo :
	public Action
{

	vector<Action*>*undolist;
	vector<Action*>*redolist;

public:
	Redo(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	void Execute();
};

