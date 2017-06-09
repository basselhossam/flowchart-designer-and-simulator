#include "Drag.h"
#include"../ApplicationManager.h"
#include"../GUI/Output.h"
#include"../GUI/Input.h"
#include "../Statements/Conditional.h"

//constructor: set the ApplicationManager pointer inside this action
Drag::Drag(ApplicationManager *pAppManager) :Action(pAppManager)
{
	h = -1;
}

void Drag::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	if (pManager->GetSelectedStatement() == NULL && pManager->GetSelectedStatements()->size() == 0)
	{
		h = 0;
		pOut->PrintMessage("Please Select a statement to Move !");
		SetUndo(false);
		return;
	}
	//single statement drag
	else if (pManager->GetSelectedStatement() != NULL && pManager->GetSelectedStatements()->size() == 0)
	{
		pManager->GetSelectedStatements()->push_back(pManager->GetSelectedStatement());
		h = 1;
	}
	moved = *pManager->GetSelectedStatements();
}

void Drag::Execute()
{

	ReadActionParameters();

	for (int i = 0; i < moved.size(); i++){
		Position.push_back(moved[i]->get_lcorner());
	}
	//Calculating left corner of assignement statement block
	//moved = pManager->GetSelectedStatements();
	//NEED TO BE CALCULATED
	Output *pOut = pManager->GetOutput();
	if (h != 0)
		pManager->multi_drag();
}

void Drag::undo(){
	for (int i = 0; i < Position.size(); i++){
		Point temp = moved[i]->get_lcorner();
		moved[i]->Move(Position[i]);
		moved[i]->SetInlet();
		moved[i]->SetOutlet();
		if (dynamic_cast<Conditional *>(moved[i])){
			Conditional*ptr = (Conditional*)moved[i];
			ptr->calc_yout();
			ptr->calc_nout();
		}
		Position[i] = temp;
	}
}