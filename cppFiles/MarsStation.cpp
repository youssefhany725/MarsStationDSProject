#include "..\hFiles\MarsStation.h"
#include "..\hFiles\Mission.h"
#include "..\hFiles\Event.h"

MarsStation::MarsStation()
{
	CurrentDay = 0;
	UserI.input(this);
}

void MarsStation::StationInput(LinkedQueue<Event>*)
{

}

void MarsStation::MExecute()
{
	Event *E;
	bool b = EventList.peek(E);
	if (b && CurrentDay == E->getday())
	{
		EventList.dequeue(E);
		E->Execute();
		Mission* M = E->getMission();
		if (M->gettype() == emergency)
			EMissionList.enqueue(M,M->getPkey());//priority needed
		else
			PMissionList.enqueue(M);
	}
}

void MarsStation::Assign()
{
	Mission* M;
	Rover* R;
	while (EMissionList.peek(M))//Emergency Assign
	{
		if (!ERoverList.isEmpty())
		{
			ERoverList.dequeue(R);
			EMissionList.dequeue(M);
			M->Assign(R,CurrentDay);
			InExMissions.enqueue(M,-M->getcmpday());
			InExRovers.enqueue(R, -M->getcmpday());
		}
		else if (!PRoverList.isEmpty())
		{
			PRoverList.dequeue(R);
			EMissionList.dequeue(M);
			M->Assign(R,CurrentDay);
			InExMissions.enqueue(M,-M->getcmpday());
			InExRovers.enqueue(R,-M->getcmpday());
		}
		else
		{
			break;
		}
	}
	while (PMissionList.peek(M))//Polar Assign
	{
		if (!PRoverList.isEmpty())
		{
			PRoverList.dequeue(R);
			PMissionList.dequeue(M);
			M->Assign(R, CurrentDay);
			InExMissions.enqueue(M, -M->getcmpday());
			InExRovers.enqueue(R, -M->getcmpday());
		}
		else
		{
			break;
		}
	}
}
void MarsStation::Interactive()
{
	cout << "CurrentDay: " << CurrentDay << endl;
	string s;
	s = "Waiting Missions: ";
	UserI.MPrintDef(EMissionList, '[', ']',s);
	UserI.MPrintDef(PMissionList, '(', ')');
	//inEx
	Mission* M;
	LinkedQueue<Mission*>temp;
	while (InExMissions.dequeue(M))
		temp.enqueue(M);
	LinkedQueue<Mission*> temp2(temp);
	while (temp.dequeue(M))
		InExMissions.enqueue(M,-M->getcmpday());

	s = "In-Execution Missions/Rovers: ";
	UserI.PrintInex(temp2, s);
	s = "Available Rovers: ";
	UserI.RPrintDef(ERoverList, '[', ']', s);
	UserI.RPrintDef(PRoverList, '(', ')');
	s = "Completed Missions: ";
	UserI.PrintComp(CompletedMissions, s);
}
void MarsStation::Finish()
{
	Mission* m;
	Rover* R;
	while(InExMissions.peek(m)&&m->getcmpday()==CurrentDay)
	{
		InExMissions.dequeue(m);
		CompletedMissions.enqueue(m);
	        R = m->getRover();
		R->setcheckuptime();
		if (R->getcheckuptime())
		{
		if(R->getrovertype()==polarrover)
		{
			checkP.enqueue(R);
			R->setCheckupEndDate(CurrentDay+R->getcheckupdays());
		}
		else
		{
			checkE.enqueue(R);
			R->setCheckupEndDate(CurrentDay + R->getcheckupdays());
		}

		}
		else
		{
			if (R->getrovertype() == polarrover)
			{
				PRoverList.enqueue(R);
			}
			else
			{
				ERoverList.enqueue(R);
			}
		}
	}
	while(checkP.peek(R)&&R->getCheckupEndDate()==CurrentDay)
	{
		PRoverList.enqueue(R);
	}	
	while (checkE.peek(R) && R->getCheckupEndDate() == CurrentDay)
	{
		ERoverList.enqueue(R);
	}

}
void MarsStation::Endday()
{
	++CurrentDay;
}

void MarsStation::AddEvent(missiontype missionType, int eventDay, int ID, int targetLocation, int missionDuration, int significance)
{
	Event* e = new Event(missionType, eventDay, ID, targetLocation, missionDuration, significance);
	EventList.enqueue(e);
}

void MarsStation::AddRover(rovertype roverType, int ID)
{
	Rover* r = new Rover(roverType, ID);
	if (roverType == polarrover) PRoverList.enqueue(r);
	else ERoverList.enqueue(r);
}

void MarsStation::setMissionsToCheckup(int n)
{
	Rover::setMissionsToCheckup(n);
}

void MarsStation::setPolar_checkupDuration(int n)
{
	Rover::setPolar_checkupDuration(n);
}

void MarsStation::setEmergency_checkupDuration(int n)
{
	Rover::setEmergency_checkupDuration(n);
}

void MarsStation::setPolar_speed(int n)
{
	Rover::setPolar_speed(n);
}

void MarsStation::setEmergency_speed(int n)
{
	Rover::setEmergency_speed(n);
}



