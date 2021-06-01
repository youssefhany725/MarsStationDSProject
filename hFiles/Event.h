#pragma once
#include "Defs.h"
#include "linkedqueue.h"
#include "priorityqueue.h"
#include "Mission.h"
class Event
{
private:
	missiontype TYP; int ED; int ID; int TLOC; int MDUR; int SIG;
	Mission* M;
public:
	Event(missiontype TYP = polar, int ED = 0, int ID = 0, int TLOC = 0, int MDUR = 0, int SIG = 0);
	Mission* getMission();
	int getday();
	void Execute();
};
