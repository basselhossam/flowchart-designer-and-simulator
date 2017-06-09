
#include "Save.h"

#include "..\ApplicationManager.h"

#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

#include <fstream>

using namespace std;

Save::Save(ApplicationManager *pAppManager) :Action(pAppManager)
{
	SetUndo(false);
}

void Save::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	if (pManager->get_stat_count()==0)
	{
		pOut->ClearStatusBar();
		pOut->PrintMessage("No flowcharts to save!");
	}

}

void Save::Execute()
{
	Output *pOut = pManager->GetOutput();
	ReadActionParameters();
	ofstream outputFile("chart.txt", ios::out);
	pManager->SaveChart(outputFile);
	outputFile.close();
		pOut->ClearStatusBar();
	pOut->PrintMessage("Flowchart is saved!");
}