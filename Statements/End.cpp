#include "End.h"


End::End(ApplicationManager * AM, string txt, Point l_cor, int width, int height, int t_width, int t_height)
: Statement(AM, txt, l_cor, width, height, t_width, t_height){

	pConn = NULL;
	calc_l_corner();

}

void End::Draw(Output* pOut) const {

	pOut->Draw_st_end(l_corner, width, height, Text, Selected);

}

bool End::Edit(){

	Point x;
	pOut->ClearStatusBar();
	pOut->PrintMessage("Can't be edited , chick any where");
	pIn->GetPointClicked(x);
	pOut->ClearStatusBar();
	return false;

}

void End::UpdateStatementText(){

}

void End::GenerateCode(ofstream &OutFile){

	OutFile << "  return 0;";
	SetGenerated(true);
}

bool End::check_range(Point p)
{
	Point centre;
	centre.x = l_corner.x + width / 2;
	centre.y = l_corner.y + height / 2;
	if ((double((p.y - centre.y) * (p.y - centre.y)) / double(height*height*0.25)) + (double((p.x - centre.x) * (p.x - centre.x)) / double(width*width*0.25)) > 1)
		return false;
	else
		return true;
}

void End::Save(ofstream &OutFile)
{
	OutFile << "END"<<"             "<< ID << "  " << l_corner.x << "  " << l_corner.y<<" ";
	
	OutFile << "\"" << comment << "\"" << endl;
}


void End::Load(ifstream & Infile)
{
	Infile >> ID >> l_corner.x >> l_corner.y;
	getline(Infile, comment);
	Text = "End";
	set_stat_dim(Text);
	SetInlet();
	SetOutlet();
	comment.erase(comment.begin());
	comment.erase(comment.end()-1);
	
}

void End::calc_l_corner()
{
	AppMan->GetInput()->calc_stat_corner(inlet, l_corner, width);
}

void End::PrintInfo(Output * pOut)
{
	pOut->PrintMessage(comment);
}

void End::set_stat_dim(string str)
{
	pIn->set_ellipse_Dim(Text,width,height,t_width,t_height);
}

bool End::Simulate(){
	return true;
}
Connector* End ::GetConnect(){
	return pConn;
}
void End:: SetConnect(Connector*p){
	pConn = p;
}
