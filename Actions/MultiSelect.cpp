#include "MultiSelect.h"


MultiSelect::MultiSelect(ApplicationManager *pAppManager) :Action(pAppManager)
{
	SetUndo(false);
}

void MultiSelect::ReadActionParameters(){

	Point p;
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	//deselecting any normally selected connector or statement
	if (pManager->GetSelectedStatement() != NULL)
		pManager->GetSelectedStatement()->SetSelected(false);
	pManager->SetSelectedStatement(NULL);
	if (pManager->GetSelectedConnector() != NULL)
		pManager->GetSelectedConnector()->set_selected(false);

	do{
		pOut->PrintMessage("Selecting Statements or connectors , after you Finish selecting click on an empty space of the drawing area");
		pIn->GetPointClicked(p);
		ptr = pManager->GetStatement(p);
		if (ptr != NULL && ptr->GetCut())
			ptr = NULL;
		if (ptr != NULL){
			pManager->addSelectedStatement(ptr);
			pManager->UpdateInterface();
		}
		else if (ptr == NULL)
		{
			con = pManager->GetConnector(p);
			if (con != NULL)
			{
				pManager->addSelectedConnector(con);
				pManager->UpdateInterface();
			}
		}

	} while (!(ptr == NULL && con ==NULL));
}

void MultiSelect::Execute()
{

	ReadActionParameters();
	pManager->GetOutput()->PrintMessage("statements selected now choose an action");

}