#ifndef _SINGLEOPERATOR_H
#define  _SINGLEOPERATOR_H

#include "Statement.h"

class SingleOperator : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	string RHS1;	
	string OP;
	string RHS2;

	Connector *pConn;	//Single operator Stat. has one Connector to next statement


	virtual void UpdateStatementText();
	friend class Paste;

public:
	SingleOperator(ApplicationManager * AM, string txt="", Point l_cor=(0,0), int width=0, int height=0, int t_width=0, int t_height=0, string LeftHS = "", string RightHS1 = "", string op = "", string RightHS2 = "");

	void setLHS(const string &L);
	void setRHS1(const string &R1);
	void setOperator(const string &p);
	void setRHS2(const string &R2);

	string GetLHS() const;
	string GetRHS1() const;
	string GetOperator() const;
	string GetRHS2() const;

	virtual void Draw(Output* pOut) const;
	virtual bool check_range(Point p);

	bool Edit();

	void GenerateCode(ofstream &OutFile);

	void Save(ofstream &OutFile);	        //Save the Statement parameters to a file
	void Load(ifstream &Infile);	        //Load the Statement parameters from a file
	bool Simulate();	                    //Execute the statement in the simulation mode
	void PrintInfo(Output* pOut);	        //print all Statement info on the status bar
	void set_stat_dim(string str);                    //for setting stat. dimensions & text dimensions
	void calc_l_corner();

	Connector*GetConnect();
	void SetConnect(Connector*);

	//string getLHS();
	//string getRHS1();
	//string getRHS2();
};

#endif
