#include "Start.h"

Start::Start(ApplicationManager * AM, string txt, Point l_cor, int width, int height, int t_width, int t_height)
: Statement(AM,txt,l_cor,width,height,t_width,t_height){

	pConn = NULL;
	calc_l_corner();

}

void Start::Draw(Output* pOut) const {

	pOut->Draw_st_end(l_corner, UI.start_end_width, UI.start_end_height, Text , Selected);

}

bool Start::Edit(){

	Point x;
	pOut->ClearStatusBar();
	pOut->PrintMessage("Can't be edited , chick any where");
	pIn->GetPointClicked(x);
	pOut->ClearStatusBar();
	return false;

}

void Start::GenerateCode(ofstream &OutFile){

	OutFile << "int main()" << endl<<"{"<<endl;
	SetGenerated(true);
}

bool Start::check_range(Point p)
{
	Point centre;
	centre.x = l_corner.x + width / 2;
	centre.y = l_corner.y + height / 2;
	if ((double((p.y - centre.y) * (p.y - centre.y)) / double(height*height*0.25)) + (double((p.x - centre.x) * (p.x - centre.x)) / double(width*width*0.25)) > 1)
		return false;
	else
		return true;
}

void Start::Save(ofstream &OutFile)
{
	OutFile << "STRT"<<"           "<< ID << "  " << l_corner.x << "  " << l_corner.y<<" ";

	OutFile << "\"" << comment << "\"" << endl;
}


void Start::Load(ifstream & Infile)
{
	Infile >> ID >> l_corner.x >> l_corner.y;
	Text = "Start";
	getline(Infile, comment);
	UpdateStatementText();

	set_stat_dim(Text);
	SetInlet();
	SetOutlet();
	comment.erase(comment.begin());
	comment.erase(comment.end()-1);
}

void Start::calc_l_corner()
{
	AppMan->GetInput()->calc_stat_corner(inlet, l_corner, width);
}

void Start::PrintInfo(Output * pOut)
{
	pOut->PrintMessage(comment);
}

void Start::set_stat_dim(string str)
{
	pIn->set_ellipse_Dim(Text, width, height, t_width, t_height);
}

Connector* Start ::GetConnect(){
	return pConn;
}
void Start :: SetConnect(Connector*p){
	pConn =p;
}

bool Start::Simulate(){
	return true;
}