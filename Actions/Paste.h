#ifndef PASTE_H
#define PASTE_H
#include "Action.h"
#include "../Statements/allstatements.h"


class Paste : public Action
{
private:
	Point Position;	//Position where the user clicks to add the stat.
	Point Positions[50];
	Statement*pasted;
	Statement*newstat;
	Statement *ptr;
	Point lastpos;
	vector<Statement*>* pastedstatments;
	string txt;   //this will be the text of the statement
	//bool redo;
	int width, height, t_width, t_height;
	
public:
	Paste(ApplicationManager *pAppManager);
	//Read Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

	//void undo();
	
};

#endif