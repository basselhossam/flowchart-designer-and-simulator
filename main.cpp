#include "ApplicationManager.h"

//to add icon to the program
#include "resource.h"

//this is the setting changed in the project linker setting.
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

//last integrated

int main()
{
	ActionType ActType;
	//Create an object of ApplicationManager
	ApplicationManager AppManager;
	do
	{		
		//Step I - Read user input (action)
		ActType = AppManager.GetUserAction();

		//Steps II & III - Create & Exexute the action
		AppManager.ExecuteAction(ActType);

		//Step IV - Update the interface
		AppManager.UpdateInterface();	

	}while(ActType != EXIT);	
	return 0;
}

