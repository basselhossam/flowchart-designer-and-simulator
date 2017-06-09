#pragma once
#include"Action.h"

class Connector;
class Statement;
class ApplicationManager;

class AddConnecter : public Action
{
	Connector * con;
	Statement * src, *dst;
	bool yes;
	bool redo;

public:
	AddConnecter(ApplicationManager * AM);
	void ReadActionParameters();
	void Execute();
	void undo();
};

