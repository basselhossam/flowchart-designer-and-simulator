#include "Write_Stat.h"

Write_Stat::Write_Stat(ApplicationManager * AM, string txt, Point inlet, vector <string> var, int width, int height, int t_width, int t_height, int Factor)
:Statement(AM, txt, inlet, width, height, t_width, t_height), factor(Factor)
{
	slope = 1.732051;     //slope of the inclined sides of the //-gram
	V1 = var;              //vector to hold the identifiers
	calc_l_corner();
	pConn = NULL;
}


void Write_Stat::Draw(Output * pOut) const
{
	pOut->Draw_in_out(l_corner, width, height, t_height, Text, Selected, factor);
}


bool Write_Stat::check_range(Point p)
{
	if ((p.y >= l_corner.y) && (p.y <= l_corner.y + height) && (p.y >= -slope *p.x + (l_corner.y + slope*(l_corner.x + factor))) && (p.y <= -slope *p.x + (l_corner.y + slope*(l_corner.x + width))))
		return true;
	else
		return false;
}

void Write_Stat::calc_l_corner()
{
	l_corner.x = inlet.x - factor - ((width - factor) / 2);
	l_corner.y = inlet.y;
}


void Write_Stat::PrintInfo(Output * pOut)
{
	pOut->PrintMessage(comment);
}




void Write_Stat::Save(ofstream &OutFile)
{
	OutFile << "WRITE"<<"           "<< ID << "  " << l_corner.x << "  " << l_corner.y<<"  ";
	for (int i = 0; i < int(V1.size()); i++)
	{
		OutFile << V1[i] << "  ";
	}
	OutFile <<"\""<< comment <<"\""<<endl;
}



void Write_Stat::Load(ifstream & Infile)
{
	Infile >> ID >> l_corner.x >> l_corner.y;
	do
	{
		Infile >> comment;
		V1.push_back(comment);
	} while (comment[0] != '\"');

	getline(Infile, comment);
	
	comment = V1[V1.size() - 1] + comment;
	V1.pop_back();

	UpdateStatementText();
	set_stat_dim(Text);
	SetInlet();
	SetOutlet();

	comment.erase(comment.begin());
	comment.erase(comment.end() - 1);
}

void Write_Stat::set_stat_dim(string str)
{
	pIn->set_Read_Write_Dim(str, width, height, t_width, t_height, factor);
}

void Write_Stat::UpdateStatementText(/*string str*/)
{
	if ( V1.size() == 0)	//No left handside ==>statement have no valid text yet
		Text = "Write ";
	else
	{
		//Build the statement text: Left handside then equals then right handside
		ostringstream T;
		T << "Write " << V1[0];
		for (int i = 1; i < int(V1.size()); i++)
		{
			T << " , " << V1[i];
		};
		Text = T.str();
	}
}

void Write_Stat::GenerateCode(ofstream & OutFile)
{
	OutFile << "  cout";
	for (int i = 0; i <int(V1.size()); i++)
	{
		OutFile << " << " << V1[i];
	}
	OutFile << ";"<<endl;
	SetGenerated(true);
}

Connector* Write_Stat :: GetConnect(){
	return pConn;
}
void Write_Stat :: SetConnect(Connector*p){
	pConn = p;
}

bool Write_Stat::Simulate()
{
	
	for (int i = 0; i < int(V1.size()); i++)
	{
		stringstream ss;
		if(AppMan->variables.find(V1[i])== AppMan->variables.end())
		{
			pOut->ClearStatusBar();
			pOut->PrintMessage("ERROR: Undeclared Identifier"+V1[i]);
			this->SetSelected(true);
		    AppMan->SetSelectedStatement(this);
			return false;
		}
		else 
		{
			ss<<AppMan->variables[V1[i]]<<"  ";
			AppMan->TOutput += "  " + ss.str();
		}

	}
	pOut->PrintMessage(AppMan->TOutput);
	//cout<<"OutPut: \n"<<out;
	return true;
}

bool Write_Stat::Edit()
{
	vector <string> new_identifiers = V1;
	string new_txt;
	pOut->PrintMessage(Text + "     press ESC when you want to esc editing without saving");
	new_txt = pIn->GetIdentifiers(Text, pOut, new_identifiers);

	set_stat_dim(new_txt);
	

	if (pIn->candraw(l_corner, AppMan, height, width, ID))
	{
		if (new_txt != "")
		{
			V1 = new_identifiers;
			Text = new_txt;
			pIn->calc_Read_corner(inlet, l_corner, width, factor);

			SetInlet();
	        SetOutlet();
		}
		else
		{
			pOut->PrintMessage("the statement wasn't modified: the new statemnt will be empty!");
			set_stat_dim(Text);
			return false;
		}
	}

	else
	{
		Point p = l_corner;
		Move(p);

		if (p != l_corner)
		{
			pOut->PrintMessage("moved successfully");
			V1 = new_identifiers;
			Text = new_txt;
		}

		else
		{
			set_stat_dim(Text);
			pOut->PrintMessage("failed to modify the statement");
		}
	}
	return true;
}
vector <string>Write_Stat::Getvar()const{
	return V1;
}

void Write_Stat::setvar(const vector <string> &x){
	V1 = x;
	UpdateStatementText();
}


Write_Stat::~Write_Stat()
{}
