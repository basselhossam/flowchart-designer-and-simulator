#include "Output.h"


Output::Output()
{
	//Initialize user interface parameters

	//SOME VALUES ARE CHANGED AND SOME ITEMS ARE ADDED

	UI.width = 1400;  //CHANGED
	UI.height = 700;
	UI.wx = 15;
	UI.wy = 15;

	UI.AppMode = DESIGN;	//Design Mode is the default mode

	UI.StBrWdth = 50;
	UI.TlBrWdth = 160;  //CHANGED
	UI.MnItWdth = 80;  //CHANGED

	//ADDED
	UI.SimBrWdth = 80;
	UI.SimItWdth = 1200 / 7;
	//END ADDED

	UI.DrawClr = LIGHTBLUE;
	UI.HiClr = DARKBLUE;
	UI.MsgClr = LIGHTBLUE;

	UI.ASSGN_WDTH = 150;
	UI.ASSGN_HI = 50;
	/////////////////////////////////////////////////////////
	UI.condition_width = 250;
	UI.condition_height = 50;

	UI.in_out_widht = 110;   //modified by amr
	UI.in_out_height = 50;   //modified by amr

	UI.start_end_width = 200;
	UI.start_end_height = 100;
	//////////////////////////////////////////////////////////

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Programming Techniques Project");

	pWind->SetPen(LIGHTBLUE, 3);
	CreateDesignToolBar();
	CreateDrawArea();
	CreateStatusBar();
}


Input* Output::CreateInput()
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y)
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar()
{
	pWind->DrawImage("images\\StatusBar.jpg", 0, UI.height - UI.StBrWdth-5);
}

//new
void Output::CreateDrawArea()
{
	pWind->DrawImage("images\\DrawingArea.jpg", 0, UI.TlBrWdth);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the Design Menu
void Output::CreateDesignToolBar()
{
	UI.AppMode = DESIGN;	//Design Mode
	int i = 0;
	pWind->DrawImage("images\\DesignMenu.jpg", 0, 0);

	//MODIFIED -> I REMOVED THE LINE DRAWN UNDER THE TOOL BAR AS IT GOES WRONG ON SWITCHING BETWEEN MODES


	//Draw a line under the toolbar
	//pWind->DrawLine(0, UI.height-UI.StBrWdth, UI.width, UI.height-UI.StBrWdth);

}


void Output::CreateSimulationToolBar()
{
	UI.AppMode = SIMULATION;	//Simulation Mode

	///TODO: add code to create the simulation tool bar

	//MODIFIED-> THE NEXT LINE IS ADDED

	pWind->DrawImage("images\\SimMenu.jpg", 0, 0);


}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(LIGHTBLUE, 1);
	pWind->DrawImage("images\\StatusBar.jpg", 0, UI.height - UI.StBrWdth-5);
	//pWind->SetBrush(BLACK);
	//pWind->DrawRectangle(0, UI.height - UI.StBrWdth, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearDrawArea()
{
	pWind->SetPen(LIGHTBLUE, 1);
	pWind->DrawImage("images\\DrawingArea2.jpg", 0, UI.TlBrWdth);
	//pWind->SetBrush(WHITE);
	//pWind->DrawRectangle(0, UI.TlBrWdth, UI.width, UI.height - UI.StBrWdth);

}

void Output :: ClearVariablesArea()
{
	pWind->DrawImage("images\\DrawingArea1.jpg", 1200, UI.TlBrWdth);
}
//////////////////////////////////////////////////////////////////////////////////////////
window* Output::getwindow() const {
	return pWind;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::PrintMessage(string msg)	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar

	pWind->SetPen(UI.MsgClr, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, UI.height - (int)(UI.StBrWdth-7 / 1.5), msg);
}

//======================================================================================//
//								Statements Drawing Functions								//
//======================================================================================//

//Draw assignment statement and write the "Text" on it
void Output::DrawAssign(Point Left, int width, int height, string Text, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HiClr, 5);	//use highlighting color
	else
		pWind->SetPen(UI.DrawClr, 5);	//use normal color

	//getting size of the ststement
	int x, y;
	pWind->GetStringSize(x, y, Text);

	//Draw the statement block rectangle
	pWind->DrawRectangle(Left.x, Left.y, Left.x + x + 30, Left.y + height, FRAME);

	//writting the text
	pWind->SetPen(WHITE);
	pWind->DrawString(Left.x + 15, Left.y + height / 2 - y / 2, Text);

}
//////////////////////////////////////////////////////////////////////////////////////////

//Draw reading or printing statements 
void Output::Draw_in_out(Point left, int  width, int  height, int t_height, string Text, bool Selected, int factor) //factor affects the slope of the sides of the parallelogram 
{


	//setting the parallelogram points
	int x_points[4] = { left.x + factor, left.x + width, left.x + width - factor, left.x };
	int y_points[4] = { left.y, left.y, left.y + height, left.y + height };


	// drawing the parallelogram
	if (Selected == false)
		pWind->SetPen(UI.DrawClr, 5);
	else
		pWind->SetPen(UI.HiClr, 5);
	pWind->DrawPolygon(x_points, y_points, 4, FRAME);

	// drawing the text 
	pWind->SetPen(WHITE);
	pWind->DrawString(left.x + factor / 2 + 15, left.y + height / 2 - t_height / 2, Text);
}
//*******************************************************************************************************************************************



//Draw conditional statement
void Output::Drawcondition(Point left, int width, int height, int t_width, int t_height, string Text, bool Selected)
{
	/*
	double slope = 0.5773503;      //tan(30)
	Point head;
	head.y = left.y;
	head.x = left.x + width / 2;
	//gettig string size
	int x, y;
	pWind->GetStringSize(x, y, Text);

	//setting the points
	int d1 = 15 + x / 2 + int((y/2)/slope);
	int d2 = y / 2 + int((x / 2)*slope + 15 * slope);

	if (d1 < 40 && d2 < 23)
	{
	d1 = 40;  d2 = 23;
	}
	*/
	//here drawing starts
	int x_points[4] = { left.x, left.x + width / 2, left.x + width, left.x + width / 2 };
	int y_points[4] = { left.y + height / 2, left.y, left.y + height / 2, left.y + height };


	//drawing rhombus
	if (Selected == false)
		pWind->SetPen(UI.DrawClr, 5);
	else
		pWind->SetPen(UI.HiClr, 5);
	pWind->DrawPolygon(x_points, y_points, 4, FRAME);

	//drawing string
	pWind->SetPen(WHITE);
	pWind->DrawString(left.x + width / 2 - t_width / 2, left.y + height / 2 - t_height / 2, Text);
}

//***********************************************************************************************************************



//Drawing start or end statements
void Output::Draw_st_end(Point left, int width, int height, string Text, bool Selected)
{

	double slope = 0.3639702;    //tan(20)

	//getting string size
	int x, y;
	pWind->GetStringSize(x, y, Text);


	//drawing ellipse
	int d1 = 15 + x / 2 + int((y / 2) / slope);
	int d2 = y / 2 + int((x / 2)*slope + 15 * slope);
	if (Selected == false)
		pWind->SetPen(UI.DrawClr, 5);
	else
		pWind->SetPen(UI.HiClr, 5);

	if (d1 < 40 && d2 < 23)
	{
		d1 = 40;  d2 = 23;
	}
	pWind->DrawEllipse(left.x, left.y, left.x + 2 * d1, left.y + 2 * d2, FRAME);

	//drawing string
	pWind->SetPen(WHITE);
	pWind->DrawString(left.x + d1 - x / 2, left.y + d2 - y / 2, Text);
}
//***************************************************************************************************************************

void Output::Draw_connector(vector<Point> v1, bool selected)
{
	if (selected == true)
		pWind->SetPen(UI.HiClr, 4);
	else
		pWind->SetPen(UI.DrawClr, 4);
	//drawing the connector
	if (v1.size() > 1)
	{
		for (int i = 0; i < (int)v1.size() - 1; i++)
			pWind->DrawLine(v1[i].x, v1[i].y, v1[i + 1].x, v1[i + 1].y);

		pWind->DrawLine(v1[v1.size() - 1].x, v1[v1.size() - 1].y, v1[v1.size() - 1].x, v1[v1.size() - 1].y + 20);
		pWind->DrawLine(v1[v1.size() - 1].x, v1[v1.size() - 1].y + 20, v1[v1.size() - 1].x - 7, v1[v1.size() - 1].y + 10);
		pWind->DrawLine(v1[v1.size() - 1].x, v1[v1.size() - 1].y + 20, v1[v1.size() - 1].x + 7, v1[v1.size() - 1].y + 10);
	}
}


//Drawing connector
void Output::Draw_conn(Point initial, Point end, f_direction dir, bool Selected)
{

	Point p1, p2;                    //for drawing the arrow head
	Point mid;                       //in case the arrow is composed of two st-lines

	if (Selected == false)
		pWind->SetPen(UI.DrawClr, 5);    //setting the pen for drawing in normal or highlighted colour
	else
		pWind->SetPen(UI.HiClr, 5);
	if (abs(initial.x - end.x)<15 && abs(initial.y - end.y)<15)
	{
		PrintMessage("the connector is too short to be drawn");
		return;
	}

	else if (abs(initial.x - end.x)<15)                     //this means that the arrow is only one  vertical st-line
	{
		end.x = initial.x;                            //if the prrevious condition exists then we can neglect this difference
		pWind->DrawLine(initial.x, initial.y, end.x, end.y);
		if (end.y < initial.y)                           //if true then the end point is upper than initial point 
		{
			p1.p_set(end.x + 6, end.y + 10);
			p2.p_set(end.x - 6, end.y + 10);
		}
		else
		{
			p1.p_set(end.x + 6, end.y - 10);
			p2.p_set(end.x - 6, end.y - 10);
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////
	else if (abs(initial.y - end.y)<15)      //if the arrow is one horizontal line
	{
		end.y = initial.y;

		pWind->DrawLine(initial.x, initial.y, end.x, end.y);
		if (end.x > initial.x)                   //if true then the end point is on the right of the initial point 
		{
			p1.p_set(end.x - 10, end.y - 6);
			p2.p_set(end.x - 10, end.y + 6);
		}
		else
		{
			p1.p_set(end.x + 10, end.y - 6);
			p2.p_set(end.x + 10, end.y + 6);
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////
	else    //  the arrow will be composed of two lines
	{
		if (dir == horizontal)
		{
			mid.p_set(end.x, initial.y);
			if (end.y<initial.y)                   //if true then the end point is upper than initial point 
			{
				p1.p_set(end.x + 6, end.y + 10);
				p2.p_set(end.x - 6, end.y + 10);
			}
			else
			{
				p1.p_set(end.x + 6, end.y - 10);
				p2.p_set(end.x - 6, end.y - 10);
			}
		}
		else                                      //first direction is vertical
		{
			mid.p_set(initial.x, end.y);
			if (end.x>initial.x)                   //if true then the end point is on the right of the initial point 
			{
				p1.p_set(end.x - 10, end.y - 6);
				p2.p_set(end.x - 10, end.y + 6);
			}
			else
			{
				p1.p_set(end.x + 10, end.y - 6);
				p2.p_set(end.x + 10, end.y + 6);
			}
		}
		pWind->DrawLine(initial.x, initial.y, mid.x, mid.y);
		pWind->DrawLine(mid.x, mid.y, end.x, end.y);
	}
	//drawing arrow head
	pWind->DrawLine(end.x, end.y, p1.x, p1.y);
	pWind->DrawLine(end.x, end.y, p2.x, p2.y);
}
/////////////////////////////////////////////////////////////////



void Output :: OutVariables( int &x,int& y,string op)  
{
	pWind->SetPen(UI.MsgClr, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	int W,H,ind,i=0;
	string result;
	pWind->GetStringSize(W,H,op);
	if(W + x >1380)
	{
		while(i<op.size())
		{
		string s = "";
		int ws,ls;
		for(i; i<op.size();i++)
		{ s+=op[i];
		      pWind->GetStringSize(ws,ls,s);
				if(op[i] == '=' || ws + x >1350)
			{
				pWind->DrawString(x,y,s);
				i++;
				y+=20;
			   break;
			}
		}
		result = s;
		//y+=20;
	}
		pWind->DrawString(x,y,result);
		y+=20;
	}
	else
	{
		pWind->DrawString(x, y, op);
		y+=20;
	}
}

Output::~Output()
{
	delete pWind;
}
