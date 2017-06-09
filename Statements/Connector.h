#pragma once
#include<cmath>
#include<vector>
#include"..\GUI\UI_Info.h"
#include"..\ApplicationManager.h"

class ApplicationManager;
class Statement;
class Output;

class Connector	//a connector that connects two statements (Source & Destination)
{
private:
	Statement *SrcStat;	//The source statement of the connector
	Statement *DstStat;	//The destination statement of the connector
	Point Start;	//Start point of the connector
	Point End;		//End point of the connector
	vector<Point> path;   
	ApplicationManager * pManager;
	bool Selected;
	bool yes;    //used by a conditional source statement only
public:
	int get_last_direc(vector<Point> path);
	Connector(Statement* Src, Statement* Dst, ApplicationManager * AM, bool yes=0);

	Connector(ApplicationManager * AM);

	void		setSrcStat(Statement *Src);
	Statement*	getSrcStat();	
	void		setDstStat(Statement *Dst);
	Statement*	getDstStat();

	void setStartPoint(Point P);
	Point getStartPoint();

	int check_barriers(Statement ** List, Point p1, Point p2);

	int dist(vector<Point> p);

	void setEndPoint(Point P);
	Point getEndPoint();

	void Draw(Output* pOut) const;
	bool check_int( Statement ** St_list, Point start, Point end);
	bool check_for_direct_path(Point start, Point end, Point & mid);

	void find_path(Statement ** St_list, vector<Point> & v1, direc a, direc b, direc c);
	bool set_path(Statement ** St_list, vector<Point> & v1, direc d);
	void set_selected(bool s);
	bool get_selected();
	vector <Point> & get_path();
	void Print_info(Output *) const;
	void make_connector(Statement* Src, Statement* Dst, ApplicationManager * AM);
	void Edit();

	void Save(ofstream &OutFile);
	void Load(ifstream &Infile);

	void modify();
	//void Edit();

	//bool set_path(Statement ** St_list, vector<Point> & v1, Point dst);
};
