#include "..\hFiles\Event.h"
#include "..\hFiles\Mission.h"
Event::Event(type typ,int ed,int id,int tloc,int mdur,int sig)
{
	TYP = typ; ED = ed; ID = id;  TLOC = tloc;  MDUR = mdur;  SIG = sig; M = nullptr;
}
void Event::Execute()
{
	M=new Mission(TYP,ED, ID, TLOC, MDUR, SIG);
}
Mission* Event::getMission()
{
	return M;
}
int Event::getday()
{
	return ED;
}