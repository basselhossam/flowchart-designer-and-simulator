#include "AddSingleOperator.h"

#include "..\ApplicationManager.h"

#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddSingleOperator::AddSingleOperator(ApplicationManager *pAppManager) :Action(pAppManager)
{
	draw = true;
	redo = false;
}

void AddSingleOperator::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("Single Operator Statement: Left Click on empty area to add the statement or Right Click to cancel.");
	if (!pIn->GetPointClicked(inlet)){
		lhs = "";
		return;
	}
	pOut->ClearStatusBar();
	pOut->PrintMessage("Enter the left hand side or ESC to Cancel.");
	lhs = pIn->GetIdentifier(pOut);

	if (lhs == "")
		return;

	pOut->ClearStatusBar();
	pOut->PrintMessage("Enter the first operand or ESC to Cancel.");
	rhs1 = pIn->GetString("",pOut);

	if (rhs1 == "")
		return;

	pOut->ClearStatusBar();
	pOut->PrintMessage("Enter the operator or ESC to Cancel.");
	op = pIn->GetArithmaticOperator(pOut);

	if (op == "")
		return;

	pOut->ClearStatusBar();
	pOut->PrintMessage("Enter the second operand or ESC to Cancel.");
	rhs2 = pIn->GetString("",pOut);

	if (rhs2 == "")
		return;

	txt = lhs + " " + rhs1 + " " + " " + op + " " + " " + rhs2;
	pIn->set_Assign_Dim(txt, width, height, t_width, t_height);

	int count = 0;
	Point lcorner;
	pIn->calc_stat_corner(inlet, lcorner, width);
	string str;
	while ((!pIn->candraw(lcorner, pManager, height, width) && count != 11) || (pIn->intersect_with_connector(height, width, lcorner, pManager))){
		str = to_string(count);
		pOut->PrintMessage("choose another position to draw or Right Click to Cancel    Error counter:" + str + "     be careful  error count max =10");
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

void AddSingleOperator::Execute()
{

	ReadActionParameters();

	if (lhs == "" || rhs1 == "" || op == "" || rhs2 == ""){
		pManager->GetOutput()->PrintMessage("Canceled !!");
		SetUndo(false);
		return;
	}

	if (draw){
		newstat = new SingleOperator(pManager, txt, inlet, width, height, t_width, t_height, lhs, rhs1, op, rhs2);
		pManager->AddStatement(newstat);
	}
	else
		SetUndo(false);
}

void AddSingleOperator::undo(){
	if (!redo){
		pManager->RemoveStatment(newstat);
		redo = true;
	}
	else{
		pManager->AddStatement(newstat);
		redo = false;
	}
}