#pragma once
#include "Action.h"
#include "../Statements/Statement.h"

class Connector;

class MultiSelect :
	public Action
{
	Connector *con;
	Statement *ptr;
	Point p;

public:
	MultiSelect(ApplicationManager *pAppManager);
	void ReadActionParameters();
	void Execute();
};

