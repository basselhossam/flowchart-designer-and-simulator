#include "Conditional.h"
#include "End.h"

#include <sstream>

Conditional::Conditional(ApplicationManager * AM, string txt, Point l_cor, int width, int height, int t_width, int t_height, string LeftHS, string op, string RightHS)
: Statement(AM, txt, l_cor, width, height, t_width, t_height)
{
    
	LHS = LeftHS;
	RHS = RightHS;
	OPR = op;

	UpdateStatementText();

	calc_l_corner();

	YConn = NULL;	//No connectors yet
	NConn = NULL;

	// HERE MISSING THE INITIALIZATION OF Inlet,Noutlet,YOutlet

	calc_nout();
	calc_yout();


}
	
void Conditional :: setLHS(const string &L){
	LHS = L;
	UpdateStatementText();
}

void Conditional :: setRHS(const string &R){
	RHS = R;
	UpdateStatementText();
}
string Conditional::GetLHS()const
{
	return LHS;
}
string Conditional::GetRHS()const
{
	return RHS;
}

void Conditional ::setOperator(const string &s){
	if( s=="==" ||s == "<" || s=="<="|| s==">" || s==">=" )
    	OPR = s;
}
string Conditional::GetOperator()const{
	return OPR;
}



void Conditional::setLoop(bool b)
{
	Is_Loop = b;
}
bool Conditional::getLoop()
{
	return Is_Loop;
}

void Conditional::UpdateStatementText()
{
	if(LHS=="")	//No left handside ==>statement have no valid text yet
		Text = "    = ";
	else
	{
		//Build the statement text: Left handside then equals then right handside
		ostringstream T;
		T<<LHS<<' '<<OPR<<' '<<RHS;	
		Text = T.str();	 
	}
}

void Conditional :: Draw(Output* pOut) const{
	pOut->Drawcondition(l_corner, width, height,t_width,t_height, Text, Selected);
	

}

bool Conditional :: check_range(Point p)
{
    double slope = 0.5773503;  
		if ((p.y >= -slope*p.x + l_corner.y + slope*(l_corner.x + width / 2)) && (p.y >= slope*p.x + l_corner.y - slope*(l_corner.x + width / 2)) && (p.y <= slope*p.x + l_corner.y + height - slope*(l_corner.x + width / 2)) && (p.y <= -slope*p.x + l_corner.y + height + slope*(l_corner.x + width / 2)))
		return true;
	else
		return false;

}

bool Conditional::Edit(){

	string lhs,opr,rhs;

	pOut->ClearStatusBar();
	pOut->PrintMessage("Enter the left hand side");
	lhs = pIn->GetIdentifier(pOut);

	if (lhs == ""){
		pOut->PrintMessage("Cancel !!");
		return false;
	}

	pOut->ClearStatusBar();
	pOut->PrintMessage("Enter the operator");
	opr = pIn->GetLogicalOperator(pOut);
	
	if (opr == ""){
		pOut->PrintMessage("Cancel !!");
		return false;
	}

	pOut->ClearStatusBar();
	pOut->PrintMessage("Enter the right hand side");
	rhs = pIn->GetString("", pOut);

	if (rhs == ""){
		pOut->PrintMessage("Cancel !!");
		return false;
	}

	LHS = lhs;
	OPR = opr;
	RHS = rhs;

	UpdateStatementText();
	pIn->set_cond_Dim(Text, width, height, t_width, t_height);

	calc_l_corner();
	calc_nout();
	calc_yout();
	SetInlet();
	return true;
}


void Conditional::calc_l_corner()
{
	AppMan->GetInput()->calc_stat_corner(inlet, l_corner, width);
}

void Conditional::Save(ofstream &OutFile)
{
	OutFile << "COND  " << ID << "  " << l_corner.x << "  " << l_corner.y << " "<< LHS <<" "<< OPR <<" "<< RHS<<" ";

	OutFile << "\"" << comment << "\"" << endl;
}


void Conditional::Load(ifstream & Infile)
{
	Infile >> ID >> l_corner.x >> l_corner.y >> LHS >> OPR >> RHS;

	UpdateStatementText();
	set_stat_dim(Text);
	SetInlet();
	calc_nout();
	calc_yout();

	getline(Infile, comment);
	comment.erase(comment.begin());
	comment.erase(comment.end()-1);
}

void Conditional::PrintInfo(Output * pOut)
{
	pOut->PrintMessage(comment);
}

void Conditional::set_stat_dim(string str)
{
	pIn->set_cond_Dim(Text, width, height, t_width, t_height);
}

void Conditional ::SetCond(bool b){
	cond = b;
}
bool Conditional :: GetCond(){
	return cond;
}

Connector* Conditional ::get_YConn(){
	return YConn;
}

Connector*Conditional::get_NConn(){
	return NConn;
}

void Conditional ::set_Yout(Connector*p){
	YConn = p;
}

void Conditional :: set_Nout(Connector*p){
	NConn = p;
}

Point Conditional::get_yout()
{
	return YOutlet;
}

Point Conditional::get_nout()
{
	return NOutlet;
}
void Conditional::calc_yout()
{
	YOutlet.y = l_corner.y + height / 2;
	YOutlet.x = l_corner.x + width;
}

void Conditional::calc_nout()
{
	NOutlet.y = l_corner.y + height / 2;
	NOutlet.x = l_corner.x;
}
bool Conditional::Simulate(){
	double x,y;
	bool error = false;

	if(AppMan->variables.find(LHS)== AppMan->variables.end())
	{
		pOut->ClearStatusBar();
		pOut->PrintMessage("ERROR: Undeclared Identifier "+LHS);

		this->SetSelected(true);
		AppMan->SetSelectedStatement(this);

		return false;
	}
	else
		x=AppMan->variables[LHS];

	if(!CheckValue(RHS) && !CheckIdentifier(RHS))
	{
			pOut->ClearStatusBar();
		    pOut->PrintMessage("ERROR in RHS Operand !");

    		this->SetSelected(true);
	    	AppMan->SetSelectedStatement(this);

		    return false;
	}	
	
	if (CheckValue(RHS))
	{
		stringstream s;
		s<<RHS;
		s>>y;
		s.str("");
		s.clear();
	}
	else if(CheckIdentifier(RHS))
	{
		if(AppMan->variables.find(RHS)!=AppMan->variables.end())
		   y = AppMan->variables[RHS];
		else
		{
			pOut->ClearStatusBar();
		    pOut->PrintMessage("ERROR in RHS Operand !");

    		this->SetSelected(true);
	    	AppMan->SetSelectedStatement(this);

		    return false;
		}

	}



	if(OPR == "<")
	{
		if(x<y)
			SetCond(true);
		else
			SetCond(false);
	}
	else if(OPR == "<=")
	{
		if(x<=y)
			SetCond(true);
		else
			SetCond(false);
	}
	else if(OPR == ">")
	{
		if(x>y)
			SetCond(true);
		else
			SetCond(false);
	}
	else if(OPR == ">=")
	{
		if(x>=y)
			SetCond(true);
		else
			SetCond(false);
	}
	else if(OPR == "=" || OPR == "==")
	{
		if(x==y)
			SetCond(true);
		else
			SetCond(false);
	}
	else if(OPR == "!=")
	{
		if(x!=y)
			SetCond(true);
		else
			SetCond(false);
	}

	return true;
}

void Conditional::GenerateCode(ofstream &OutFile){

	//we need to make a varible list to know if it's the first time being intialized or not
	//if the varible is exist in the varible list

	Connector*p;
	p = get_YConn();
	setLoop(false);
	bool flag=false;
	while (p != NULL)
	{
		//if (p->getDstStat()->get_ID() == ID && p->getSrcStat()->Is_Generated() == false)
		if ((p->getSrcStat()->Is_Generated() == false && p->getDstStat()->Is_Generated()) 	|| p->getDstStat()->get_ID()==ID)
		{
			setLoop(true);
			break;
		}
		if (dynamic_cast<Conditional*>(p->getDstStat()))
		{
			Conditional*pcond = (Conditional*)p->getDstStat();
			if (pcond->GetCond())
				p = pcond->get_YConn();
			else
				p = pcond->get_NConn();
		}
		else
			p = p->getDstStat()->GetConnect();
	}

	if (getLoop())
		OutFile << "  while(" << Text << ")"<<endl<<"  {"<<endl;
	else
 	OutFile <<"  if (" << Text << ")"<<endl<<"  {"<<endl;
	SetGenerated(true);
}