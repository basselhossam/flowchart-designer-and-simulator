#include "AddConnector.h"
#include "../Statements/allstatements.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddConnecter::AddConnecter(ApplicationManager *pAppManager) :Action(pAppManager)
{
	con = NULL;
	src = NULL;
	dst = NULL;
	redo = false;
}


void AddConnecter::ReadActionParameters()
{
	int num_of_stat = pManager->get_stat_count();

	if (num_of_stat <2)
	{
		if (num_of_stat == 0)
			pManager->GetOutput()->PrintMessage("are you crazy there are no statements to connect");
		else
			pManager->GetOutput()->PrintMessage("are you crazy there is only one statement");
		dst = NULL;
		src = NULL;
		return;
	}
	Output * pOut = pManager->GetOutput();
	Input * pIn = pManager->GetInput();
	Point p;

	pOut->PrintMessage("Click on the source statement, click in the darawing area to cancel the connector action");
	do
	{
		pIn->GetPointClicked(p);
		src = pManager->GetStatement(p);
		if (src == NULL)
		{
			pOut->PrintMessage("the connector action was cancelled, try again");
			src = NULL;
			dst = NULL;
			return;
		}
		else if (dynamic_cast<End *>(src))
		{
			pOut->PrintMessage("you can't make the End statement a source statement, choose another one");
			src = NULL;
		}
		else if (src->GetConnect() != NULL)
		{
			pOut->PrintMessage("Ohhhh! ,hey friend you are making a fatal mistake, the statement you are choosig has a connector");
			src = NULL;
		}
		if (dynamic_cast<Conditional *>(src))
		{
			if (p.x >= src->get_lcorner().x + src->get_width() / 2)
			{
				if (dynamic_cast<Conditional *>(src)->get_YConn() != NULL)
				{
					pOut->PrintMessage("there is no room for another YES conector");
					src = NULL;
				}
				else
					yes = true;
			}
			else
			{
				if (dynamic_cast<Conditional *>(src)->get_NConn() != NULL)
				{
					pOut->PrintMessage("there is no room for another NO conector");
					src = NULL;
				}
				yes = false;
			}
		}
	} while (src == NULL);



	pOut->PrintMessage("Click on the destination Statement, click on an empty place to cancel the action");
	do
	{
		pIn->getwindow()->WaitMouseClick(p.x, p.y);
		dst = pManager->GetStatement(p);
		if (dst == NULL)
		{
			pOut->PrintMessage("the connector action  was cancelled, try again");
			SetUndo(false);
			dst = NULL;
			src = NULL;
			return;
		}
		else if (dst == src)
		{
			dst = NULL;
			pOut->PrintMessage("you can't do such stupid case");
		}

		else if (dynamic_cast<Start *>(dst))
		{
			pOut->PrintMessage("you can't make the Start statement a destination statement");
			dst = NULL;
		}

	} while (dst == NULL);
	pOut->ClearStatusBar();
}

void AddConnecter::Execute(){

	ReadActionParameters();
	if (dst == NULL || src == NULL){
		SetUndo(false);
		return;
	}
	dst->SetConnected(true);
	con = new Connector(src, dst, pManager, yes);
	pManager->Add_Connector(con);
}

void AddConnecter::undo(){
	if (!redo){
		pManager->RemoveConnector(con);
		redo = true;
	}
	else{
		pManager->Add_Connector(con);
		redo = false;
	}
}
