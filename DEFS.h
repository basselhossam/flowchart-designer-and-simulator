#pragma once

#include <vector>
#include <string>
//This file contais some global constants and definitions to be used in the project.

enum ActionType //The actions supported (you can add more if needed)
{
	ADD_SMPL_ASSIGN,//Add simple assignment statement
	ADD_VAR_ASSIGN,	//Add variable assignment statement
	ADD_SINGLE_OPERATOR, //Add single operator statement
	ADD_CONDITION, //Add a conditional statement (for if and while-loop statements)

	ADD_CONNECTOR, //Add a connector between two statements

	EDIT_STAT,	//Edit a statement
	
	SELECT,		//Select a statement, a connector

	DEL,		//Delete a figure(s)
	MOVE,		//Move a figure(s)
	ZoomIn,		//Resize a figure(s)
	ZoomOut,
	SAVE,		//Save the whole graph to a file
	LOAD,		//Load a graph from a file
	EXIT,		//Exit the application
	STATUS,		//A click on the status bar
	DSN_TOOL,	//A click on an empty place in the design tool bar
		
	SIM_MODE,	//Switch to simulatiom mode

	//BEGIN ADDED ACTIONS
	DEL_ALL,
	ADD_COMMENT,
	EDIT_CONNECT,
	COPY,
	CUT,
	PASTE,
	START,
	END,
	READ,
	WRITE,
	MULTISELECT,
	UNDO,
	REDO,
	INFO,
	//FOR SIMULATION MODE

	RUN,	
	STP,	
	GENERATE,
	CHART_VALIDATION,
	DSN_MODE,	 //Switch to Design mode
    SIM_TOOL,
	EXIT_SIM,
	//END ADDED

};

enum  MODE	//Modes of operation
{
	DESIGN,
	SIMULATION
};

enum DsgnMenuItem //The items of the design menu (you should add more items)  //***EDITED BY ADDING NEW ITEMS***
{
	//Note: Items are ordered here as they appear in menu
	//If you change the menu items order, change the order here too
	ITM_START,
	ITM_READ,
	ITM_SMPL_ASSIGN,//simple assignment statement  ****
	ITM_VAR_ASSIGN, //variable assignment statement  
	ITM_SINGLE_OPERATOR,
	ITM_COND,
	ITM_WRITE,
	ITM_END,
	ITM_CONNECT, 
	
	
	//TODO: Add more items names here

	//BEGIN ADDED ITEMS	

	ITM_EDIT_STAT,
	ITM_ZOOM_IN,
	ITM_ZOOM_OUT,
	ITM_INFO,
	ITM_EXIT1, //FOR EXIT BUTTON
	ITM_EXIT2,
    ITM_COPY,
	ITM_CUT,
	ITM_PASTE,
	ITM_UNDO,
	ITM_REDO,
	ITM_DEL,
	ITM_MOVE,
	ITM_MULTISELECT,

	ITM_EDIT_CONNECT,
	ITM_ADD_COMMENT,

	ITM_SAVE,
	ITM_LOAD,

	ITM_SIM_MODE,
	//ITM_EXIT3,
	//ITM_EXIT4,

	ITM_SELECT,
	ITM_DSN_TOOL,
	ITM_STATUS,
	
	//END ADDED ITEMS


	//ITM_EXIT,		//Exit         
	
	ITM_DSN_CNT		//no. of design menu items ==> This should be the last line in this enum             ****
	
};




enum SimMenuItem //The items of the simulation menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu

	//THERE ARE ADDED ITEMS HERE
	ITM_CHART_VALIDATION,
	ITM_RUN,	//Run
	ITM_STP,	//Step by step
	ITM_GENERATE,
	ITM_INFOSIM,
	ITM_DSN_MODE,
	ITM_EXITSIM,
	
		
    ITM_SIM_TOOL,
	//END ADDED ITEMS
	
	ITM_SIM_CNT		//no. of simulation menu items ==> This should be the last line in this enum
	
};




#ifndef NULL
#define NULL 0
#endif


#ifndef inv
#define inv -99898956.65
#endif