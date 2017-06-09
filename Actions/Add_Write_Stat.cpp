#include "Add_Write_Stat.h"
#include"..\Statements\Write_Stat.h"

Add_Write_Stat::Add_Write_Stat(ApplicationManager *pAppManager)
:Action(pAppManager)
{
	txt = "";
	draw = true;
	redo = false;
}


void  Add_Write_Stat::ReadActionParameters()
{
	Output *pOut = pManager->GetOutput();
	Input *pIn = pManager->GetInput();
	pOut->PrintMessage("writing Statement: Click to add the statement");
	if (!pIn->GetPointClicked(inlet)){
		txt = "Print ";
		return;
	}

	pOut->PrintMessage("now enter the variables that will be read from the user in this way Iden1,Iden2,..");
	txt = "Print " + pIn->GetIdentifiers(txt, pOut, v1);

	if (txt == "Print ")
		return;

	pIn->set_Read_Write_Dim(txt, width, height, t_width, t_height, factor);   //for setting the dimensions of the statement
	                                                    //width,height,t_width,t_height are passed by reference to be calculated then returned
	Point lcorner;
	pIn->calc_Read_corner(inlet, lcorner, width, factor);

	int count = 0;
	string str;
	while ((!pIn->candraw(lcorner, pManager, height, width) && count != 11) || (pIn->intersect_with_connector(height, width, lcorner, pManager))){
		str = to_string(count);
		pOut->PrintMessage("choose another position to draw         Error counter:" + str + "     becareful  error count max =10");
		if (!pIn->GetPointClicked(inlet)){
			txt = "Print ";
			return;
		}
		pIn->calc_Read_corner(inlet, lcorner, width, factor);
		count++;
		draw = pIn->candraw(lcorner, pManager, height, width);
	}
	if (count != 11)
		pOut->PrintMessage("statement added correctly");
}


void Add_Write_Stat::Execute()
{
	Output *pOut = pManager->GetOutput();
	Input *pIn = pManager->GetInput();
	ReadActionParameters();
	if (txt == "Print " || !draw){
		pOut->PrintMessage("the statement is empty, this isn't allowed try to add again");
		SetUndo(false);
		return;
	}
	else
	{
		write = new Write_Stat(pManager, txt, inlet, v1, width, height, t_width, t_height, factor);
		pManager->AddStatement(write);
	}
}

void Add_Write_Stat::undo()
{
	if (!redo){
		pManager->RemoveStatment(write);
		redo = true;
	}
	else{
		pManager->AddStatement(write);
		redo = false;
	}
}
