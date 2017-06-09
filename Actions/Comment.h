#pragma once
#include"Action.h"
#include"../ApplicationManager.h"

class Comment:public Action
{
	Statement*ptr;
	string comment;
	string lastcomment;
public:
	Comment(ApplicationManager *pAppManager);
	void ReadActionParameters();
	void Execute();
	void undo();
};

