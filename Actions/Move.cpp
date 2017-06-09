#include "Move.h"

#include "..\ApplicationManager.h"

#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Move::Move(ApplicationManager *pAppManager):Action(pAppManager)
{}

void Move::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	moved = pManager->GetSelectedStatement();
	if (moved == NULL)
		{
			pOut->ClearStatusBar();	
			pOut->PrintMessage("No statement statement is selected to Move !");
			SetUndo(false);
	    }
	else
	{
		pOut->ClearStatusBar();
		pOut->PrintMessage("Select position to Move!");
		pIn->GetPointClicked(Position);
		lastPosition = moved->get_lcorner();
	}
	
}

void Move::Execute()
{
	
	ReadActionParameters();
		
	//Calculating left corner of assignement statement block

	//NEED TO BE CALCULATED
	Output *pOut = pManager->GetOutput();
	if (moved != NULL)
	{
		moved->Move(Position);
		pOut->ClearStatusBar();
		pOut->PrintMessage("Move is Excuted");
		pManager->GetSelectedStatement()->SetSelected(false);
		pManager->SetSelectedStatement(NULL);
	}
}

void Move::undo(){
	moved->Move(lastPosition);
}