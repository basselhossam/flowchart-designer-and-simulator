#include "AddEnd.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddEnd::AddEnd(ApplicationManager *pAppManager) :Action(pAppManager)
{
	draw = true;
	redo = false;
}


void AddEnd::ReadActionParameters()
{
	Output *pOut = pManager->GetOutput();
	Input *pIn = pManager->GetInput();
	pOut->PrintMessage("End  Statement: Click to add the statement");
	if (!pIn->GetPointClicked(inlet)){
		txt = "";
		return;
	}
	txt = "End";
	pIn->set_ellipse_Dim(txt, width, height, t_width, t_height);
	int count = 0;
	Point lcorner;
	pIn->calc_stat_corner(inlet, lcorner, width);
	string str;
	while ((!pIn->candraw(lcorner, pManager, height, width) && count != 11) || (pIn->intersect_with_connector(height, width, lcorner, pManager)))
	{
		str = to_string(count);
		pOut->PrintMessage("choose another position to draw         Error counter:" + str + "     be careful  error count max =10");
		if (!pIn->GetPointClicked(inlet)){
			txt = "";
			return;
		}
		pIn->calc_stat_corner(inlet, lcorner, width);
		count++;
		draw = pIn->candraw(lcorner, pManager, height, width);
	}
	if (count != 11)
		pOut->PrintMessage("statement added correctly");
}

void AddEnd::Execute(){

	ReadActionParameters();

	if (txt == ""){
		pManager->GetOutput()->PrintMessage("Canceled. !!");
		SetUndo(false);
		return;
	}

	if (draw){

		newstat = new End(pManager, txt, inlet, width, height, t_width, t_height);

		pManager->AddStatement(newstat);
	}
	else
		SetUndo(false);

}

void AddEnd::undo(){
	if (!redo){
		pManager->RemoveStatment(newstat);
		redo = true;
	}
	else{
		pManager->AddStatement(newstat);
		redo = false;
	}
}
