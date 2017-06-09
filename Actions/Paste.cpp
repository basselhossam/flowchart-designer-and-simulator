#include "Paste.h"

#include "..\ApplicationManager.h"

#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Paste::Paste(ApplicationManager *pAppManager):Action(pAppManager)
{
	SetUndo(false);
	//redo = false;
}

void Paste::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	if (pManager->GetCopied() || pManager->GetCut())
	{
		if (pManager->GetCopied() != NULL)
			pasted = pManager->GetCopied();
		else
			pasted = pManager->GetCut();
		pasted->get_data(txt, width, height, t_width, t_height);

		pOut->ClearStatusBar();
		pOut->PrintMessage("Select position to Paste!");
		pIn->GetPointClicked(Position);
		Point lcorner;
		pIn->calc_stat_corner(Position, lcorner, width);

		int count = 0;
		pIn->calc_stat_corner(Position, lcorner, width);
		string str;
		while (!pIn->candraw(lcorner, pManager, height, width) && count != 11)
		{
			str = to_string(count);
			pOut->PrintMessage("choose another position to draw         Error counter:" + str + "     be careful  error count max =10");
			pIn->GetPointClicked(Position);
			pIn->calc_stat_corner(Position, lcorner, width);
			count++;
		}
		if (count != 11)
			pOut->PrintMessage("statement added correctly");

	}
	else if (pManager->GetMultiCut()->size()>0 || pManager->GetMultiCopy()->size()>0)
	{
		if (pManager->GetMultiCut()->size() > 0)
			pastedstatments = pManager->GetMultiCut();
		else
			pastedstatments = pManager->GetMultiCopy();
		if (pastedstatments->size() >0)
		{
			string counter;
			int i = pastedstatments->size() - 1;
			while (i >= 0)
			{
				counter = to_string(pastedstatments->size() - i);
				pManager->addSelectedStatement(pastedstatments->operator[](i));
				pManager->UpdateInterface();
				pOut->ClearStatusBar();
				pOut->PrintMessage("Select position for statement no." + counter + ": " + pastedstatments->operator[](i)->get_text());
				pIn->GetPointClicked(Positions[i]);
				Point lcorner;
				pIn->calc_stat_corner(Positions[i], lcorner, pastedstatments->operator[](i)->get_width());

				int count = 0;
				string str;
				while (!pIn->candraw(lcorner, pManager, pastedstatments->operator[](i)->get_height(), pastedstatments->operator[](i)->get_width()) && count != 11)
				{
					str = to_string(count);
					pOut->PrintMessage("choose another position to draw         Error counter:" + str + "     be careful  error count max =10");
					pIn->GetPointClicked(Positions[i]);
					pIn->calc_stat_corner(Positions[i], lcorner, pastedstatments->operator[](i)->get_width());
					count++;
				}
				if (count != 11)
				{
					pOut->PrintMessage("Statement was added");
					pManager->UpdateInterface();
				}
				pManager->unSelectStatement(pastedstatments->operator[](i));
				i--;
			}
		}
	}
	else
		pOut->PrintMessage("No statement is Copied,Cut or Moved !");

}

void Paste::Execute()
{
	
	ReadActionParameters();
		
	//Calculating left corner of assignement statement block

	//NEED TO BE CALCULATED
	Output *pOut = pManager->GetOutput();

	Statement *ptr = pManager->GetCopied();
	if (ptr)
	{
		if (dynamic_cast<Conditional*>(ptr))
		{
			Conditional*cond = (Conditional*)ptr;
			Conditional*pCond = new Conditional(pManager, txt, Position, width, height, t_width, t_height, cond->LHS, cond->OPR, cond->RHS);
			pManager->AddStatement(pCond);
			pOut->ClearStatusBar();
			pOut->PrintMessage("Pasted!!");
		}
		else if (dynamic_cast<SmplAssign*>(ptr))
		{
			SmplAssign*sa = (SmplAssign*)ptr;
			SmplAssign*pSa = new SmplAssign(pManager, txt, Position, width, height, t_width, t_height, sa->LHS, sa->RHS);
			pManager->AddStatement(pSa);
			pOut->ClearStatusBar();
			pOut->PrintMessage("Pasted!!");
		}

		else if (dynamic_cast<VarAssign*>(ptr))
		{
			VarAssign*sa = (VarAssign*)ptr;
			VarAssign*pSa = new VarAssign(pManager, txt, Position, width, height, t_width, t_height, sa->LHS, sa->RHS);
			pManager->AddStatement(pSa);
			pOut->ClearStatusBar();
			pOut->PrintMessage("Pasted!!");
		}

		else if (dynamic_cast<SingleOperator*>(ptr))
		{
			SingleOperator*so = (SingleOperator*)ptr;
			SingleOperator*pSa = new SingleOperator(pManager, txt, Position, width, height, t_width, t_height, so->LHS, so->RHS1, so->OP, so->RHS2);
			pManager->AddStatement(pSa);
			pOut->ClearStatusBar();
			pOut->PrintMessage("Pasted!!");
		}

		else if (dynamic_cast<Read_Stat*>(ptr))
		{
			Read_Stat*so = (Read_Stat*)ptr;
			Read_Stat*pSa = new Read_Stat(pManager, txt, Position, so->V1, width, height, t_width, t_height, so->factor);
			pManager->AddStatement(pSa);
			pOut->ClearStatusBar();
			pOut->PrintMessage("Pasted!!");
		}

		else if (dynamic_cast<Write_Stat*>(ptr))
		{
			Write_Stat*so = (Write_Stat*)ptr;
			Write_Stat*pSa = new Write_Stat(pManager, txt, Position, so->V1, width, height, t_width, t_height, so->factor);
			pManager->AddStatement(pSa);
			pOut->ClearStatusBar();
			pOut->PrintMessage("Pasted!!");
		}

		else if (dynamic_cast<Start*>(ptr))
		{
			Start*so = (Start*)ptr;
			Start*pSa = new Start(pManager, txt, Position, width, height, t_width, t_height);
			pManager->AddStatement(pSa);
			pOut->ClearStatusBar();
			pOut->PrintMessage("Pasted!!");
		}

		else if (dynamic_cast<End*>(ptr))
		{
			End*so = (End*)ptr;
			End*pSa = new End(pManager, txt, Position, width, height, t_width, t_height);
			pManager->AddStatement(pSa);
			pOut->ClearStatusBar();
			pOut->PrintMessage("Pasted!!");
		}

		if (pManager->GetSelectedStatement())
			pManager->GetSelectedStatement()->SetSelected(false);
		pManager->SetSelectedStatement(NULL);
		//pManager->SetCopied(NULL);
	}
	else if (pManager->GetCut())
	{
		ptr = pManager->GetCut();
		ptr->Move(Position);
		ptr->SetCut(false);
		pManager->SetCopied(ptr);
		pManager->SetCut(NULL);
	}

	else if (pManager->GetMultiCopy()->size() > 0)
	{
		Statement *ptr;
		int i = pManager->GetMultiCopy()->size() - 1;
		while (i >= 0)
		{
			pManager->UpdateInterface();
			ptr = pManager->GetMultiCopy()->operator[](i);
			if (ptr)
			{
				if (dynamic_cast<Conditional*>(ptr))
				{
					Conditional*cond = (Conditional*)ptr;
					Conditional*pCond = new Conditional(pManager, ptr->get_text(), Positions[i], ptr->get_width(), ptr->get_height(), ptr->get_t_width(), ptr->get_t_height(), cond->LHS, cond->OPR, cond->RHS);
					pManager->AddStatement(pCond);
					pOut->ClearStatusBar();
					pOut->PrintMessage("Pasted!!");
				}
				else if (dynamic_cast<SmplAssign*>(ptr))
				{
					SmplAssign*sa = (SmplAssign*)ptr;
					SmplAssign*pSa = new SmplAssign(pManager, ptr->get_text(), Positions[i], ptr->get_width(), ptr->get_height(), ptr->get_t_width(), ptr->get_t_height(), sa->LHS, sa->RHS);
					pManager->AddStatement(pSa);
					pOut->ClearStatusBar();
					pOut->PrintMessage("Pasted!!");
				}

				else if (dynamic_cast<VarAssign*>(ptr))
				{
					VarAssign*sa = (VarAssign*)ptr;
					VarAssign*pSa = new VarAssign(pManager, ptr->get_text(), Positions[i], ptr->get_width(), ptr->get_height(), ptr->get_t_width(), ptr->get_t_height(), sa->LHS, sa->RHS);
					pManager->AddStatement(pSa);
					pOut->ClearStatusBar();
					pOut->PrintMessage("Pasted!!");
				}

				else if (dynamic_cast<SingleOperator*>(ptr))
				{
					SingleOperator*so = (SingleOperator*)ptr;
					SingleOperator*pSa = new SingleOperator(pManager, ptr->get_text(), Positions[i], ptr->get_width(), ptr->get_height(), ptr->get_t_width(), ptr->get_t_height(), so->LHS, so->RHS1, so->OP, so->RHS2);
					pManager->AddStatement(pSa);
					pOut->ClearStatusBar();
					pOut->PrintMessage("Pasted!!");
				}

				else if (dynamic_cast<Read_Stat*>(ptr))
				{
					Read_Stat*so = (Read_Stat*)ptr;
					Read_Stat*pSa = new Read_Stat(pManager, ptr->get_text(), Positions[i], so->V1, ptr->get_width(), ptr->get_height(), ptr->get_t_width(), ptr->get_t_height(), so->factor);
					pManager->AddStatement(pSa);
					pOut->ClearStatusBar();
					pOut->PrintMessage("Pasted!!");
				}

				else if (dynamic_cast<Write_Stat*>(ptr))
				{
					Write_Stat*so = (Write_Stat*)ptr;
					Write_Stat*pSa = new Write_Stat(pManager, ptr->get_text(), Positions[i], so->V1, ptr->get_width(), ptr->get_height(), ptr->get_t_width(), ptr->get_t_height(), so->factor);
					pManager->AddStatement(pSa);
					pOut->ClearStatusBar();
					pOut->PrintMessage("Pasted!!");
				}

				else if (dynamic_cast<Start*>(ptr))
				{
					Start*so = (Start*)ptr;
					Start*pSa = new Start(pManager, ptr->get_text(), Positions[i], ptr->get_width(), ptr->get_height(), ptr->get_t_width(), ptr->get_t_height());
					pManager->AddStatement(pSa);
					pOut->ClearStatusBar();
					pOut->PrintMessage("Pasted!!");
				}

				else if (dynamic_cast<End*>(ptr))
				{
					End*so = (End*)ptr;
					End*pSa = new End(pManager, ptr->get_text(), Positions[i], ptr->get_width(), ptr->get_height(), ptr->get_t_width(), ptr->get_t_height());
					pManager->AddStatement(pSa);
					pOut->ClearStatusBar();
					pOut->PrintMessage("Pasted!!");
				}
				pManager->UpdateInterface();
			}
			i--;
		}
		pManager->GetMultiCut()->clear();
		pManager->GetOutput()->ClearStatusBar();
		pManager->GetOutput()->PrintMessage("Statements are Pasted successfully!");
		pManager->unSelectStatements();
	}
	else if (pManager->GetMultiCut()->size() > 0)
	{
		Statement *ptr;
		int i = pManager->GetMultiCut()->size() - 1;
		while (i >= 0)
		{
			pManager->UpdateInterface();
			ptr = pManager->GetMultiCut()->operator[](i);
			ptr->Move(Positions[i]);
			pManager->GetMultiCut()->operator[](i)->SetCut(false);
			i--;
			pManager->UpdateInterface();
		}
		pManager->SetMultiCopy((*pManager->GetMultiCut()));
		pManager->GetMultiCut()->clear();
	}
}

//void Paste::undo(){
//	if (!redo){
//		if (ptr)
//			pManager->RemoveStatment(newstat);
//		else{
//			Point temp = ptr->get_lcorner();
//			ptr->Move(lastpos);
//			lastpos = temp;
//			ptr->SetCut(true);
//			pManager->SetCopied(NULL);
//			pManager->SetCut(ptr);
//		}
//	}
//	else{
//		if (ptr)
//			pManager->AddStatement(newstat);
//		else{
//			Point temp = ptr->get_lcorner();
//			ptr->Move(lastpos);
//			lastpos = temp;
//			ptr->SetCut(false);
//			pManager->SetCopied(ptr);
//			pManager->SetCut(NULL);
//		}
//	}
//}