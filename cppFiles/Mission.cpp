#include "..\hFiles\Mission.h"
Mission::Mission(missiontype a,int ed, int c, int d, int e, int f, int w1)
{
	TYP = a;
	ID = c;
	Rassigned = nullptr;
	CD = -1;
	ED = ed;
	TLOC = d;
	MDUR = e;
	SIG = f;
	WD = w1;
}
void Mission::Assign(Rover* R,int cd)
{
	Rassigned = R;
	CD = cd + MDUR + ((TLOC/R->getspeed()) / 25);
}
int Mission::getcmpday()
{
	return CD;
}
int Mission::gettype()
{
	return TYP;
}
int Mission::getPkey() {
	return 0;
}
int Mission::getMDUR()
{
	return MDUR;
}

void Mission::setwatingday(int w2)
{
	WD = w2-getcmpday();
}

int Mission::getwaitingday()
{
	return WD;
}

void Mission::getRover(Rover*&r)
{
	r = Rassigned;
}

