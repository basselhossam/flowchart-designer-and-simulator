#pragma once
#include "statement.h"
#include <string>

class Conditional : public Statement
{
	private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	string OPR;    //the operator
	string RHS;	//Right Handside (Value)
	
	Connector *YConn;	//Yes Connector
	Connector*NConn;    //No Connector

	//Point Inlet;	//A point where connections enters this statement 
	Point YOutlet;	//A point yes connection leaves this statement
	Point NOutlet;  //A point No connection leaves this statement  

	bool cond;
	bool Is_Loop;

	friend class Paste;

	virtual void UpdateStatementText();
	
public:
	Conditional(ApplicationManager * AM, string txt="", Point l_cor=(0,0), int width=0, int height=0, int t_width=0, int t_height=0, string LeftHS = "", string op = "", string RightHS = "");
	
	void setLHS(const string &L);
	void setRHS(const string &R);
	void setOperator(const string &s);

	string GetLHS() const;
	string GetRHS() const;
	string GetOperator() const;

	virtual bool check_range(Point p);
	virtual void Draw(Output* pOut) const;

	bool Edit();

	void GenerateCode(ofstream &OutFile);

	void Save(ofstream &OutFile);	        //Save the Statement parameters to a file
	void Load(ifstream &Infile);	        //Load the Statement parameters from a file
	bool Simulate();	                    //Execute the statement in the simulation mode
	void PrintInfo(Output* pOut);	        //print all Statement info on the status bar
	void set_stat_dim(string str);                    //for setting stat. dimensions & text dimensions
	void calc_l_corner();

	void SetCond(bool);
	bool GetCond();
	

	void calc_yout();
	void calc_nout();
	Point get_yout();
	Point get_nout();
	void set_Yout(Connector * dst);
	void set_Nout(Connector * dst);

	Connector *get_YConn();
	Connector *get_NConn();

	//string getLHS();
	//string getRHS();

	void setLoop(bool);
	bool getLoop();


};


