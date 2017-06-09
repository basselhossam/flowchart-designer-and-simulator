#include "Info.h"


Info::Info(ApplicationManager *pAppManager):Action(pAppManager){
	SetUndo(false);
}

void Info::ReadActionParameters(){
	
}

void Info::Execute()
{
	pManager->GetOutput()->CreateDrawArea();
	pManager->GetOutput()->getwindow()->DrawImage("images\\credits.jpg", 0, UI.TlBrWdth);
	pManager->GetInput()->GetUserAction();
}


