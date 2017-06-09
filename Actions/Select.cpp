#include "Select.h"


Select::Select(ApplicationManager *pAppManager) :Action(pAppManager)
{
	SetUndo(false);
}

void Select::ReadActionParameters(){

	Point p;
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	pIn->GetPointClicked(p);
	ptr = pManager->GetStatement(p);
	if (ptr != NULL && ptr->GetCut())
		ptr = NULL;
	if (ptr == NULL)
		con = pManager->GetConnector(p);
}

void Select::Execute(){

	ReadActionParameters();

	pManager->unSelectStatements();

	if (ptr != NULL)
	{
		if (pManager->GetSelectedStatement() != NULL)
			pManager->GetSelectedStatement()->SetSelected(false);
		if (pManager->GetSelectedConnector() != NULL)
		{
			pManager->GetSelectedConnector()->set_selected(false);
			pManager->GetSelectedConnector() = NULL;
		}
		ptr->SetSelected(true);
		pManager->SetSelectedStatement(ptr);
		ptr->PrintInfo(pManager->GetOutput());
	}
	else
	{
		if (pManager->GetSelectedStatement() != NULL)
			pManager->GetSelectedStatement()->SetSelected(false);
		pManager->SetSelectedStatement(NULL);

		if (con != NULL)
		{
			if (pManager->GetSelectedConnector() != NULL)
				pManager->GetSelectedConnector()->set_selected(false);
			con->set_selected(true);
			pManager->SetSelectedConnector(con);
			con->Print_info(pManager->GetOutput());
		}
		else
		{
			if (pManager->GetSelectedConnector() != NULL)
				pManager->GetSelectedConnector()->set_selected(false);
			pManager->SetSelectedConnector(NULL);
		}

	}
}