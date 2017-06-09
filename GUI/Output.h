#pragma once

#include "Input.h"

class Input;
class Output	//The application manager should have a pointer to this class
{
private:
	window* pWind;	//Pointer to the Graphics Window
public:
	Output();

	window* CreateWind(int, int, int, int);
	void CreateDesignToolBar();	//Tool bar of the design mode
	void CreateSimulationToolBar();//Tool bar of the simulation mode
	window * getwindow()const;
	void CreateStatusBar();
	void CreateDrawArea();

	Input* CreateInput(); //creates a pointer to the Input object	
	void ClearStatusBar();	//Clears the status bar
	void ClearDrawArea();	//Clears the drawing area



	// -- Statements Drawing Functions
	void DrawAssign(Point Left, int width, int height, string Text, bool Selected = false);

	//TODO: Add similar functions for drawing all other statements.
	//		e.g. DrawCondtionalStat(......), DrawStart(......), DrawEnd(.......), ...etc
	//		Decide the parameters that should be passed to each of them

	void Output::Drawcondition(Point left, int width, int height, int t_width, int t_height, string Text, bool Selected = false);

	//--drawing read & print statement
	void Draw_in_out(Point left, int  width, int  height, int t_height, string Text, bool Selected, int factor = 20);

	//--drawing start or end statement
	void Draw_st_end(Point left, int width, int height, string Text, bool Selected = false);

	//--drawing connector
	void Draw_connector(vector<Point> v1, bool selected);

	void Draw_conn(Point initial, Point end, f_direction dir, bool Selected = false);

	//////////////////////////////////////////////////////////////////////////

	void OutVariables(int& x  ,int& y ,string op); //printing the output
	void ClearVariablesArea();
	void PrintMessage(string msg);	//Prints a message on Status bar

	~Output();
};