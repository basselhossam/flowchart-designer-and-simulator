#include "Edit.h"
#include "../Statements/allstatements.h"

Edit::Edit(ApplicationManager *pAppManager) :Action(pAppManager)
{
}

void Edit::ReadActionParameters(){

	ptr = pManager->GetSelectedStatement();

}

void Edit::Execute(){

	ReadActionParameters();

	if (ptr != NULL){
		if (dynamic_cast<Conditional*>(ptr)){
			Conditional*pcond = (Conditional*)ptr;
			lhs = pcond->GetLHS();
			rhs1 = pcond->GetRHS();
			op = pcond->GetOperator();
		}
		else if (dynamic_cast<SmplAssign*>(ptr)){
			SmplAssign*pcond = (SmplAssign*)ptr;
			lhs = pcond->GetLHS();
			rhs = pcond->GetRHS();
		}
		else if (dynamic_cast<VarAssign*>(ptr)){
			VarAssign*pcond = (VarAssign*)ptr;
			lhs = pcond->GetLHS();
			rhs1 = pcond->GetRHS();
		}
		else if (dynamic_cast<SingleOperator*>(ptr)){
			SingleOperator*pcond = (SingleOperator*)ptr;
			lhs = pcond->GetLHS();
			op = pcond->GetOperator();
			rhs1 = pcond->GetRHS1();
			rhs2 = pcond->GetRHS2();
		}
		else if (dynamic_cast<Read_Stat*>(ptr)){
			Read_Stat*pcond = (Read_Stat*)ptr;
			var = pcond->Getvar();
		}
		else if (dynamic_cast<Write_Stat*>(ptr)){
			Write_Stat*pcond = (Write_Stat*)ptr;
			var = pcond->Getvar();
		}
		SetUndo(ptr->Edit());
		ptr->SetSelected(false);
		pManager->SetSelectedStatement(NULL);
	}
	else{
		pManager->GetOutput()->PrintMessage("ERROR : there is no Selected Statement , Click any where to containue");
		SetUndo(false);
	}

}

void Edit::undo(){
	if (ptr != NULL){
		string temp;
		if (dynamic_cast<Conditional*>(ptr)){
			Conditional*pcond = (Conditional*)ptr;
			temp = pcond->GetLHS();
			pcond->setLHS(lhs);
			lhs = temp;
			temp = pcond->GetRHS();
			pcond->setRHS(rhs1);
			rhs1 = temp;
			temp = pcond->GetOperator();
			pcond->setOperator(op);
			op = temp;
		}
		else if (dynamic_cast<SmplAssign*>(ptr)){
			SmplAssign*pcond = (SmplAssign*)ptr;
			temp = pcond->GetLHS();
			pcond->setLHS(lhs);
			lhs = temp;
			double x = pcond->GetRHS();
			pcond->setRHS(rhs);
			rhs = x;
		}
		else if (dynamic_cast<VarAssign*>(ptr)){
			VarAssign*pcond = (VarAssign*)ptr;
			temp = pcond->GetLHS();
			pcond->setLHS(lhs);
			lhs = temp;
			temp = pcond->GetRHS();
			pcond->setRHS(rhs1);
			rhs1 = temp;
		}
		else if (dynamic_cast<SingleOperator*>(ptr)){
			SingleOperator*pcond = (SingleOperator*)ptr;
			temp = pcond->GetLHS();
			pcond->setLHS(lhs);
			lhs = temp;
			temp = pcond->GetOperator();
			pcond->setOperator(op);
			op = temp;
			temp = pcond->GetRHS1();
			pcond->setRHS1(rhs1);
			rhs1 = temp;
			temp = pcond->GetRHS2();
			pcond->setRHS2(rhs2);
			rhs2 = temp;
		}
		else if (dynamic_cast<Read_Stat*>(ptr)){
			Read_Stat*pcond = (Read_Stat*)ptr;
			vector<string>tmp = pcond->Getvar();
			pcond->setvar(var);
			var = tmp;
		}
		else if (dynamic_cast<Write_Stat*>(ptr)){
			Write_Stat*pcond = (Write_Stat*)ptr;
			vector<string>tmp = pcond->Getvar();
			pcond->setvar(var);
			var = tmp;
		}
	}
}