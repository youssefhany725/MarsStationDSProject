#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include "linkedqueue.h"
#include "priorityqueue.h"
#include "Mission.h"
#include "Rover.h"
#include "MarsStation.h"
using namespace std;
//class MarsStation;

class UI
{
private:
	static ifstream ReadActionParameters();
public:
	static void input(MarsStation* ms);
	static void output();
	static void PrintInex(priorityqueue<Mission*>,string = "");
	static int ModeSelection();
	static void intend();
	template<typename T>
	static void PrintDef(LinkedQueue<T>, string = "");
	static void PrintDefR(LinkedQueue<Rover*>, string = "");
	static void PrintDefM(LinkedQueue<Mission*>, string = "");
};
ifstream UI::ReadActionParameters()
{
	ifstream inputFile;
	bool firstInput = true;
	do {
		if (!firstInput) {
			cout << "File not found, please try again\n";
		}
		cout << "Enter the name of file you want to load from: ";
		string fileName;
		getline(cin, fileName, '\n');
		if (fileName.empty()) break;
		fileName += ".txt";
		inputFile.open(fileName);
		firstInput = false;
	} while (!inputFile.is_open());
	return inputFile;
}
void UI::input(MarsStation* ms)
{
	ifstream inputFile = ReadActionParameters();
	int x, P, E, SP, SE, N, CP, CE, Ev, ED, ID, TLOC, MDUR, SIG;
	char c, TYP;
	inputFile >> x;
	inputFile >> P;
	for (int i = 0; i < P; i++) ms->AddRover(polarrover, i);
	inputFile >> E;
	for (int i = 0; i < E; i++) ms->AddRover(emergencyrover, i + P);
	inputFile >> x;
	inputFile >> SP;
	ms->setPolar_speed(SP);
	inputFile >> SE;
	ms->setEmergency_speed(SE);
	inputFile >> N;
	ms->setMissionsToCheckup(N);
	inputFile >> x;
	inputFile >> CP;
	ms->setPolar_checkupDuration(CP);
	inputFile >> CE;
	ms->setEmergency_checkupDuration(CE);
	inputFile >> x;
	inputFile >> Ev;
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
			ms->AddEvent((TYP == 'E') ? emergency : polar, ED, ID, TLOC, MDUR, SIG);
		}
		inputFile.ignore(128, '\n');
	}
}
int UI::ModeSelection()
{
	cout << "Mode Selection:\n1)Interactive\n2)Step-by-Step\n3)Silent\n";
	int slct;
	cin >> slct;
	cout << endl;
	return slct;
}
void UI::intend()
{
	string c;
	getline(cin,c);
	//cin.ignore(128,'\n');
	cout << endl;
}
void UI::PrintDefR(LinkedQueue<Rover*> list, string txt)
{
	Rover* R;
	string comma = "";
	LinkedQueue<Rover*> temp;
	cout << list.getCount() << " ";
	cout << txt;
	cout << '[';
	while (list.dequeue(R))
	{
		if (R->gettype() == emergency)
		{
			cout << comma;
			cout << R->getid();
			comma = ",";
		}
		else
		{
			temp.enqueue(R);
		}
	}
	cout << ']' << " ";
	cout << '(';
	while (temp.dequeue(R))
	{
		cout << R->getid();
		if (!temp.isEmpty())
		{
			cout << ",";
		}
	}
	cout << ')' << "\n-------------------------------\n";
}
void UI::PrintInex(priorityqueue<Mission*> list, string txt)
{
	Mission* M;
	string comma = "";
	LinkedQueue<Mission*> temp;
	cout << list.getCount() << " ";
	cout << txt;
	cout << '[';
	while (list.dequeue(M))
	{
		if (M->gettype() == emergency)
		{
			cout << comma;
			cout << M->getid() << "/" << M->getRover()->getid();
			comma = ",";
		}
		else
		{
			temp.enqueue(M);
		}
	}
	cout << ']' << " ";
	cout << '(';
	while (temp.dequeue(M))
	{
		cout << M->getid() << "/" << M->getRover()->getid();
		if (!temp.isEmpty())
		{
			cout << ",";
		}
	}
	cout << ')' << "\n-------------------------------\n";
}
template<typename T>
void UI::PrintDef(LinkedQueue<T> list, string txt)
{
	T R;
	string comma = "";
	LinkedQueue<T> temp;
	cout << list.getCount() << " ";
	cout << txt;
	cout << '[';
	while (list.dequeue(R))
	{
		if (R->gettype() == 1)
		{
			cout << comma;
			cout << R->getid();
			comma = ",";
		}
		else
		{
			temp.enqueue(R);
		}
	}
	cout << ']' << " ";
	cout << '(';
	while (temp.dequeue(R))
	{
		cout << R->getid();
		if (!temp.isEmpty())
		{
			cout << ",";
		}
	}
	cout << ')' << "\n-------------------------------\n";
}
void UI::PrintDefM(LinkedQueue<Mission*> list, string txt)
{
	Mission* M;
	string comma = "";
	LinkedQueue<Mission*> temp;
	cout << list.getCount() << " ";
	cout << txt;
	cout << '[';
	while (list.dequeue(M))
	{
		if (M->gettype() == 1)
		{
			cout << comma;
			cout << M->getid();
			comma = ",";
		}
		else
		{
			temp.enqueue(M);
		}
	}
	cout << ']' << " ";
	cout << '(';
	while (temp.dequeue(M))
	{
		cout << M->getid();
		if (!temp.isEmpty())
		{
			cout << ",";
		}
	}
	cout << ')' << "\n-------------------------------\n";
}
void UI::output()
{

}

