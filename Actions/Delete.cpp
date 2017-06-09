#include "Delete.h"

#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "../Statements/Statement.h"

#include <sstream>
using namespace std;

Delete::Delete(ApplicationManager *pAppManager) :Action(pAppManager)
{
	redo = false;
}

void Delete::ReadActionParameters()
{
}

void Delete::Execute()
{
	ReadActionParameters();
	vector <Statement *>* slist = pManager->GetSelectedStatements();
	vector <Connector *>* clist = pManager->GetSelectedConnectors();
	int statsize = slist->size();
	int connsize = clist->size();
	deletedst = pManager->GetSelectedStatement();
	deletedco = pManager->GetSelectedConnector();
	if (deletedst == NULL && deletedco == NULL && statsize == 0 && connsize == 0){
		pManager->GetOutput()->PrintMessage("No selected statements or connectors !");
		SetUndo(false);
		return;
	}

	deletedstat = pManager->get_stat_count();
	deletedconn = pManager->get_ConnCount();
	if (deletedst == NULL && deletedco == NULL)
	{
		while (statsize > 0)
			pManager->RemoveStatment((*slist)[--statsize]);
		while (connsize > 0)
			pManager->RemoveConnector((*clist)[--connsize]);
		pManager->unSelectConnectors();
		pManager->unSelectStatements();
		pManager->GetSelectedStatements()->clear();
		pManager->GetSelectedConnectors()->clear();
	}
	else
	{
		if (pManager->GetSelectedStatement() != NULL)
		{
			pManager->RemoveStatment(pManager->GetSelectedStatement());
			pManager->GetSelectedStatement()->SetSelected(false);
			pManager->SetSelectedStatement(NULL);
		}
		else if (pManager->GetSelectedConnector() != NULL)
		{
			pManager->RemoveConnector(pManager->GetSelectedConnector());
			pManager->GetSelectedConnector()->set_selected(false);
			pManager->SetSelectedConnector(NULL);
		}
	}
	deletedstat -= pManager->get_stat_count();
	deletedconn -= pManager->get_ConnCount();
}

void Delete::undo(){
	if (!redo){
		int loop = deletedstat;
		while (loop > 0){
			int size = pManager->get_deleted_statements()->size() - 1;
			pManager->AddStatement((*pManager->get_deleted_statements())[size]);
			loop--;
			pManager->get_deleted_statements()->pop_back();
		}
		loop = deletedconn;
		while (loop > 0){
			int size = pManager->get_deleted_Connectors()->size() - 1;
			pManager->Add_Connector((*pManager->get_deleted_Connectors())[size]);
			loop--;
			pManager->get_deleted_Connectors()->pop_back();
		}
		redo = true;
	}
	else{
		int loop = deletedstat;
		while (loop > 0){
			int size = pManager->get_stat_count() - 1;
			pManager->RemoveStatment((pManager->get_statement_list())[size]);
			loop--;
		}
		loop = deletedconn;
		while (loop > 0){
			int size = pManager->get_ConnCount() - 1;
			pManager->RemoveConnector((pManager->get_conn_list())[size]);
			loop--;
		}
		redo = false;
	}
}