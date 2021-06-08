#pragma once
#include "linkedqueue.h"
#include "Linkedlist.h"
#include "priorityqueue.h"
#include "Event.h"
#include "Mission.h"
#include"Rover.h"
class MarsStation
{
private:
	int CurrentDay;
	priorityqueue<Event*> EventList;
	LinkedQueue<Mission*> PMissionList;
	priorityqueue<Mission*> EMissionList;
	priorityqueue<Mission*> InExMissions;
	priorityqueue<Rover*> Checkup;
	LinkedQueue<Rover*> MaintenanceE;
	LinkedQueue<Rover*> MaintenanceP;
	LinkedQueue<Rover*> PRoverList;
	LinkedQueue<Rover*> ERoverList;
	LinkedQueue<Mission*>CompletedMissions;
	void inputFromFile();
	void outputToFile();
	void MExecute();
	void Assign();
	void Prints();
	void Finish();
	void Endday();
	void Interface(int);
public:
	MarsStation();
	void Sim();
	~MarsStation();
};
