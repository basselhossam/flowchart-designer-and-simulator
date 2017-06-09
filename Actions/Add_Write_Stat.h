#pragma once
#include"Action.h"
class Add_Write_Stat: public Action

{
	friend class Write_Stat;
private:
	vector<string> v1;
	int factor;
	Point inlet;
	string txt;   //this will be the text of the statement
	int width, height, t_width, t_height;
	bool draw;
	bool redo;
	Write_Stat* write;

public:
	Add_Write_Stat(ApplicationManager *);

	void ReadActionParameters();              //overriding the function in the class action

	void Execute();                             //overriding the function in the action class

	void undo();
};

