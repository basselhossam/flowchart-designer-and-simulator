#include "Statement.h"
#include "Conditional.h"

int Statement::ID_creator = 0;

Statement::Statement(ApplicationManager * AM, string txt, Point Inlet, int width, int height, int t_width, int t_height)
:AppMan(AM), Text(txt), inlet(Inlet), width(width), height(height), t_width(t_width), t_height(t_height)
{
	comment = "";
	pIn = AM->GetInput();
	pOut = AM->GetOutput();
	ID = ++ID_creator;
	Selected = false;
	IsCut = false;
	IsConnected = false;
	generated=false;
	outlet.x = inlet.x;
	outlet.y = inlet.y + height;
}

void Statement::SetSelected(bool s)
{
	Selected = s;
}

void Statement::SetCut(bool s){
	IsCut = s;
}

bool Statement::GetCut() const{
	return IsCut;
}

void Statement::Edit_comment(string txt)
{
	comment = txt;
}

bool Statement::IsSelected() const
{
	return Selected;
}


Point & Statement:: get_lcorner()
{
	return l_corner;
}

int Statement::get_width()
{
	return width;
}

int Statement::get_height()
{
	return height;
}

string Statement::get_text(){
	return Text;
}

void Statement::get_data(string &txt, int &width, int &height, int &t_width, int &t_height){
	txt = Text;
	width = this->width;
	height = this->height;
	t_width = this->t_width;
	t_height = this->t_height;
}

int Statement::get_ID()const
{
	return ID;
}

void Statement::Move(Point P){
	
	int count = 0;
	while (!pIn->candraw(P, AppMan, width, height, ID) && count != 10)
	{
		if (count == 10)
			break;
		pOut->PrintMessage("please choose another position to Draw , probable intersection may occur in this position");
		pIn->GetPointClicked(P);
		count++;
	}
	if (count == 10)
	{
		pOut->PrintMessage("the statement wasn't moved due to failure of multiple stupid user moves");
		return;
	}
	pOut->PrintMessage("Statement moved successfully");
	l_corner = P;
}

Point Statement::GetInlet(){
	return inlet;
}

Point Statement::GetOutlet(){
	return outlet;
}

void Statement :: SetInlet(){
	inlet.x = l_corner.x + width/2;
	inlet.y = l_corner.y;
}

void Statement :: SetConnected(bool b){
	IsConnected = b;

}
bool Statement ::GetConnected(){
	return IsConnected;
}

string Statement::GetComment(){
	return comment;
}

void Statement::Drag()
{
	AppMan->GetOutput()->getwindow()->FlushKeyQueue();
	int iXOld = 0, iYOld = 0;
	Point old_corner = l_corner;
	Point p;     //current point
	bool Drag = false;
	char c;
	Connector ** clist = AppMan->get_conn_list();
	while (pIn->getwindow()->GetKeyPress(c) != ESCAPE)
	{
		pOut->PrintMessage("press \"ESC\" to cancel moving action");
		if (Drag == false)
		{
			if (pIn->getwindow()->GetButtonState(LEFT_BUTTON, p.x, p.y) == BUTTON_DOWN)
			{
				//if (((iX > RectULX) && (iX < (RectULX + RectWidth))) && ((iY > RectULY) && (iY < (RectULY + RectWidth))))
				if (check_range(p))
				{
					Drag = true;
					iXOld = p.x;     iYOld = p.y;
					SetInlet();
					if (dynamic_cast<Conditional *>(this) == false)
					{
						SetOutlet();
					}
					else
					{
						dynamic_cast<Conditional *>(this)->calc_nout();
						dynamic_cast<Conditional *>(this)->calc_yout();
					}
					for (int i = 0; i < AppMan->get_ConnCount(); i++)
					{
						clist[i]->get_path().clear();
						clist[i]->make_connector(clist[i]->getSrcStat(), clist[i]->getDstStat(), AppMan);
					}
					AppMan->UpdateInterface();
				}
			}
		}
		else {
			if (pIn->getwindow()->GetButtonState(LEFT_BUTTON, p.x, p.y) == BUTTON_UP)
			{
				Drag = false;
			}
			else
			{
				if (p.x != iXOld)
				{
					l_corner.x = l_corner.x + (p.x - iXOld);
					iXOld = p.x;
				}
				if (p.y != iYOld)
				{
					l_corner.y = l_corner.y + (p.y - iYOld);
					iYOld = p.y;
				}
				SetInlet();
				if (dynamic_cast<Conditional *>(this) == false)
				{
					SetOutlet();
				}
				else
				{
					dynamic_cast<Conditional *>(this)->calc_nout();
					dynamic_cast<Conditional *>(this)->calc_yout();
				}
				for (int i = 0; i < AppMan->get_ConnCount(); i++)
				{
					clist[i]->get_path().clear();
					clist[i]->make_connector(clist[i]->getSrcStat(), clist[i]->getDstStat(), AppMan);
				}
				AppMan->UpdateInterface();
			}
		}
	}
	if (pIn->candraw(l_corner, AppMan, height, width, ID))
	{
		pOut->PrintMessage("Moved successfully");
	}
	else
	{
		l_corner = old_corner;
		SetInlet();
		if (dynamic_cast<Conditional *>(this) == false)
		{
			SetOutlet();
		}
		else
		{
			dynamic_cast<Conditional *>(this)->calc_nout();
			dynamic_cast<Conditional *>(this)->calc_yout();
		}
		for (int i = 0; i < AppMan->get_ConnCount(); i++)
		{
			clist[i]->get_path().clear();
			clist[i]->make_connector(clist[i]->getSrcStat(), clist[i]->getDstStat(), AppMan);
		}
		AppMan->UpdateInterface();
		pOut->PrintMessage("intersection may happen in this position, this isn't allowed");
	}
	Selected = false;
	AppMan->SetSelectedStatement(NULL);
}

void Statement::SetOutlet()
{
	outlet.y = l_corner.y + height;
	outlet.x = l_corner.x + width / 2;
}


bool Statement :: CheckIdentifier(string s)
{
	if(isdigit(s[0]))
		return false;
	for(int i=1; i<s.size(); i++)
		if(!isalnum(s[i]) && s[i]!='_')
			return false;
	return true;
}
bool Statement :: CheckValue(string s)
{
	if(!isdigit(s[0]) && s[0]!='-')
		return false;

	for(int i=1; i<s.size(); i++)
		if(!isdigit(s[i]))
			return false;
	return true;
}

int Statement::get_t_width()
{
	return t_width;
}
int Statement::get_t_height()
{
	return t_width;
}

void Statement::SetGenerated(bool b)
{
	generated = b;
}
bool Statement::Is_Generated()
{
	return generated;
}

Statement::~Statement()
{
	/*delete pIn;
	delete pOut;*/
}