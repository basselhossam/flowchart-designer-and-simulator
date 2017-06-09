#include "AddSmplAssign.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
#include<string>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddSmplAssign::AddSmplAssign(ApplicationManager *pAppManager):Action(pAppManager)
{
	draw = true;
	redo = false;
}

void AddSmplAssign::ReadActionParameters()
{
	Output *pOut = pManager->GetOutput();
	Input *pIn = pManager->GetInput();
	pOut->PrintMessage("Simple Assign Statement: Left Click on empty space to add the statement or right click to cancel.");
	if (!pIn->GetPointClicked(inlet)){
		lhs = "";
		return;
	}
	
	pOut->ClearStatusBar();
	pOut->PrintMessage("enter the left hand side or ESC to cancel.");
	lhs = pIn->GetIdentifier(pOut);

	if (lhs == "")
		return;

	pOut->ClearStatusBar();
	pOut->PrintMessage("enter the right hand side or ESC to cancel.");
	rhs = pIn->GetValue(pOut);

	if (rhs == inv)
		return;

	stringstream outStream;
	outStream << rhs;
	string srhs = outStream.str();
	txt = lhs + " = " + srhs;

	pIn->set_Assign_Dim(txt, width, height, t_width, t_height);
	
	int count = 0;
	Point lcorner;
	pIn->calc_stat_corner(inlet, lcorner, width);
	string str;
	while ((!pIn->candraw(lcorner, pManager, height, width) && count != 11) || (pIn->intersect_with_connector(height, width, lcorner, pManager))){
		str = to_string(count);
		pOut->PrintMessage("choose another position to draw or right click to cancel.      Error counter:" + str + "     be careful  error count max =10");
		if (pIn->GetPointClicked(inlet)){
			pIn->calc_stat_corner(inlet, lcorner, width);
			count++;
			draw = pIn->candraw(lcorner, pManager, height, width);
		}
		else{
			lhs = "";
			return;
		}
	}
	if (count != 11)
		pOut->PrintMessage("statement added correctly");
	
}

void AddSmplAssign::Execute()
{

	ReadActionParameters();

	if (lhs == "" || rhs == inv){
		pManager->GetOutput()->PrintMessage("Canceled !!");
		SetUndo(false);
		return;
	}

	if (draw){
		newstat = new SmplAssign(pManager, txt, inlet, width, height, t_width, t_height, lhs, rhs);

		pManager->AddStatement(newstat);
	}
	else
		SetUndo(false);
}

void AddSmplAssign::undo(){
	if (!redo){
		pManager->RemoveStatment(newstat);
		redo = true;
	}
	else{
		pManager->AddStatement(newstat);
		redo = false;
	}
}