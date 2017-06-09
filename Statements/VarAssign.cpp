#include "VarAssign.h"
#include <sstream>
using namespace std;


VarAssign::VarAssign(ApplicationManager * AM, string txt, Point l_cor, int width, int height, int t_width, int t_height, string LeftHS, string RightHS)
: Statement(AM, txt, l_cor, width, height, t_width, t_height)
{
	LHS = LeftHS;
	RHS = RightHS;

	UpdateStatementText();

	l_corner = l_cor;

	pConn = NULL;	//No connectors yet

	calc_l_corner();
}

void VarAssign::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}


void VarAssign::setRHS(string R)
{
	RHS = R;
	UpdateStatementText();
}

bool VarAssign::Edit(){

	string lhs, rhs;

	pOut->PrintMessage("enter the left hand side");
	lhs = pIn->GetIdentifier(pOut);

	if (lhs == ""){
		pOut->PrintMessage("Cancel !!");
		return false;
	}

	pOut->PrintMessage("enter the right hand side");
	rhs = pIn->GetIdentifier(pOut);

	if (rhs == ""){
		pOut->PrintMessage("Cancel !!");
		return false;
	}

	LHS = lhs;
	RHS = rhs;

	UpdateStatementText();
	pIn->set_Assign_Dim(Text, width, height, t_width, t_height);

	calc_l_corner();
	SetInlet();
	SetOutlet();

	return true;
}


void VarAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(l_corner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}


//This function should be called when LHS or RHS changes
void VarAssign::UpdateStatementText()
{
	if (LHS == "")	//No left handside ==>statement have no valid text yet
		Text = "    = ";
	else
	{
		//Build the statement text: Left handside then equals then right handside
		ostringstream T;
		T << LHS << " = " << RHS;
		Text = T.str();
	}
}

bool VarAssign :: check_range(Point p)
{
	if (p.x >= l_corner.x  &&   p.x <= l_corner.x + UI.ASSGN_WDTH   &&   p.y >= l_corner.y  &&  p.y <= l_corner.y + UI.ASSGN_HI)
		return true;
	else
		return false;
}

void VarAssign::GenerateCode(ofstream &OutFile){

	//we need to make a varible list to know if it's the first time being intialized or not
	//if the varible is exist in the varible list
	OutFile <<"  "<< LHS << " = " << RHS << ";\n";
	SetGenerated(true);
}

void VarAssign::Save(ofstream &OutFile)
{
	OutFile << "VARASSIGN"<<"       "<< ID << "  " << l_corner.x << "  " << l_corner.y << "  " << LHS << "  " << RHS << "  ";

	OutFile << "\"" << comment << "\"" << endl;
}


void VarAssign::Load(ifstream & Infile)
{
	Infile >> ID >> l_corner.x >> l_corner.y >> LHS >> RHS;
	UpdateStatementText();
	set_stat_dim(Text);
	SetInlet();
	SetOutlet();

	getline(Infile, comment);
	comment.erase(comment.begin()+1);
	comment.erase(comment.end()-1);

}

void VarAssign::PrintInfo(Output * pOut)
{
	pOut->PrintMessage(comment);
}

void VarAssign::set_stat_dim(string str)
{
	pIn->set_Assign_Dim(Text, width, height, t_width, t_height);
}

void VarAssign::calc_l_corner(){
	AppMan->GetInput()->calc_stat_corner(inlet, l_corner, width);
}

Connector* VarAssign ::GetConnect(){
	return pConn;
}
void VarAssign :: SetConnect(Connector*p){
	pConn = p;
}

bool VarAssign::Simulate(){
	bool error = false;
	if(AppMan->variables.find(RHS)!= AppMan->variables.end())
	{
		AppMan->variables[LHS] = AppMan->variables[RHS];
	}
	else {
		pOut->ClearStatusBar();
		pOut->PrintMessage("ERROR : Undeclared Identifier "+RHS);
		this->SetSelected(true);
		AppMan->SetSelectedStatement(this);
		error = true;
		return false;
	}
	return true;
}

string VarAssign::GetLHS ()const
{
	return LHS;
}
string VarAssign::GetRHS () const
{
	return RHS;
}


