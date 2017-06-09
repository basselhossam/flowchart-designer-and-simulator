#pragma once
#include "Statement.h"
class End :
	public Statement
{
	Connector *pConn;	//has one Connector to next statement



public:
	End(ApplicationManager * AM, string txt="", Point l_cor=(0,0), int width=0, int height=0, int t_width=0, int t_height=0);

	void UpdateStatementText();

	bool Edit();

	virtual void Draw(Output* pOut) const;

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
	

	friend class Paste;

};

