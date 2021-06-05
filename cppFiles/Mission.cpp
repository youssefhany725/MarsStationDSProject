#include "..\hFiles\Mission.h"
Mission::Mission(missiontype a,int ed, int id, int tloc, int mdur, int sig)
{
	TYP = a;
	ID = id;
	Rassigned = nullptr;
	CD = -1;
	ED = ed;
	TLOC = tloc;
	MDUR = mdur;
	SIG = sig;
	WD = 0;
}
void Mission::Assign(Rover* R,int cd)
{
	Rassigned = R;
	CD = cd + MDUR + ((TLOC/R->getspeed()) / 25);
	WD = CD - ED;
}
int Mission::getcmpday()
{
	return CD;
}
Rover* Mission::getRover()
{
	return Rassigned;
}
missiontype Mission::gettype()
{
	return TYP;
}
int Mission::getPkey() {
	return 0;
}
int Mission::getid()
{
	return ID;
}
int Mission::getMDUR()
{
	return MDUR;
}

