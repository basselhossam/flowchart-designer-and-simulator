#pragma once
#include <iostream>
#include "..\defs.h"
#include "Connector.h"
class Output;
#include "..\GUI\Output.h"
#include "..\ApplicationManager.h"
#include <fstream>
#include <sstream>
//Base class for all Statements
class ApplicationManager;
class Input;
class Connector;
class Statement
{
protected:
	int ID;			//Each Statement has an ID
	string Text;	//Statement text (e.g.  "X = 5" OR "if(salary > 3000)" and so on )
	bool Selected;	//true if the statement is selected on the folwchart
	virtual void UpdateStatementText(/*string str*/) = 0;	//is called when any part of the stat. is edited
	int width, height;
	Point l_corner;
	Point inlet;
	Point outlet;
	string comment;
	Input * pIn;
	Output * pOut;
	int t_width;              //text width
	int t_height;             //text height
	bool IsCut;
	ApplicationManager * AppMan;
	static int ID_creator;  //  this variable is used to initialize the variables IDs
	// Add more parameters if needed.
	bool IsConnected;  //bool to know if the statement is a distination
	bool generated;

public:
	Statement(ApplicationManager * AM, string txt, Point l_cor, int width, int height, int t_width, int t_height);   //added by amr    
	void SetSelected(bool s);
	bool IsSelected() const;
	void SetCut(bool s);
	bool GetCut() const;
	virtual void Draw(Output* pOut) const = 0;	//Draw the statement
	virtual bool check_range(Point) = 0;              //added by amr
	int get_width();                       //added by amr
	int get_height();                     //added by amr
	string get_text();
	string GetComment();
	void get_data(string &txt, int &width, int &height, int &t_width, int &t_height);
	Point & get_lcorner();                  //added by amr
	virtual void set_stat_dim(string str) = 0;        //for setting stat. dimensions & text dimensions
	int get_ID()const;         //by amr
	void Edit_comment(string txt);     //by amr
	///TODO:The following functions should be supported by the Statement class
	///		It should then be overridden by each derived Statement
	///		Decide the parameters that you should pass to each function and its return type	

	virtual void calc_l_corner() = 0;           //virtual because read & write have one way for calculation while other statements have another way

	virtual void Save(ofstream &OutFile) = 0;	//Save the Statement parameters to a file
	virtual void Load(ifstream &Infile) = 0;	//Load the Statement parameters from a file


	virtual void Move(Point P);		//Move the Statement on the flowchart
	virtual bool Edit() = 0;		//Edit the Statement parameter

	virtual void GenerateCode(ofstream &OutFile) = 0;	//write the statement code to a file
	virtual bool Simulate() = 0;	//Execute the statement in the simulation mode

	virtual void PrintInfo(Output* pOut) = 0;	//print all Statement info on the status bar

	virtual Connector*GetConnect(){ return NULL; }
	virtual void SetConnect(Connector*){}

	void SetConnected(bool);
	bool GetConnected();

	void Drag();

	~Statement();
	//TODO: Add more functions if needed
	Point GetInlet();
	Point GetOutlet();
	virtual void SetInlet();
	virtual void SetOutlet();
	bool CheckIdentifier(string);
    bool CheckValue(string);
	int get_t_width();
    int get_t_height();
	void SetGenerated(bool);
	bool Is_Generated();



};