///added by amr

#pragma once       
#include"Action.h"
#include"..\Statements\Statement.h"
#include"..\Statements\Read_Stat.h"
class Add_Read_Stat : public Action
{
private:
	vector<string> v1;
	Statement *ptr;
	int factor;
	Point inlet;
	string txt;   //this will be the text of the statement
	int width, height, t_width, t_height;
	bool draw;
	bool redo;
	Read_Stat* read;


public:
	Add_Read_Stat(ApplicationManager *);
	
	void ReadActionParameters();              //overriding the function in the class action
	
	void Execute();                             //overriding the function in the action class
	                                                                                             
	void undo();
};

