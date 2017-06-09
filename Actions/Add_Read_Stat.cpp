///added by amr

#include "Add_Read_Stat.h"
#include<sstream>

Add_Read_Stat::Add_Read_Stat(ApplicationManager *pAppManager)
:Action(pAppManager)
{
	ptr = NULL;
	txt = "";
	draw = true;
	redo = false;
}

void  Add_Read_Stat::ReadActionParameters()
{
	Output *pOut = pManager->GetOutput();
	Input *pIn = pManager->GetInput();
	pOut->PrintMessage("Reading  Statement: Click to add the statement");
	if (!pIn->GetPointClicked(inlet)){
		txt = "Read ";
		return;
	}

	pOut->PrintMessage("now enter the variables that will be read from the user in this way  Iden1,Iden2,..");
	txt ="Read "+ pIn->GetIdentifiers(txt, pOut, v1);

	if (txt=="Read ")
		return;
	pIn->set_Read_Write_Dim(txt, width, height, t_width, t_height, factor);
	int count = 0;
	Point lcorner;
	pIn->calc_Read_corner(inlet, lcorner, width, factor);
	string str;
	while ((!pIn->candraw(lcorner, pManager, height, width) && count != 11) || (pIn->intersect_with_connector(height, width, lcorner, pManager)))
	{
		str = to_string(count);
		pOut->PrintMessage("choose another position to draw         Error counter:" + str+"     be careful  error count max =10");
		if (!pIn->GetPointClicked(inlet)){
			txt = "Read ";
			return;
		}
		pIn->calc_Read_corner(inlet, lcorner, width, factor);
		count++;
		draw = pIn->candraw(lcorner, pManager, height, width);
	}
	if (count != 11)
		pOut->PrintMessage("statement added correctly");
}

void Add_Read_Stat::Execute()
{
	Output *pOut = pManager->GetOutput();
	Input *pIn = pManager->GetInput();
	ReadActionParameters();
	if (txt == "Read "){
		pOut->PrintMessage("Canceled !!");
		SetUndo(false);
		return;
	}
	if (txt == "Read " || !draw){
		pOut->PrintMessage("the statement is empty, this isn't allowed try to add again");
		SetUndo(false);
		return;
	}
	else
	{
		read = new Read_Stat(pManager, txt, inlet, v1, width, height, t_width, t_height, factor);
		pManager->AddStatement(read);
	}
}


void Add_Read_Stat::undo()
{
	if (!redo){
		pManager->RemoveStatment(read);
		redo = true;
	}
	else
	{
		pManager->AddStatement(read);
		redo = false;
	}
}
