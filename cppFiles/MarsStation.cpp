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
			//InExRovers.enqueue(R, -M->getcmpday());
		}
		else if (!PRoverList.isEmpty())
		{
			PRoverList.dequeue(R);
			EMissionList.dequeue(M);
			M->Assign(R,CurrentDay);
			InExMissions.enqueue(M,-M->getcmpday());
			//InExRovers.enqueue(R,-M->getcmpday());
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
			//InExRovers.enqueue(R, -M->getcmpday());
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
	Mission* M;
	Rover* R;
	//-------------------------Launch------------------------------
	s = "Waiting Missions: ";
	LinkedQueue<Mission*>templist1(EMissionList);
	LinkedQueue<Mission*>templist2(PMissionList);
	while (templist2.dequeue(M)) { templist1.enqueue(M); }
	UserI.PrintDefM(templist1,s);
	//-------------------------Waiting----------------------------
	s = "In-Execution Missions/Rovers: ";
	priorityqueue<Mission*>temp;
	temp = InExMissions;
	/*while (InExMissions.dequeue(M))
		temp.enqueue(M);
	LinkedQueue<Mission*> temp2(temp);
	while (temp.dequeue(M))
		InExMissions.enqueue(M,-M->getcmpday());*/
	UserI.PrintInex(temp, s);
	//-------------------------Execution----------------------------
	s = "Available Rovers: ";
	LinkedQueue<Rover*>templist3(ERoverList);
	LinkedQueue<Rover*>templist4(PRoverList);
	while (templist4.dequeue(R)) { templist3.enqueue(R); }
	UserI.PrintDefR(templist3, s);
	//------------------------AvailableRovers------------------------
	s = "In-Checkup Rovers: ";
	priorityqueue<Rover*> temp2=Checkup;
	LinkedQueue<Rover*> temp3(temp2);
	UserI.PrintDefR(temp3, s);
	//------------------------CheckupRovers--------------------------
	s = "Completed Missions: ";
	UserI.PrintDefM(CompletedMissions, s);
	//------------------------CompletedMissions---------------------
}
void MarsStation::Finish()
{
	Mission* M;
	Rover* R;
	while (InExMissions.peek(M) && M->getcmpday() == CurrentDay)
	{
		InExMissions.dequeue(M);
		CompletedMissions.enqueue(M);
		R = M->getRover();
		R->setcheckuptime();
		if (R->getcheckuptime())
		{
			R->setCheckupEndDate(CurrentDay + R->getcheckupdays());
			Checkup.enqueue(R,-R->getCheckupEndDate());
		}
	}
	while (Checkup.peek(R) && R->getCheckupEndDate() == CurrentDay)
	{
		if (R->getrovertype() == emergencyrover)
		{
			ERoverList.enqueue(R);
		}
		else
		{
			PRoverList.enqueue(R);
		}
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



