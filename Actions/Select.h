#pragma once
#include "Action.h"
#include "../Statements/Statement.h"
class Select :
	public Action
{
	Statement *ptr;
	Point p;
	Connector * con;
	
public:
	Select(ApplicationManager *pAppManager);
	void ReadActionParameters();
	void Execute();
};

