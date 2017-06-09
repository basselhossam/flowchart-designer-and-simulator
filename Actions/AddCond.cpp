#include "AddCond.h"
#include "..\Statements\Conditional.h"

#include "..\ApplicationManager.h"

#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddCond::AddCond(ApplicationManager *pAppManager):Action(pAppManager)
{
	redo = false;
}

void AddCond::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	pOut->PrintMessage("Conditional Statement: Click to add the statement");
	if (!pIn->GetPointClicked(inlet)){
		lhs = "";
		return;
	}
	
	pOut->ClearStatusBar();		
	pOut->PrintMessage("Enter the left hand side");
	lhs = pIn->GetIdentifier(pOut);

	if (lhs == "")
		return;

	pOut->ClearStatusBar();		
	pOut->PrintMessage("Enter the operator");
	op=pIn->GetLogicalOperator(pOut);

	if (op == "")
		return;

	pOut->ClearStatusBar();
	pOut->PrintMessage("Enter the right hand side");
	rhs= pIn->GetString("",pOut);

	if (rhs == "")
		return;

	txt = rhs + op + lhs;

	pIn->set_cond_Dim(txt, width, height, t_width, t_height);

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

void AddCond::Execute()
{
	
	ReadActionParameters();
	if (lhs == "" || op == "" || rhs == ""){
		pManager->GetOutput()->PrintMessage("Canceled !!");
		SetUndo(false);
		return;
	}

	if (draw){
		newstat = new Conditional(pManager, txt, inlet, width, height, t_width, t_height, lhs, op, rhs);
		pManager->AddStatement(newstat);
	}
	else
		SetUndo(false);
}

void AddCond::undo(){
	if (!redo){
		pManager->RemoveStatment(newstat);
		redo = true;
	}
	else{
		pManager->AddStatement(newstat);
		redo = false;
	}
}