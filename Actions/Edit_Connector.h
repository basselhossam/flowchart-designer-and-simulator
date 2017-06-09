#pragma once
#include"Action.h"

class ApplicationManager;

class Edit_Connector:public Action
{
	bool ok;
public:
	Edit_Connector(ApplicationManager * AM);
	void ReadActionParameters();
	void Execute();
};

