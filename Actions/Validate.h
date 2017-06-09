#pragma once
#include "Action.h"
#include "../ApplicationManager.h"
#include "../Statements/allstatements.h"

class Validate :
	public Action
{
public:
	Validate(ApplicationManager *pAppManager);
	void ReadActionParameters();
	void Execute();
};

