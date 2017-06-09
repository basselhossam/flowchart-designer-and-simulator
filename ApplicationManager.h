#pragma once

#include <iostream>
#include "DEFS.h"
#include "Statements\Statement.h"
#include <fstream>
#include <map>

class Input;
class Output;
class Statement;
class Connector;
class Action;

//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxCount = 200 };	//Max no of statements/connectors in a single flowchart

private:
	int StatCount;		//Actual number of statements
	int ConnCount;		//Actual number of connectors
	Statement* StatList[MaxCount];	//List of all statements (Array of pointers)
	Connector* ConnList[MaxCount];	//List of all connectors (Array of pointers)

	Statement *pSelectedStat; //a pointer to the last selected statement
	Statement*pCopied;
	Statement*pCut;

	Connector*pSelectedConn;
	vector <Connector*>pSelectedConnectors;
	vector <Statement*>DeletedStatements;
	vector <Connector*>DeletedConnectors;

	vector <variable> var;
	vector <Statement*>pSelectedStatements;

	Action* pAct;
	vector <Action*>undolist;
	vector<Action*>redolist;

	vector<Statement*>pMultiCopy;
	vector<Statement*>pMultiCut;


	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;

	MODE currentmode;



public:	
	ApplicationManager(); 
	~ApplicationManager();

	map<string, double> variables;
	string TOutput;
	
	// -- Actions Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType) ; //Creates an action and executes it
	
	// -- Statements/Connector Management Functions
	void AddStatement(Statement* pStat); //Adds a new Statement to the Flowchart
	Statement *GetStatement(Point P) const;	//search for a statement where point P belongs

	void RemoveStatment(Statement *pStat);
	void RemoveConnector(Connector * pConn);

	void Add_Connector(Connector* pConn); //Adds a new Connector to the Flowchart
	Connector *GetConnector(Point P) const;	//search for a Connector where point P belongs
	Connector * & GetSelectedConnector();
	void SetSelectedConnector(Connector * pCon);

	int get_ConnCount()const;
	Connector ** get_conn_list();

	Statement *GetSelectedStatement() const;	//Returns the selected Statement
	void SetSelectedStatement(Statement *pStat); //Set the Statement selected by the user
	
	vector <Statement*>*GetSelectedStatements();
	void unSelectStatements();
	void addSelectedStatement(Statement *pStat);
	void unSelectStatement(Statement *pStat);

	int get_stat_count();     //added by amr  :returns the statement counter
	vector <variable> & get_var_list();
	Statement ** get_statement_list();

	Statement *GetCopied() const;
	void SetCopied(Statement *pStat);

	Statement *GetCut() const;
	void SetCut(Statement *pStat);

	//added
	void LoadChart(ifstream &Infile);

	void RunChart();

	bool CheckValidation() const;

	vector <Action*>*GetUndolist();
	vector <Action*>*GetRedolist();
	
	vector <Connector*>*GetSelectedConnectors();
	void unSelectConnectors();
	void addSelectedConnector(Connector *pConn);
	void unSelectConnector(Connector *pConn);

	vector<Statement*>*get_deleted_statements();
	vector<Connector*>*get_deleted_Connectors();
		
	void SaveChart(ofstream &OutFile);

	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window
	

	//For MultiSelections

	vector<Statement*>* GetMultiCut();
	void SetMultiCut(vector<Statement*>);
	vector<Statement*>* GetMultiCopy();
	void SetMultiCopy(vector<Statement*>);

	void multi_drag();

	void GenerateCodeFile(ofstream &OutFile);
};

