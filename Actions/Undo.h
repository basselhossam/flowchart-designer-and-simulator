#pragma once
#include "Action.h"
#include "../ApplicationManager.h"
class ApplicationManager;

class Undo :
	public Action
{

	vector<Action*>*undolist;
	vector<Action*>*redolist;

public:
	Undo(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	void Execute();
};

