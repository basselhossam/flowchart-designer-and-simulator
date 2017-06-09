#include "Run.h"

#include "..\ApplicationManager.h"

#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include <fstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Run::Run(ApplicationManager *pAppManager):Action(pAppManager)
{
}

void Run::ReadActionParameters()
{
//	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	pOut->ClearStatusBar();
	pOut->PrintMessage("Running .. Check Console!");
}

void Run::Execute()
{
	ReadActionParameters();
	pManager->RunChart();
	pManager->variables.clear();
	
}