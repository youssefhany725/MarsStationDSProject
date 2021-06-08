#pragma once
#include"Defs.h"

class Rover
{
	static int missionsToCheckup, polar_checkupDuration, emergency_checkupDuration, polar_speed, emergency_speed;
	int ID, checkupEndDate;
	int speed;
	type roverType;
	int time;
	int maintenance;
public:
	Rover(type rt, int id);

	static void setMissionsToCheckup(int n);
	static int getMissionsToCheckup();
	static void setPolar_checkupDuration(int n);
	static int getPolar_checkupDuration();
	static void setEmergency_checkupDuration(int n);
	static int getEmergency_checkupDuration();
	void setspeed(int n);
	int getspeed();
	static void setEmergency_speed(int n);
	static int getEmergency_speed();
	static void setPolar_speed(int n);
	static int getPolar_speed();
	int getid();
	void setid(int x);
	void setrovertype(type rt);
	type gettype();
	int getcheckupdays();
	int getCheckupEndDate();
	void setCheckupEndDate(int n);
	void setcheckuptime();
	bool getcheckuptime();
	void setmaintance(int);
	bool getmaintaince();
};