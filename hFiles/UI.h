#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "linkedqueue.h"
#include "priorityqueue.h"
#include "Mission.h"
#include "Rover.h"
using namespace std;
class MarsStation;

class UI
{
private:
	ifstream ReadActionParameters();
public:
	void input(MarsStation* ms);
	void output();
	void PrintInex(LinkedQueue<Mission*>,string = "");
	void PrintDefM(LinkedQueue<Mission*>, string = "");
	void PrintDefR(LinkedQueue<Rover*>, string = "");
};

