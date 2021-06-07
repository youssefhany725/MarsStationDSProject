#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include "linkedqueue.h"
#include "priorityqueue.h"
#include "Mission.h"
#include "Rover.h"
#include "MarsStation.h"
using namespace std;

class UI
{
private:

public:
	static void InputActionParameters(ifstream& inputFile);
	static void OutputActionParameters(ofstream& outputFile);
	static void endOfSim();
	static void PrintInex(priorityqueue<Mission*>, string = "");
	static int ModeSelection();
	static void intend();
	static void stepend();
	static void silentend();
	template<typename T>
	static void PrintDef(LinkedQueue<T>, string = "");
};
void UI::InputActionParameters(ifstream& inputFile)
{
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
}
void UI::OutputActionParameters(ofstream& outputFile)
{
	string fileName;
	cout << "Enter the name you want for your save file: ";
	getline(cin, fileName, '\n');
	if (fileName.empty()) fileName = "save";
	fileName += ".txt";
	outputFile.open(fileName);
}
void UI::endOfSim() {
	cout << "Simulation ends, Output File was created\n";
}
int UI::ModeSelection()
{
	cout << "Mode Selection:\n1)Interactive\n2)Step-by-Step\n3)Silent\n";
	int slct = 0;
	while (slct < 1 || slct>3)
		cin >> slct;
	cin.ignore(128, '\n');
	return slct;
}
void UI::intend()
{
	cin.ignore(128, '\n');
	cout << endl;
}
void UI::stepend()
{
	Sleep(1000);
}
void UI::silentend()
{
	cout << "Silent Mode" << endl << "Simulation Starts..." << endl;
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