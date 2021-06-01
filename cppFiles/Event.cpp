#include "..\hFiles\Event.h"
#include "..\hFiles\Mission.h"
Event::Event(missiontype a,int b,int c,int d,int e,int f)
{
	TYP = a; ED = b; ID = c;  TLOC = d;  MDUR = e;  SIG = f; M = nullptr;
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
