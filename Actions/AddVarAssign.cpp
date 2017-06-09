
#include "AddVarAssign.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

AddVarAssign::AddVarAssign(ApplicationManager *pAppManager) :Action(pAppManager)
{
	draw = true;
	redo = false;
}

void AddVarAssign::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("Variable Assignment Statement: Click to add the statement");
	if (!pIn->GetPointClicked(inlet)){
		lhs = "";
		return;
	}
	pOut->ClearStatusBar();

	pOut->PrintMessage("enter the left hand side");
	lhs = pIn->GetIdentifier(pOut);

	if (lhs == "")
		return;

	pOut->PrintMessage("enter the right hand side");
	rhs = pIn->GetIdentifier(pOut);

	if (rhs == "")
		return;

	txt = lhs + rhs;
	pIn->set_Assign_Dim(txt, width, height, t_width, t_height);

	int count = 0;
	Point lcorner;
	pIn->calc_stat_corner(inlet, lcorner, width);
	string str;
	while ((!pIn->candraw(lcorner, pManager, height, width) && count != 11) || (pIn->intersect_with_connector(height, width, lcorner, pManager))){
		str = to_string(count);
		pOut->PrintMessage("choose another position to draw         Error counter:" + str + "     be careful  error count max =10");
		if (!pIn->GetPointClicked(inlet)){
			lhs = "";
			return;
		}
		pIn->calc_stat_corner(inlet, lcorner, width);
		count++;
		draw = pIn->candraw(lcorner, pManager, height, width);
	}
	if (count != 11)
		pOut->PrintMessage("statement added correctly");
}

void AddVarAssign::Execute()
{
	ReadActionParameters();

	if (lhs == "" || rhs == ""){
		pManager->GetOutput()->PrintMessage("Canceled !!");
		SetUndo(false);
		return;
	}

	if (draw){
		VarAssign *newstat = new VarAssign(pManager, txt, inlet, width, height, t_width, t_height, lhs, rhs);

		pManager->AddStatement(newstat);
	}
	else
		SetUndo(false);
}

void AddVarAssign::undo(){
	if (!redo){
		pManager->RemoveStatment(newstat);
		redo = true;
	}
	else{
		pManager->AddStatement(newstat);
		redo = false;
	}
}