#include "Validate.h"

Validate::Validate(ApplicationManager *pAppManager) :Action(pAppManager)
{
}


void Validate::ReadActionParameters(){

}

void Validate::Execute(){
	
	pManager->CheckValidation();

}