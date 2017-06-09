#pragma once
#include "Action.h"
#include "../Statements/Statement.h"
class Edit :
	public Action
{
	Statement *ptr;
	string lhs;
	string rhs1;
	string rhs2;
	string op;
	double rhs;
	vector<string>var;
public:
	Edit(ApplicationManager *pAppManager);
	void ReadActionParameters();
	void Execute();
	void undo();
};

