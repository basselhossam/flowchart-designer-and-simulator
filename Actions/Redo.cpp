#include "Redo.h"


Redo::Redo(ApplicationManager *pAppManager) :Action(pAppManager)
{
	SetUndo(false);
}


void Redo::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	undolist = pManager->GetUndolist();
	redolist = pManager->GetRedolist();
}

void Redo::Execute()
{
	ReadActionParameters();
	int size = redolist->size();
	if (redolist->size() > 0){
		(*redolist)[size - 1]->undo();
		undolist->push_back((*redolist)[size - 1]);
		redolist->pop_back();
	}
	else
		pManager->GetOutput()->PrintMessage("there are no actions left to redo !!!");
}