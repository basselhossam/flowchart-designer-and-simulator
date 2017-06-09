#pragma once
#include"Action.h"
#include"../GUI/UI_Info.h"

class Statement;
class ApplicationManager;

class Drag : public Action
{
private:
	vector<Point> Position;	//Position where the user clicks to add the stat.
	vector<Statement*>moved;
	int h;
public:
	Drag(ApplicationManager *pAppManager);
	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
	
	void undo();
};
