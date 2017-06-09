#ifndef MOVE_H
#define MOVE_H
#include "Action.h"
#include "../Statements/Statement.h"
#include "Copy.h"
#include "../Statements/Conditional.h"
#include "../Statements/SmplAssign.h"

class Move : public Action
{
private:
	Point lastPosition;
	Point Position;	//Position where the user clicks to add the stat.
	Statement*moved;
public:
	Move(ApplicationManager *pAppManager);
	//Read Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
	
	void undo();
};







#endif