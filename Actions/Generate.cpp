#include "Generate.h"

#include <fstream>
using namespace std;

Generate::Generate(ApplicationManager *pAppManager) :Action(pAppManager)
{
}


void Generate::ReadActionParameters()
{
	Output *pOut = pManager->GetOutput();

	if (pManager->get_stat_count() == 0)
	{
		pOut->ClearStatusBar();
		pOut->PrintMessage("Please draw a flowchart first!");
	}
	else
	{
		pOut->ClearStatusBar();
		pOut->PrintMessage("Generating C++ code!");
	}
}

void Generate::Execute()
{
	ReadActionParameters();
	Output *pOut = pManager->GetOutput();
	ofstream outputFile("code.cpp", ios::out);
	pManager->GenerateCodeFile(outputFile);
	outputFile.close();
	pOut->ClearStatusBar();
	pOut->PrintMessage("Code is generated!");
	system("notepad.exe code.cpp");
}