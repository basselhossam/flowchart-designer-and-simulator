#include "Input.h"
#include "Output.h"
#include <sstream>

Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

bool Input::GetPointClicked(Point &P) const
{
	pWind->FlushMouseQueue();
	clicktype x = pWind->WaitMouseClick(P.x, P.y);	//Wait for mouse click
	if (x == RIGHT_CLICK)
		return false;
	else if (x == LEFT_CLICK)
		return true;
}

void Input:: set_ellipse_Dim(string Text, int & width, int & height, int & t_width, int & t_height)
{
	double slope = 0.3639702;    //tan(20)

	//getting string size
	int x, y;
	pWind->GetStringSize(x, y, Text);

	t_height = y;
	t_width = x;

	width = 2 * (15 + x / 2 + int((y / 2) / slope));
	height = 2 * (y / 2 + int((x / 2)*slope + 15 * slope));
}

void Input::set_Read_Write_Dim(string Text, int & width, int & height, int & t_width, int & t_height, int & factor)
{
	double slope = 0.5773507;
	pWind->GetStringSize(t_width, t_height, Text);
	height = t_height + 30;
	factor = int(slope* height);
	width = 30 + t_width + factor;
}

void Input::set_cond_Dim(string Text, int & width, int & height, int & t_width, int & t_height)
{
	double slope = 0.5773503;      //tan(30)
	//gettig string size
	int x, y;
	pWind->GetStringSize(x, y, Text);

	t_height = y;
	t_width = x;
	//setting the points
	width = 2 * (15 + x / 2 + int((y / 2) / slope));
	height = 2 * (y / 2 + int((x / 2)*slope + 15 * slope));
}

void Input::set_Assign_Dim(string Text, int & width, int & height, int & t_width, int & t_height)
{
	//getting size of the ststement
	int x, y;
	pWind->GetStringSize(x, y, Text);

	width = x + 30;
	height = y + 30;
	t_width = x;
	t_height = y;
}

string Input::GetArithmaticOperator(Output*Po)
{
	pWind->FlushKeyQueue();
	string Str;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Str.size() == 0)
		{
			if (Key == '+' || Key == '-' || Key == '*' || Key == '/')
			{
				Str.push_back(Key);
				Po->PrintMessage(Str);
			}

			else if (Key == 27)
				return "";

			else
				Po->PrintMessage("Invalid operator !");
		}
		else if (Str.size() == 1)
		{
			if (Key == '=')
			{
				Str.push_back(Key);
				Po->PrintMessage(Str);
			}
			else if (Key == '\r')
			{
				return Str;
				break;
			}
			else
				Po->PrintMessage("Invalid operator !");
		}
		else if (Key == '\r')
		{
			return Str;
			break;
		}
	}
}

string Input::GetLogicalOperator(Output*Po){
	pWind->FlushKeyQueue();
	string Str;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Str.size() == 0)
		{
			if (Key == '<' || Key == '>' || Key == '=' || Key == '!')
			{
				Str.push_back(Key);
				Po->PrintMessage(Str);
			}
			
			else if (Key == 27)
				return "";
			
			else
				Po->PrintMessage("Invalid operator !");
		}
		else if (Str.size() == 1)
		{
			if (Key == '=')
			{
				Str.push_back(Key);
				Po->PrintMessage(Str);
			}
			else if (Key == 27)
				return "";

			else if (Key == '\r')
			{
				if (Str == "!")
					Po->PrintMessage("You have to enter = or escipe to cancel.");
				else
					return Str;
					break;
			}
			else
				Po->PrintMessage("Invalid operator !");
		}
		else if (Key == '\r')
		{
			return Str;
			break;
		}
	}
}

string Input::GetString(string txt,Output *pO) const
{
	pWind->FlushKeyQueue();
	string Str=txt;
	char Key;

	while (1)
	{
		pWind->WaitKeyPress(Key);


		if (Key == 8)                      // 8------>>backspace
		{
			if (Str.size() != 0)                //checking if str is empty or not because resizing a string to length to -1 leads to an error
			{
				Str.resize(Str.size() - 1);
				pO->PrintMessage(Str);
			}
		}
		else if (Key == '\r')                   // '\r' means "enter" key
		{
			if (Str.size() == 0)
			{
				pO->PrintMessage(" enter somthing");
			}
			else
			{
				pO->PrintMessage(Str + " stored");
				break;
			}
		}
		else if (Key == 27)	                     //ESCAPE key is pressed   
		{
			return txt;
		}
		else
		{
			Str.push_back(Key);
			pO->PrintMessage(Str);
		}
	}
	pWind->FlushMouseQueue();
	return Str;
}


//reading an identifier from the user
string Input::GetIdentifier(Output *pO) const
{
	pWind->FlushKeyQueue();
	string Str;
	char Key;

	//pO->PrintMessage("enter an identifier");
	while (1)
	{
		pWind->WaitKeyPress(Key);

		if (Key >= 48 && Key <= 57)         // if the key pressed is a number from 0 to 9
		{
			if (Str.size() == 0)
			{
				pO->PrintMessage("an identifier can't start with a number");
			}
			else
			{
				Str.push_back(Key);
				pO->PrintMessage(Str);
			}
		}
		else if (Key == 8)                      // 8------>>backspace
		{
			if (Str.size() != 0)                //checking if str is empty or not because resizing a string to length to -1 leads to an error
			{
				Str.resize(Str.size() - 1);
				pO->PrintMessage(Str);
			}
		}
		else if (Key == '\r')                   // '\r' means "enter" key
		{
			if (Str.size() == 0)
			{
				pO->PrintMessage(" enter an identifier");
			}
			else
			{
				pO->PrintMessage(Str + "   stored");
				break;
			}
		}
		else if (Key == 27)	                     //ESCAPE key is pressed
		{
			return "";
		}
		else if (!((Key >= 65 && Key <= 90) || (Key >= 97 && Key <= 122) || (Key == '_')))  //   if key isnot included in the range of capital or  
		{                                                                //   small letters or it's not undescore
			pO->PrintMessage("you can use letters and underscore only");
		}
		else
		{
			Str.push_back(Key);
			pO->PrintMessage(Str);
		}
	}
	pWind->FlushMouseQueue();
	return Str;
}



string Input::GetIdentifiers(string txt, Output * pO, vector <string> & var)
{
	pWind->FlushKeyQueue();
	vector<string> v1 = var;
	string str = txt;
	string current;
	if (v1.size() != 0)
	{
		current = v1[v1.size() - 1];
		v1.erase(v1.end() - 1);
	}
	char Key;
	do
	{
		pWind->WaitKeyPress(Key);
		if (Key == 8)
		{
			if (str.size() != 0)                //checking if str is empty or not because resizing a string to length to -1 leads to an error
			{
				if (*(str.end() - 1) == ' ')
				{
					current = *(v1.end() - 1);
					v1.erase(v1.end() - 1);
					str.resize(str.size() - 2);
				}
				else
				{
					str.resize(str.size() - 1);
					current.resize(current.size() - 1);
				}
				pO->PrintMessage(str);
			}
		}
		else if (Key >= 48 && Key <= 57)         // if the key pressed is a number from 0 to 9
		{
			if (current.size() == 0)
			{
				pO->PrintMessage("an identifier can't start with a number");
			}
			else
			{
				current.push_back(Key);
				str.push_back(Key);
				pO->PrintMessage(str);
			}
		}
		else if (Key == '\r')                   // '\r' means "enter" key
		{
			if (current.size() == 0)
			{
				pO->PrintMessage(" enter an identifier");
				Key = '*';
			}
			else
			{
				v1.push_back(current);
				pO->PrintMessage(str);
				break;
			}
		}
		else if (Key == ',')
		{
			if (str.size() == 0)
				pO->PrintMessage("you didn't enter any thing");
			else if (current.size() == 0)
				pO->PrintMessage("it's not allowed to enter two succesive commas ");
			else
			{
				str.push_back(Key);
				str.push_back(' ');
				v1.push_back(current);
				current = "";
				if (str.size() >= 25)
					pO->PrintMessage(str + "   max range reached");
				else
					pO->PrintMessage(str);
			}
		}
		else if (Key == 27)	                     //ESCAPE key is pressed
		{
			return txt;                          //to escape editing without saving
		}
		else if (!((Key >= 65 && Key <= 90) || (Key >= 97 && Key <= 122) || (Key == '_')))  //   if key isnot included in the range of capital or  
		{                                                                //   small letters or it's not undescore
			pO->PrintMessage("you can use letters nums and underscore only");
		}
		else
		{

			if (str.size() < 25)
			{
				str.push_back(Key);
				current.push_back(Key);
				pO->PrintMessage(str);
			}
			if (str.size() == 25)
			{
				pO->PrintMessage(str + "   max range reached");
				continue;
			}
		}
	} while (Key != '\r');
	var = v1;
	return str;
}






/*
if(Key == 27 )	//ESCAPE key is pressed                                *I can see that it has no meaninig
return "";	//returns nothing as user has cancelled label
if(Key == 13 )	//ENTER key is pressed
return Str;

if(Key == 8 )	//BackSpace is pressed
Str.resize(Str.size()-1);
else
{
Str += Key;
pO->PrintMessage(Str);
}
}
return Str;
*/


window * Input::getwindow()const
{
	return pWind;
}


double Input::GetValue(Output* pO) const	// Reads a double value from the user 
{
	//test to clear the keyboard queue
	//window::FlushKeyQueue;
	pWind->FlushKeyQueue();
	//end test
	///TODO: add code to read a double value from the user and assign it to D
	char key;
	string str;
	stringstream ss;
	bool check_dec = true;   //to check if the user input contains two decimal points or not         
	double D;

	//Read a double value from the user
	do
	{
		pWind->WaitKeyPress(key);
		if (key == 8)       //the pressed key is back space
		{
			if (str.size() != 0)
			{
				if (*(str.end() - 1) == '.')  check_dec = true;             //if the decimal point is deleted check must be initialized to true again
				//note that the 2nd wrong decimal point will not be pushed in the string 
				str.resize(str.size() - 1);
				pO->PrintMessage(str);

			}                                         //when the first decimal point is detected check will be false  
		}                                             //to prevent the user from entering another decimal point through condithion <1>  
		else if (key == 46 && check_dec == false)//----------------> condition<1>   //46 is a dot
		{
			pO->PrintMessage("the number can't have two decimal points");
		}
		else if (key == '-' && str.size()>0)
		{
			pO->PrintMessage("no minus sign is allowed in the middle of a number");
		}

		else if (key == 27)    //27------->escape
		{
			return inv;       //if the user enters the "escape" key the function will return 0 as an initial value for the double variable
		}
		else if (key == '\r')           //'\r'   is enter
		{
			if (str == "-." || str == "-" || str == "." || str.size() == 0)
			{
				str.resize(0);
				str.push_back('0');
			}
		}
		else if (!((key >= 48 && key <= 57) || key == 46 || key == '-'))
		{
			pO->PrintMessage("it is allowed to enter a decimal point character only");
		}
		else
		{
			if (key == 46) check_dec = false;
			str.push_back(key);
			pO->PrintMessage(str);
		}
	} while (key != '\r');
	ss << str;
	ss >> D;
	//test deleting the mousequeue
	pWind->FlushMouseQueue();
	//end test
	return D;
}


//ActionType Input::GetUserAction() const
//{	
//	//This function reads the position where the user clicks to determine the desired action
//
//	int x,y;
//	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
//
//	if(UI.AppMode == DESIGN )	//application is in design mode
//	{
//		//[1] If user clicks on the Toolbar
//		if ( y >= 0 && y < UI.TlBrWdth)
//		{	//Check whick Menu item was clicked
//			if( x >= 0 && x < UI.MnItWdth  )
//				return ADD_SMPL_ASSIGN;
//			if( x >= UI.MnItWdth && x < 2* UI.MnItWdth  )		
//				return ADD_CONDITION;
//			if( x >= UI.MnItWdth && x < 3* UI.MnItWdth  )		
//				return EXIT;
//
//			return DSN_TOOL;	//a click on empty part of the tool bar
//		
//		}
//		
//		//[2] User clicks on the drawing area
//		if ( y >= UI.TlBrWdth && y < UI.height - UI.StBrWdth)
//		{
//			return SELECT;	//user want to select/unselect a statement in the flowchart
//		}
//		
//		//[3] User clicks on the status bar
//		return STATUS;
//	}
//	else	//Application is in Simulation mode
//	{
//		return SIM_MODE;	//This should be changed after creating the compelete simulation bar 
//	}
//
//}
//

ActionType Input::GetUserAction() const
{	
	//This function reads the position where the user clicks to determine the desired action

	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.AppMode == DESIGN )	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.TlBrWdth)
		{	
			//Check whick Menu item was clicked
			//This assumes that menu items are lined up horizontally
			int ClickedItem = (x / UI.MnItWdth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==>+ first item is clicked, if 1 ==> 2nd item and so on  //EDITED BY ADDING NEW CASES
			ClickedItem = (y >= 80) ? ClickedItem + 15 : ClickedItem;
			switch (ClickedItem)
			{
			case ITM_SMPL_ASSIGN: return ADD_SMPL_ASSIGN;
			
			case ITM_COND: return ADD_CONDITION;

			//BEGIN ADDED CASES

			case ITM_VAR_ASSIGN : return ADD_VAR_ASSIGN;

			case ITM_SINGLE_OPERATOR: return ADD_SINGLE_OPERATOR;

			case ITM_CONNECT : return ADD_CONNECTOR;

			case ITM_EDIT_STAT : return EDIT_STAT;

			case ITM_MULTISELECT: return MULTISELECT;
			//case ITM_SELECT : return SELECT;

			case ITM_DEL : return DEL;

			case ITM_MOVE : return MOVE;

			case ITM_ZOOM_IN : return ZoomIn;

			case ITM_ZOOM_OUT:return ZoomOut;

			case ITM_INFO:return INFO;

			case ITM_SAVE : return SAVE;

			case ITM_LOAD : return LOAD;
			
			case ITM_UNDO:return UNDO;

			case ITM_REDO:return REDO;
			//case ITM_STATUS :	return STATUS;

			//case ITM_DSN_TOOL :	return DSN_TOOL;

			case ITM_SIM_MODE :	return SIM_MODE;

			case ITM_ADD_COMMENT: return ADD_COMMENT; 
			case ITM_EDIT_CONNECT: return EDIT_CONNECT;
			case ITM_COPY: return COPY;
			case ITM_CUT: return CUT;
			case ITM_PASTE: return PASTE;
			case ITM_START: return START;
			case ITM_END: return END;
			case ITM_READ: return READ;
			case ITM_WRITE: return WRITE;

				//for exit 
			/*case ITM_EXIT3: return EXIT;	
			case ITM_EXIT: return EXIT;
			case ITM_EXIT2: return EXIT;
			case ITM_EXIT4: return EXIT;*/

				//END ADDED CASES

			default: return EXIT;
			}
		}

	
		//[2] User clicks on the drawing area
		if ( y >= UI.TlBrWdth && y < UI.height - UI.StBrWdth)
		{
			return SELECT;	//user want to select/unselect a statement in the flowchart
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//Application is in Simulation mode
	{
		if ( y >= 0 && y < UI.TlBrWdth)
		{	
			int ClickedItem = (x / UI.SimItWdth);
			switch (ClickedItem)
			{
			case ITM_CHART_VALIDATION: return CHART_VALIDATION;
			case ITM_RUN: return RUN;
			case ITM_STP: return STP;
			case ITM_GENERATE: return GENERATE;
			case ITM_INFOSIM: return INFO;
			case ITM_DSN_MODE: return DSN_MODE;	
			case ITM_EXITSIM: return EXIT;

			default: return SIM_TOOL;	
			}

		//return SIM_MODE;	//This should be changed after creating the compelete simulation bar 

	}
		//[2] User clicks on the drawing area
		if ( y >= UI.TlBrWdth && y < UI.height - UI.StBrWdth)
		{
			return SELECT;	//user want to select/unselect a statement in the flowchart
		}
		
		//[3] User clicks on the status bar
		return STATUS;

  }
}

//I created those two functions here because I want to use them before creating the statement and ssfter creating it , this appears clearly in read pramameters of add_read and add write

//calc_Read_corner(): this function calculates the left corner of the reading or writing statements only
// left corner is calculated and returned by reference
void Input::calc_Read_corner(Point in,Point & lcorner, int width,int factor)
{
	lcorner.x = in.x - (width-factor) / 2 - factor;
	lcorner.y = in.y;
}


//calc_stat_corner(): calculates the left corner of any statement except read or write 
// this because read & write contain factor which doesn't exist in other statements
// left corner is calculated and returned by reference
void Input::calc_stat_corner(Point in, Point & lcorner, int width)
{
	lcorner.x = in.x - width / 2;
	lcorner.y = in.y;
}


//function can draw checks for three conditions:
//intersection with
//1-other statements
//2-status bar or tool bar
//3-right and left boundaries of the window

bool Input::candraw(Point p, ApplicationManager * AppMan, int height, int width, int id)
{
	if ((p.y - 20 >= UI.TlBrWdth && p.y < UI.height - (UI.StBrWdth + height + 20)) && (!check_intersection(AppMan, p, width, height, id)) && p.x>20 && p.x + 20 + width<UI.width)
	{
		return true;
	}
	else
	{
		AppMan->GetOutput()->PrintMessage("Can't draw here , try again in the drawing area");
		return false;
	}
}



bool Input::intersect_with_connector(int height, int width, Point l_corner, ApplicationManager * AM)
{
	Connector ** list = AM->get_conn_list();
	for (int i = 0; i < AM->get_ConnCount(); i++)
	{
		for (int j = 0; j < list[i]->get_path().size() - 1; j++)
		{
			if (list[i]->get_path()[j].x == list[i]->get_path()[j + 1].x)   //vertical
			{
				if (l_corner.x <= list[i]->get_path()[j].x  && l_corner.x + width >= list[i]->get_path()[j].x && l_corner.y <= max(list[i]->get_path()[j].y, list[i]->get_path()[j + 1].y) && l_corner.y + height >= min(list[i]->get_path()[j].y, list[i]->get_path()[j + 1].y))
					return 1;
			}
			else                                                          //horizontal
			{
				if (l_corner.y <= list[i]->get_path()[j].y && l_corner.y + height >= list[i]->get_path()[j].y && l_corner.x <= max(list[i]->get_path()[j].x, list[i]->get_path()[j + 1].x) && l_corner.x + width >= min(list[i]->get_path()[j].x, list[i]->get_path()[j + 1].x))
					return 1;
			}
		}
	}
	return false;
}

bool Input::check_intersection(ApplicationManager * AppMan, Point p, int width, int height, int id)
{
	Statement ** s_list = AppMan->get_statement_list();
	for (int i = 0; i < AppMan->get_stat_count(); i++)
	{
		if (AppMan->get_statement_list()[i]->get_ID() != id && !(AppMan->get_statement_list()[i]->GetCut()))
		{
			if ((p.x >= s_list[i]->get_lcorner().x && p.x - 20 <= s_list[i]->get_lcorner().x + width + 20) || (p.x + width + 20 >= s_list[i]->get_lcorner().x - 20 && p.x <= s_list[i]->get_lcorner().x))
			{
				if ((p.y >= s_list[i]->get_lcorner().y && p.y - 20 <= s_list[i]->get_lcorner().y + height + 20) || (p.y + height + 20 >= s_list[i]->get_lcorner().y - 20 && p.y <= s_list[i]->get_lcorner().y))
					return true;
			}
		}
	}
	return false;
}

Input::~Input()
{
}
