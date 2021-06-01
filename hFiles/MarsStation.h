#pragma once
#include "linkedqueue.h"
#include "Linkedlist.h"
#include "priorityqueue.h"
#include "Event.h"
#include "Mission.h"
#include"Rover.h"
#include "UI.h"
class MarsStation
{
private:
	int CurrentDay;
	UI UserI;
	LinkedQueue<Event*> EventList;
	LinkedQueue<Mission*> PMissionList;
	priorityqueue<Mission*> EMissionList;
	priorityqueue<Mission*> InExMissions;
	LinkedQueue<Mission*> CMissions;
	LinkedQueue<Rover*>checkE;
	LinkedQueue<Rover*>checkP;
	LinkedQueue<Rover*> PRoverList;
	LinkedQueue<Rover*> ERoverList;
	priorityqueue<Rover*> InExRovers;
public:
	MarsStation();
	void StationInput(LinkedQueue<Event>*);
	void MExecute();
	void Assign();
	void Complete();
	void AddEvent(missiontype missionType, int eventDay, int ID, int targetLocation, int missionDuration, int significance);
	void AddRover(rovertype roverType, int ID);
	//void AddRover(rovertype roverType, int checkupDuration, int speed);
	void setMissionsToCheckup(int n);
	void setPolar_checkupDuration(int n);
	void setEmergency_checkupDuration(int n);
	void setPolar_speed(int n);
	void setEmergency_speed(int n);
	void incrimintcurrentday();
};


