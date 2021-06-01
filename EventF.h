#pragma once
#include "Event.h"
#include "Mission.h"
class EventF :public Event
{
private:
	int TYP; int ED; int ID; int TLOC; int MDUR; int SIG;
	Mission* M;
public:
	EventF(int TYP=0,int ED=0,int ID=0,int TLOC=0,int MDUR=0,int SIG=0);
	Mission *getMission();
	int getday();
	void Execute();
};