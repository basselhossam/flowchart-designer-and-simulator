#ifndef INPUT_H
#define INPUT_H

#include "..\DEFS.h"
#include "UI_Info.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include"..\ApplicationManager.h"
class Output;
class ApplicationManager;
class Input		//The application manager should have a pointer to this class
{
private:
	window *pWind;	//Pointer to the Graphics Window
	Point p;                                                                            //*****
public:
	Input(window *pW);		//Consturctor
	bool GetPointClicked(Point &P) const;//Gets coordinate where user clicks
	
	Point GetPoint(int x1, int y1) const;   //******
	//void SetPoint(int x1, int y1);

	window * getwindow()const;

	double GetValue(Output* pO) const;	               // Reads a double value from the user 

	string GetString(string txt,Output* pO) const;               //Returns a string entered by the user

	ActionType GetUserAction() const;                  //Read the user click and map it to an action

	string GetIdentifier(Output* pO)  const;   //for reading an identifier from the user
	
	string GetIdentifiers(string txt, Output * pO, vector <string> & v1);   //added by amr  //getting comma separated identifiers

	bool candraw(Point p, ApplicationManager * AppMan, int height, int width, int id=-1);

	void set_ellipse_Dim(string Text, int & width, int & height, int & t_width, int & t_height);

	void set_Read_Write_Dim(string Text, int & width, int & height, int & t_width, int & t_height, int & factor);

	void set_cond_Dim(string Text, int & width, int & height, int & t_width, int & t_height);

	void set_Assign_Dim(string Text, int & width, int & height, int & t_width, int & t_height);

	bool check_intersection(ApplicationManager * AppMan, Point p, int width, int height, int id);

	bool intersect_with_connector(int height, int width, Point l_corner, ApplicationManager * AM);
	
	void calc_Read_corner(Point in, Point & lcorner, int width, int factor);

	void calc_stat_corner(Point in, Point & lcorner, int width);
	////////////////////////////////////////
	string GetLogicalOperator(Output*);

	//new
	string GetArithmaticOperator(Output*Po);

	~Input();
};

#endif