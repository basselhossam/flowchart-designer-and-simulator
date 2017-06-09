#include "Copy.h"

#include "..\ApplicationManager.h"

#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Copy::Copy(ApplicationManager *pAppManager):Action(pAppManager)
{
	SetUndo(false);
}

void Copy::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	if (pManager->GetSelectedStatement() == NULL)
		{
			pOut->ClearStatusBar();	
			pOut->PrintMessage("Please Select a statement to copy !");
	    }
	
}

void Copy::Execute()
{
	
	ReadActionParameters();
	if (pManager->GetSelectedStatement())
	{
		pManager->SetCopied(pManager->GetSelectedStatement());
		//CANCELLING CUT
		//and deleting cut
		if (pManager->GetCut() != NULL)
			pManager->RemoveStatment(pManager->GetCut());
		pManager->SetCut(NULL);
		pManager->GetOutput()->ClearStatusBar();
		pManager->GetOutput()->PrintMessage("Copy is excuted!");
		pManager->GetSelectedStatement()->SetSelected(false);
		pManager->SetSelectedStatement(NULL);
	}
	else if (pManager->GetSelectedStatements())
	{
		pManager->SetMultiCopy((*pManager->GetSelectedStatements()));
		if (pManager->GetMultiCut()->size()>0)
		{
			int i = pManager->GetMultiCut()->size() - 1;
			while (i >= 0)
			{
				pManager->RemoveStatment(pManager->GetMultiCut()->operator[](i));
				i--;
			}
		}
		pManager->GetMultiCut()->clear();
		pManager->GetOutput()->ClearStatusBar();
		pManager->GetOutput()->PrintMessage("Statements are Copied!");
		pManager->unSelectStatements();
	}

}