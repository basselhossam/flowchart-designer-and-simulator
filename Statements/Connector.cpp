#include"Connector.h"
#include"..\GUI\Output.h"
#include"..\ApplicationManager.h"

#include"Statement.h"
#include"Conditional.h"
#include"Start.h"
#include"End.h"

Connector::Connector(Statement* Src, Statement* Dst, ApplicationManager * AM, bool yes)	
//When a connector is created, it must have a source statement and a destination statement
//There are no free connectors in the folwchart
:pManager(AM), yes(yes)
{	
	SrcStat = Src;
	DstStat = Dst;

	Selected = false;
	
	make_connector(Src, Dst, AM);
}

Connector::Connector(ApplicationManager*AM) :pManager(AM)
{
}

void Connector::make_connector(Statement* Src, Statement* Dst, ApplicationManager * AM)
{
	End = Dst->GetInlet();
	End.y -= 20;
	if (dynamic_cast<Conditional *>(Src))
	{
		if (yes == true)
		{
			Start = dynamic_cast<Conditional *>(Src)->get_yout();
			path.push_back(Start);
			Point p(Start.x + 10, Start.y);
			path.push_back(p);
			find_path(pManager->get_statement_list(), path, E, S, N);
			dynamic_cast<Conditional *>(Src)->set_Yout(this);
		}
		else
		{
			Start = dynamic_cast<Conditional *>(Src)->get_nout();
			path.push_back(Start);
			Point p(Start.x - 10, Start.y);
			path.push_back(p);
			find_path(pManager->get_statement_list(), path, W, S, N);
			dynamic_cast<Conditional *>(Src)->set_Nout(this);
		}
	}
	else
	{
		Start = Src->GetOutlet();
		path.push_back(Start);
		Point p(Start.x, Start.y + 10);
		path.push_back(p);
		find_path(pManager->get_statement_list(), path, W, E, S);
		Src->SetConnect(this);
	}
}

void Connector::Edit()
{
	bool yes=false;
	Output *pOut=pManager->GetOutput();
	Input * pIn = pManager->GetInput();
	Point p;
	Statement * old_source=SrcStat;
	Statement * old_destination = DstStat;
	pOut->PrintMessage("Click on the source statement, or click in the drawing area to cancel editing");
	do
	{
		pIn->getwindow()->WaitMouseClick(p.x, p.y);
		SrcStat = pManager->GetStatement(p);
		
		if (SrcStat == NULL)
		{
			pOut->PrintMessage("Editing was cancelled, try again");
			SrcStat = old_source;
			DstStat = old_destination;
			Selected = false;
			return;
		}
		else if (dynamic_cast<class End *>(SrcStat))
		{
			pOut->PrintMessage("you can't make the End statement a source statement, choose another one");
			SrcStat = NULL;
		}
		else if (SrcStat->GetConnect() != old_source->GetConnect() && SrcStat->GetConnect() != NULL)
		{
			pOut->PrintMessage("Ohhhh! ,hey friend you are making a fatal mistake, the statement you are choosig has a connector");
			SrcStat = NULL;
		}
		if (dynamic_cast<Conditional *>(SrcStat))
		{
			if (p.x >= SrcStat->get_lcorner().x + SrcStat->get_width() / 2)
			{
				if (dynamic_cast<Conditional *>(SrcStat)->get_YConn() != dynamic_cast<Conditional *>(old_source)->get_YConn() && dynamic_cast<Conditional *>(SrcStat)->get_YConn() != NULL)
				{
					pOut->PrintMessage("there is no room for another YES conector");
					SrcStat = NULL;
				}
				else
					yes = true;
			}
			else
			{
				if (dynamic_cast<Conditional *>(SrcStat)->get_NConn() != dynamic_cast<Conditional *>(old_source)->get_NConn() && dynamic_cast<Conditional *>(SrcStat)->get_NConn() != NULL)
				{
					pOut->PrintMessage("there is no room for another NO conector");
					SrcStat = NULL;
				}
				yes = false;
			}
		}
	} while (SrcStat == NULL);


	//setting the destination statement
	pOut->PrintMessage("Click on the destination Statement, or click in the drawing area to cancel editing");	
do
	{
		pIn->getwindow()->WaitMouseClick(p.x, p.y);
		DstStat = pManager->GetStatement(p);
		if (DstStat == NULL)
		{
			pOut->PrintMessage("Editing was cancelled, try again");
			DstStat = old_source;
			SrcStat = old_destination;
			Selected = false;
			return;
		}
		else if (DstStat == SrcStat)
		{
			DstStat = NULL;
			pOut->PrintMessage("you can't do such stupid case, choose another statement , or click in the drawing area to cancel editing");
		}
		else if (dynamic_cast<class Start *>(DstStat))
		{
			pOut->PrintMessage("you can't make the Start statement a destination statement");
			DstStat = NULL;
		}

	} while (DstStat == NULL);
	if (SrcStat != NULL && DstStat != NULL)
	{
		path.clear();
		make_connector(SrcStat, DstStat, pManager);
		Selected = false;
	}
	pOut->PrintMessage("Editing completed");
}

bool Connector::get_selected()
{
	return Selected;
}

bool Connector:: check_int(Statement ** St_list, Point start, Point end)
{
	for (int i = 0; i < pManager->get_stat_count(); i++)
		if (end.y >= St_list[i]->get_lcorner().y && end.y < St_list[i]->get_lcorner().y + St_list[i]->get_height() && end.x >= St_list[i]->get_lcorner().x && end.x <= St_list[i]->get_lcorner().x + St_list[i]->get_width())
			return true;
		else if (end.y >= UI.height - UI.StBrWdth || end.y <= UI.TlBrWdth || end.x >= UI.width || end.x <= 0)
			return true;
	return false;
}


void Connector:: Print_info(Output * pOut) const
{
	pOut->PrintMessage("A connector from the statement " + SrcStat->get_text()+" to the statement " +DstStat->get_text());
}

void Connector::set_selected(bool s)
{
	Selected = s;
}

vector <Point> & Connector:: get_path()
{
	return path;
}

bool Connector::check_for_direct_path(Point start, Point end, Point & mid)
{
	Statement ** list = pManager->get_statement_list();
	int i1, i2;
	//case 1
	mid.x = start.x;   mid.y = end.y;
	i1 = check_barriers(list, start, mid);
	i2 = check_barriers(list,mid,end);
	if (i1 == 0 && i2 == 0)
		return true;
	else
	{
		mid.x = end.x;   mid.y = start.y;
		i1 = check_barriers(list, start, mid);
		i2 = check_barriers(list, mid, end);
		if (i1 == 0 && i2 == 0)
			return true;
		else 
			return false;
	}
}


//bool Connector::check_for_direct_path(Point start, Point end, Point & mid)
//{
//	Point p1, p2;      int Case;   bool b = true, a = true, c=true, d=true;
//	Statement ** St_list = pManager->get_statement_list();
//	if (start.x < end.x && end.y > start.y)
//	{
//		p1 = start;  p2 = end;  Case = 1;
//	}
//	else if (start.x > end.x&&end.y < start.y)
//	{
//		p1 = end;   p2 = start;   Case = 1;
//	}
//	else if (start.x>end.x&&start.y < end.y)
//	{
//		p1 = start;  p2 = end;  Case = 2;
//	}
//	else if (start.x<end.x && start.y>end.y)
//	{
//		p1 = end;   p2 = start;  Case = 2;
//	}
//
//		for (int i = 0; i < pManager->get_stat_count(); i++)
//		{
//			if (St_list[i]->get_lcorner().y >= p1.y - St_list[i]->get_height() && St_list[i]->get_lcorner().y <= p2.y)
//			{
//				if (St_list[i]->get_lcorner().x <= p1.x &&  St_list[i]->get_lcorner().x + St_list[i]->get_width() >= p1.x)
//					b = false;
//				if (St_list[i]->get_lcorner().x <= p2.x&& St_list[i]->get_lcorner().x + St_list[i]->get_width()>p2.x)
//					d = false;
//			}
//			if (St_list[i]->get_lcorner().x >= p1.x - St_list[i]->get_width() && St_list[i]->get_lcorner().x < p2.x)
//			{
//				if (St_list[i]->get_lcorner().y <= p1.y && St_list[i]->get_lcorner().y + St_list[i]->get_height() >= p1.y)
//					a = false;
//			    if (St_list[i]->get_lcorner().y <= p2.y && St_list[i]->get_lcorner().y + St_list[i]->get_height() >= p2.y)
//					c = false;
//			}
//		}
//
//		if (Case == 1)
//		{
//			if (b == true && c == true)
//			{
//				mid.x = p1.x;   mid.y = p2.y;   return 1;
//			}
//			else if (a == true && d == true)
//			{
//				mid.x = p2.x;   mid.y = p1.y;  return 1;
//			}
//			
//		}
//		else
//		{
//			if (a == true && b == true)
//			{
//				mid.x = p2.x;   mid.y = p1.y;  return 1;
//			}
//			else if (d == true && c == true)
//			{
//				mid.x = p1.x;   mid.y = p2.y;   return 1;
//			}
//		}
//		return 0;
//}


int Connector::get_last_direc(vector<Point>path)
{
	if (path[path.size() - 2].x == path[path.size() - 1].x && path[path.size() - 1].y > path[path.size() - 2].y)         //  downwards
		return 3;
	else if (path[path.size() - 2].x == path[path.size() - 1].x && path[path.size() - 1].y < path[path.size() - 2].y)     //upwards
		return 1;
	else if (path[path.size() - 2].y == path[path.size() - 1].y && path[path.size() - 2].x < path[path.size() - 1].x)       //right
		return 2;
	else
		return 4;                                                                                                           //left
}

int Connector::check_barriers(Statement ** List, Point p1, Point p2)
{
	Point start, end;
	if (p1.x == p2.x)  //vertical line
	{
		if (p1.y > p2.y)
		{
			start = p2;
			end = p1;                  //start is always the upper point
		}
		else
		{
			start = p1;
			end = p2;                 //the same
		}
		for (int i = 0; i<pManager->get_stat_count(); i++)
		{
			if (List[i]->get_lcorner().x <= end.x && List[i]->get_lcorner().x + List[i]->get_width()>=end.x)
			if (List[i]->get_lcorner().y >= start.y - List[i]->get_height() && List[i]->get_lcorner().y <= end.y)
				return 1;
		}
		if (start.y <= UI.TlBrWdth || end.y >= UI.height - UI.StBrWdth)
			return -1;
		else
			return 0;
	}
	else
	{
		if (p1.x > p2.x)
		{
			start = p1;  end = p2;
		}
		else
		{
			start = p2;  end = p1;
		}
		for (int i = 0; i < pManager->get_stat_count(); i++)
		{
			if (List[i]->get_lcorner().y<=end.y && List[i]->get_lcorner().y + List[i]->get_height()>=end.y)
			if (List[i]->get_lcorner().x >= end.x - List[i]->get_width() && List[i]->get_lcorner().x <= start.x)
				return 1;
		}
		if (end.x <= 0 || start.x >= UI.width)
			return -1;
		else
			return 0;
	}
}

void Connector:: modify()
{
	Connector ** list = pManager->get_conn_list();
	vector<Point> PATH;
	for (int i = 0; i < pManager->get_ConnCount(); i++)
	{
		if (list[i] != this)
		{
			PATH = list[i]->get_path();
			for (int g = 1; g < path.size()-1; g++)
			for (int j = 1; j < list[i]->get_path().size(); j++)
			{
				if (path[g].x == path[g - 1].x  && PATH[j].x==PATH[j-1].x)//vertical
				{
					if ((path[g].y>PATH[j].y && path[g - 1].y < PATH[j].y || path[g].y<PATH[j].y && path[g - 1].y>PATH[j].y)
						|| (path[g].y>PATH[j - 1].y && path[g - 1].y < PATH[j - 1].y || path[g].y<PATH[j - 1].y && path[g - 1].y>PATH[j - 1].y)
						|| (abs(path[g].y - PATH[j].y)<4 || abs(path[g - 1].y - PATH[j].y)<4 || abs(path[g - 1].y - PATH[j - 1].y)<4 || abs(path[g].y - PATH[j-1].y)<4))
					{
						path[g].x += 10;  path[g - 1].x += 10;
					}
				}
				else if(path[g].y == path[g - 1].y  && PATH[j].y == PATH[j - 1].y)//horizontal
				{
					if ((path[g].x>PATH[j].x && path[g - 1].x < PATH[j].x || path[g].x<PATH[j].x && path[g - 1].x>PATH[j].x)
						|| (path[g].x>PATH[j - 1].x && path[g - 1].x < PATH[j - 1].x || path[g].x<PATH[j - 1].x && path[g - 1].x>PATH[j - 1].x)
						|| (abs(path[g].x - PATH[j].x) < 4 || abs(path[g - 1].x - PATH[j].x) < 4 || abs(path[g - 1].x - PATH[j - 1].x) < 4 || abs(path[g].x - PATH[j - 1].x) < 4))
					{
						path[g].y += 10; path[g - 1].y += 10;
					}
				}
			}
		}
	}
}

void Connector::find_path(Statement ** St_list, vector<Point> & v1, direc a, direc b, direc c)
{
	vector<Point> va=v1, vb=v1, vc=v1;
	bool p1, p2, p3;
	p1 = set_path(St_list, va, a);
	p2 = set_path(St_list, vb, b);
	p3 = set_path(St_list, vc, c);

	if (p1 == true && p2 == false && p3 == false)
		v1 = va;
	else if (p1 == false && p2 == true && p3 == false)
		v1 = vb;
	else if (p1 == false && p2 == false && p3 == true)
		v1 = vc;
	else if (p1 == true && p2 == true && p3 == false)
	{
		if (dist(va)<=dist(vb))
			v1 = va;
		else
			v1 = vb;
	}
	else if (p1 == false && p2 == true && p3 == true)
	{
		if (dist(vb) <= dist(vc))
			v1 = vb;
		else
			v1 = vc;
	}
	else if (p1 == true && p2 == false && p3 == true)
	{
		if (dist(va) <= dist(vc))
			v1 = va;
		else
			v1 = vc;
	}
	else
	{
		if (p1 == false)  va.clear();
		if (p2 == false)  vb.clear();
		if (p3 == false)  vc.clear();
		int va_dist = dist(va);
		int vb_dist = dist(vb);
		int vc_dist = dist(vc);
		int s = min(va_dist,min(vb_dist,vc_dist));
		if (s == va_dist)   v1 = va;
		else if (s == vb_dist)  v1 = vb;
		else  v1 = vc;
	}
}

bool Connector:: set_path(Statement ** St_list, vector<Point> & v1, direc d)
{
	if (v1.size() == 10)
		return false;

	Point mid;       
	if (check_for_direct_path(v1[v1.size() - 1], End, mid))
	{
		v1.push_back(mid);
		v1.push_back(End);
		return 1;
	}

	int k = 0;     //for checking the val. of check barriers
	vector<Point> v2,v3;
	bool way1, way2;
	v1.push_back(v1[v1.size() - 1]);
	
	if (d == E)   //towards east
	{
		while (1)
		{
			v1[v1.size() - 1].x+=20;
			k=check_barriers(St_list, v1[v1.size() - 1], v1[v1.size() - 2]);
			if (k == -1)
				return false;
			else if (k == 0)
			{
				if (check_for_direct_path(v1[v1.size() - 1], End, mid))
				{
					v1.push_back(mid);
					v1.push_back(End);
					return 1;
				}
			}
			else
				break;
		}
		v1[v1.size() - 1].x -= 20;
		v2 = v1;   v3 = v1;
		way1 = set_path(St_list, v2, N);
		way2 = set_path(St_list, v3, S);
	}
	else if (d == W)   //towards east
	{
		while (1)
		{
			v1[v1.size() - 1].x -= 20;
			k = check_barriers(St_list, v1[v1.size() - 1], v1[v1.size() - 2]);
			if (k == -1)
				return false;
			else if (k == 0)
			{
				if (check_for_direct_path(v1[v1.size() - 1], End, mid))
				{
					v1.push_back(mid);
					v1.push_back(End);
					return 1;
				}
			}
			else
				break;
		}
		v1[v1.size() - 1].x += 20;
		v2 = v1;   v3 = v1;
		way1 = set_path(St_list, v2, N);
		way2 = set_path(St_list, v3, S);
	}

	else if (d == N)   //towards north
	{
		while (1)
		{
			v1[v1.size() - 1].y -= 20;
			k = check_barriers(St_list, v1[v1.size() - 1], v1[v1.size() - 2]);
			if (k == -1)
				return false;
			else if (k == 0)
			{
				if (check_for_direct_path(v1[v1.size() - 1], End, mid))
				{
					v1.push_back(mid);
					v1.push_back(End);
					return 1;
				}
			}
			else
				break;
		}
		v1[v1.size() - 1].y += 20;
		v2 = v1;   v3 = v1;
		way1 = set_path(St_list, v2, E);
		way2 = set_path(St_list, v3, W);
	}
	else if (d == S)   //towards south
	{
		while (1)
		{
			v1[v1.size() - 1].y += 20;
			k = check_barriers(St_list, v1[v1.size() - 1], v1[v1.size() - 2]);
			if (k == -1)
				return false;
			else if (k == 0)
			{
				if (check_for_direct_path(v1[v1.size() - 1], End, mid))
				{
					v1.push_back(mid);
					v1.push_back(End);
					return 1;
				}
			}
			else
				break;
		}
		v1[v1.size() - 1].y -= 20;
		v2 = v1;   v3 = v1;
		way1 = set_path(St_list, v2, E);
		way2 = set_path(St_list, v3, W);
	}

	if (way1 == false && way2 == false)
		return false;
	else if (way1 == true && way2 == false)
	{
		v1 = v2;
		return true;
	}
	else if (way1 == false && way2 == true)
	{
		v1 = v3;
		return true;
	}
	else
	{
		if (dist(v3)<=dist(v2))
		{
			v1 = v3;
		}
		else
			v1 = v2;
		return true;
	}
}

int Connector:: dist(vector<Point> v)
{
	int sum = 0, m;
	for (int i = 1; i < int(v.size()); i++)
	{
		if (v[i].x == v[i - 1].x)
		{
			m = v[i].y - v[i - 1].y;
			sum += m < 0 ? -m : m;
		}
		else
		{
			m = v[i].x - v[i - 1].x;
			sum += m < 0 ? -m : m;
		}
	}
	return sum;
}

/*
int Connector:: check_for_direct_path(Point start, Point end)
{
	int c1=0, c2=0;  //counters for the numbers of the intersections
	Statement ** ptr = pManager->get_statement_list();
	if (end.x> start.x && end.y>start.y)
	for (int i = 0; i < pManager->get_stat_count(); i++)
	{
		if (ptr[i]->get_lcorner().y >= start.y - ptr[i]->get_height() && ptr[i]->get_lcorner().y <= end.y)
		{
			if (start.x >= ptr[i]->get_lcorner().x && start.x <= ptr[i]->get_lcorner().x + ptr[i]->get_width())
				c1++;
			else if (end.x >= ptr[i]->get_lcorner().x && end.x <= ptr[i]->get_lcorner().x + ptr[i]->get_width())
				c2++;
		}
		if (ptr[i]->get_lcorner().x >= start.x - ptr[i]->get_width() && ptr[i]->get_lcorner().x <= end.x)
		{
			if (start.y >= ptr[i]->get_lcorner().y && start.y <= ptr[i]->get_lcorner().y + ptr[i]->get_height())
				c2++;
			else if (end.y >= ptr[i]->get_lcorner().y && end.y <= ptr[i]->get_lcorner().y + ptr[i]->get_height())
				c1++;
		}
	}

	else if (end.y<start.y && end.x>start.x)
	for (int i = 0; i < pManager->get_stat_count(); i++)
	{
		if ()
	}
}
*/
void Connector::setSrcStat(Statement *Src)
{	SrcStat = Src;	}

Statement* Connector::getSrcStat()
{	return SrcStat;	}

void Connector::setDstStat(Statement *Dst)
{	DstStat = Dst;	}

Statement* Connector::getDstStat()
{	return DstStat;	}


void Connector::setStartPoint(Point P)
{	Start = P;	}

Point Connector::getStartPoint()
{	return Start;	}

void Connector::setEndPoint(Point P)
{	End = P;	}

Point Connector::getEndPoint()
{	return End;	}

void Connector::Draw(Output* pOut) const
{
	pOut->Draw_connector(path,Selected);
	///TODO: Call output to draw a connector from SrcStat to DstStat on the output window
}

void Connector::Save(ofstream &OutFile){

	OutFile << SrcStat->get_ID() << "  " << DstStat->get_ID() << "  ";
	Conditional*ptr = dynamic_cast<Conditional*>(SrcStat);
	if (ptr)
	{
		if (ptr->get_YConn() == this)
			OutFile << 1 << "  ";
		else if (ptr->get_NConn() == this)
			OutFile << 2 << "  ";
	}
	else
		OutFile << 0 << "  ";
	OutFile << endl;

}
void Connector::Load(ifstream &Infile)
{
	int x, y, z;
	Infile >> x;
	for (int i = 0; i<pManager->get_stat_count(); i++)
	{
		if (pManager->get_statement_list()[i]->get_ID() == x)
		{
			SrcStat = pManager->get_statement_list()[i];
			pManager->get_statement_list()[i]->SetConnect(this);
			break;
		}
	}
	Infile >> y;
	for (int i = 0; i<pManager->get_stat_count(); i++)
	{
		if (pManager->get_statement_list()[i]->get_ID() == y)
		{
			DstStat = pManager->get_statement_list()[i];
			DstStat->SetConnected(true);
			break;
		}
	}
	End = DstStat->GetInlet();
	End.y -= 20;

	Selected = false;
	Infile >> z;

	Conditional*ptr = dynamic_cast<Conditional*> (SrcStat);
	if (z != 0 && ptr)
	{
		if (z == 1)
			yes = true;
		else
			yes = false;
	}

	make_connector(SrcStat, DstStat, pManager);
}


