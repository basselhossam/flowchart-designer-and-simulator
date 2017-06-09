#include "Comment.h"


Comment::Comment(ApplicationManager *pAppManager)
:Action(pAppManager)
{
	ptr = NULL;
}

void Comment:: ReadActionParameters()
{
	Output * pOut = pManager->GetOutput();
	Input *pIn = pManager->GetInput();
	pOut->PrintMessage("Enter the comment");
	comment = pIn->GetString(comment, pOut);
	ptr = pManager->GetSelectedStatement();
	if (ptr != NULL)
		lastcomment = pManager->GetSelectedStatement()->GetComment();
}

void Comment::Execute()
{
	ReadActionParameters();
	if (comment == ""){
		pManager->GetOutput()->PrintMessage("Canceled !!");
		SetUndo(false);
		return;
	}

	if (ptr != NULL)
		pManager->GetSelectedStatement()->Edit_comment(comment);
	else
		SetUndo(false);
}

void Comment::undo(){
	if (ptr){
		comment = ptr->GetComment();
		ptr->Edit_comment(lastcomment);
		lastcomment = comment;
	}
}