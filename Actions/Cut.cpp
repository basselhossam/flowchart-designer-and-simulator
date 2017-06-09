#include "Cut.h"

#include "../ApplicationManager.h"

#include "../GUI\Input.h"
#include "../GUI\Output.h"
#include "../Statements/Conditional.h"
#include <sstream>

using namespace std;

Cut::Cut(ApplicationManager *pAppManager) :Action(pAppManager)
{
	ptr = NULL;
	SetUndo(false);
}


void Cut::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	ptr = pManager->GetSelectedStatement();
	if (ptr == NULL)
	{
		pOut->ClearStatusBar();
		pOut->PrintMessage("No statement is selected !");
	}
}

void Cut::Execute()
{
	ReadActionParameters();
	if (pManager->GetSelectedStatement())
	{
		if (pManager->GetCut() != NULL)
			pManager->RemoveStatment(pManager->GetCut());
		pManager->SetCut(pManager->GetSelectedStatement());
		pManager->SetCopied(NULL);
		pManager->GetSelectedStatement()->SetCut(true);

		//Deleting the Out Connectors

		Conditional*condPtr = dynamic_cast<Conditional*>(pManager->GetSelectedStatement());
		if (condPtr == NULL)
		{
			if (pManager->GetSelectedStatement()->GetConnect() != NULL)
				pManager->RemoveConnector(pManager->GetSelectedStatement()->GetConnect()); //deleting the connector
		}
		else
		{
			if (condPtr->get_YConn())
				pManager->RemoveConnector(condPtr->get_YConn());
			if (condPtr->get_NConn())
				pManager->RemoveConnector(condPtr->get_NConn());
		}

		//Deleting the In Connectors

		for (int i = 0; i<pManager->get_ConnCount(); i++)
		if (pManager->get_conn_list()[i]->getDstStat() != NULL &&  pManager->get_conn_list()[i]->getDstStat() == pManager->GetSelectedStatement())
			pManager->RemoveConnector(pManager->get_conn_list()[i]);

		pManager->GetOutput()->ClearStatusBar();
		pManager->GetOutput()->PrintMessage("Statement is Cut!");

		pManager->GetSelectedStatement()->SetSelected(false);
		pManager->SetSelectedStatement(NULL);
	}
	else if (pManager->GetSelectedStatements()->size()>0)
	{
		if (pManager->GetMultiCut()->size()>0)
		{
			int i = pManager->GetMultiCut()->size() - 1;
			while (i >= 0)
			{
				pManager->RemoveStatment(pManager->GetMultiCut()->operator[](i));
				i--;
			}
		}
		pManager->SetMultiCut((*pManager->GetSelectedStatements()));
		pManager->GetMultiCopy()->clear();
		int i = pManager->GetSelectedStatements()->size() - 1;
		while (i >= 0)
		{
			pManager->GetSelectedStatements()->operator[](i)->SetCut(true);

			Conditional*condPtr = dynamic_cast<Conditional*>(pManager->GetSelectedStatements()->operator[](i));
			if (condPtr == NULL)
			{
				if (pManager->GetSelectedStatements()->operator[](i)->GetConnect() != NULL)
					pManager->RemoveConnector(pManager->GetSelectedStatements()->operator[](i)->GetConnect()); //deleting the connector
			}
			else
			{
				if (condPtr->get_YConn() != NULL)
					pManager->RemoveConnector(condPtr->get_YConn());
				if (condPtr->get_NConn() != NULL)
					pManager->RemoveConnector(condPtr->get_NConn());
			}

			//Deleting the In Connectors
			int ConCnt = pManager->get_ConnCount();
			for (int j = 0; j<ConCnt; j++)
			{
				if (pManager->get_conn_list()[j] != NULL&&pManager->get_conn_list()[j]->getDstStat() != NULL &&  pManager->get_conn_list()[j]->getDstStat() == pManager->GetSelectedStatements()->operator[](i))
					pManager->RemoveConnector(pManager->get_conn_list()[j]);
			}
			i--;
		}
		pManager->GetOutput()->ClearStatusBar();
		pManager->GetOutput()->PrintMessage("Statements were Cut!");
		pManager->unSelectStatements();
	}
}

//void Cut::undo(){
//	//add a way to save statements instead of deleting it on cut overwrite
//	if (ptr){
//		ptr->SetCut(false);
//		//temparary option
//		pManager->SetCut(NULL);
//	}
//}