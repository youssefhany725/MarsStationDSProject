#pragma once
#include"Defs.h"
#include "Rover.h"
class Mission
{
private:
	type TYP;
	Rover* Rassigned;
	int CD;
	int ID;
	int TLOC;
	int MDUR;
	int SIG;
	int FD;
	int WD;
public:
	Mission(type typ = polar, int fd = 0, int id = 0, int tloc = 0, int mdur = 0, int sig = 0);
	type gettype();
	void Assign(Rover* R, int);
	int getcmpday();
	int getWD();
	int getFD();
	int getPkey();
	Rover* getRover();
	int getid();
	int getMDUR();
};