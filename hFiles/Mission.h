#pragma once
#include"Defs.h"
#include"Rover.h"
class Mission
{
private:
	missiontype TYP;
	Rover * Rassigned;
	int CD;
	int ID;
	int TLOC;
	int MDUR;
	int SIG;
	int ED;
	int WD;
public:
	Mission(missiontype a = polar, int ed=0, int c = 0, int d = 0, int e = 0, int f = 0,int w =0);
	int gettype();
	void Assign(Rover* R,int);
	int getcmpday();
	int getPkey();
	int getMDUR();
	void setwatingday(int);
	int getwaitingday();
	void getRover(Rover*&);

};
