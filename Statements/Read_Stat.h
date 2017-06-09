//added by amr 
#pragma once
#include <sstream>
#include"Statement.h"
class Read_Stat: public Statement
{
private:
	double slope;               //slope of the inclined sides w.t.to y-axis
	int factor;               //it's an indicator to slope 
	vector <string> V1;      //vector containing identifiers
	Connector*pConn;
public:
	friend class Add_Read_Stat;
	Read_Stat(ApplicationManager *, string txt="", Point inlet = (0,0), vector <string> var=vector<string>(),int width=0, int height=0, int t_width=0, int t_height=0, int Factor=0);
	void UpdateStatementText(/*string str*/);
	bool check_range(Point);
	void Draw(Output*) const;
    void Save(ofstream &OutFile);	        //Save the Statement parameters to a file
	void Load(ifstream &Infile);	        //Load the Statement parameters from a file
	bool Edit();                            //Edit the Statement parameter
	void GenerateCode(ofstream &OutFile);	//write the statement code to a file
	bool Simulate();	                    //Execute the statement in the simulation mode
    void PrintInfo(Output* pOut);	        //print all Statement info on the status bar
	void set_stat_dim(string str);         //for setting stat. dimensions & text dimensions    
	void calc_l_corner();

	Connector*GetConnect();
	void SetConnect(Connector*);

	vector <string> Getvar()const;
	void setvar(const vector <string> &);

	~Read_Stat();
	friend class Paste;
};

