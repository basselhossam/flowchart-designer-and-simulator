#include "StpByStp.h"

#include "..\ApplicationManager.h"

#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include <fstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
StpByStp::StpByStp(ApplicationManager *pAppManager):Action(pAppManager)
{
	op = false;
	nxt=true;
	varx=1210; 
	vary=180;
	/*
			for (it = variables.begin(); it != variables.end(); it++)
				{
					string out = "";
					ostringstream T;
					T<<it->second; 
					out+=(it->first + " = " + T.str());
					pOut->Out(x,y,out);
			    }*/
}

void StpByStp::ReadActionParameters()
{
	char key;
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	pOut->ClearVariablesArea();
	if(op)
	{
		varx=1210; 
        vary=180;
		pOut->ClearVariablesArea();
		map<string,double> :: iterator it;
		for (it = pManager->variables.begin(); it != pManager-> variables.end(); it++)
				{
					string out = "";
					ostringstream T;
					T<<it->second; 
					out+=(it->first + " = " + T.str());
					pOut->OutVariables(varx,vary,out);
			    }
	}
	else
	{
	pOut->ClearStatusBar();
	pOut->PrintMessage("Stp by Stp Mode : Press any key to continue ");
	cout << "Output :"<<endl;
	}
	pIn->getwindow()->WaitKeyPress(key);

	while(key!= '\r' && key!= 27)
	{
		pOut->ClearStatusBar();
		pOut->PrintMessage("Please, Press Enter to continue or Esc to end ");
	    pIn->getwindow()->WaitKeyPress(key);
	}
		if(key == 27)
		{
			nxt = false;
			pOut->PrintMessage("Escape is pressed .. The action is cancelled");
		}
}

void StpByStp::Execute()
{
	if(pManager->GetSelectedStatement())
	{
		pManager->GetSelectedStatement()->SetSelected(false);
		pManager->SetSelectedStatement(pManager->GetSelectedStatement());
	}

	if(pManager->GetSelectedStatements()->size() > 0)
	{
		pManager->unSelectStatements();
	}


	ReadActionParameters();
	
	Connector*p;
	bool error = false;
	if(pManager->CheckValidation())
	{
	for(int i=0; i<pManager->get_stat_count();i++)
		if(dynamic_cast<Start*>(pManager->get_statement_list()[i]))
		{
			p = pManager->get_statement_list()[i]->GetConnect();
			pManager->get_statement_list()[i]->SetSelected(true);
			pManager->SetSelectedStatement(pManager->get_statement_list()[i]);
			pManager->UpdateInterface();
			break;
		}

		while(p!=NULL)
		{
			ReadActionParameters();
			if(!nxt)
				{
					if(pManager->GetSelectedStatement())
	                 {
		              pManager->GetSelectedStatement()->SetSelected(false);
		              pManager->SetSelectedStatement(pManager->GetSelectedStatement());
	                 }

					break;
			}

			if(pManager->GetSelectedStatement()!= NULL)
					pManager->GetSelectedStatement()->SetSelected(false);
				p->getDstStat()->SetSelected(true);
				pManager->SetSelectedStatement(p->getDstStat());
				pManager->UpdateInterface();


			if(p->getDstStat()->Simulate())
			{
				//ReadActionParameters();
				
				if(dynamic_cast<Conditional*>(p->getDstStat()))
				{
					Conditional*pcond = (Conditional*)p->getDstStat();
					if(pcond->GetCond())
						p=pcond->get_YConn();
					else
						p = pcond->get_NConn();
				}
				else
					p = p->getDstStat()->GetConnect();
				op=true;
			}
			else
			{
				error = true;
				break;
			}
		}

	//ReadActionParameters();

	pManager->variables.clear();
	pManager->TOutput = "";
	}
	
}