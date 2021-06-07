#include "..\hFiles\Mission.h"
Mission::Mission(missiontype typ, int fd, int id, int tloc, int mdur, int sig)
{
	TYP = typ;
	ID = id;
	Rassigned = nullptr;
	CD = -1;
	FD = fd;
	TLOC = tloc;
	MDUR = mdur;
	SIG = sig;
	WD = 0;
	Epriority = 0;
}
void Mission::Assign(Rover* R, int cday)
{
	Rassigned = R;
	CD = cday + MDUR + 2 * ((TLOC / R->getspeed()) / 25);
	WD = cday - FD;
}
int Mission::getcmpday()
{
	return CD;
}
int Mission::getWD()
{
	return WD;
}
int Mission::getFD()
{
	return FD;
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