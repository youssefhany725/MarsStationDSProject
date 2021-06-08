#include "..\hFiles\Rover.h"
Rover::Rover(type rt, int id) {
	roverType = rt;
	ID = id;
	checkupEndDate = -1;
	speed = 0;
	time = 0;
	maintenance = 0;
}

int Rover::missionsToCheckup = 0, Rover::polar_checkupDuration = 0,
Rover::emergency_checkupDuration = 0, Rover::polar_speed = 0, Rover::emergency_speed = 0;
void Rover::setMissionsToCheckup(int n) {
	missionsToCheckup = n;
}

int Rover::getMissionsToCheckup() {
	return missionsToCheckup;
}

void Rover::setPolar_checkupDuration(int n) {
	polar_checkupDuration = n;
}

int Rover::getPolar_checkupDuration() {
	return polar_checkupDuration;
}

void Rover::setEmergency_checkupDuration(int n) {
	emergency_checkupDuration = n;
}

int Rover::getEmergency_checkupDuration() {
	return emergency_checkupDuration;
}

void Rover::setspeed(int n) {
	speed = n;
}

int Rover::getspeed() {
	return speed;
}

void Rover::setEmergency_speed(int n) {
	emergency_speed = n;
}

int Rover::getEmergency_speed() {
	return emergency_speed;
}
void Rover::setPolar_speed(int n) {
	polar_speed = n;
}

int Rover::getPolar_speed() {
	return polar_speed;
}
int Rover::getid() {
	return ID;
}

void Rover::setid(int x) {
	ID = x;
}

void Rover::setrovertype(type rt) {
	roverType = rt;
}

type Rover::gettype() {
	return roverType;
}

int Rover::getcheckupdays() {
	if (roverType == polar) return polar_checkupDuration;
	else return emergency_checkupDuration;
}

int Rover::getCheckupEndDate() {
	return checkupEndDate;
}

void Rover::setCheckupEndDate(int n) {
	checkupEndDate = n;

}
void Rover::setcheckuptime()
{
	time++;
}
bool Rover::getcheckuptime()
{
	if (time == 0)
	{
		return false;
	}
	return (time % getMissionsToCheckup() == 0);
}
void Rover::setmaintance(int n)
{
	if (n < 0)
	{
		maintenance = 0;
		return;
	}
	maintenance++;
}
bool Rover::getmaintaince()
{
	if (maintenance <= 0)
	{
		return false;
	}
	else
	{
		return (maintenance >= 5);
	}
}