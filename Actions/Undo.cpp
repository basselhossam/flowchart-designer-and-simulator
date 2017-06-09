#include "Undo.h"


Undo::Undo(ApplicationManager *pAppManager) :Action(pAppManager)
{
	SetUndo(false);
}


void Undo::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	undolist = pManager->GetUndolist();
	redolist = pManager->GetRedolist();
}

void Undo::Execute()
{
	ReadActionParameters();
	int size = undolist->size();
	if (undolist->size() > 0){
		(*undolist)[size - 1]->undo();
		redolist->push_back((*undolist)[size - 1]);
		undolist->pop_back();
	}
	else
		pManager->GetOutput()->PrintMessage("there are no actions left to undo !!!");
}