#pragma once

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\DEFS.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	MODE AppMode;		//Application Mode (design or simulation)
	
	int width, height;	//Window width and height
	int wx, wy;			//Window starting coordinates

	int StBrWdth;		//Status Bar Width
	int TlBrWdth;		//Tool Bar Width
	int MnItWdth;		//Menu Item Width

	//ADDED 
	int SimItWdth;
	int SimBrWdth;
	//END ADDED

	color DrawClr;		//Drawing color
	color HiClr;		//Highlighting color
	color MsgClr;		//Messages color

	int ASSGN_WDTH;		//Assignment statement default width
	int ASSGN_HI;		//Assignment statement default height
	/////////////////////////////////////////////////////////////////////
	int condition_width;   //codition width
	int condition_height;   //condition height

	int in_out_widht;    // input or output width
	int in_out_height;   //  input or output height

	int start_end_width;  // start or end  statement width
	int start_end_height;  //start or end  statement height
	/////////////////////////////////////////////////////////////////////
	
}UI;	//create a single global object UI

struct Point
{
	int x, y;
	Point(int a = 0, int b = 0)	//constructor
	{
		x = a;	y = b;
	}
	void p_set(int a, int b)
	{
		x = a;   y = b;
	}
	bool operator!=(Point p)
	{
		if (x != p.x  &&  y != p.y)
			return true;
		else
			return false;
	}

};

struct variable       //added by amr
{
	double value;
	string name;
};

enum direc
{
	E, W, N, S               //the direction of branching for connector
};

enum f_direction
{
	horizontal, vertical
};   //indicator to the direction that the arrow will start with it from the initial point


