#include "SingleOperator.h"
#include <sstream>

using namespace std;

SingleOperator::SingleOperator(ApplicationManager * AM, string txt, Point l_cor, int width, int height, int t_width, int t_height, string LeftHS, string RightHS1, string op, string RightHS2)
: Statement(AM, txt, l_cor, width, height, t_width, t_height)
{
	LHS = LeftHS;
	RHS1 = RightHS1;
	OP = op;
	RHS2 = RightHS2;

	UpdateStatementText();

	calc_l_corner();

	pConn = NULL;	//No connectors yet
}

void SingleOperator::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}


void SingleOperator::setRHS1(const string &R1)
{
	//missing
	RHS1 = R1;
	UpdateStatementText();
}


void SingleOperator::setOperator(const string &p)
{
	//missing
	if (p == "+" || p == "-" || p == "*" || p == "/")
		OP = p;
	UpdateStatementText();
}

string SingleOperator::GetOperator()const{
	return OP;
}

void SingleOperator::setRHS2(const string &R2)
{
	//missing
	RHS2 = R2;
	UpdateStatementText();
}

void SingleOperator::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(l_corner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}


//This function should be called when LHS or RHS changes
void SingleOperator::UpdateStatementText()
{
	if (LHS == "")	//No left handside ==>statement have no valid text yet
		Text = "    = ";
	else
	{
		//Build the statement text: Left handside then equals then right handside
		ostringstream T;
		T << LHS << " = " << RHS1<<OP<<RHS2;
		Text = T.str();
	}
}

bool SingleOperator::Edit(){

	string lhs, rhs1, op, rhs2;

	pOut->ClearStatusBar();
	pOut->PrintMessage("Enter the left hand side");
	lhs = pIn->GetIdentifier(pOut);

	if (lhs == ""){
		pOut->PrintMessage("Cancel !!");
		return false;
	}

	pOut->ClearStatusBar();
	pOut->PrintMessage("Enter the first operand");
	rhs1 = pIn->GetString("",pOut);

	if (rhs1 == ""){
		pOut->PrintMessage("Cancel !!");
		return false;
	}

	pOut->ClearStatusBar();
	pOut->PrintMessage("Enter the operator");
	op = pIn->GetArithmaticOperator(pOut);

	if (op == ""){
		pOut->PrintMessage("Cancel !!");
		return false;
	}

	pOut->ClearStatusBar();
	pOut->PrintMessage("Enter the first operand");
	rhs2 = pIn->GetString("",pOut);

	if (rhs2 == ""){
		pOut->PrintMessage("Cancel !!");
		return false;
	}

	LHS = lhs;
	RHS1 = rhs1;
	OP = op;
	RHS2 = rhs2;

	UpdateStatementText();
	pIn->set_Assign_Dim(Text, width, height, t_width, t_height);
	calc_l_corner();
	SetInlet();
	SetOutlet();
	return true;
}

string SingleOperator::GetLHS()const
{
	return LHS;
}
string SingleOperator::GetRHS1() const
{
	return RHS1;
}
string SingleOperator::GetRHS2()const
{
	return RHS2;
}


void SingleOperator::GenerateCode(ofstream &OutFile){

	//we need to make a varible list to know if it's the first time being intialized or not
	//if the varible is exist in the varible list
	OutFile <<"  "<< Text << ";\n";
	SetGenerated(true);
}
void SingleOperator::calc_l_corner()
{
	AppMan->GetInput()->calc_stat_corner(inlet, l_corner, width);
}

void SingleOperator::Save(ofstream &OutFile)
{
	OutFile << "SNGLOP"<<"  "<< ID << "  " << l_corner.x << "  " << l_corner.y<<"  "<<LHS<<"  "<<RHS1<<"  "<<OP<<"  "<<RHS2<<"  ";

	OutFile << "\"" << comment << "\"" << endl;
}


void SingleOperator::Load(ifstream & Infile)
{
	Infile >> ID >> l_corner.x >> l_corner.y >> LHS >>  RHS1 >> OP >> RHS2;
	UpdateStatementText();

	set_stat_dim(Text);
	SetInlet();
	SetOutlet();
	getline(Infile, comment);

	comment.erase(comment.begin());
	comment.erase(comment.end()-1);

}

bool SingleOperator::check_range(Point p)
{
	if (p.x >= l_corner.x && p.x <= l_corner.x + width && p.y >= l_corner.y && p.y <= l_corner.y + height)
		return true;
	else
		return false;

}

void SingleOperator::PrintInfo(Output * pOut)
{
	pOut->PrintMessage(comment);
}

void SingleOperator::set_stat_dim(string str)
{
	pIn->set_Assign_Dim(Text, width, height, t_width, t_height);
}

Connector* SingleOperator :: GetConnect(){
	return pConn;
}
void SingleOperator :: SetConnect(Connector*p){
	pConn = p;
}

bool SingleOperator::Simulate(){
	double a ,b ;

	//For first operand
	if(!CheckValue(RHS1) && !CheckIdentifier(RHS1))
	{
			pOut->ClearStatusBar();
		    pOut->PrintMessage("ERROR in First Operand !");

    		this->SetSelected(true);
	    	AppMan->SetSelectedStatement(this);

		    return false;
	}	
	
	if (CheckValue(RHS1))
	{
		stringstream s;
		s<<RHS1;
		s>>a;
		s.str("");
		s.clear();
	}
	else if(CheckIdentifier(RHS1))
	{
		if(AppMan->variables.find(RHS1)!=AppMan->variables.end())
		   a = AppMan->variables[RHS1];
		else
			{pOut->ClearStatusBar();
		    pOut->PrintMessage("ERROR : First Operand Undeclared !");

    		this->SetSelected(true);
	    	AppMan->SetSelectedStatement(this);

		    return false;
		   }
	}

	//for second operand

	if(!CheckValue(RHS2) && !CheckIdentifier(RHS2))
	{
			pOut->ClearStatusBar();
		    pOut->PrintMessage("ERROR in Second Operand !");

    		this->SetSelected(true);
	    	AppMan->SetSelectedStatement(this);

		    return false;
	}	
	
	if (CheckValue(RHS2))
	{
		stringstream s;
		s<<RHS2;
		s>>b;
		s.str("");
		s.clear();
	}
	else if(CheckIdentifier(RHS2))
	{
		if(AppMan->variables.find(RHS2)!=AppMan->variables.end())
		   b = AppMan->variables[RHS2];
		else
		{
			pOut->ClearStatusBar();
		    pOut->PrintMessage("ERROR : Second Operand Undeclared !");

    		this->SetSelected(true);
	    	AppMan->SetSelectedStatement(this);

		    return false;
		}

	}



	if(OP == "+")
		AppMan->variables[LHS]= a + b;
	else if (OP == "-")
		AppMan->variables[LHS]= a - b;
	else if(OP == "/")
	{
		if(b == 0)
		{
			pOut->ClearStatusBar();
			pOut->PrintMessage("MATHS ERROR : Can't divide on zero !");
			this->SetSelected(true);
	    	AppMan->SetSelectedStatement(this);
			return false;
		}
		AppMan->variables[LHS]= a / b;
	}
	else if(OP == "*")
		AppMan->variables[LHS]= a * b;
return true;
}