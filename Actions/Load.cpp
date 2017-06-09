#include "Load.h"

#include "..\ApplicationManager.h"

#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include <fstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Load::Load(ApplicationManager *pAppManager):Action(pAppManager)
{
	redo = false;
}

void Load::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	pOut->ClearStatusBar();
	pOut->PrintMessage("Loading ...");
}


void Load::Execute()
{
	ReadActionParameters();
	deletedstat = pManager->get_stat_count();
	deletedconn = pManager->get_ConnCount();
	/*
	for (int i = 0; i < deletedstat; i++)
	{
		pManager->RemoveStatment(pManager->get_statement_list()[i]);
	}
	*/
	while (pManager->get_stat_count() > 0)
	{
		pManager->RemoveStatment(pManager->get_statement_list()[0]);
	}
	while (pManager->get_ConnCount() > 0)
	{
		pManager->RemoveConnector(pManager->get_conn_list()[0]);
	}
	ifstream inputFile("chart.txt", ios::in);
	pManager->LoadChart(inputFile);
	/*if( inputFile.peek() != ifstream::traits_type::eof())
	{pManager->LoadChart(inputFile);
	}*/
	/*else
	{Output *pOut = pManager->GetOutput();
	pOut->PrintMessage("No Saved Charts !!");
	}*/
	inputFile.close();
	statcount = pManager->get_stat_count();
	conncount = pManager->get_ConnCount();
}

void Load::undo(){
	if (!redo){
		vector<Statement*>*deletedstats = pManager->get_deleted_statements();
		vector<Connector*>*deletedconns = pManager->get_deleted_Connectors();
		int size;
		int loop;
		loop = statcount;
		while (loop != 0)
		{
			pManager->RemoveStatment(pManager->get_statement_list()[0]);
			loop--;
		}

		loop = conncount;
		while (loop != 0)
		{
			pManager->RemoveConnector(pManager->get_conn_list()[0]);
			loop--;
		}

		loop = deletedstat;
		while (loop > 0){
			size = deletedstats->size();
			pManager->AddStatement((*deletedstats)[size - 1 - statcount]);
			loop--;
			deletedstats->erase(deletedstats->begin() + (size - 1 - statcount));
		}

		loop = deletedconn;
		while (loop > 0){
			size = deletedconns->size();
			pManager->Add_Connector((*deletedconns)[size - 1 - conncount]);
			loop--;
			deletedconns->erase(deletedconns->begin() + (size - 1 - conncount));
		}
		
		redo = true;
	}
	else{
		vector<Statement*>*deletedstats = pManager->get_deleted_statements();
		vector<Connector*>*deletedconns = pManager->get_deleted_Connectors();
		int loop;
		
		loop = deletedstat;
		while (loop > 0)
		{
			pManager->RemoveStatment(pManager->get_statement_list()[0]);
			loop--;
		}
		loop = deletedconn;
		while (loop > 0)
		{
			pManager->RemoveConnector(pManager->get_conn_list()[0]);
			loop--;
		}

		loop = statcount;
		while (loop > 0){
			int size = deletedstats->size();
			pManager->AddStatement((*deletedstats)[size - 1 - deletedstat]);
			loop--;
			deletedstats->erase(deletedstats->begin() + (size - 1 - deletedstat));
		}
		loop = conncount;
		while (loop > 0){
			int size = deletedconns->size();
			pManager->Add_Connector((*deletedconns)[size - 1 - deletedconn]);
			loop--;
			deletedconns->erase(deletedconns->begin() + (size - 1 - deletedconn));
		}

		redo = false;
	}
}