#include "Edit_Connector.h"
#include"../ApplicationManager.h"
#include"../Statements/Connector.h"

Edit_Connector::Edit_Connector(ApplicationManager * AM)
:Action(AM), ok(false)
{}

void Edit_Connector::ReadActionParameters()
{
	if (pManager->GetSelectedConnector() != NULL)
		ok = true;
	else
		SetUndo(false);
}
void Edit_Connector::Execute()
{
	ReadActionParameters();
	if (ok)
		pManager->GetSelectedConnector()->Edit();
	else
		pManager->GetOutput()->PrintMessage("no selected connector");
	pManager->SetSelectedConnector(NULL);
    
}

