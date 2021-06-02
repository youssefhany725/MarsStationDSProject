#pragma once
#include"Defs.h"
#include "Rover.h"
class Mission
{
private:
	missiontype TYP;
	Rover* Rassigned;
	int CD;
	int ID;
	int TLOC;
	int MDUR;
	int SIG;
	int ED;
public:
	Mission(missiontype a = polar, int ed=0, int id = 0, int tloc = 0, int mdur = 0, int sig = 0);
	missiontype gettype();
	void Assign(Rover* R,int);
	int getcmpday();
	int getPkey();
	Rover* getRover();
	int getid();
	int getMDUR();
};
