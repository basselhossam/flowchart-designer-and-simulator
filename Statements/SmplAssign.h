#pragma once


#include "Statement.h"

//Simple Assignment statement class
//The simple assignment statement assigns a variable to a value
class SmplAssign : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	double RHS;	//Right Handside (Value)
	
	Connector *pConn;	//Simple Assignment Stat. has one Connector to next statement

	virtual void UpdateStatementText();
	
public:
	SmplAssign(ApplicationManager * AM, string txt="", Point l_cor=(0,0), int width=0, int height=0, int t_width=0, int t_height=0, string LeftHS = "", double RightHS = 0);
	
	void setLHS(const string &L);
	void setRHS(double R);

	string GetLHS() const;
	double GetRHS() const;

	virtual void Draw(Output* pOut) const;

	bool Edit();

	void GenerateCode(ofstream &OutFile);

	bool check_range(Point p);

	void Save(ofstream &OutFile);	        //Save the Statement parameters to a file
	void Load(ifstream &Infile);	        //Load the Statement parameters from a file
	bool Simulate();	                    //Execute the statement in the simulation mode
	void PrintInfo(Output* pOut);	        //print all Statement info on the status bar
	void set_stat_dim(string str);                    //for setting stat. dimensions & text dimensions
	void calc_l_corner();

	Connector*GetConnect();
	void SetConnect(Connector*);

	//string getLHS();

	friend class Paste;


};
