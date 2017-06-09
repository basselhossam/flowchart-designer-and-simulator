#include "ApplicationManager.h"
#include "Actions\AllActions.h"
#include "GUI\Input.h"
#include "GUI\Output.h"


//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	StatCount = 0;
	ConnCount = 0;
	pSelectedStat = NULL;	//no Statement is selected yet
	pSelectedConn = NULL;
	pCopied = NULL;
	pCut = NULL;
	
	currentmode = DESIGN;

	//Create an array of Statement pointers and set them to NULL		
	for(int i=0; i<MaxCount; i++)
	{
		StatList[i] = NULL;	
		ConnList[i] = NULL;
	}
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	pOut->ClearStatusBar();
	pAct = NULL;
	
	//According to ActioType, create the corresponding action object
	switch (ActType)
	{

		case START:
			pAct = new AddStart(this);
			break;

		case READ:
			pAct = new Add_Read_Stat(this);
			break;

		case ADD_CONDITION:
			///create AddCondition Action here
			pAct = new AddCond(this);
			break;

		case ADD_SMPL_ASSIGN:
			pAct = new AddSmplAssign(this);
			break;

		case ADD_VAR_ASSIGN:
			pAct = new AddVarAssign(this);
			break;

		case ADD_SINGLE_OPERATOR:
			pAct = new AddSingleOperator(this);
			break;

		case WRITE:
			pAct = new Add_Write_Stat(this);
			break;

		case COPY:
			pAct = new Copy(this);
			break;

		case PASTE:
			pAct = new Paste(this);
			break;

		case INFO:
			pAct = new Info(this);
			break;

		case MOVE:
			pAct = new Drag(this);
			break;

		case EDIT_CONNECT:
			pAct = new Edit_Connector(this);
			break;

		case STP:
			pAct = new StpByStp(this);
			break;

		case CUT:
			pAct = new Cut(this);
			break;

		case DEL:
			pAct = new Delete(this);
			break;

		case MULTISELECT:
			pAct = new MultiSelect(this);
			break;

		case END:
			pAct = new AddEnd(this);
			break;

		case ADD_COMMENT:
			pAct = new Comment(this);
			break;

		case EDIT_STAT:
			pAct = new Edit(this);
			break;

		case SELECT:
			///create Select Action here
			pAct = new Select(this);
			break;

		case SAVE:
			pAct = new Save(this);
			break;

		case LOAD:
			pAct = new Load(this);
			break;

		case UNDO:
			pAct = new Undo(this);
			break;

		case REDO:
			pAct = new Redo(this);
			break;


		case EXIT:
			///create Exit Action here
			
			break;

		case SIM_MODE:
			pOut->PrintMessage("Action: Switch to Simulation Mode, creating simualtion tool bar");
			pOut->CreateSimulationToolBar();
			pOut->ClearVariablesArea();
			currentmode = SIMULATION;
			break;
		
		case DSN_MODE:
			pOut->PrintMessage("Action: Switch to Design Mode, creating Design tool bar");
			pOut->CreateDesignToolBar();
			pOut->ClearVariablesArea();
			currentmode = DESIGN;
			break;

		case CHART_VALIDATION:
			pAct = new Validate(this);
			break;

		case RUN:
			pAct = new Run(this);
			break;

		case ADD_CONNECTOR:
			pAct = new AddConnecter(this);
			break;
		case GENERATE:
			pAct = new Generate(this);
			break;
			
		case STATUS:
			return;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		if (!(pAct->GetUndo())){
			delete pAct;	//Action is not needed any more ==> delete it
		}
		else{
			undolist.push_back(pAct);
			redolist.clear();
		}
	}
}



//==================================================================================//
//						Statements Management Functions								//
//==================================================================================//
//Add a statement to the list of statements
void ApplicationManager::AddStatement(Statement *pStat)
{
	if(StatCount < MaxCount)
		StatList[StatCount++] = pStat;
	
}

////////////////////////////////////////////////////////////////////////////////////
Statement *ApplicationManager::GetStatement(Point P) const
{
	//If this point P(x,y) belongs to a statement return a pointer to it.
	//otherwise, return NULL


	///Add your code here to search for a statement given a point P(x,y)
	for (int i = 0; i < StatCount; i++){
		if (StatList[i]->check_range(P))
			return StatList[i];
	}
	return NULL;
}
////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::Add_Connector(Connector *pConn)
{
	if (ConnCount < MaxCount)
		ConnList[ConnCount++] = pConn;

}

Connector * ApplicationManager::GetConnector(Point p) const
{
	vector <Point> way;
	int max, min;
	for (int j = 0; j < ConnCount; j++)
	{
		way = ConnList[j]->get_path();
		for (int i = 1; i<int(way.size()); i++)
		if (way[i].x == way[i - 1].x)      //vertical
		{
			//finding the max in height
			if (way[i].y > way[i - 1].y)  { max = way[i].y;  min = way[i - 1].y; }
			else                           { max = way[i - 1].y;  min = way[i].y; }

			if (p.x <= way[i].x + 7 && p.x >= way[i].x - 7 && p.y >= min &&p.y <= max)
				return ConnList[j];
		}
		else
		{
			if (way[i].x > way[i - 1].x)    { max = way[i].x;  min = way[i - 1].x; }
			else                            { max = way[i - 1].x;   min = way[i].x; }

			if (p.y <= way[i].y + 7 && p.y >= way[i].y - 7 && p.x >= min && p.x <= max)
				return ConnList[j];
		}
	}
	return NULL;
}

Connector * & ApplicationManager::GetSelectedConnector()
{
	return pSelectedConn;
}
void ApplicationManager::SetSelectedConnector(Connector * pCon)
{
	pSelectedConn = pCon;
}
////////////////////////////////////////////////////////////////////////////////////
//Returns the selected statement
Statement *ApplicationManager::GetSelectedStatement() const
{	return pSelectedStat;	}

////////////////////////////////////////////////////////////////////////////////////
//Set the statement selected by the user
void ApplicationManager::SetSelectedStatement(Statement *pStat)
{
	pSelectedStat = pStat;
}


vector <Statement*>* ApplicationManager::GetSelectedStatements()
{
	return &pSelectedStatements;
}


void ApplicationManager::addSelectedStatement(Statement *pStat)
{
	if (!pStat->IsSelected()){
		pSelectedStatements.push_back(pStat);
		pStat->SetSelected(true);
		pStat->PrintInfo(pOut);
	}
	else
		unSelectStatement(pStat);
}

void ApplicationManager::unSelectStatements(){

	int i = pSelectedStatements.size() - 1;
	while (i >= 0){
		if (pSelectedStatements[i] != NULL)
			pSelectedStatements[i]->SetSelected(false);
		i--;
	}
	pSelectedStatements.clear();

}

void ApplicationManager::unSelectStatement(Statement *pStat){

	int i = pSelectedStatements.size() - 1;
	while (i >= 0){
		if (pSelectedStatements[i] == pStat){
			pSelectedStatements[i]->SetSelected(false);
			pSelectedStatements.erase(pSelectedStatements.begin()+i);
		}
		i--;
	}
}

void ApplicationManager::RemoveStatment(Statement *pStat)
{
	/*int x = pSelectedStat->GetID();
	if(x==StatCount-1)
	{
	delete StatList[x];
	StatList[x]=NULL;
	}
	StatList[x]=StatList[StatCount-1];
	//StatList[StatCount]=NULL;
	//swap(StatList[x], StatList[StatCount]);
	StatCount--;*/
	//delete pStat;
	//pStat=NULL;
	for (int i = 0; i<StatCount; i++)
	{
		if (StatList[i] == pStat)
		{
			DeletedStatements.push_back(pStat);

			for (int j = 0; j < ConnCount; j++)
			{
				if (ConnList[j]->getDstStat() == pStat)
				{
					RemoveConnector(ConnList[j]);
					j--;
				}
			}

			if (dynamic_cast<Conditional *>(pStat))
			{
				if (dynamic_cast<Conditional *>(pStat)->get_YConn() != NULL)
					RemoveConnector(dynamic_cast<Conditional *>(pStat)->get_YConn());
				if (dynamic_cast<Conditional *>(pStat)->get_NConn() != NULL)
					RemoveConnector(dynamic_cast<Conditional *>(pStat)->get_NConn());
			}
			else
			{
				if (pStat->GetConnect() != NULL)
					RemoveConnector(pStat->GetConnect());
			}

			StatList[i] = StatList[StatCount - 1];
			StatList[StatCount - 1] = NULL;
			break;
		}
	}
	StatCount--;
}

Statement* ApplicationManager::GetCopied() const	{
	return pCopied;
}
void ApplicationManager::SetCopied(Statement *pStat){
	pCopied = pStat;
}

Statement* ApplicationManager::GetCut() const{
	return pCut;
}
void ApplicationManager::SetCut(Statement *pStat){
	pCut = pStat;
}


vector <Action*>* ApplicationManager::GetUndolist()
{
	return &undolist;
}

vector <Action*>* ApplicationManager::GetRedolist()
{
	return &redolist;
}

//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();
	if (currentmode == DESIGN)
		pOut->CreateDesignToolBar();
	else
		pOut->CreateSimulationToolBar();
	//Draw all statements
	for (int i = 0; i<StatCount; i++)
		if (!StatList[i]->GetCut())
			StatList[i]->Draw(pOut);

	//Draw all connections
	for (int i = 0; i<ConnCount; i++)
		ConnList[i]->Draw(pOut);

}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////
vector <variable> & ApplicationManager::get_var_list()
{
	return var;
}

int ApplicationManager::get_stat_count()
{
	return StatCount;
}

int ApplicationManager::get_ConnCount()const
{
	return ConnCount;
}

Connector ** ApplicationManager::get_conn_list()
{
	return ConnList;
}

Statement ** ApplicationManager::get_statement_list()
{
	return StatList;
}


//LOADING
void ApplicationManager::LoadChart(ifstream &Infile){
	string s;
	int count, count2;
	Statement*st;
	Connector*ConPtr;

	Infile >> count;
	while (count>0){

		Infile >> s;

		if (s == "STRT")
			st = new Start(this);
		else if (s == "END")
			st = new End(this);
		else if (s == "SNGLOP")
			st = new SingleOperator(this);
		else if (s == "COND")
			st = new Conditional(this);
		else if (s == "VARASSIGN")
			st = new VarAssign(this);
		else if (s == "SMPLASSIGN")
			st = new SmplAssign(this);
		else if (s == "READ")
			st = new Read_Stat(this);
		else if (s == "WRITE")
			st = new Write_Stat(this);

		st->Load(Infile);
		this->AddStatement(st);
		count--;
	}

	Infile >> count2;
	while (count2>0)
	{
		ConPtr = new Connector(this);
		ConPtr->Load(Infile);
		Add_Connector(ConPtr);
		count2--;
	}
}

vector<Statement*>* ApplicationManager::get_deleted_statements()
{
	return &DeletedStatements;
}
vector<Connector*>* ApplicationManager::get_deleted_Connectors()
{
	return &DeletedConnectors;
}

void ApplicationManager::RemoveConnector(Connector * pConn)
{
	if (pConn == NULL)
		return;
	int in_conns = 0;  //to detect the num of incoming conectors to a statemant
	for (int i = 0; i<ConnCount; i++)
	{
		if (ConnList[i] == pConn)
		{
			DeletedConnectors.push_back(pConn);
			for (int k = 0; k < ConnCount; k++)
			{
				if (ConnList[k]->getDstStat() == pConn->getDstStat())
					in_conns++;
			}
			/*
			if (in_conns==1)
			pConn->getDstStat()->SetConnected(false);
			*/
			if (pConn->getSrcStat() != NULL && !dynamic_cast<Conditional *>(pConn->getSrcStat()))
				pConn->getSrcStat()->SetConnect(NULL);
			else
			{
				if (dynamic_cast<Conditional *>(pConn->getSrcStat())->get_YConn() == pConn)
				{
					dynamic_cast<Conditional *>(pConn->getSrcStat())->set_Yout(NULL);
				}
				else
					dynamic_cast<Conditional *>(pConn->getSrcStat())->set_Nout(NULL);
			}
			ConnList[i] = ConnList[ConnCount - 1];
			ConnList[ConnCount - 1] = NULL;
			break;
		}
	}
	ConnCount--;
}

vector <Connector*>* ApplicationManager::GetSelectedConnectors()
{
	return &pSelectedConnectors;
}
void ApplicationManager::unSelectConnectors()
{
	int i = pSelectedConnectors.size() - 1;
	while (i >= 0){
		if (pSelectedConnectors[i] != NULL)
			pSelectedConnectors[i]->set_selected(false);
		i--;
	}
	pSelectedStatements.clear();

}
void ApplicationManager::addSelectedConnector(Connector *pConn)
{

	if (!pConn->get_selected()){
		pSelectedConnectors.push_back(pConn);
		pConn->set_selected(true);
		pConn->Print_info(pOut);
	}
	else
		unSelectConnector(pConn);
}
void ApplicationManager::unSelectConnector(Connector *pConn)
{
	int i = pSelectedConnectors.size() - 1;
	while (i >= 0){
		if (pSelectedConnectors[i] == pConn){
			pSelectedConnectors[i]->set_selected(false);
			pSelectedConnectors.erase(pSelectedConnectors.begin() + i);
		}
		i--;
	}
}

bool ApplicationManager::CheckValidation() const{

	if (StatCount == 0){
		pOut->PrintMessage("It looks like there are no statements at all. !!!!");
		return false;
	}

	int startnum = 0, endnum = 0;
	bool valid = true;

	for (int i = 0; i < StatCount; i++){
		if (dynamic_cast<Start*>(StatList[i]))
			startnum++;
		else if (dynamic_cast<End*>(StatList[i]))
			endnum++;

		//check the statement to be connected as a source
		if (StatList[i]->GetConnect() == NULL && !(dynamic_cast<End*>(StatList[i])) && !(StatList[i]->GetCut()) && !(dynamic_cast<Conditional*>(StatList[i]))){
			valid = false;
			break;
		}
		//check the statement to be connected as a destination
		if (!(StatList[i]->GetConnected()) && !(dynamic_cast<Start*>(StatList[i]))){
			valid = false;
			break;
		}
		if (dynamic_cast<Conditional*>(StatList[i])){
			Conditional * p = (Conditional*)StatList[i];
			if (p->get_NConn() == NULL || p->get_YConn() == NULL){
				valid = false;
				break;
			}
		}
	}
	if (startnum != 1 || endnum != 1){
		valid = false;
	}

	if (!valid)
		pOut->PrintMessage("Invalid Chart !! check the statements and again.");
	else
		pOut->PrintMessage("Good Work , The Chart is Valid");
	
	return valid;

}

void ApplicationManager::RunChart(){
	pOut->ClearVariablesArea();
	Connector*p;
	bool error = false;
	if (!CheckValidation())
		return;

		for (int i = 0; i < get_stat_count(); i++)
		if (dynamic_cast<Start*>(StatList[i]))
		{
			p = StatList[i]->GetConnect();
			break;
		}

		while (p != NULL)
		{
			if (p->getDstStat()->Simulate())
			{
				if (dynamic_cast<Conditional*>(p->getDstStat()))
				{
					Conditional*pcond = (Conditional*)p->getDstStat();
					if (pcond->GetCond())
						p = pcond->get_YConn();
					else
						p = pcond->get_NConn();
				}
				else
					p = p->getDstStat()->GetConnect();
			}
			else
			{
				error = true;
				TOutput = "";
				break;
			}
		}

		if (!error)
		{
			map<string, double> ::iterator it;
			
			int x=1210; int y=180;
			for (it = variables.begin(); it != variables.end(); it++)
				{
					string out = "";
					ostringstream T;
					T<<it->second; 
					out+=(it->first + " = " + T.str());
					pOut->OutVariables(x,y,out);
			    }
		}
	
	TOutput = "";
}

void ApplicationManager::SaveChart(ofstream &OutFile)
{
	OutFile << StatCount << endl;
	for (int i = 0; i < StatCount; i++)
	{
		if (StatList[i] != NULL)
			StatList[i]->Save(OutFile);
	}
	OutFile << ConnCount << endl;
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i] != NULL)
			ConnList[i]->Save(OutFile);
	}
}

vector<Statement*>* ApplicationManager::GetMultiCopy()
{
	return &pMultiCopy;
}
void ApplicationManager::SetMultiCopy(vector<Statement*> v1)
{
	pMultiCopy = v1;
}

//new
vector<Statement*>* ApplicationManager::GetMultiCut()
{
	return &pMultiCut;
}
void ApplicationManager::SetMultiCut(vector<Statement*> v1)
{
	pMultiCut = v1;
}

void ApplicationManager::multi_drag()
{

	pOut->getwindow()->FlushKeyQueue();
	int iXOld = 0, iYOld = 0;
	Statement * ptr = NULL;
	vector<Point> l_corns;     //for saving original corners
	for (int i = 0; i < pSelectedStatements.size(); i++)
	{
		l_corns.push_back(pSelectedStatements[i]->get_lcorner());
	}
	Point p;     //current point
	bool Drag = 0;      bool draw = true;
	char c;
	while (pIn->getwindow()->GetKeyPress(c) != ESCAPE)
	{
		pOut->PrintMessage("press \"ESC\" to cancel moving action");
		draw = true;
		ptr = NULL;
		if (Drag == false)
		{
			if (pIn->getwindow()->GetButtonState(LEFT_BUTTON, p.x, p.y) == BUTTON_DOWN)
			{
				//if (((iX > RectULX) && (iX < (RectULX + RectWidth))) && ((iY > RectULY) && (iY < (RectULY + RectWidth))))
				for (int i = 0; i < pSelectedStatements.size(); i++)
				{
					if (pSelectedStatements[i]->check_range(p))
					{
						ptr = pSelectedStatements[i];
						break;
					}
				}
				if (ptr)
				{
					Drag = true;
					iXOld = p.x;     iYOld = p.y;
					for (int i = 0; i < pSelectedStatements.size(); i++)
					{
						pSelectedStatements[i]->SetInlet();
						if (dynamic_cast<Conditional *>(pSelectedStatements[i]) == false)
						{
							pSelectedStatements[i]->SetOutlet();
						}
						else
						{
							dynamic_cast<Conditional *>(pSelectedStatements[i])->calc_nout();
							dynamic_cast<Conditional *>(pSelectedStatements[i])->calc_yout();
						}
					}
					for (int i = 0; i < ConnCount; i++)
					{
						ConnList[i]->get_path().clear();
						ConnList[i]->make_connector(ConnList[i]->getSrcStat(), ConnList[i]->getDstStat(), this);
					}
					UpdateInterface();
					pOut->ClearStatusBar();
				}
			}
		}
		else
		{
			if (pIn->getwindow()->GetButtonState(LEFT_BUTTON, p.x, p.y) == BUTTON_UP)
			{
				Drag = false;
			}
			else
			{
				if (p.x != iXOld)
				{
					for (int i = 0; i < pSelectedStatements.size(); i++)
					{
						pSelectedStatements[i]->get_lcorner().x = pSelectedStatements[i]->get_lcorner().x + (p.x - iXOld);
					}
					iXOld = p.x;
				}
				if (p.y != iYOld)
				{
					for (int i = 0; i < pSelectedStatements.size(); i++)
					{
						pSelectedStatements[i]->get_lcorner().y = pSelectedStatements[i]->get_lcorner().y + (p.y - iYOld);
					}
					iYOld = p.y;
				}
				for (int i = 0; i < pSelectedStatements.size(); i++)
				{
					pSelectedStatements[i]->SetInlet();
					if (dynamic_cast<Conditional *>(pSelectedStatements[i]) == false)
					{
						pSelectedStatements[i]->SetOutlet();
					}
					else
					{
						dynamic_cast<Conditional *>(pSelectedStatements[i])->calc_nout();
						dynamic_cast<Conditional *>(pSelectedStatements[i])->calc_yout();
					}
				}

				for (int i = 0; i < ConnCount; i++)
				{
					ConnList[i]->get_path().clear();
					ConnList[i]->make_connector(ConnList[i]->getSrcStat(), ConnList[i]->getDstStat(), this);
				}
				UpdateInterface();
				pOut->ClearStatusBar();
			}
		}
	}
	for (int i = 0; i < pSelectedStatements.size(); i++)
	{
		draw = pIn->candraw(pSelectedStatements[i]->get_lcorner(), this, pSelectedStatements[i]->get_height(), pSelectedStatements[i]->get_width(), pSelectedStatements[i]->get_ID());
		if (!draw)  break;
	}
	if (draw)
	{
		pOut->PrintMessage("Moved successfully");
	}
	else
	{
		for (int i = 0; i < pSelectedStatements.size(); i++)
		{
			pSelectedStatements[i]->get_lcorner() = l_corns[i];
			pSelectedStatements[i]->SetInlet();
			if (dynamic_cast<Conditional *>(pSelectedStatements[i]) == false)
			{
				pSelectedStatements[i]->SetOutlet();
			}
			else
			{
				dynamic_cast<Conditional *>(pSelectedStatements[i])->calc_nout();
				dynamic_cast<Conditional *>(pSelectedStatements[i])->calc_yout();
			}
		}
		for (int i = 0; i <ConnCount; i++)
		{
			ConnList[i]->get_path().clear();
			ConnList[i]->make_connector(ConnList[i]->getSrcStat(), ConnList[i]->getDstStat(), this);
		}
		UpdateInterface();
		pOut->ClearStatusBar();
		pOut->PrintMessage("intersection may happen in this position, this isn't allowed");
	}
	for (int i = 0; i < pSelectedStatements.size(); i++)
	{
		pSelectedStatements[i]->SetSelected(0);
	}
	for (int i = 0; i < pSelectedConnectors.size(); i++)
	{
		pSelectedConnectors[i]->set_selected(0);
	}
	pSelectedStat = NULL;
	pSelectedConnectors.clear();
	pSelectedStatements.clear();
	pOut->getwindow()->FlushMouseQueue();
}

void ApplicationManager::GenerateCodeFile(ofstream &OutFile)
{
	if (CheckValidation())
	{
		OutFile << "#include <iostream>" << endl;
		OutFile << "using namespace std;" << endl << endl;
		StatList[0]->GenerateCode(OutFile);

		for (int i = 0; i < get_stat_count(); i++)
		{
			if (dynamic_cast<SmplAssign*>(StatList[i]))
			{
				SmplAssign*temp = (SmplAssign*)StatList[i];
				if (variables.find(temp->GetLHS()) == variables.end())
					variables[temp->GetLHS()] = 0;
				//OutFile << temp->getLHS();
			}
			if (dynamic_cast<VarAssign*>(StatList[i]))
			{
				VarAssign*temp = (VarAssign*)StatList[i];
				if (variables.find(temp->GetLHS()) == variables.end())
					variables[temp->GetLHS()] = 0;
				if (variables.find(temp->GetRHS()) == variables.end())
					variables[temp->GetRHS()] = 0;
				//OutFile << temp->getLHS() << " "<<temp->getRHS();
			}
			if (dynamic_cast<Conditional*>(StatList[i]))
			{
				Conditional*temp = (Conditional*)StatList[i];
				if (variables.find(temp->GetLHS()) == variables.end())
					variables[temp->GetLHS()] = 0;
				if (!(StatList[i]->CheckValue(temp->GetRHS())))
				{
					if (variables.find(temp->GetRHS()) == variables.end())
						variables[temp->GetRHS()] = 0;
				}
			}
			if (dynamic_cast<SingleOperator*>(StatList[i]))
			{
				SingleOperator*temp = (SingleOperator*)StatList[i];
				if (variables.find(temp->GetLHS()) == variables.end())
					variables[temp->GetLHS()] = 0;
				if (!(StatList[i]->CheckValue(temp->GetRHS1())))
				{
					if (variables.find(temp->GetRHS1()) == variables.end())
						variables[temp->GetRHS1()] = 0;
				}
				if (!(StatList[i]->CheckValue(temp->GetRHS2())))
				{
					if (variables.find(temp->GetRHS2()) == variables.end())
						variables[temp->GetRHS2()] = 0;
				}
			}
			if (dynamic_cast<Read_Stat*>(StatList[i]))
			{
				Read_Stat*temp = (Read_Stat*)StatList[i];
				int j = temp->Getvar().size() - 1;
				while (j >= 0)
				{
					if (variables.find(temp->Getvar().operator[](j)) == variables.end())
						variables[temp->Getvar().operator[](j)] = 0;
					j--;
				}
			}
			if (dynamic_cast<Write_Stat*>(StatList[i]))
			{
				Write_Stat*temp = (Write_Stat*)StatList[i];
				int j = temp->Getvar().size() - 1;
				while (j >= 0)
				{
					if (variables.find(temp->Getvar().operator[](j)) == variables.end())
						variables[temp->Getvar().operator[](j)] = 0;
					j--;
				}
			}
		}
		if (variables.size()>0)
			OutFile << "  double ";
		map<string, double> ::iterator it;
		for (it = variables.begin(); it != variables.end(); it++)
		{
			if (it != variables.begin())
				OutFile << ",";
			OutFile << it->first;
		}
		variables.clear();
		OutFile << ";" << endl;
		Connector*p, *Ntemp;
		for (int i = 0; i < get_stat_count(); i++)
		if (dynamic_cast<Start*>(StatList[i]))
		{
			p = StatList[i]->GetConnect();
			break;
		}
		bool flag = false;
		Ntemp = NULL;
		while (p != NULL)
		{
			if (dynamic_cast<Conditional*>(p->getDstStat()))
			{
				Conditional*pcond = (Conditional*)p->getDstStat();
				if (pcond->Is_Generated() == false)
				{
					pcond->GenerateCode(OutFile);
					flag = true;
				}
				//else if (!pcond->Is_Loop())
				//OutFile << "else" << endl << "{" << endl;
				p = pcond->get_YConn();
				Ntemp = pcond->get_NConn();
			}
			else
			{
				if ((dynamic_cast<Conditional*>(p->getSrcStat())))
				{
					Conditional*pcond = (Conditional*)p->getSrcStat();
					if (p == Ntemp && pcond->getLoop()==false)
						OutFile <<endl<< "  }" << endl << "  else" << endl << "  {" << endl;
				}
				/*if (dynamic_cast<Conditional*>(p->getSrcStat()) && p->getDstStat()->Is_Generated())
				p = Ntemp;*/
				//if (!p->getDstStat()->Is_Generated())
				p->getDstStat()->GenerateCode(OutFile);
				if ((dynamic_cast<End*>(p->getDstStat()) && flag == true) || (p->getDstStat()->Is_Generated() && flag == true))
				{
					p = p->getDstStat()->GetConnect();
					p->getDstStat()->GenerateCode(OutFile);
					p = Ntemp;
					flag = false;
				}
				else
					p = p->getDstStat()->GetConnect();
			}
		}
		OutFile << endl << "  }"<<endl<<"}";
	}
	else
		pOut->PrintMessage("Can't Generate code,Invalid chart!");
}

//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<StatCount; i++)
		delete StatList[i];
	for(int i=0; i<ConnCount; i++)
		delete ConnList[i];
	delete pIn;
	delete pOut;
	
}
