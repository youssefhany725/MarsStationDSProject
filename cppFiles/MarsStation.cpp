#include "..\hFiles\MarsStation.h"
#include "..\hFiles\Mission.h"
#include "..\hFiles\Event.h"
#include "..\hFiles\UI.h"

void MarsStation::inputFromFile()
{
	ifstream inputFile;
	UI::InputActionParameters(inputFile);
	int x, P, E, SP, SE, N, CP, CE, Ev, ED, ID, TLOC, MDUR, SIG;
	char c, TYP;
	inputFile >> x >> P >> E;
	inputFile >> x >> SP >> SE;
	inputFile >> N >> x >> CP >> CE;
	if ((P == 0 && E == 0) || SP <= 0 || SE <= 0 || N <= 0 || CP <= 0 || CE <= 0) {
		cout << "The file you entered is invalid, please try again\n";
		inputFromFile();
	}
	else if (P == 0) {
		char c1;
		int fail = 0;
		while (inputFile >> c1)
			if (c1 == 'P') {
				inputFile.unget();
				inputFile.unget();
				inputFile.unget();
				inputFile >> c1;
				if (c1 == 'F') {
					fail = 1;
					break;
				}
				inputFile >> c1;
			}
		if (fail) {
			cout << "The file you entered is invalid, please try again\n";
			inputFromFile();
		}
		else {
			inputFile.clear();
			inputFile.seekg(21);
		}
	}
	for (int i = 1; i <= P; i++) {
		Rover* r = new Rover(polar, i);
		PRoverList.enqueue(r);
	}
	for (int i = 1; i <= E; i++) {
		Rover* r = new Rover(emergency, i + P);
		ERoverList.enqueue(r);
	}
	Rover::setPolar_speed(SP);
	Rover::setEmergency_speed(SE);
	Rover::setMissionsToCheckup(N);
	Rover::setPolar_checkupDuration(CP);
	Rover::setEmergency_checkupDuration(CE);
	inputFile >> x;
	inputFile >> Ev;
	streamoff l = inputFile.tellg();
	char c1;
	int fail = 0;
	int LineCount = 0;
	while (inputFile.get(c1))
		if (c1 == '\n') {
			LineCount++;
		}
	inputFile.clear();
	inputFile.seekg(l);
	if (Ev<0 || Ev>LineCount) Ev = LineCount;
	for (int i = 0; i < Ev; i++) {
		inputFile >> c;
		if (c == 'F') {
			inputFile >> TYP;
			if (TYP != 'E' && TYP != 'P') {
				inputFile.ignore(128, '\n');
				continue;
			}
			inputFile >> ED;
			inputFile >> ID;
			inputFile >> TLOC;
			inputFile >> MDUR;
			inputFile >> SIG;
			Event* e = new Event((TYP == 'E') ? emergency : polar, ED > 0 ? ED : 1, ID, TLOC > 0 ? TLOC : 1, MDUR > 0 ? MDUR : 1, SIG);
			EventList.enqueue(e, -ED);
		}
		inputFile.ignore(128, '\n');
	}
	inputFile.close();
}

void MarsStation::outputToFile()
{
	ofstream outputFile;
	UI::OutputActionParameters(outputFile);
	int Mcount = CompletedMissions.getCount();
	int TotalWD = 0, TotalED = 0, PMcount = 0;
	if (Mcount != 0) {
		outputFile << "CD\tID\tFD\tWD\tED\n";
		Mission* M, * M1 = nullptr;
		int CD = -1;
		do {
			CompletedMissions.dequeue(M);
			CompletedMissions.enqueue(M);
			if (CD == -1) M1 = M;
			priorityqueue<Mission*> M_Q;
			CD = M->getcmpday();
			int FD = M->getFD();
			int WD = M->getWD();
			int ED = CD - FD - WD;
			M_Q.enqueue(M, -ED);
			while (CompletedMissions.peek(M) && M->getcmpday() == CD && M != M1) {
				CompletedMissions.dequeue(M);
				CompletedMissions.enqueue(M);
				int CD1 = M->getcmpday();
				int FD1 = M->getFD();
				int WD1 = M->getWD();
				int ED1 = CD1 - FD1 - WD1;
				M_Q.enqueue(M, -ED);
			}
			while (M_Q.dequeue(M)) {
				int CD1 = M->getcmpday();
				int FD1 = M->getFD();
				int WD1 = M->getWD();
				int ID1 = M->getid();
				int ED1 = CD1 - FD1 - WD1;
				TotalWD += WD1;
				TotalED += ED1;
				if (M->gettype() == polar) PMcount++;
				outputFile << CD1 << '\t' << ID1 << '\t'
					<< FD1 << '\t' << WD1 << '\t'
					<< ED1 << '\n';
			}
			CompletedMissions.peek(M);
		} while (M != M1);
	}
	outputFile << "Missions: " << Mcount << "\t[P: " << PMcount << ", E: " << Mcount - PMcount << "]\n";
	int PRcount = PRoverList.getCount(), ERcount = ERoverList.getCount();
	outputFile << "Rovers: " << PRcount + ERcount << "\t[P: " << PRcount << ", E: " << ERcount << "]\n";
	outputFile << "Avg Wait = " << (double)TotalWD / ((Mcount > 0) ? Mcount : 1) << ",\tAvg Exec = " << (double)TotalED / ((Mcount > 0) ? Mcount : 1) << '\n';
	outputFile.close();
}

MarsStation::MarsStation()
{
	CurrentDay = 1;
	inputFromFile();
}
void MarsStation::Sim()
{
	int Mode = UI::ModeSelection();
	Interface(Mode);
}

void MarsStation::MExecute()
{
	Event* E;
	while (EventList.peek(E) && CurrentDay == E->getday())
	{
		EventList.dequeue(E);
		E->Execute();
		Mission* M = E->getMission();
		if (M->gettype() == emergency)
			EMissionList.enqueue(M, M->getPkey());
		else
			PMissionList.enqueue(M);
		delete E;
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
			M->Assign(R, CurrentDay);
			InExMissions.enqueue(M, -M->getcmpday());
		}
		else if (!PRoverList.isEmpty())
		{
			PRoverList.dequeue(R);
			EMissionList.dequeue(M);
			M->Assign(R, CurrentDay);
			InExMissions.enqueue(M, -M->getcmpday());
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
		}
		else
		{
			break;
		}
	}
}
void MarsStation::Interface(int mod)
{
	if (mod == 3) //Silent Mode
	{
		UI::silentend();
	}
	while (!EventList.isEmpty() || !EMissionList.isEmpty() || !PMissionList.isEmpty() || !InExMissions.isEmpty() || !Checkup.isEmpty())
	{
		MExecute();
		Assign();
		Finish();
		if (mod != 3)
		{
			Prints();
		}
		Endday();
		if (mod == 1) //Interactive Mode
			UI::intend();
		else if (mod == 2) //Step-by-Step Mode
			UI::stepend();
	}
	outputToFile();
	UI::endOfSim();
}
void MarsStation::Prints()
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
	UI::PrintDef(templist1, s);
	//-------------------------Waiting----------------------------
	s = "In-Execution Missions/Rovers: ";
	UI::PrintInex(InExMissions, s);
	//-------------------------Execution----------------------------
	s = "Available Rovers: ";
	LinkedQueue<Rover*>templist3(ERoverList);
	LinkedQueue<Rover*>templist4(PRoverList);
	while (templist4.dequeue(R)) { templist3.enqueue(R); }
	UI::PrintDef(templist3, s);
	//------------------------AvailableRovers------------------------
	s = "In-Checkup Rovers: ";
	LinkedQueue<Rover*> temp(Checkup);
	UI::PrintDef(temp, s);
	//------------------------CheckupRovers--------------------------
	s = "Completed Missions: ";
	UI::PrintDef(CompletedMissions, s);
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
			Checkup.enqueue(R, -R->getCheckupEndDate());
		}
		else
		{
			if (R->gettype() == emergency)
				ERoverList.enqueue(R);
			else
			{
				PRoverList.enqueue(R);
			}
		}
	}
	while (Checkup.peek(R) && R->getCheckupEndDate() == CurrentDay)
	{
		if (R->gettype() == emergency)
		{
			Checkup.dequeue(R);
			ERoverList.enqueue(R);
		}
		else
		{
			Checkup.dequeue(R);
			PRoverList.enqueue(R);
		}
	}
	Assign();
}
void MarsStation::Endday()
{
	++CurrentDay;
}

MarsStation::~MarsStation()
{
	Rover* R;
	while (PRoverList.dequeue(R) || ERoverList.dequeue(R))
		delete R;
	Mission* M;
	while (CompletedMissions.dequeue(M))
		delete M;
}
