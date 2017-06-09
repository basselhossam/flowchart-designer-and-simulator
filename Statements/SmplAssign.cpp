#include "SmplAssign.h"
#include <sstream>

using namespace std;

SmplAssign::SmplAssign(ApplicationManager * AM, string txt, Point l_cor, int width, int height, int t_width, int t_height, string LeftHS, double RightHS)
: Statement(AM, txt, l_cor, width, height, t_width, t_height)
{
	LHS = LeftHS;
	RHS = RightHS;

	UpdateStatementText();

	
	pConn = NULL;	//No connectors yet
	
	calc_l_corner();
}

void SmplAssign::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void SmplAssign::setRHS(double R)
{
	RHS = R;
	UpdateStatementText();
}

void SmplAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(l_corner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);	
}


//This function should be called when LHS or RHS changes
void SmplAssign::UpdateStatementText()
{
	if(LHS=="")	//No left handside ==>statement have no valid text yet
		Text = "    = ";
	else
	{
		//Build the statement text: Left handside then equals then right handside
		ostringstream T;
		T<<LHS<<" = "<<RHS;	
		Text = T.str();	 
	}
}

bool SmplAssign::Edit(){

	string lhs;
	double rhs;

	pOut->PrintMessage("enter the left hand side");
	lhs = pIn->GetIdentifier(pOut);

	if (lhs == ""){
		pOut->PrintMessage("Cancel !!");
		return false;
	}

	pOut->PrintMessage("enter the right hand side");
	rhs = pIn->GetValue(pOut);

	if (rhs == inv){
		pOut->PrintMessage("Cancel !!");
		return false;
	}

	RHS = rhs;
	LHS = lhs;

	UpdateStatementText();
	pIn->set_Assign_Dim(Text, width, height, t_width, t_height);

	calc_l_corner();
	SetInlet();
	SetOutlet();

	return true;
}

void SmplAssign::GenerateCode(ofstream &OutFile){

	//we need to make a varible list to know if it's the first time being intialized or not
	//if the varible is exist in the varible list
	OutFile <<"  "<< LHS << " = " << RHS << ";\n";
	SetGenerated(true);
}

bool SmplAssign::check_range(Point p)
{
	if (p.x >= l_corner.x && p.x <= l_corner.x + width && p.y >= l_corner.y && p.y <= l_corner.y + height)
		return true;
	else
		return false;
}

void SmplAssign::Save(ofstream &OutFile)
{
	OutFile << "SMPLASSIGN"<<"      "<< ID << "  " << l_corner.x << "  " << l_corner.y << "  " << LHS << "  " << RHS << "  ";

	OutFile << "\"" << comment << "\"" << endl;
}


void SmplAssign::Load(ifstream & Infile)
{
	Infile >> ID >> l_corner.x >> l_corner.y >> LHS >> RHS;
	UpdateStatementText();

	set_stat_dim(Text);
	SetInlet();
	SetOutlet();
	getline(Infile, comment);

	comment.erase(comment.begin());
	comment.erase(comment.end()-1);

}

void SmplAssign::calc_l_corner()
{
	AppMan->GetInput()->calc_stat_corner(inlet, l_corner, width);
}

void SmplAssign::PrintInfo(Output * pOut)
{
	pOut->PrintMessage(comment);
}

void SmplAssign::set_stat_dim(string str)
{
	pIn->set_Assign_Dim(Text, width, height, t_width, t_height);
}

Connector* SmplAssign ::GetConnect(){
	return pConn;
}
void SmplAssign :: SetConnect(Connector*p){
	pConn = p;
}

string SmplAssign::GetLHS() const
{
	return LHS;
}

double SmplAssign :: GetRHS() const
{
	return RHS;
}

bool SmplAssign::Simulate(){
	AppMan->variables[LHS] = RHS;
	return true;
}